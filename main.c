
/*
 * Data Structures Project 3
 * Celil Mete
 * 150116042
 * 27/12/2018
 */


#include <stdio.h>
#include "stdlib.h"
#include "string.h"

struct queue {
    int items[10];
    int front;
    int rear;
};
struct graphNode {
    char *name;
    struct graphNode *next;
};
typedef struct  graphNode graphNode;

struct list {
    graphNode *start;
};
typedef struct list list;

struct graph {
    int V;
    list *nodes;
};
typedef struct graph graph;


graphNode *newGraphNode() ;
void addEdge(graph *graph1, char *srcName, char *destName) ;
graph* newGraph(int V) ;
void printGraph(graph *graph1) ;
void printAdjMatrix(graph *graph1) ;

int calculateDegreeCentrality(graphNode *start) ;

void printDegreeCentrality(graph *graph1) ;

int main() {

    //create the graph and add the edges
    graph *graph1 = newGraph(10);
    addEdge(graph1,"Cem","Ayse");
    addEdge(graph1,"Cem","Ferit");
    addEdge(graph1,"Cem","Dundar");

    addEdge(graph1,"Ayse","Cem");
    addEdge(graph1,"Ayse","Ferit");
    addEdge(graph1,"Ayse","Dundar");
    addEdge(graph1,"Ayse","Belma");

    addEdge(graph1,"Belma","Ayse");
    addEdge(graph1,"Belma","Dundar");
    addEdge(graph1,"Belma","Edip");

    addEdge(graph1,"Edip","Belma");
    addEdge(graph1,"Edip","Dundar");
    addEdge(graph1,"Edip","Gamze");

    addEdge(graph1,"Dundar","Ferit");
    addEdge(graph1,"Dundar","Gamze");
    addEdge(graph1,"Dundar","Cem");
    addEdge(graph1,"Dundar","Belma");
    addEdge(graph1,"Dundar","Ayse");
    addEdge(graph1,"Dundar","Edip");

    addEdge(graph1,"Gamze","Halit");
    addEdge(graph1,"Gamze","Dundar");
    addEdge(graph1,"Gamze","Ferit");
    addEdge(graph1,"Gamze","Edip");


    addEdge(graph1,"Ferit","Ayse");
    addEdge(graph1,"Ferit","Cem");
    addEdge(graph1,"Ferit","Dundar");
    addEdge(graph1,"Ferit","Gamze");
    addEdge(graph1,"Ferit","Halit");

    addEdge(graph1,"Halit","Ferit");
    addEdge(graph1,"Halit","Gamze");
    addEdge(graph1,"Halit","Ilke");

    addEdge(graph1,"Ilke","Halit");
    addEdge(graph1,"Ilke","Jale");

    addEdge(graph1,"Jale","Ilke");

    printf("\t\t\t\t\tADJ MATRIX OF THE GRAPH \n\n");
    printAdjMatrix(graph1);
    printf(" Degree Centrality Of The Nodes \n");
    printDegreeCentrality(graph1);






    return 0;
}

graph* newGraph(int V) {
    graph *newGraph = malloc(sizeof(graph));


    newGraph -> nodes = malloc(V * sizeof(list));
    newGraph -> nodes[0] . start = NULL;
    newGraph->V = V;
    return newGraph;
}

void addEdge(graph *graph1, char *srcName, char *destName) {
    int i=0;
    graphNode *node = NULL;
    while (graph1 ->nodes[i].start !=NULL) {
        if(strcmp(srcName,graph1->nodes[i].start->name) == 0)break;
        i++;
    }
    if(graph1->nodes[i].start == NULL){
        graph1->nodes[i].start = newGraphNode();
        graph1->nodes[i].start->name = srcName;
        graph1->nodes[i].start->next = newGraphNode();
        graph1->nodes[i].start->next->name = destName;
        graph1->nodes[i].start->next->next = NULL;
        graph1->nodes[i+1].start = NULL;
    } else{
        node = graph1->nodes[i].start ;
        while (node ->next) {
            node = node->next;
        }
        node->next = newGraphNode();
        node->next->name =destName;
        node ->next ->next = NULL;
    }
}

graphNode *newGraphNode() {
    graphNode *newNode = malloc(sizeof(graphNode));
    return newNode;
}
//function to print graph as adj list
void printGraph(graph *graph1) {
    int i = 0;
    graphNode *node ;
    while (graph1->nodes[i].start) {
        node = graph1->nodes[i].start;
        char * srName = node->name;
        node = node->next;
        while (node){
            printf("%s -> %s | ",srName,node->name);
            node = node->next;
        }
        printf("\n");
        i++;
    }
}
//function to print the graph as adj matrix
void printAdjMatrix(graph *graph1) {
    char *nameList1[graph1->V];
    char *nameList2[graph1->V];
    for (int i = 0 ; i < graph1->V ; i++) {
        if(graph1->nodes[i].start == NULL){
            nameList1[i] = NULL;
            nameList2[i] = NULL;
            break;
        }
        nameList1[i] = graph1->nodes[i].start->name;
        nameList2[i] = graph1->nodes[i].start->name;
    }
    printf("            ");
    for (int i = 0 ; i < graph1->V ; i++) {
        if(nameList1[i] == NULL)break;
        printf("%-10s",nameList1[i]);
    }
    printf("\n\n\n");
    for (int i = 0 ; i <sizeof(nameList1)/ sizeof(nameList1[0]) ; i++) {
        printf("%-13s",nameList1[i]);

        for (int k = 0 ; k < sizeof(nameList1)/ sizeof(nameList1[0]) ; k++) {
            int value = 0;
            graphNode *node = graph1->nodes[i].start;
            while(node){
                for (int j = 0 ; j < sizeof(nameList1)/ sizeof(nameList1[0]) ; j++) {
                    if(i == k)break;
                    if(strcmp(node->name,nameList1[k]) == 0){
                        value = 1;
                        break;
                    }
                }
                if(value == 1)break;
                if(i == k )break;
                node = node -> next;
            }
            printf("%-10d",value);
        }
        printf("\n\n\n");
    }

}
//function to calculate degree centrality score of a node
int calculateDegreeCentrality(graphNode *start) {
    graphNode *node = start->next;
    int value = 0;
    while(node) {
        value++;
        node = node->next;
    }
    return value;
}

void printDegreeCentrality(graph *graph1) {
    printf("%-10s%-10s%-10s\n","Node","Score","Standardized Score ");
    for(int i = 0; i < graph1->V ; i++) {
        if(graph1->nodes[i].start == NULL)break;
        int score = calculateDegreeCentrality(graph1->nodes[i].start);
        printf("%-10d",i);
        printf("%-10d",score);
        printf("%-10.2f\n",(double)score/(graph1->V-1));
    }
}