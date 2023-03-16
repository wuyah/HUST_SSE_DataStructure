#include <stdio.h>
#include "Dijkstra.h"


int DJSHOW()
{
    // show graph
    ALGraph *G;
    Creategraph(&G);

    int startNode;
    printf("Please Enter the Start Node:\n");
    scanf("%d", &startNode);
    int *shortest;
    shortest = Dijkstra(G, startNode);
    showShortest(shortest, G->vexnum);
    return 0;
}

void showShortest(int *shortestArr, int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%6d", shortestArr[i]);
    }
}

int *Dijkstra(ALGraph *G, int startNode)
{
    int *visited = (int *)malloc(sizeof(int) * (G->vexnum));
    int *shortest = (int *)malloc(sizeof(int) * (G->vexnum));

    // init shortest arr
    for (int i = 0; i < G->vexnum; ++i)
        shortest[i] = INF;

    shortest[startNode] = 0;

    // Init visited arr
    for (int i = 0; i < G->vexnum; ++i)
        visited[i] = 0;

    ArcNode *temp;
    temp = G->vertices[startNode].firstarc;
    //    根据开始节点更新shortest数组;
    for (; temp != NULL; temp = temp->nextarc)
        shortest[temp->adjvex] = temp->weight;

    //主循环
    for (int i = 0; i < G->vexnum; i++)
    {

        int min = INF, Node = -1;
        //    找到已经连接的节点中最小的路径(除了首节点)
        for (int j = 0; j < G->vexnum; j++)
        {
            if (visited[j] == 0 && shortest[j] < min)
            {
                min = shortest[j];
                Node = j;
            }
        }
        //到这里说明可以退出了不连通
        if (Node == -1)
            return shortest;
        //将当前节点放入visited中;
        visited[Node] = 1;
        //根据当前节点调整最短路径:
        //到当前节点的距离是min，而到下一个节点的最小距离，只可能是min+n 或者是 shortest中已经记录的值
        temp = G->vertices[Node].firstarc;
        for (; temp != NULL; temp = temp->nextarc)
            if (visited[temp->adjvex] == 0 && min + temp->weight < shortest[temp->adjvex])
                shortest[temp->adjvex] = min + temp->weight;
    }

    //    到这里说明成功了
    return shortest;
}

/*
7 12
0 1 2
0 3 1
1 3 3
1 4 10
2 0 4
2 5 5
3 2 2
3 4 2
3 5 8
3 6 4
4 6 6
6 5 1
 */
