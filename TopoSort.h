#include<stdio.h>
#include<stdlib.h>
#define MAX_VERTEX_NUM 100
//
typedef struct ArcNode
{
    int adjvex;
    struct ArcNode *nextarc;
    int weight;
} ArcNode, *NodePointer;

typedef struct VNode
{
    int data; //顶点信息
    ArcNode *firstarc;
} VNode, AdjList[MAX_VERTEX_NUM];

typedef struct
{
    AdjList vertices;
    int vexnum, arcnum;
    int kind;
} ALGraph;

typedef struct
{
    int stack[MAX_VERTEX_NUM + 1];
    int top;
} Sq;

void Creategraph(ALGraph **G);
void InsertVex(ALGraph **G, int vi, int vj, int weight);
void calInDegree(ALGraph G, int indegree[MAX_VERTEX_NUM]);
int TopogicalSort(ALGraph G, int Topo[]);
int Push_Sq(Sq **sq, int n);
int Pop_Sq(Sq **sq);
void Ct_Sq(Sq **sq);
int isEmtpy(Sq sq);