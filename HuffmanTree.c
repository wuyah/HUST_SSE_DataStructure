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
void dic2HF(HFArr *hfArr, pairRoot dict, int diclength) {
//    dict is sorted, so just need to init each hfArr
    int *lc = (int *) malloc(sizeof(int));
    int *rc = (int *) malloc((sizeof(int)));
    int total_length = diclength * 2 - 1;

    printf("\ndiclength = %d\n", diclength);
    printf("\n");
    for (int i = 0; i < diclength; i++) {
        printf("%5.0ld", dict[i].weight);
    }
    printf("\n");
    for (int i = 0; i <= diclength; i++) {
        (*hfArr)[i].weight = dict[i].weight;
        (*hfArr)[i].lchild = -1;
        (*hfArr)[i].rchild = -1;
        (*hfArr)[i].value = dict[i].key;
        (*hfArr)[i].parent = -1;
    }
    for (int i = diclength; i < total_length; i++) {
        (*hfArr)[i].weight = 0;
        (*hfArr)[i].lchild = -1;
        (*hfArr)[i].rchild = -1;
        (*hfArr)[i].value = '\0';
        (*hfArr)[i].parent = -1;
    }
    printf("\n");
    for (int i = 0; i <= total_length; i++)
        printf("%4.2lf", (*hfArr)[i].weight);
    printf("\n");
    //init huffman tree
    for (int i = diclength; i <= total_length; i++) {
        SelectMin(hfArr, i-1 , lc, rc);
        // generate the parent node in i, and delete the leaf node.
        if (*lc == *rc) break;
        (*hfArr)[(*lc)].parent = i;
        (*hfArr)[(*rc)].parent = i;
        (*hfArr)[i].lchild = *lc;
        (*hfArr)[i].rchild = *rc;
        (*hfArr)[i].weight = (*hfArr)[*lc].weight + (*hfArr)[*rc].weight;
    }
}

void SelectMin(HFArr *hfArr, int end, int *lc, int *rc) {
    int p1 = 0;
    int p2 = 1;
    double min1 = 10000;
    double min2 = 10000;
    // find initial p1, p2;
    for (int i = 0; i <= end; i++) {
        if ((*hfArr)[i].parent == -1 && (*hfArr)[i].weight < min1) {
            p1 = i;
            min1 = (*hfArr)[i].weight;
        }
    }
    for (int i = 0; i <= end; i++) {
        if ((*hfArr)[i].parent == -1 && i != p1 && (*hfArr)[i].weight < min2) {
            p2 = i;
            min2 = (*hfArr)[i].weight;
        }
    }
//    min1 < min2

    if (min1 == 10000 || min2 == 10000) {
        (*lc) = (*rc);
        return;
    }
    (*lc) = p1;
    (*rc) = p2;
}

//main function
void main() {
    char string_ori[MAXSTRING];
    scanf("%s", string_ori);

    HFArr hfArr;
    pairNode dic[256];

    // Use dicLenth to record.
    int dicLength = countFrequency(string_ori, dic);

    int HFSize = dicLength * 2 - 1;
    printf("\ndicLength is %d\n", dicLength);
    // 冒泡进行逆序排序
    bubblesortDic(dic, dicLength);
    for (int i = 0; i < dicLength; i++) {
        printf("%lf\t%c\n", dic[i].weight, dic[i].key);
    }
    dic2HF(&hfArr, dic, dicLength);

    showHaffmanTree(hfArr, HFSize);

    printf("\nHFSize in hfArr = %lf\n",hfArr[HFSize-1].weight);
    codeArray encodeArray = generateCode(hfArr, HFSize);
    printf("\n");
    for (int i = 0; i < dicLength; i++) {
        printf("%c\t%s\n", encodeArray[i].key, encodeArray[i].codes);
    }

    DeccodeTxt(hfArr,HFSize);

}

void InitRoot(HFPointer *root) {
    (*root) = (HFPointer) malloc(sizeof(HFNode));
    (*root)->value = 0;
    (*root)->weight = 0;
    (*root)->lchild = -1;
    (*root)->rchild = -1;
    (*root)->parent = -1;
}

// 数组长度固定，只需要对256个字符排序就可以了(char 类型总共只有256，所以数组可以开成固定大小)
// 利用冒泡排序进行__降序__排序；计算次数不会有很大的差异
void bubblesortDic(pairRoot dic, int dicLength) {
    int i;
    pairNode temp = {1, 'l'};
    int flag = 0;
    for (i = 0; i < dicLength; i++) {
        flag = 0;
        for (int j = 0; j < dicLength - i - 1; j++) {
            if (dic[j].weight > dic[j + 1].weight) {
                swap_Node(&dic[j], &dic[j + 1]);
                flag = 1;
            }
        }
        if (flag == 0)
            break;
    }
}

void swap_Node(pairNode *a, pairNode *b) {
    pairNode temp = *b;
    *b = *a;
    *a = temp;
}

int countFrequency(char string_ori[MAXSTRING], pairRoot dic) {

    int keyNum = 0;
    int stringLenth = strlen(string_ori);
    for (int i = 0; i < strlen(string_ori); i++) {
        // search if is in dic; if is in, return position and ++ weight;
        // position is the key position in the
        int position = isInDic(dic, string_ori[i], keyNum);
        if (position >= 0) {
            dic[position].weight = dic[position].weight + 1;
        } else {
            dic[keyNum].key = string_ori[i];
            dic[keyNum].weight = 1;
            keyNum = keyNum + 1;
        }
    }
    return keyNum;
}

int isInDic(pairRoot dic, char key, int keyNum) {
    for (int i = 0; i <= keyNum; i++) {
        if (dic[i].key == key)
            return i;
    }
    return -1;
}

void showHaffmanTree(HFPointer root, int HFSize) {
    for (int i = 0; i < HFSize; i++) {
        printf("%.1lf\t", root[i].weight);
    }
    for (int i = 0; i < HFSize; i++) {
        if (root[i].lchild == -1 && root[i].rchild == -1) {
            printf("%c", root[i].value);
        }
    }
    printf("\n");
    for (int i = 0; i < HFSize; i++) {
        printf("%4d", root[i].parent);
    }
}

codeArray generateCode(HFPointer HFTree, int HFSize) {
    codeArray encodeArray;
    encodeArray = (codeArray) malloc(sizeof(codeNode) * ((HFSize + 1) / 2));

    int cursor = 0;
    for (int i = 0; i < HFSize - 1; i++) {
        char temp[MAXCODESIZE];
        // 如果该节点无左右节点，则遍历该节点的父节点
        if (HFTree[i].lchild == -1 && HFTree[i].rchild == -1) {
            char *encodes = getCode(HFTree, i, temp);
            encodeArray[cursor].key = HFTree[i].value;
            strcpy(encodeArray[cursor].codes, encodes);
            cursor++;
        }
    }
    return encodeArray;
}

char *getCode(HFPointer HFTree, int position, char encodes[MAXCODESIZE]) {
    HFNode temp = HFTree[position];

    int cursor = 0;
    while (temp.parent != -1) {
        if (position == HFTree[temp.parent].lchild) {
            encodes[cursor] = '0';
        } else
            encodes[cursor] = '1';
        cursor++;
        position = temp.parent;
        temp = HFTree[temp.parent];
    }
    // the end is '\0' to show it is a string.
    encodes[cursor] = '\0';
    return revstr(encodes);
}

char *revstr(char *str) {
    char *start = str;
    char *end = str + strlen(str) - 1;
    char ch;

    if (str != NULL) {
        while (start < end) {
            ch = *start;
            *start++ = *end;
            *end-- = ch;
        }
    }
    return str;
}

char* decoder(char *decodeStr, HFArr hft, int hfSize)
{
    unsigned long long strLen = strlen(decodeStr);
    char encodeStr[256];
    HFNode root = hft[hfSize - 1];
    HFNode temp = root;
    int i = 0;
    char cur = decodeStr[i];
    int enCur = 0;

   while(i<=strLen)
   {
       if(temp.lchild == -1 && temp.rchild == -1){
           encodeStr[enCur] = temp.value;
           enCur+=1;
           temp = root;
       } else if(cur == '0')
       {
           temp = hft[temp.lchild]; i++;
       } else{
           temp = hft[temp.rchild]; i++;
       }
       cur = decodeStr[i];
   }
    encodeStr[enCur] = '\0';
    printf("%s",encodeStr);
    return encodeStr;
}

void DeccodeTxt(HFArr hfArr,int HFSize)
{
    char decodedArr[256];
    char *encodedArr;
    printf("\n");
    printf("Plsease enter a decoded text:\n");
    scanf("%s",decodedArr);
    encodedArr = decoder(decodedArr,hfArr,HFSize);
    printf("%s",encodedArr);
}

//hdwuohduhewhdwhedhwehdhehudwhd
//10101011100001101