#include <stdio.h>
#include "TopoSort.h"
#include "HuffmanTree.h"

#define MAX_DijNode 50
#define INF 10000


int main() {
    // show graph
    HF_2Main();
//    HFTMain();
    return 0;
}

/*
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