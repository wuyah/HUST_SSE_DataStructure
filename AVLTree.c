#include <stdio.h>
#include <stdlib.h>

#define MAX_AVL_LENGTH 100
#define LH 1
#define RH -1
#define EH 0

typedef struct AVLNode
{
    int data;
    int bf;
    struct AVLNode *lchild;
    struct AVLNode *rchild;
} AVLNode, *AVLTree;

int InitAVL(AVLTree *AVLT, int key);
int SearchKEy(AVLTree AVLT, int key, AVLNode **p);
int InsertAVL(AVLTree *AVLT, int key, int *taller);
void printTree(AVLTree AVLT);

void L_Rotate(AVLTree *p);
void R_Rotate(AVLTree *p);
void LeftBalance(AVLTree *AVLT);
void RightBalance(AVLTree *AVLT);
#define TEST 0

#if TEST
int main()
{
    AVLTree AVLT;
    int keyArr[20] = {1, 2, 3, 4, 5, 6, 7, 8};
    int *taller;
    int a = 0;
    taller = &a;
    for (int i = 0; i <= 7; i++)
        InsertAVL(&AVLT, keyArr[i], taller);
    printTree(AVLT);
    return 0;
}
#endif
int InitAVL(AVLTree *AVLT, int key)
{
    (*AVLT) = (AVLTree)malloc(sizeof(AVLNode));
    (*AVLT)->data = key;
    (*AVLT)->bf = EH;
    (*AVLT)->lchild = NULL;
    (*AVLT)->rchild = NULL;
    return 1;
}

int SearchKey(AVLTree AVLT, int key)
{
    if (!AVLT)
        return 0;
    if (AVLT->data == key)
    {
        return 1;
    }
    else if (AVLT->data < key)
    {
        return SearchKey(AVLT->rchild, key);
    }
    else
    {
        return SearchKey(AVLT->lchild, key);
    }
}

int InsertAVL(AVLTree *AVLT, int key, int *taller)
{
    if ((*AVLT) == NULL)
    {
        (*AVLT) = (AVLTree)malloc(sizeof(AVLNode));
        (*AVLT)->data = key;
        (*AVLT)->bf = EH;
        (*AVLT)->lchild = NULL;
        (*AVLT)->rchild = NULL;
        *taller = 1;
    }
    else
    {
        if (key == (*AVLT)->data)
        {
            *taller = 0;
            return 0;
        }

        else if (key < (*AVLT)->data)
        {
            if (!InsertAVL(&(*AVLT)->lchild, key, taller))
            {
                return 0;
            }

            if (*taller)
            {
                switch ((*AVLT)->bf)
                {
                case EH:
                    (*AVLT)->bf = LH;
                    *taller = 1;
                    break;
                case LH:
                    LeftBalance(AVLT);
                    *taller = 0;
                    break;
                case RH:
                    (*AVLT)->bf = EH;
                    *taller = 0;
                    break;
                default:
                    break;
                }
            }
        }
        else
        {
            if (!InsertAVL(&(*AVLT)->rchild, key, taller))
                return 0;

            if (*taller)
            {
                switch ((*AVLT)->bf)
                {
                case EH:
                    (*AVLT)->bf = RH;
                    *taller = 1;
                    break;
                case RH:
                    RightBalance(AVLT);
                    *taller = 0;
                    break;
                case LH:
                    (*AVLT)->bf = EH;
                    *taller = 0;
                    break;
                default:
                    break;
                }
            }
        }
    }
    return 1;
}


void R_Rotate(AVLTree *p)
{
    AVLTree temp;

    temp = (*p)->lchild;
    (*p)->lchild = temp->rchild;

    temp->rchild = *p;
    *p = temp;
}

void L_Rotate(AVLTree *p)
{
    AVLTree temp;

    temp = (*p)->rchild;
    (*p)->rchild = temp->lchild;

    temp->lchild = (*p);
    (*p) = temp;
}

void LeftBalance(AVLTree *AVLT)
{
    AVLTree lc, rc;
    lc = (*AVLT)->lchild;
    switch (lc->bf)
    {
    case LH:
        (*AVLT)->bf = lc->bf = EH;
        R_Rotate(AVLT);
        break;

    case RH:
        rc = lc->rchild;
        switch (rc->bf)
        {
        case LH:
            (*AVLT)->bf = RH;
            lc->bf = EH;
            break;
        case EH:
            (*AVLT)->bf = lc->bf = EH;
            break;
        case RH:
            (*AVLT)->bf = EH;
            lc->bf = LH;
            break;
        }
        rc->bf = EH;
        L_Rotate(&(*AVLT)->lchild);
        R_Rotate(AVLT);

        break;
    default:
        break;
    }
}

void RightBalance(AVLTree *AVLT)
{
    AVLTree lc, rc;
    rc = (*AVLT)->rchild;
    switch (rc->bf)
    {
        // 右侧的右侧高，经过一次旋转就可以平衡
    case RH:
        (*AVLT)->bf = rc->bf = EH;
        L_Rotate(AVLT);
        break;
        // 右子树的左子树高，进行两次旋转，一次是右旋转，这一次旋转中可以平衡右子树的右子树，
        // 右子树的左子树高的情况下，要讨论右子树的左子树的平衡情况，如果右子树的左子树原本就是平衡的，则在旋转之后仍然是平衡的
        // 然而如果右子树的左子树的左子树高，则在旋转之后，可以得到原本的rc会让右子树高一些,因为原本rc的左子树的右子树转换为现在rc的左子树
    // 其余也是 同理的

    // 因为是对rc进行旋转,所以rc的lc的右子树会成为现在rc的左子树
    case LH:
        lc = rc->lchild;
        switch (lc->bf)
        {
        case LH:
            (*AVLT)->bf = EH;
            rc->bf = RH;
            break;
        case RH:
            (*AVLT)->bf = LH;
            rc->bf = EH;
            break;
        case EH:
            (*AVLT)->bf = lc->bf = EH;
            break;
        }
        lc->bf = EH;
        R_Rotate(&(*AVLT)->rchild);
        L_Rotate(AVLT);
        break;
    }
}

int calHeight(AVLTree AVLT)
{
    int LDepth, RDepth;
    if (AVLT == NULL)
        return 0;

    else
    {
        LDepth = calHeight(AVLT->lchild);
        RDepth = calHeight(AVLT->rchild);
    }
    return (LDepth > RDepth ? LDepth : RDepth) + 1;
}

void printTree(AVLTree AVLT)
{
    static int level = -1;
    int i;
    if (NULL == AVLT)
        return;
    level++;
    printTree(AVLT->rchild);
    level--;

    level++;
    for (i = 0; i < level; i++)
        printf("\t");
    printf("%2d\n", AVLT->data);
    printTree(AVLT->lchild);
    level--;
}
