#include "MST.h"

#if (TEST)
int main()
{

    int *graphSize = (int *)malloc(sizeof(int));
    int **matrix;
    matrix = InitMatrix(graphSize);
    // show graph
    showMatrix(matrix, *graphSize);
    enterNode(matrix, *graphSize);

    while (!warshall(matrix, *graphSize))
    {
        printf("graph is not connected, please add edge");
        enterNode(matrix, *graphSize);
    }
    int **mst;
    int *sum = (int *)malloc(sizeof(int));
    (*sum) = 0;
    warshall(matrix, *graphSize);
#if (!TEST)
    mst = Prim(matrix, *graphSize, sum);
    if (mst != NULL)
    {
        printf("the matrix of MST is show below:\n");
        showMatrix(mst, *graphSize);
        printf("\nthe weight sum of MST is %d\n", *sum);
    }
    else
        printf("graph is not connected");
#endif
    return 0;
}
#endif

void MST()
{
    int *graphSize = (int *)malloc(sizeof(int));
    int **matrix;
    matrix = InitMatrix(graphSize);
    // show graph
    showMatrix(matrix, *graphSize);
    enterNode(matrix, *graphSize);

//    graph should be connected
    while (!warshall(matrix, *graphSize))
    {
        printf("graph is not connected, please add edge");
        enterNode(matrix, *graphSize);
    }
    int **mst;
    int *sum = (int *)malloc(sizeof(int));
    (*sum) = 0;
    warshall(matrix, *graphSize);
    mst = Prim(matrix, *graphSize, sum);

    if (mst != NULL)
    {
        printf("the matrix of MST is show below:\n");
        showMatrix(mst, *graphSize);
        printf("\nthe weight sum of MST is %d\n", *sum);
    }
    else
        printf("graph is not connected");
}


int **InitMatrix(int *graphSize)
{
    printf("\nPlease Enter the Number of Nodes:\n");
    int temp;
    scanf("%d", &temp);
    *graphSize = temp;
    // init graph
    int **matrix = (int **)malloc(sizeof(int *) * (*graphSize));
    for (int i = 0; i < *graphSize; i++)
        matrix[i] = (int *)malloc(sizeof(int) * (*graphSize));
    // init each node as 0;
    for (int i = 0; i < *graphSize; i++)
        for (int j = 0; j < *graphSize; j++)
            matrix[i][j] = 0;
    return matrix;
}

int **InitMST(int graphSize)
{
    // init graph
    int **mst = (int **)malloc(sizeof(int *) * graphSize);
    for (int i = 0; i < graphSize; i++)
        mst[i] = (int *)malloc(sizeof(int) * graphSize);
    // init each node as 0;
    for (int i = 0; i < graphSize; i++)
        for (int j = 0; j < graphSize; j++)
            mst[i][j] = 0;
    return mst;
}

int **Prim(int **matrix, int graphSize, int *sum)
{
    // mst是最终要返回的生成树,初始为一个全部为0的邻接矩阵
    int **mst;
    mst = InitMST(graphSize);

    // arr存放节点，nodeNum 记录已经存放的节点数量
    int *arr = (int *)malloc(sizeof(int) * graphSize);
    int nodeNum = 1;
    // 将第一个节点作为起始节点:
    arr[0] = 0;

    // 循环n遍即可查找到所有的节点。
    for (int i = 0; i < graphSize - 1; i++)
    {
        //  一次遍历要做的事情是:找到当前数组中除了0之外最小的值，将其中的最小的节点加进数组中，然后将最小的边加入到边数组中；
        // 将已经加入进入节点数组的两两相连的边删除

        // 遍历已经在点集中的点的位置，返回其中最小的.
        int min = 0;
        // vi vj记录最小边的左右节点;
        int vi, vj;
        for (int j = 0; j < graphSize; j++)
        {
            for (int k = 0; k < nodeNum; k++)
            {
                if ((min > matrix[arr[k]][j] || min == 0) && matrix[arr[k]][j] != 0)
                {
                    min = matrix[arr[k]][j];
                    vi = arr[k];
                    vj = j;
                }
            }
        }
        // 如果min为0,说明当前树与其余节点没有连通，直接退出for循环;
        if (min == 0)
            break;

        // 在mst中删除除了当前vj vi之外、vj行的，已经在arr中的列的节点(置为0),将在arr中的，vj列的所有权值清除为0;

        for (int k = 0; k < nodeNum; k++)
        {
            // if (arr[k] == vi && j == vj)
            //     continue;
            matrix[arr[k]][vj] = 0;
            matrix[vj][arr[k]] = 0;
        }

        // 下一步, 将sum += min，将需要的节点加入arr，节点的数目增加
        arr[i + 1] = vj;
        *sum += min;
        nodeNum++;
        mst[vi][vj] = min;
        mst[vj][vi] = min;
    }
    if (nodeNum < graphSize)
    {
        printf("\nno MST!\n");
        return NULL;
    }
    printf("the nodes of MST is show below:\n");
    for (int l = 0; l < nodeNum; l++)
        printf("%3d", arr[l]);
    printf("\n");
    return mst;
}

int findMin(int *arr, int graphSize)
{
    int k = arr[0];
    for (int j = 0; k == 0; j++)
        k = arr[j];
    if (k == 0)
        return -1;

    int cur = 0;
    for (int i = 0; i < graphSize; i++)
    {
        if (arr[i] == 0)
            continue;
        else
        {
            if (k > arr[i])
            {
                k = arr[i];
                cur = i;
            }
        }
    }
    if (cur == 0)
        return -1;

    return cur;
}

void showMatrix(int **matrix, int graphSize)
{
    printf("\n");
    for (int i = 0; i < graphSize; i++)
    {
        for (int j = 0; j < graphSize; j++)
        {
            printf("%-3d", matrix[i][j]);
        }
        printf("\n");
    }
}

void enterNode(int **matrix, int graphSize)
{
    int i = 0, j = 0, weight;
    int EdgeNum = 0;
    printf("Please Enter the Number of edge you want to add\n");
    scanf("%d", &EdgeNum);
    while (EdgeNum > graphSize * (graphSize + 1) / 2)
    {
        printf("Edge too much!\n");
        scanf("%d", &EdgeNum);
    }

    for (int k = 0; k < EdgeNum; k++)
    {
        printf("Please Enter the %d position of Edge(0-%d)", k, graphSize - 1);
        scanf("%d%d", &i, &j);
        getchar();
        while (i < 0 || i > graphSize || j < 0 || j > graphSize || i == j || matrix[i][j] != 0)
        {
            printf("Invalid Position, Please re-enter!\n");
            scanf("%d%d", &i, &j);
            getchar();
        }
        scanf("%d", &weight);
        matrix[i][j] = weight;
        matrix[j][i] = weight;
        showMatrix(matrix, graphSize);
    }
}
// 10

// 利用warshall算法测试图的连通性
int warshall(int **testMt, int graphSzie)
{

    int **warshallMT;
    warshallMT = InitMST(graphSzie);
    for (int m = 0; m < graphSzie; m++)
        for (int n = 0; n < graphSzie; n++)
            if (testMt[m][n] != 0)
                warshallMT[m][n] = 1;
    
    int i = 0, j = 0, k = 0;
    for (i = 0; i < graphSzie; i++)
        for (j = 0; j < graphSzie; j++)
            if (warshallMT[j][i])
                for (k = 0; k < graphSzie; k++)
                    warshallMT[j][k] = warshallMT[j][k] | warshallMT[i][k];

    for (i = 0; i < graphSzie; i++)
        for (j = 0; j < graphSzie; j++)
            if (warshallMT[i][j] == 0)
                return 0;
    return 1;
}
// 一组测试数据,用以检测最小生成数字是否正确
// 7
// 10
// 0 1 7 0 3 5 1 3 9 1 2 8 2 4 5 1 4 7 3 4 15 3 5 6 4 5 8 4 6 9 5 6 11