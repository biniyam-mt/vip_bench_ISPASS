// C Program for Floyd Warshall Algorithm
#include <stdio.h>
#include <stdint.h>
#include <limits.h>

#include "../config.h"
#include "../common/utils.h"
 
// Number of vertices in the graph
const int V = 100;
 
/* Define Infinite as a large enough value. This value will be used
  for vertices not connected to each other */
#define INF 99999
#define N 99999

// A function to print the solution matrix
void printSolution(VIP_ENCINT dist[][V]);
 
// distance array
VIP_ENCINT dist[V][V];

// Solves the all-pairs shortest path problem using Floyd Warshall algorithm
void
floydWarshall (VIP_ENCINT graph[][V])
{
  /* dist[][] will be the output matrix that will finally have the shortest 
    distances between every pair of vertices */
  int i, j, k;
 
  /* Initialize the solution matrix same as input graph matrix. Or 
     we can say the initial values of shortest distances are based
     on shortest paths considering no intermediate vertex. */
  for (i = 0; i < V; i++)
    for (j = 0; j < V; j++)
      dist[i][j] = graph[i][j];
 
  /* Add all vertices one by one to the set of intermediate vertices.
    ---> Before start of a iteration, we have shortest distances between all
    pairs of vertices such that the shortest distances consider only the
    vertices in set {0, 1, 2, .. k-1} as intermediate vertices.
    ----> After the end of a iteration, vertex no. k is added to the set of
    intermediate vertices and the set becomes {0, 1, 2, .. k} */
  for (k = 0; k < V; k++)
  {
    // Pick all vertices as source one by one
    for (i = 0; i < V; i++)
    {
      // Pick all vertices as destination for the
      // above picked source
      for (j = 0; j < V; j++)
      {
        // If vertex k is on the shortest path from
        // i to j, then update the value of dist[i][j]
        if (dist[i][k] + dist[k][j] < dist[i][j])
          dist[i][j] = dist[i][k] + dist[k][j];
      }
    }
  }
}
 
/* A utility function to print solution */
void
printSolution(VIP_ENCINT dist[][V])
{
    printf ("Following matrix shows the shortest distances"
            " between every pair of vertices \n");
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (VIP_DEC(dist[i][j]) == INF)
                printf("%7s", "INF");
            else
                printf ("%7d", VIP_DEC(dist[i][j]));
        }
        printf("\n");
    }
}
 


//Used to initialize the graph
void
initializeData(VIP_ENCINT graph[V][V])
{
	mysrand(10);
	for (int i=0; i < V; i++)
  {
		for (int j=0;j<V;j++)
    {
      if (i==j)
				graph[i][j] = 0; //Connection to same node is 0
			else
      {
				if (myrand() % 4 == 0)
					graph[i][j] = 1 + (myrand() % 20); //With some probability, connect with weight 0-20	
				else
					graph[i][j] = N;			
			}
		}
	}
}

// driver program to test above function
int
main(void)
{
  // Let us create a weighted graph randomly

	VIP_ENCINT graph[V][V];
  initializeData(graph);	
  printSolution(graph);

  {
    Stopwatch s("VIP_Bench Runtime");

    // Print the solution
    floydWarshall(graph);
  }
 
  // Print the shortest distance matrix
  printSolution(dist);
  return 0;
}

