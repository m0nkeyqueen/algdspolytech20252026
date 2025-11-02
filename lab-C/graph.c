#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

#define MAX_LINE_LENGTH 300

Queue *create_queue(unsigned capacity)
{
    if (capacity == 0)
    {
        return NULL;
    }
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    if (queue == NULL)
        return NULL;
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int *)malloc(queue->capacity * sizeof(int));
    if (queue->array == NULL)
    {
        free(queue);
        return NULL;
    }
    return queue;
}

void enqueue(Queue *queue, int item)
{
    if (queue == NULL || queue->size == queue->capacity)
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size++;
}

int dequeue(Queue *queue)
{
    if (queue == NULL || queue->size == 0)
        return -1;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return item;
}

void free_queue(Queue *queue)
{
    if (queue == NULL)
        return;
    free(queue->array);
    free(queue);
}

AdjListNode *new_adjlist_node(int dest)
{
    AdjListNode *new_node = (AdjListNode *)malloc(sizeof(AdjListNode));
    if (new_node == NULL)
        return NULL;
    new_node->dest = dest;
    new_node->next = NULL;
    return new_node;
}

Graph *create_graph(int V)
{
    if (V <= 0)
    {
        return NULL;
    }
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    if (graph == NULL)
        return NULL;
    graph->V = V;
    graph->array = (AdjList *)malloc(V * sizeof(AdjList));
    if (graph->array == NULL)
    {
        free(graph);
        return NULL;
    }
    for (int i = 0; i < V; i++)
        graph->array[i].head = NULL;
    return graph;
}

void add_edge(Graph *graph, int src, int dest)
{
    if (graph == NULL)
        return;

    AdjListNode *new_node = new_adjlist_node(dest);
    if (new_node == NULL)
        return;
    new_node->next = graph->array[src].head;
    graph->array[src].head = new_node;

    new_node = new_adjlist_node(src);
    if (new_node == NULL)
        return;
    new_node->next = graph->array[dest].head;
    graph->array[dest].head = new_node;
}

void free_graph(Graph *graph)
{
    if (graph == NULL)
        return;
    for (int v = 0; v < graph->V; v++)
    {
        AdjListNode *temp = graph->array[v].head;
        while (temp)
        {
            AdjListNode *to_delete = temp;
            temp = temp->next;
            free(to_delete);
        }
    }
    free(graph->array);
    free(graph);
}

PathResult *bfs_shortest_path(Graph *graph, int start, int end)
{
    PathResult *result = (PathResult *)malloc(sizeof(PathResult));
    if (result == NULL)
        return NULL;

    result->path = NULL;
    result->length = 0;
    result->found = 0;

    if (graph == NULL)
        return result;
    if (start < 0 || start >= graph->V || end < 0 || end >= graph->V)
        return result;
    if (start == end)
    {
        result->path = (int *)malloc(sizeof(int));
        if (result->path != NULL)
        {
            result->path[0] = start;
            result->length = 1;
            result->found = 1;
        }
        return result;
    }

    int V = graph->V;
    int *visited = (int *)calloc(V, sizeof(int));
    if (visited == NULL)
        return result;

    int *parent = (int *)malloc(V * sizeof(int));
    if (parent == NULL)
    {
        free(visited);
        return result;
    }

    for (int i = 0; i < V; i++)
    {
        parent[i] = -1;
    }

    Queue *queue = create_queue(V);
    if (queue == NULL)
    {
        free(visited);
        free(parent);
        return result;
    }

    visited[start] = 1;
    enqueue(queue, start);
    int found = 0;

    while (queue->size != 0)
    {
        int current = dequeue(queue);
        AdjListNode *temp = graph->array[current].head;
        while (temp != NULL)
        {
            int neighbor = temp->dest;
            if (!visited[neighbor])
            {
                visited[neighbor] = 1;
                parent[neighbor] = current;
                enqueue(queue, neighbor);
                if (neighbor == end)
                {
                    found = 1;
                    break;
                }
            }
            temp = temp->next;
        }
        if (found)
            break;
    }

    if (found)
    {
        int path_length = 0;
        int current = end;
        while (current != -1)
        {
            path_length++;
            current = parent[current];
        }

        result->path = (int *)malloc(path_length * sizeof(int));
        if (result->path != NULL)
        {
            int idx = 0;
            current = end;
            while (current != -1)
            {
                result->path[idx++] = current;
                current = parent[current];
            }
            for (int i = 0; i < path_length / 2; i++)
            {
                int temp_val = result->path[i];
                result->path[i] = result->path[path_length - 1 - i];
                result->path[path_length - 1 - i] = temp_val;
            }
            result->length = path_length;
            result->found = 1;
        }
    }

    free(visited);
    free(parent);
    free_queue(queue);
    return result;
}

void free_path_result(PathResult *result)
{
    if (result == NULL)
        return;
    free(result->path);
    free(result);
}

Graph *read_graph_from_file(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file %s!\n", filename);
        return NULL;
    }
    int max_vertex = -1;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file))
    {
        if (strlen(line) > 1)
        {
            int src;
            sscanf(line, "%d:", &src);
            if (src > max_vertex)
                max_vertex = src;
            char *token = strtok(line, " :");
            while (token != NULL)
            {
                int dest;
                if (sscanf(token, "%d", &dest) == 1)
                {
                    if (dest > max_vertex)
                        max_vertex = dest;
                }
                token = strtok(NULL, " ");
            }
        }
    }
    rewind(file);
    Graph *graph = create_graph(max_vertex + 1);
    while (fgets(line, sizeof(line), file))
    {
        if (strlen(line) > 1)
        {
            int src;
            char *ptr = line;
            sscanf(ptr, "%d:", &src);
            while (*ptr && *ptr != ':')
                ptr++;
            if (*ptr == ':')
                ptr++;
            char *token = strtok(ptr, " \n");
            while (token != NULL)
            {
                int dest = atoi(token);
                add_edge(graph, src, dest);
                token = strtok(NULL, " \n");
            }
        }
    }
    fclose(file);
    return graph;
}
