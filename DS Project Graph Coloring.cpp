#include<stdio.h>
#include<bits/stdc++.h>
#include<iostream>
#include<graphics.h>
#include<vector>
#include<conio.h>
using namespace std;
// Number of vertices in the graph
#define V 4
int colors_int[4]={4,3,2,14};

void create_graph(int color[])
{

    setfillstyle(SOLID_FILL,BLUE);
    floodfill(1,1,BLUE);


    setcolor(BROWN);
    circle(200,100,45);
    setfillstyle(SOLID_FILL,colors_int[color[0]]);
    floodfill(200,100,BROWN);

    setcolor(BROWN);
    circle(400,100,45);
    setfillstyle(SOLID_FILL,colors_int[color[1]]);
    floodfill(400,100,BROWN);

    setcolor(BROWN);
    circle(200,300,45);
    setfillstyle(SOLID_FILL,colors_int[color[3]]);
    floodfill(200,300,BROWN);

    setcolor(BROWN);
    circle(400,300,45);
    setfillstyle(SOLID_FILL,colors_int[color[2]]);
    floodfill(400,300,BROWN);

    setcolor(BLACK);
    line(200+45,100,400-45,100);
    line(400,100+45,400,300-45);
    line(400-45,300,200+45,300);
    line(200,300-45,200,100+45);
    line(400-45+9.3,100+45-9.3,200+45-9.3,300-45+9.3);

    delay(2000);


}

void printSolution(int color[]);

/* A utility function to check if the current color assignment
is safe for vertex v */
bool isSafe (int v, int graph[V][V], int color[], int c)
{
	for (int i = 0; i < V; i++)
		if (graph[v][i] && c == color[i])
			return false;
	return true;
}

/* A recursive utility function to solve m coloring problem */
bool graphColoringUtil(int graph[V][V], int m, int color[], int v)
{
	/* base case: If all vertices are assigned a color then
	return true */
	if (v == V)
		return true;

	/* Consider this vertex v and try different colors */
	for (int c = 1; c <= m; c++)
	{
		/* Check if assignment of color c to v is fine*/
		if (isSafe(v, graph, color, c))
		{
		    create_graph(color);
		color[v] = c;
		create_graph(color);

		/* recur to assign colors to rest of the vertices */
		if (graphColoringUtil (graph, m, color, v+1) == true)
			return true;

			/* If assigning color c doesn't lead to a solution
			then remove it */
		color[v] = 0;
		create_graph(color);
		}
	}

	/* If no color can be assigned to this vertex then return false */
	return false;
}

/* This function solves the m Coloring problem using Backtracking.
It mainly uses graphColoringUtil() to solve the problem. It returns
false if the m colors cannot be assigned, otherwise return true and
prints assignments of colors to all vertices. Please note that there
may be more than one solutions, this function prints one of the
feasible solutions.*/
bool graphColoring(int graph[V][V], int m)
{
	// Initialize all color values as 0. This initialization is needed
	// correct functioning of isSafe()
	int *color = new int[V];
	for (int i = 0; i < V; i++)
	color[i] = 0;

	// Call graphColoringUtil() for vertex 0
	if (graphColoringUtil(graph, m, color, 0) == false)
	{
	printf("Solution does not exist");
	return false;
	}

	// Print the solution
	printSolution(color);
	return true;
}

/* A utility function to print solution */
void printSolution(int color[])
{
	printf("Solution Exists:"
			" Following are the assigned colors \n");
	for (int i = 0; i < V; i++)
	printf(" %d ", color[i]);
	printf("\n");
}

// driver program to test above function
int main()
{
    int gdriver=DETECT,gmode;
	initgraph(&gdriver,&gmode,"");
	/* Create following graph and test whether it is 3 colorable
	(3)---(2)
	| / |
	| / |
	| / |
	(0)---(1)
	*/
	int graph[V][V]={
	    {0,1,0,1},
	{
	    1,0,1,1
	},
	{
	    0,1,0,1
	},
	{
	    1,1,1,0
	}
	};

	int m = 3; // Number of colors
	graphColoring (graph, m);
   // create_graph();
	getch();
	closegraph();

	return 0;
}

