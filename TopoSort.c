
#include "TopoSort.h"


#ifdef TEST
int main()
{
    ALGraph *G;
    Creategraph(&G);
    Sq *sq;
    int test;
    Ct_Sq(&sq);
    int Topo[MAX_VERTEX_NUM + 1];
    TopogicalSort(*G,Topo);
    // printf("%d\n", (*G).vexnum);
    // printf("%d\n", (*G).vertices[0].firstarc->nextarc->weight);
    for (int i = 0; i < G->vexnum; i++)
        printf("%4d", Topo[i]);

    return 0;
}
#endif


// main funciton
void TopoSortShow() {
    ALGraph *G;
    Creategraph(&G);
    Sq *sq;
    int test;
    Ct_Sq(&sq);
    int Topo[MAX_VERTEX_NUM + 1];
    TopogicalSort(*G, Topo);
    for (int i = 0; i < G->vexnum; i++)
        printf("%4d", Topo[i]);
}

//create stack
void Ct_Sq(Sq **sq) {
    (*sq) = (Sq *) malloc(sizeof(Sq));
    (*sq)->top = 0;
}

// stack_pop
int Pop_Sq(Sq **sq) {
    if ((*sq)->top == 0) {
        printf("stack is null, don't pop!");
        return -1;
    }
    (*sq)->top -= 1;

    int k = (*sq)->stack[(*sq)->top];
    return k;
}

int Push_Sq(Sq **sq, int n) {
    if ((*sq)->top == MAX_VERTEX_NUM) {
        printf("stack is full, don't push!");
        return 0;
    }
    (*sq)->stack[(*sq)->top] = n;
    (*sq)->top += 1;

    return 1;
}

int isEmtpy(Sq sq) {
    if (sq.top == 0)
        return 1;
    return 0;
}

void Creategraph(ALGraph **G) {
    (*G) = (ALGraph *) malloc(sizeof(ALGraph));
    for (int i = 0; i < MAX_VERTEX_NUM; i++) {
        (*G)->vertices[i].firstarc = NULL;
    }

    int num = 0;
    printf("Please Choose if weight:(1 means have weight)");
    scanf("%d", &((*(*G)).kind));
    printf("Please Enter vexnum (max 100)\n");
    scanf("%d", &((*(*G)).vexnum));
    getchar();
    printf("Please Enter Arc Num\n");
    scanf("%d", &((*(*G)).arcnum));
    printf("Please enter the arc:");

    if ((*(*G)).kind == 1) {
        for (num = 0; num < (*G)->arcnum; num++) {
            int vi, vj, weight;
            scanf("%d%d", &vi, &vj);
            InsertVex(G, vi, vj, 1);
        }
    }
    if ((*(*G)).kind == 0) {
        for (num = 0; num < (*G)->arcnum; num++) {
            int vi, vj, weight;
            scanf("%d%d%d", &vi, &vj, &weight);
            InsertVex(G, vi, vj, weight);
        }
    }
}

void InsertVex(ALGraph **G, int vi, int vj, int weight) {
    ArcNode *p;
    p = (*G)->vertices[vi].firstarc;
    ArcNode *temp = (ArcNode *) malloc(sizeof(ArcNode));
    temp->nextarc = p;
    temp->adjvex = vj;
    temp->weight = weight;
    (*G)->vertices[vi].firstarc = temp;
}

void calInDegree(ALGraph G, int indegree[MAX_VERTEX_NUM]) {
    int i;
    ArcNode *p;
    for (i = 1; i <= G.vexnum; i++)
        indegree[i] = 0;
    for (i = 1; i <= G.vexnum; i++) {
        p = G.vertices[i].firstarc;
        while (p) {
            indegree[p->adjvex]++;
            p = p->nextarc;
        }
    }
}

int TopogicalSort(ALGraph G, int Topo[]) {
    ArcNode *p;
    Sq *sq;
    Ct_Sq(&sq);
    int i, k, count, indegree[MAX_VERTEX_NUM + 1];
    calInDegree(G, indegree);

    for (i = 0; i < G.vexnum; i++) {
        if (!indegree[i])
            Push_Sq(&sq, i);
    }

    count = 0;
    while (!isEmtpy(*sq)) {
        i = Pop_Sq(&sq);
        count++;
        Topo[count] = i;

        for (p = G.vertices[i].firstarc; p; p = p->nextarc) {
            k = p->adjvex;
            if (!(--indegree[k])) {
                Push_Sq(&sq, k);
            }
        }
    }
    if (count < G.vexnum)
        return -1;
    else
        return 1;
}

// 0 5 6 0 7 2 0 4 3 0 1 999
// following  is test function;
// 0 1 1 0 2 3 1 2 1 1 3 1 2 3 1 2 4 1 3 4 1