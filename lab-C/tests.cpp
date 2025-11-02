#include <gtest/gtest.h>
#include "graph.h"

Graph *create_simple_graph()
{
    Graph *graph = create_graph(5);
    add_edge(graph, 0, 1);
    add_edge(graph, 0, 2);
    add_edge(graph, 1, 3);
    add_edge(graph, 2, 4);
    return graph;
}

Graph *create_disconnected_graph()
{
    Graph *graph = create_graph(4);
    add_edge(graph, 0, 1);
    add_edge(graph, 2, 3);
    return graph;
}

TEST(GRTest, CreateQueue_ValidCapacity_ReturnsValid_no1)
{
    Queue *queue = create_queue(5);
    ASSERT_NE(queue, nullptr);
    free_queue(queue);
}

TEST(GRTest, CreateQueue_ZeroCapacity_ReturnsNull_no2)
{
    Queue *queue = create_queue(0);
    ASSERT_EQ(queue, nullptr);
}

TEST(GRTest, Enqueue_SingleElement_QueueNotEmpty_no3)
{
    Queue *queue = create_queue(5);
    enqueue(queue, 10);
    free_queue(queue);
}

TEST(GRTest, Dequeue_SingleElement_ReturnsValue_no4)
{
    Queue *queue = create_queue(5);
    enqueue(queue, 10);
    EXPECT_EQ(dequeue(queue), 10);
    free_queue(queue);
}

TEST(GRTest, Dequeue_EmptyQueue_ReturnsError_no5)
{
    Queue *queue = create_queue(5);
    EXPECT_EQ(dequeue(queue), -1);
    free_queue(queue);
}

TEST(GRTest, CreateGraph_ValidVertices_ReturnsValid_no6)
{
    Graph *graph = create_graph(3);
    ASSERT_NE(graph, nullptr);
    EXPECT_EQ(graph->V, 3);
    free_graph(graph);
}

TEST(GRTest, CreateGraph_ZeroVertices_ReturnsNull_no7)
{
    Graph *graph = create_graph(0);
    ASSERT_EQ(graph, nullptr);
}

TEST(GRTest, NewAdjListNode_ValidDest_ReturnsValid_no8)
{
    AdjListNode *node = new_adjlist_node(5);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->dest, 5);
    free(node);
}

TEST(GRTest, AddEdge_ValidVertices_SourceToDest_ReturnsValid_no9)
{
    Graph *graph = create_graph(3);
    add_edge(graph, 0, 1);
    AdjListNode *node = graph->array[0].head;
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->dest, 1);
    free_graph(graph);
}

TEST(GRTest, AddEdge_ValidVertices_DestToSource_ReturnsValid_no10)
{
    Graph *graph = create_graph(3);
    add_edge(graph, 0, 1);
    AdjListNode *node = graph->array[1].head;
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->dest, 0);
    free_graph(graph);
}

TEST(GRTest, BFSShortestPath_SameStartEnd_ReturnsPathLength1_no11)
{
    Graph *graph = create_simple_graph();
    PathResult *result = bfs_shortest_path(graph, 2, 2);
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(result->found);
    free_path_result(result);
    free_graph(graph);
}

TEST(GRTest, BFSShortestPath_DirectConnection_ReturnsFound_no12)
{
    Graph *graph = create_simple_graph();
    PathResult *result = bfs_shortest_path(graph, 0, 1);
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(result->found);
    free_path_result(result);
    free_graph(graph);
}

TEST(GRTest, BFSShortestPath_NoPathExists_ReturnsNotFound_no13)
{
    Graph *graph = create_disconnected_graph();
    PathResult *result = bfs_shortest_path(graph, 0, 3);
    ASSERT_NE(result, nullptr);
    EXPECT_FALSE(result->found);
    free_path_result(result);
    free_graph(graph);
}

TEST(GRTest, BFSShortestPath_InvalidStart_ReturnsNotFound_no14)
{
    Graph *graph = create_simple_graph();
    PathResult *result = bfs_shortest_path(graph, -1, 2);
    ASSERT_NE(result, nullptr);
    EXPECT_FALSE(result->found);
    free_path_result(result);
    free_graph(graph);
}
