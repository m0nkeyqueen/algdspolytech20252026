#ifndef GRAPH_H
#define GRAPH_H

#define MAX_LINE_LENGTH 300

typedef struct AdjListNode
{
    int dest;
    struct AdjListNode *next;
} AdjListNode;

typedef struct AdjList
{
    AdjListNode *head;
} AdjList;

typedef struct Graph
{
    int V;
    AdjList *array;
} Graph;

typedef struct Queue
{
    int front, rear, size;
    unsigned capacity;
    int *array;
} Queue;

typedef struct PathResult
{
    int *path;
    int length;
    int found;
} PathResult;

Queue *create_queue(unsigned capacity);
void enqueue(Queue *queue, int item);
int dequeue(Queue *queue);
void free_queue(Queue *queue);
AdjListNode *new_adjlist_node(int dest);
Graph *create_graph(int V);
void add_edge(Graph *graph, int src, int dest);
void free_graph(Graph *graph);
PathResult *bfs_shortest_path(Graph *graph, int start, int end);
void free_path_result(PathResult *result);
Graph *read_graph_from_file(const char *filename);

#endif