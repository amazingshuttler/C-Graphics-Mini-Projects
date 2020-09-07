#include<iostream>
#include<graphics.h>
#include<cmath>
#include<cstring>

#define radius 15
using namespace std;

char red_score=48;
char blue_score=48;

class Ball
{
    public:
    int prev_x=0;int prev_y=0;
    int curr_x;int curr_y;
    int next_x=0;int next_y=0;
}ball[2];

void make_point()
{
    red_score++;
    return;
}

void make_arc()
{
    setcolor(BROWN);
    setfillstyle(SOLID_FILL,BLACK);
    arc(30,30,-90,0,40);             floodfill(32,32,BROWN);
    arc(600,30,180,270,40);          floodfill(600-2,32,BROWN);
    arc(600,450,90,180,40);          floodfill(600-2,450-2,BROWN);
    arc(30,450,0,90,40);             floodfill(32,450-2,BROWN);
    arc((30+600)/2,(30),-180,0,35);  floodfill((30+600)/2,32,BROWN);
    arc((30+600)/2,450,0,180,35);    floodfill((30+600)/2,450-2,BROWN);
}

void make_table(void)
{
    setcolor(BROWN);
    rectangle(30,30,600,450);

    make_arc();
    setfillstyle(SOLID_FILL,GREEN);
    floodfill(32,72,BROWN);

    setfillstyle(SOLID_FILL,BLUE);
    floodfill(1,1,BROWN);

    outtextxy(1,1,"SCORE");
    outtextxy(50,1,&red_score);

    outtextxy(300,1,"BLUE-SCORE");
    outtextxy(350,1,&blue_score);
}

void draw_red_ball(int x,int y)
{
        setcolor(RED);
        circle(x,y,radius);
        setfillstyle(SOLID_FILL,RED);
        floodfill(x,y,RED);
}

void draw_blue_ball(int x,int y)
{
        setcolor(BLUE);
        circle(x,y,radius);
        setfillstyle(SOLID_FILL,BLUE);
        floodfill(x,y,BLUE);
}

bool check_pot(int i,int j)
{
    if(abs(600-i)<30 && abs(30-j)<30) {make_point();return true;}
    if(abs(30-i)<30 && abs(30-j)<30) {make_point();return true;}
    if(abs(600-i)<30 && abs(450-j)<30) {make_point();return true;}
    if(abs(30-i)<30 && abs(450-j)<30) {make_point();return true;}
    if(abs(315-i)<30 && abs(30-j)<30) {make_point();return true;}
    if(abs(315-i)<30 && abs(450-j)<30) {make_point();return true;}
    return false;
}

bool check_collision(int i,int j,int l,int m)
{
    if(pow(i-l,2)+pow(j-m,2)<=900) return true;
    return false;
}

int main()
{


    int gd= DETECT;
    int gm;
    initgraph(&gd,&gm,"");

    while(1)
{
    POINT p,q;
    int power=100;
    float x1=1,x2=1,x3=1,x4=1;
    int x1_sign=1,x2_sign=1,x3_sign=1,x4_sign=1;
    bool red_ball_fall=false,blue_ball_fall=false,col_active=true;

    float c=0.1;
    float a=c,b=c,e=c,f=c;
    float k;
    int extra=1;
    for(float i=0,j=0,l=0,m=0,k=2*power;k!=0;i+=(a*k),j+=(b*k),l+=(e*k),m+=(f*k),k-=01,extra++)
    {
        if(extra%10==0) col_active=true;
        if(red_ball_fall==true && blue_ball_fall==true) break;

        if(red_ball_fall==false)
        {
        ball[0].curr_x=315+i;
        ball[0].curr_y=240+j;
        }
        if(blue_ball_fall==false)
        {
        ball[1].curr_x=450+l;
        ball[1].curr_y=240+m;
        }
        make_table();
        if(ball[0].curr_y + radius>=450 || ball[0].curr_y - radius<=30) b*=-1;
        if(ball[0].curr_x + radius>=600 || ball[0].curr_x - radius<=30) a*=-1;
        if(ball[1].curr_y + radius>=450 || ball[1].curr_y - radius<=30) f*=-1;
        if(ball[1].curr_x + radius>=600 || ball[1].curr_x - radius<=30) e*=-1;

        if(check_pot(ball[0].curr_x,ball[0].curr_y)==false && red_ball_fall==false) {  draw_red_ball(ball[0].curr_x,ball[0].curr_y);  }
        else {red_ball_fall=true;ball[0].curr_x=1000;ball[0].curr_y=1000;}

        if(check_pot(ball[1].curr_x,ball[1].curr_y)==false && blue_ball_fall==false){  draw_blue_ball(ball[1].curr_x,ball[1].curr_y); }
        else {blue_ball_fall=true;ball[1].curr_x=1000;ball[1].curr_y=1000;}

        if(check_collision(ball[0].curr_x,ball[0].curr_y,ball[1].curr_x,ball[1].curr_y)==true && col_active==true)
        {
            // a*=-1;b*=-1;e*=-1;f*=-1;
            int col_x= (ball[0].curr_x + ball[1].curr_x)/2;
            int col_y= (ball[0].curr_y + ball[1].curr_y)/2;
            ball[0].next_x=2*col_x-ball[1].prev_x;
            ball[0].next_y=2*col_y-ball[1].prev_y;
            ball[1].next_x=2*col_x-ball[0].prev_x;
            ball[1].next_y=2*col_y-ball[0].prev_y;

            if(ball[0].prev_x==ball[0].next_x) a*=-1;
            if(ball[0].prev_y==ball[0].next_y) b*=-1;
            if(ball[1].prev_x==ball[1].next_x) e*=-1;
            if(ball[1].prev_y==ball[1].next_y) f*=-1;
            col_active=false;
           // delay(300);
        }


        delay(20);
        if(k==2*power)
        {
            getch();
            GetCursorPos(&p);
            p.x-=3;
            p.y-=26;
            {
                x1=p.x-315;
                x2=p.y-240;
                x1>0?x1_sign=1:x1_sign=-1;
                x2>0?x2_sign=1:x2_sign=-1;
                if(abs(x1)>abs(x2)) {x2/=x1;x1=1;}
                else {x1/=x2;x2=1;}
                if(x1<0) x1*=-1;
                if(x2<0) x2*=-1;
                x1*=x1_sign;
                x2*=x2_sign;
            }
            a*=x1;b*=x2;
        }
        if(k==2*power)
        {
            getch();
            GetCursorPos(&q);
            q.x-=3;
            q.y-=26;
            {
                x3=q.x-450;
                x4=q.y-240;
                x3>0?x3_sign=1:x3_sign=-1;
                x4>0?x4_sign=1:x4_sign=-1;
                if(abs(x3)>abs(x4)) {x4/=x3;x3=1;}
                else {x3/=x4;x4=1;}
                if(x3<0) x3*=-1;
                if(x4<0) x4*=-1;
                x3*=x3_sign;
                x4*=x4_sign;
            }
            e*=x3;f*=x4;
        }
        for(int i=0;i<2;i++) {ball[i].prev_x=ball[i].curr_x;ball[i].prev_y=ball[i].curr_y;}
    }
}

    getch();
    closegraph();
    return 0;
}
