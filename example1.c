#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} NODE;

typedef struct Graph {
    int vertices;
    int* visited;
    struct Node** adjacency_list;
} GRAPH;

typedef struct Stack {
    int top;
    int capacity;
    int* array;
} STACK;

NODE* create_node(int value) {
    NODE* new_node = malloc(sizeof(NODE));
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

void add_edge(GRAPH* graph, int source, int destination) {
    NODE* new_node = create_node(destination);
    new_node->next = graph->adjacency_list[source];
    graph->adjacency_list[source] = new_node;
    new_node = create_node(source);
    new_node->next = graph->adjacency_list[destination];
    graph->adjacency_list[destination] = new_node;
}

GRAPH* create_graph(int vertices) {
    int i;
    GRAPH* graph = malloc(sizeof(GRAPH));
    graph->vertices = vertices;
    graph->adjacency_list = malloc(sizeof(NODE*) * vertices);
    graph->visited = malloc(sizeof(int) * vertices);

    for (i = 0; i < vertices; i++) {
        graph->adjacency_list[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

STACK* create_stack(int capacity) {
    STACK* stack = malloc(sizeof(STACK));
    stack->array = malloc(capacity * sizeof(int));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

void push(STACK* stack, int item) {
    stack->top++;
    stack->array[stack->top] = item;
}

int pop(STACK* stack) {
    int item = stack->array[stack->top];
    stack->top--;
    return item;
}

void depth_first_search(GRAPH* graph, STACK* stack, int vertex) {
    NODE* adjacency_list = graph->adjacency_list[vertex];
    NODE* temp = adjacency_list;
    graph->visited[vertex] = 1;
    printf("%d ", vertex);
    push(stack, vertex);
    while (temp != NULL) {
        int connected_vertex = temp->data;
        if (graph->visited[connected_vertex] == 0)
            depth_first_search(graph, stack, connected_vertex);
        temp = temp->next;
    }
}

void insert_edges(GRAPH* graph, int edge_count, int vertex_count) {
    int source, destination, i;
    printf("Introdu %d muchii (de la 1 la %d)\n", edge_count, vertex_count);
    for (i = 0; i < edge_count; i++) {
        scanf("%d %d", &source, &destination);
        add_edge(graph, source, destination);
    }
}

void reset_visited(GRAPH* graph, int vertex_count) {
    for (int i = 0; i < vertex_count; i++) {
        graph->visited[i] = 0;
    }
}

void check_direct_path(GRAPH* graph, int start, int end, STACK* stack) {
    depth_first_search(graph, stack, start);
    if (graph->visited[end] == 1) {
        printf("\nDrumuri directe intre %d si %d\n", start, end);
    } else {
        printf("\nN-avem drumuri directe intre %d si %d\n", start, end);
    }
}

int main() {
    int vertex_count;
    int edge_count;
    printf("Cate noduri? ");
    scanf("%d", &vertex_count);
    printf("Cate muchii?");
    scanf("%d", &edge_count);
    GRAPH* graph = create_graph(vertex_count);
    STACK* stack = create_stack(2 * vertex_count);
    insert_edges(graph, edge_count, vertex_count);
    int start_vertex, end_vertex;
    printf("Nodul de start si sfarsit pentru verificare daca exista drum direct: ");
    scanf("%d %d", &start_vertex, &end_vertex);
    check_direct_path(graph, start_vertex, end_vertex, stack);
    return 0;
}
