#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main()
{
    const char *filename = "graph.txt";
    Graph *graph = read_graph_from_file(filename);
    if (graph == NULL)
    {
        printf("Failed to create graph from file '%s'.\n", filename);
        return 1;
    }
    printf("Graph successfully loaded from file '%s'\n", filename);
    printf("Graph contains %d vertices (0-%d)\n", graph->V, graph->V - 1);
    int start, end;
    printf("\nEnter starting vertex: ");
    if (scanf("%d", &start) != 1)
    {
        printf("Input error!\n");
        free_graph(graph);
        return 1;
    }
    printf("Enter ending vertex: ");
    if (scanf("%d", &end) != 1)
    {
        printf("Input error!\n");
        free_graph(graph);
        return 1;
    }

    PathResult *result = bfs_shortest_path(graph, start, end);
    if (result != NULL)
    {
        if (!result->found)
        {
            printf("Path between vertices %d and %d does not exist!\n", start, end);
        }
        else
        {
            printf("Shortest path between vertices %d and %d:\n", start, end);
            for (int i = 0; i < result->length; i++)
            {
                printf("%d", result->path[i]);
                if (i < result->length - 1)
                    printf(" -> ");
            }
            printf("\nPath length: %d edges\n", result->length - 1);
        }
        free_path_result(result);
    }

    free_graph(graph);
    return 0;
}
