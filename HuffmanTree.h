#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTRING 1000
#define MAXTREESIZE 1000
#define MAXCODESIZE 100
#define TEST 0

// rclid > lchlid
// parent weight > child weight
// parent weight = r.weight+l.weight
typedef struct HFNode {
    double weight;
    char value;
    unsigned int parent;
    unsigned int lchild, rchild;
} HFNode, *HFPointer;

typedef HFNode HFArr[256 * 2 + 1];

typedef struct pairNode {
    double weight;
    char key;
} pairNode, *pairRoot;

typedef struct codeNode {
    char key;
    char codes[MAXCODESIZE];
} codeNode, *codeArray;

void InitRoot(HFPointer *root);

void bubblesortDic(pairRoot dic, int dicLength);

int countFrequency(char string_ori[MAXSTRING], pairRoot dic);

codeArray generateCode(HFPointer HFTree, int HFSize);

void showHaffmanTree(HFPointer root, int HFSize);

char *getCode(HFPointer HFTree, int position, char encodes[MAXCODESIZE]);

char *revstr(char *str);

void SelectMin(HFArr *hfArr, int end, int *lc, int *rc);

void dic2HF(HFArr *hfArr, pairRoot dict, int diclength);

void HF_2Main();

void swap_Node(pairNode *a, pairNode *b);

int isInDic(pairRoot dic, char key, int keyNum);

char* decoder(char *decodeStr, HFArr hft, int hfSize);

void DeccodeTxt(HFArr hfArr,int HFSize);