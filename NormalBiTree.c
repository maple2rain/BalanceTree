/***************************************************************************************
 *	File Name				:	NormalBiTree.c
 *	CopyRight				:	LPF
 *	ModuleName				:	BalanceTree
 *
 *	CPU						:   Inter Core 7
 *	RTOS					:
 *
 *	Create Data				:	2015/11/20
 *	Author/Corportation		:	Li PeiFeng
 *
 *	Abstract Description	:	definite the function for NormalBiTree
 *
 *--------------------------------Revision History--------------------------------------
 *	No	version		Data		Revised By			Item			Description
 *
 *
 ***************************************************************************************/

/****************************************************************************************
*	Include File Section
****************************************************************************************/
#include "NormalBiTree.h"

/****************************************************************************************
*	Function Define Section
****************************************************************************************/
/*****************************************************************************************
*@Name............: Status InsertTree(BinaryTree *T, ElemData data, Status (*CompareData)(ElemData, ElemData))
*@Description.....: 为二叉树插入新节点
*@Parameters......: T            :二叉树根节点
*                   data         :待插入数据
*                   CompareData  : 比较函数
*@Return values...: OK ：插入成功
*                   FAIL ：插入失败，可能是节点已经存在或者堆空间不足
*@PreCondition....：存在树，不存在则新建树
*@PostCondition...：插入节点
*****************************************************************************************/
Status InsertTree(BinaryTree *T, ElemData data, Status (*CompareData)(ElemData, ElemData))
{
    if(!*T)
    {
        *T = (BinaryTree)malloc(sizeof(BinaryTNode));
        (*T)->data = data;
        (*T)->lchild = (*T)->rchild = NULL;
        return OK;
    }
    else if(EQUAL == CompareData((*T)->data, data))
    {
        return FAIL;
    }
    else if(GREATER == CompareData((*T)->data, data))
    {
        return InsertTree(&(*T)->lchild, data, CompareData);
    }
    else
        return InsertTree(&(*T)->rchild, data, CompareData);
}

/****************************************************************************************
*@Name............: Status SearchTree(BinaryTree T, ElemData key, Status (*CompareData)(ElemData, ElemData))
*@Description.....: 查找是否存在该数据
*@Parameters......: T           :二叉树根节点
*                   key         :要查找的关键字
*                   CompareData : 比较函数
*@Return values...: OK：查找成功；FAIL：查找失败
*@PreCondition....：存在树
*@PostCondition...：无
*****************************************************************************************/
Status SearchTree(BinaryTree T, ElemData key, Status (*CompareData)(ElemData, ElemData))
{
    while(T)
    {
        if(EQUAL == CompareData(T->data, key))
            return OK;
        else if(GREATER == CompareData(T->data, key))
            T = T->lchild;
        else
            T = T->rchild;
    }

    return FAIL;
}

/*****************************************************************************************
*@Name............: void DestroyTree(BinaryTree *T)
*@Description.....: 销毁二叉树
*@Parameters......: T   :二叉树根节点
*@Return values...: 无
*@PreCondition....：存在树
*@PostCondition...：无
*****************************************************************************************/
void DestroyTree(BinaryTree *T)
{
    if(!*T)
        return ;

        DestroyTree(&(*T)->lchild);

        DestroyTree(&(*T)->rchild);

    free(*T);
    *T = NULL;
}

/*****************************************************************************************
*@Name............: Status CreateTree(BinaryTree *T, Status (*CompareData)(ElemData, ElemData), int select)
*@Description.....: 构建二叉树
*@Parameters......: T           : 二叉树根节点
*                   CompareData : 比较函数
*                   select      : 表示自动或手动
*@Return values...: OK：创建成功；FAIL：创建失败，原因是堆空间不足
*@PreCondition....：存在树
*@PostCondition...：无
*****************************************************************************************/
Status CreateTree(BinaryTree *T, Status (*CompareData)(ElemData, ElemData), int select)
{
    int data;
    int num;

    if(1 == select)//自动
    {
        printf("输入 '0'退出！输入要创建的普通二叉树的节点的数量：\n");
        scanf("%d", &num);
        while(num < 1)
        {
            if(0 == num)
                break;

            printf("数量输入有误，请重新输入！或按下 '0'退出！\n");
            scanf("%d", &num);
        }

        int i;
        for(i = 0; i < num; ++i)
        {
            data = rand() % INT_MAX;
            InsertTree(T, data, CompareData);
        }
    }

    if(2 == select)//手动
    {
        printf("end with \'-1\'\n");
        scanf("%d", &data);

        while(-1 != data)
        {
            InsertTree(T, data, CompareData);
            scanf("%d", &data);
        }
    }

    if(!T)
        return FAIL;
    else
        return OK;
}

/*****************************************************************************************
*@Name............: int GetNumOfNode(BinaryTree T)
*@Description.....: 获取二叉树节点数
*@Parameters......: T     : 平衡二叉树根节点
*@PreCondition....：无
*@PostCondition...：返回节点数目
*****************************************************************************************/
int GetNumOfNode(BinaryTree T)
{
    int leftNum, rightNum;

    if(!T)
        return 0;
    else
    {
        /*
        **分别获取左右子树的节点数
        */
        leftNum = GetNumOfNode(T->lchild);
        rightNum = GetNumOfNode(T->rchild);
    }

    return leftNum + rightNum + 1;//左右子树节点数加上自身即是总节点数
}

/*****************************************************************************************
*@Name............: int GetTreeDepth(BinaryTree T)
*@Description.....: 获取二叉树深度
*@Parameters......: T     : 平衡二叉树根节点
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
int GetTreeDepth(BinaryTree T)
{
    int depthLeft, depthRight;

    if(!T)
        return 0;
    else
    {
        /*
        **分别获取左右子树深度
        */
        depthLeft = GetTreeDepth(T->lchild);
        depthRight = GetTreeDepth(T->rchild);

        return 1 + (depthLeft > depthRight ? depthLeft : depthRight);//取最深子树深度再加上自身即是总深度
    }
}

/*****************************************************************************************
*@Name............: static void InOrderK(BinaryTree T, int *count, int k, ElemData *data)
*@Description.....: 递归中序辅助获取第k大的元素
*@Parameters......: T     : 平衡二叉树根节点
*                   count : 辅助计数
*                   data  : 数据存储于此
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
static void InOrderK(BinaryTree T, int *count, int k, ElemData *data)
{
    if(T->lchild)//增加*count != 1的判断条件，避免作无效的递归
    {
        InOrderK(T->lchild, count, k, data);
    }

    if(*count == k)
        *data = T->data;

    ++*count;

    if(T->rchild)
    {
        InOrderK(T->rchild, count, k, data);
    }
}

/*****************************************************************************************
*@Name............: Status GetNumberK(BinaryTree T, int k, ElemData *data)
*@Description.....: 获取第k大的元素
*@Parameters......: T     : 平衡二叉树根节点
*                   k     : 寻找的序数
*                   data  : 数据存储于此
*@return..........: OK: 找到该关键字 FAIL:参数输入有误
*@PreCondition....：树存在且k数目输入正确
*@PostCondition...：data获取到第k大的值
*****************************************************************************************/
Status GetNumberK(BinaryTree T, int k, ElemData *data)
{
    if(!T)
    {
        printf("该二叉树不存在！\n");
        return  FAIL;
    }

    if(k < 1)
    {
        printf("k取值有误，应大于0！\n");
        return FAIL;
    }

    int count = 1;
    InOrderK(T, &count, k, data);

    if(k > 1 && count <= k)//k值过大
    {
        printf("k取值过大！\n");
        return FAIL;
    }

    return OK;
}

/*****************************************************************************************
*@Name............: static void DeleteNode(BinaryTree *toDel)
*@Description.....: 辅助删除节点
*@Parameters......: toDel :要删除的节点
*@return..........: void
*@PreCondition....：要删除的节点已经找到了
*@PostCondition...：删除有该值的节点
*****************************************************************************************/
static void DeleteNode(BinaryTree *toDel)
{
    BinaryTree tmp, front;
    if(NULL == (*toDel)->rchild)
    {
        tmp = *toDel;
        *toDel = (*toDel)->lchild;
        free(tmp);
    }//连接左子树
    else if(NULL == (*toDel)->lchild)
    {
        tmp = *toDel;
        *toDel = (*toDel)->rchild;
        free(tmp);
    }//连接右子树
    else
    {
        tmp = *toDel;
        front = (*toDel)->lchild;

        while(front->rchild)//找寻前驱
        {
            tmp = front;
            front = front->rchild;
        }
        (*toDel)->data = front->data;

        if(tmp != (*toDel))//连接左子树
            tmp->rchild = front->lchild;
        else
            tmp->lchild = front->lchild;

        free(front);
    }
}

/*****************************************************************************************
*@Name............: Status DeleteTreeNode(BinaryTree *T, ElemData data, Status (*CompareData)(ElemData, ElemData))
*@Description.....: 删除含有data的节点
*@Parameters......: T     : 平衡二叉树根节点
*                   data  : 含有该数据的节点将会被删除
*                   CompareData : 比较函数
*@return..........: OK:存在该关键字  FAIL:不存在该关键字
*@PostCondition...：删除有该值的节点
*****************************************************************************************/
Status DeleteTreeNode(BinaryTree *T, ElemData data, Status (*CompareData)(ElemData, ElemData))
{
    if(!*T)
        return FAIL;
    if(EQUAL == CompareData((*T)->data, data))
    {
        DeleteNode(T);
        return OK;
    }
    else if(GREATER == CompareData((*T)->data, data))//在左子树寻找
        return DeleteTreeNode(&(*T)->lchild, data, CompareData);
    else
        return DeleteTreeNode(&(*T)->rchild, data, CompareData);
}


/*输出层次所需的空位及左右位置*/
static void PrintLayer(int layer, char pos)
{
    int i;
    for(i = 0; i < layer; ++i)
            printf("\t");

    printf("%c", pos);
}

/*****************************************************************************************
*@Name............: void FirstOrder(BinaryTree T, int layer, void (*visit)(ElemData data))
*@Description.....: 先序树状打印二叉树
*@Parameters......: T     : 平衡二叉树任意根节点
*                   layer : 层数
*                   visit : 访问函数
*@PreCondition....：无
*@PostCondition...：返回节点数目
*****************************************************************************************/
void FirstOrder(BinaryTree T, int layer, void (*visit)(ElemData data))
{
    if(!T)
        return ;

    printf("%d", layer);
    printf("|__");
    visit(T->data);
    printf("\n");

    if(T->lchild)//遍历左子树
    {
        PrintLayer(layer, 'L');
        FirstOrder(T->lchild, layer + 1, visit);
    }

    if(T->rchild)//遍历右子树
    {
        PrintLayer(layer, 'R');
        FirstOrder(T->rchild, layer + 1, visit);
    }
}

/*先序遍历*/
void PreOrderTraver(BinaryTree T)
{
    if(NULL == T)
        return;

    printf("%d ", T->data);

    if(T->lchild)
        PreOrderTraver(T->lchild);

    if(T->lchild)
        PreOrderTraver(T->rchild);
}

/*中序遍历*/
void InOrderTraver(BinaryTree T)
{
    if(NULL == T)
        return;

    if(T->lchild)
        InOrderTraver(T->lchild);

    printf("%d ", T->data);

    if(T->lchild)
        InOrderTraver(T->rchild);
}

/*倒序遍历*/
void BackTraver(BinaryTree T)
{
    if(NULL == T)
        return ;

    if(T->lchild)
        BackTraver(T->rchild);

     if(T->rchild)
        BackTraver(T->lchild);

    printf("%d ", T->data);
}

/*****************************************************************************************
*@Name............: Status LocateTree(BinaryTree T, ElemData key, struct TreeNodeAttribute* attribute, Status (*CompareData)(ElemData, ElemData))
*@Description.....: 定位二叉树，寻找关键字节点所在层数及位置
*@Parameters......: T            : 二叉树根节点
*                   attribute    : 节点属性
*@Return values...: OK   ：查找成功
*                   FAIL ：查找失败，不存在根节点
*@PreCondition....：存在树,layer默认为1
*@PostCondition...：无
*****************************************************************************************/
Status LocateTree(BinaryTree T, ElemData key, struct TreeNodeAttribute* attribute, Status (*CompareData)(ElemData, ElemData))
{
    while(T)
    {
        if(EQUAL == CompareData(T->data, key))
            return OK;
        else
        {
            attribute->layer++;
            if(GREATER == CompareData(T->data, key))
            {
                attribute->LorR = 'L';
                T = T->lchild;
            }
            else
            {
                attribute->LorR = 'R';
                T = T->rchild;
            }
        }
    }

    return FAIL;
}
