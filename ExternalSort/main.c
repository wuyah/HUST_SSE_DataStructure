#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAXKEY 10000
#define RUNEND_SYMBOL 10000
#define MAX_MEMORY 6
#define MAX_INT 2147483646
#define N 24
#define K_ROLL 2 //k路归并
#define MINKEY 0

typedef int KeyType;

typedef struct {
    KeyType key;
} ExNode, External[K_ROLL + 1];

typedef int LoserTree[K_ROLL];
typedef int LoserTree_RS[MAX_MEMORY];

typedef struct {
    int rec;
    int key;
    int rnum;
} RecNode, WorkArea[MAX_MEMORY];

void generateOri();

// function for k_merge
/*------ function start ------*/
void Adjust(LoserTree *ls, int s, External *b);

void CreatLoserTree(LoserTree *ls, External *b);

int input_txt(int *a, FILE *fi); // input函数，每次读取一个数字，将其赋值为a;

void output(int a, FILE *fo);

void K_Merge(FILE *fileIn[K_ROLL], int, int);
/*------ function start ------*/

//unused function
void generateFourOri();

// function for select and sort
/* -----function start----------- */
int get_Run(LoserTree_RS *ls, WorkArea *workArea, int rc, int *rmax, FILE *fi, FILE *fo);

void ConstructLoserTree(LoserTree_RS *ls, WorkArea *workArea, FILE *fi);

void Select_MiniMax(LoserTree_RS *ls, WorkArea workArea, int q);

//void Replace_Selection(LoserTree_RS *ls, WorkArea *workArea, FILE *fi, FILE *fo);
int Replace_Selection(LoserTree_RS *ls, WorkArea *workArea, FILE *fi);

void RS();
/* -----function end----------- */

/* -------generate test function------*/
void printOri();

int generateSpilit();

/*-------function end--------*/


int main() {
    RS();
    return 0;
}

void Merge(int runNum) {
    FILE *fi[K_ROLL];
    char Name[100];

    int flag = 0;
    // loop quit condition: runNum == 1
    while (runNum != 1) {
        int nextRunNum = 0;
        int run_turn = runNum / K_ROLL;
        if (runNum % K_ROLL != 0) run_turn++;

        for (int i = 0; i < run_turn; i++) {
            // following for loop update file
            for (int j = 0; j < K_ROLL; j++) {
                // update filename
                printf("\nfile_Num = %4d\n", i * K_ROLL + j);
                itoa(i * K_ROLL + j, Name, 10);
                strcat(Name, ".txt\0");
                char filaName[1000];
                if (flag == 0) {
                    strcpy(filaName, "./run_1/");
                } else { strcpy(filaName, "./run_2/"); }
//                create fake file.

                strcat(filaName, Name);
                if ((fi[j] = fopen(filaName, "r")) == NULL) {
                    fclose(fi[j]);
                    FILE *fo = fopen(filaName, "w");
                    fprintf(fo, "%d", MAXKEY);
                    fclose(fo);
                }
                fi[j] = fopen(filaName, "r");
                printf("\nfileName = %s",filaName);
            }

            printf("\n");
            K_Merge(fi, i, flag);
            nextRunNum++;
            //fclose
            for (int j = 0; j < K_ROLL; j++)
                fclose(fi[i]);
        }
        runNum = nextRunNum;
        if (flag == 1)flag = 0;
        else flag = 1;
    }
}

/* ---One Merge Turn--- */
//n means how many runs have.
void K_Merge(FILE *fileIn[K_ROLL], int rNum, int odd_flag) {
    printf("\nKMerge Start!");
    FILE *fo;
    char Name[1000];
    char fileName[1000];
    itoa(rNum, Name, 10);
    strcat(Name, ".txt");

//    printf("")
    // change file path through odd_flag
    if (odd_flag == 1) {
        strcpy(fileName, "./run_1/");
    } else {
        strcpy(fileName, "./run_2/");
    }
    strcat(fileName, Name);
    fo = fopen(fileName, "w");
//    初始化外部关键字作为叶子节点
// b ---> leaf
    External b;
// ls ---> parent
    LoserTree ls = {0};
//   init extern key
    for (int i = 0; i < K_ROLL; i++) {
        input_txt(&(b[i].key), fileIn[i]);
        printf("input num = %d",b[i].key);
    }
    int q;
    int cur = 0;
// create loser tree
    CreatLoserTree(&ls, &b);
    printf("\nCreate Loser Tree OK!\n");
//    最终所有的外部节点都会是MAXKEY时，程序输出（对于任意的外部排序，总是会存在一个规定大小范围内的数子，使得外部排序可以利用这个作为参照物
    while (b[ls[0]].key != MAXKEY) {
        q = ls[0];
        fprintf(fo, "%d\n", b[q].key);
//   output
        cur++;
        input_txt(&(b[q].key), fileIn[q]);
        Adjust(&ls, q, &b);
    }
    fprintf(fo, "%d", MAXKEY);
    for (int i = 0; i < K_ROLL; i++) { fclose(fileIn[i]); }
    fclose(fo);
}

void Adjust(LoserTree *ls, int s, External *b) {
    // t是父亲节点的ls的位置
    int t = (s + K_ROLL) / 2;

    while (t > 0) {
        // printf("\t(*b)[s].key = :%d\t,(*b)[ (*ls)[t] ].key = :%d\n", (*b)[s].key, (*b)[(*ls)[t]].key);
        // 判断当前位置比父亲节点的位置的key是否更大
        // 若当前位置较小，则将当前的父亲节点的值更新为更大的那个节点的值，
        // 将较小的值作为s存储起来.
        if ((*b)[s].key > (*b)[(*ls)[t]].key) {
            int temp = s;
            s = (*ls)[t];
            (*ls)[t] = temp;
        }
        t = t / 2;
    }
    // 将(*ls)[0]更新为权值最小的那个位置.
    (*ls)[0] = s;
}

void CreatLoserTree(LoserTree *ls, External *b) {
    // initial loser key
    ((*b)[K_ROLL]).key = MINKEY;
    printf("(*b)[6] = :%d\n", (*b)[K_ROLL].key);
    int i;
    // 设置败者树初始子树大小,初始败者都为不存在的位置
    for (i = 0; i < K_ROLL; ++i)
        (*ls)[i] = K_ROLL;
    // 调整败者树
    for (i = K_ROLL - 1; i >= 0; --i)
        Adjust(ls, i, b);
}

int input_txt(int *a, FILE *fi) {
    if (!feof(fi)) {
//        fread(a, sizeof(int), 1, fi);
        fscanf(fi, "%d", a);
        return 1;
    } else
        return 0;
}

//进行一次替换选择
void Select_MiniMax(LoserTree_RS *ls, WorkArea workArea, int q) {
    // q --> leaf
    // t --> iterator
    int t;
    int p;
    // p --> pointer

    for (t = (MAX_MEMORY + q) / 2, p = (*ls)[t]; t > 0; t = t / 2, p = (*ls)[t]) {
        /* --需要调整的情况只有以下两种情况，一个是段号小，无条件失败，如果是段号相同，则比较大小 -- */
        if (workArea[p].rnum < workArea[q].rnum ||
            (workArea[q].rnum == workArea[p].rnum && workArea[p].key < workArea[q].key)) {
            /* --exchange position-- */
            int temp = q;
            q = (*ls)[t];
            (*ls)[t] = temp;
        }
    }
    // ls[0] win
    (*ls)[0] = q;
}

//finished
void ConstructLoserTree(LoserTree_RS *ls, WorkArea *workArea, FILE *fi) {
    /* ------following is init the rnum of workspace, initial rec should all be 0----- */
    for (int i = 0; i < MAX_MEMORY; i++) {
//        fread(&((*workArea)[i].key), sizeof(int), 1, fi);
        (*workArea)[i].key = 0;
        (*workArea)[i].rnum = 0;
        (*ls)[i] = 0;
    }

    int i = 0;
    /* different from k_merge, select&sort construct read one and then select one */
    for (i = MAX_MEMORY - 1; i >= 0; i--) {
        fread(&((*workArea)[i].rec), sizeof(int), 1, fi);
        (*workArea)[i].key = (*workArea)[i].rec;
        (*workArea)[i].rnum = 1;
        Select_MiniMax(ls, *workArea, i);
    }
    printf("\n");
    for (int j = 0; j < MAX_MEMORY; j++) {
        printf("%3d", (*workArea)[j].key);
    }
    printf("\n");
}

// get one run
int get_Run(LoserTree_RS *ls, WorkArea *workArea, int rc, int *rmax, FILE *fi, FILE *fo) {
    // q means MIN num in; wa, wa[q] is where the min num in
    int q;
    int min;
    // rc is the current run id, if rnum == rc, write the rec into fo;
    while ((*workArea)[(*ls)[0]].rnum == rc) {
        // loser is in 0
        q = (*ls)[0];
        // min is the loser position key
        min = (*workArea)[q].key;
        fprintf(fo, "%d\n", (*workArea)[q].rec);                  // 输出
        /* attention!, the fread must before feof */
        fread(&((*workArea)[q].rec), sizeof(int), 1, fi);           //输入
        if (!feof(fi)) {

            (*workArea)[q].key = (*workArea)[q].rec;

            // update rmax, as if entered key is less than min, the new rc is new.
            if ((*workArea)[q].key < min) {
                (*rmax) = rc + 1;
                (*workArea)[q].rnum = (*rmax);
            } else {
                (*workArea)[q].rnum = rc;
            }
        } else {
            // if the file is in the end, the new rnum is lager than rmax, which means this run won't be written
            (*workArea)[q].rnum = *rmax + 1;
            (*workArea)[q].rec = MAXKEY;
            (*workArea)[q].key = MAXKEY;
        }
// adjust minimax,but when it is the end, the final need to be selected in next merge
        Select_MiniMax(ls, *workArea, q);
        printf("OK!");
    }
    return 1;
}

void RS() {
    FILE *fi;
    fi = fopen("ori1", "rb+");
    LoserTree_RS ls;
    WorkArea workArea;
//    FILE *fo;
//    fo = fopen("rs.txt", "w");
    int totalNum = 0;
    totalNum = Replace_Selection(&ls, &workArea, fi);
    printf("\n%d\n", totalNum);
    Merge(totalNum);
}

/* --- Replace_Selection to generate initial runs*/
int Replace_Selection(LoserTree_RS *ls, WorkArea *workArea, FILE *fi) {
//    fi is opened
    ConstructLoserTree(ls, workArea, fi);
    printf("\nConstruction Finished!!\n");

// Init the first output name.
    FILE *fo;
    int rNum = 0;
    char rName[1000];

// Init end
    int rc, rmax;
    rc = rmax = 1;
//    char out_name[256];
    while (rc <= rmax) {
        char fileName[1000];
        strcpy(fileName, "./run_1/");
        itoa(rNum, rName, 10);
        strcat(rName, ".txt");
        strcat(fileName, rName);
        fo = fopen(fileName, "w");
        int flag = 0;
        for (int i = 0; i < MAX_MEMORY; i++) {
            if ((*workArea)[i].key != MAXKEY) {
                flag = 1;
                break;
            }
        }
        if (flag == 0)break;

        get_Run(ls, workArea, rc, &rmax, fi, fo);
//        fprintf(fo, "%d\n", MAXKEY);
//        fclose(fo);
        fprintf(fo, "%d", MAXKEY);
        fclose(fo);
        rNum++;
        rc = (*workArea)[(*ls)[0]].rnum;                //set next rnum
    }
    fclose(fo);
    return rNum;
}
/*
 *     int a[27] = {51, 49, 39, 46, 38, 29,
                 14, 61, 15, 30, 1, 48,
                 52, 3, 63, 27, 4, 13,
                 89, 24, 46, 58, 33, 76, 49, 58, 2};*/