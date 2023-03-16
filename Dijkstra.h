#ifndef PUREC_DIJKSTRA_H
#define PUREC_DIJKSTRA_H


#endif //PUREC_DIJKSTRA_H

#include "TopoSort.h"
#define MAX_DijNode 50
#define INF 10000

void InitShortest(int *shortest, int graphSize, int startNode);
// 返回最短距离数组
int *Dijkstra(ALGraph *G, int startNode);
void InitVisit(int **visited, int graphSize, int startNode);
int DJSHOW();
void showShortest(int *shortestArr, int length);