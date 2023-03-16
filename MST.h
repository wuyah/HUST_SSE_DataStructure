#include <stdio.h>
#include <stdlib.h>

int **InitMatrix(int *graphSize);
void showMatrix(int **matrix, int graphSize);
void enterNode(int **matrix, int graphSize);
int **Prim(int **matrix, int graphSize, int *sum);
int warshall(int **testMt, int graphSzie);

#define TEST 0