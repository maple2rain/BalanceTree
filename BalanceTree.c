/***************************************************************************************
 *	File Name				:	BalanceTree.c
 *	CopyRight				:	LPF
 *	ModuleName				:	BalanceTree
 *
 *	CPU						:   Inter Core 7
 *	RTOS					:
 *
 *	Create Data				:	2015/11/20
 *	Author/Corportation		:	Li PeiFeng
 *
 *	Abstract Description	:	definite the function for BalanceTree
 *
 *--------------------------------Revision History--------------------------------------
 *	No	version		Data		Revised By			Item			Description
 *
 *
 ***************************************************************************************/

/****************************************************************************************
*	Include File Section
****************************************************************************************/
#include "BalanceTree.h"
#include <windows.h>

/****************************************************************************************
*	Function Define Section
****************************************************************************************/
/****************************************************************************************
*@Name............: static void R_Rotate(BiTree *p)
*@Description.....: 右旋处理
*@Parameters......: p   :二叉树的待旋转根节点
*@Return values...: void
*@PreCondition....：无
*@PostCondition...：进行右旋时，根节点的左子树的右子树作为根节点的左子树，
*                   然后根节点作为根节点的左子树的右子树
*                   最后根节点又重新指向原来根节点的左子树
*****************************************************************************************/
static void R_Rotate(BiTree *p)
{
    BiTree L;

    L = (*p)->lchild;           //L指向p的左子树的根节点
    (*p)->lchild = L->rchild;   //L的右子树作为p的左子树
    L->rchild = (*p);           //p作为L的右子树
    *p = L;                     //p指向新的节点
}

/*****************************************************************************************
*@Name............: static void L_Rotate(BiTree *p)
*@Description.....: 左旋处理
*@Parameters......: p   :二叉树的待旋转根节点
*@Return values...: void
*@PreCondition....：无
*@PostCondition...：进行左旋时，根节点的右子树的左子树作为根节点的右子树，
*                   然后根节点作为根节点的右子树的左子树
*                   最后根节点又重新指向原来根节点的右子树
*****************************************************************************************/
static void L_Rotate(BiTree *p)
{
    BiTree R;

    R = (*p)->rchild;
    (*p)->rchild = R->lchild;
    R->lchild = (*p);
    *p = R;
}

/****************************************************************************************
*@Name............: static void LeftBalance(BiTree *T)
*@Description.....: 左平衡旋转处理
*@Parameters......: T   :二叉树的待旋转根节点
*@Return values...: void
*@PreCondition....：被调用时已经确认子树不是平衡状态了
*@PostCondition...：检查左子树平衡度并作相应处理
*****************************************************************************************/
static void LeftBalance(BiTree *T)
{
    BiTree L, Lr;

    L = (*T)->lchild;       //L指向T的左子树根节点

    switch(L->bf)//检查T的左子树的平衡度，并作相应的平衡处理
    {
        case LH:            //新结点插入在T的左孩子的左子树上，做单右旋处理
            (*T)->bf = L->bf = EH;
            R_Rotate(T);
            break;

        case RH:
            Lr = L->rchild;//Lr指向T的左孩子的右子树根
            switch(Lr->bf)
            {
                case LH://如若左子树高，旋转后该节点等高，父节点右高
                    (*T)->bf = RH;
                    L->bf = EH;
                    break;

                case EH://如若等高，旋转后仍等高
                    (*T)->bf = L->bf = EH;
                    break;

                case RH://如若右高，旋转后该节点等高，父节点左高
                    (*T)->bf = EH;
                    L->bf = LH;
                    break;
            }

            Lr->bf = EH;
			/*先左旋后右旋*/
            L_Rotate(&(*T)->lchild);
            R_Rotate(T);
    }
}

/*****************************************************************************************
*@Name............: static void ReftBalance(BiTree *T)
*@Description.....: 右平衡旋转处理
*@Parameters......: T   :二叉树的待旋转根节点
*@Return values...: void
*@PreCondition....：被调用时已经确认子树不是平衡状态了
*@PostCondition...：检查左子树平衡度并作相应处理
*****************************************************************************************/
static void RightBalance(BiTree *T)
{
    BiTree R, Rl;

    R = (*T)->rchild;

    switch(R->bf)//检查T的右子树的平衡度，并作相应的平衡处理
    {
        case RH://新节点在右子树的右孩子上，做单左旋处理
            (*T)->bf = R->bf = EH;
            L_Rotate(T);
            break;

        case LH:
            Rl = R->lchild;//Rl指向T的右孩子的左孩子
            switch(Rl->bf)
            {
                case RH://如若右子树高，旋转后该节点等高，父节点左高
                    (*T)->bf = LH;
                    R->bf = EH;
                    break;

                case EH://如若等高，旋转后仍等高
                    (*T)->bf = R->bf = EH;
                    break;

                case LH:
                    (*T)->bf = EH;
                    R->bf = RH;
                    break;
            }

        Rl->bf = EH;
		/*先右旋后左旋*/
        R_Rotate(&(*T)->rchild);
        L_Rotate(T);
    }
}

/****************************************************************************************
*@Name............: static Status InsertAVL(BiTree *T, ElemData data, Status *taller, Status (*CompareData)(ElemData, ElemData))
*@Description.....: 插入节点操作
*@Parameters......: T           : 二叉树的待旋转根节点
*                   data        : 待插入数据
*                   taller      : 判断树是否增高
*                   CompareData : 比较函数
*@Return values...: OK 插入成功 FAIL:插入失败
*@PreCondition....：被调用时已经确认子树不是平衡状态了
*@PostCondition...：检查左子树平衡度并作相应处理
*****************************************************************************************/
static Status InsertAVL(BiTree *T, ElemData data, Status *taller, Status (*CompareData)(ElemData, ElemData))
{
    if(!*T)
    {//插入新节点，树长高，置taller为TRUE
        *T = (BiTree)malloc(sizeof(BiTNode));
        if(NULL == *T)
            return FAIL;

        (*T)->data = data;
        (*T)->lchild = (*T)->rchild = NULL;
        (*T)->bf = EH;
        *taller = TRUE;
    }
    else
    {
        if(EQUAL == CompareData((*T)->data, data))
        {
            *taller = FALSE;
            return FAIL;
        }
        else if(GREATER == CompareData((*T)->data, data))
        {
            if(FAIL == InsertAVL(&(*T)->lchild, data, taller, CompareData))//继续在左子树中查找
                return FAIL;

            if(TRUE == *taller)
            {
                switch((*T)->bf)
                {
                    case LH:
                        LeftBalance(T);//原本左子树比右子树高，需要作左平衡处理
                        *taller = FALSE;
                        break;

                    case EH:
                        (*T)->bf = LH;//原本左右子树等高，现左子树增高
                        *taller = TRUE;
                        break;

                    case RH:
                        (*T)->bf = EH;//原本右子树比较高，现左右子树等高
                        *taller = FALSE;
                        break;
                }
            }//end of "if(TRUE == *taller)"
        }//end of "else if(data < (*T)->data)"
        else
        {//在右子树中进行搜索
            if(FAIL == InsertAVL(&(*T)->rchild, data, taller, CompareData))
                return FAIL;

            if(TRUE == *taller)
            {
                switch((*T)->bf)
                {
                    case LH:
                        (*T)->bf = EH;
                        *taller = FALSE;
                        break;

                    case EH:
                        (*T)->bf = RH;
                        *taller = TRUE;
                        break;

                    case RH:
                        RightBalance(T);
                        *taller = FALSE;
                        break;
                }
            }//end of "if(TRUE == *taller)"
        }//end of "else"
    }
    return OK;
}

/*****************************************************************************************
*@Name............: Status InsertBTree(BiTree *T, ElemData data, Status (*CompareData)(ElemData, ElemData))
*@Description.....: 为平衡二叉树插入新节点
*@Parameters......: T            :二叉树根节点
*                   data         :待插入数据
*                   CompareData  : 比较函数
*@Return values...: OK ：插入成功
*                   FAIL ：插入失败，可能是节点已经存在或者堆空间不足
*@PreCondition....：存在树，不存在则新建树
*@PostCondition...：插入节点
*****************************************************************************************/
Status InsertBTree(BiTree *T, ElemData data, Status (*CompareData)(ElemData, ElemData))
{
    Status taller = FALSE;
    return InsertAVL(T, data, &taller, CompareData);
}
/****************************************************************************************
*@Name............: Status SearchBTree(BiTree T, ElemData key, Status (*CompareData)(ElemData, ElemData))
*@Description.....: 查找是否存在该数据
*@Parameters......: T           :二叉树根节点
*                   key         :要查找的关键字
*                   CompareData : 比较函数
*@Return values...: OK：查找成功；FAIL：查找失败
*@PreCondition....：存在树
*@PostCondition...：无
*****************************************************************************************/
Status SearchBTree(BiTree T, ElemData key, Status (*CompareData)(ElemData, ElemData))
{
    while(T)
    {
        if(EQUAL == CompareData(T->data, key))
            return OK;
        else if(GREATER == CompareData(T->data, key))//根节点数据大则往左子树搜索
            T = T->lchild;
        else//否则往右子树搜索
            T = T->rchild;
    }

    return FAIL;
}

/*****************************************************************************************
*@Name............: void DestroyBTree(BiTree *T)
*@Description.....: 销毁二叉树
*@Parameters......: T   :二叉树根节点
*@Return values...: 无
*@PreCondition....：存在树
*@PostCondition...：无
*****************************************************************************************/
void DestroyBTree(BiTree *T)
{
    if(!*T)
        return ;

	DestroyBTree(&(*T)->lchild);

	DestroyBTree(&(*T)->rchild);

    free(*T);
    *T = NULL;
}

/*****************************************************************************************
*@Name............: Status CreateBTree(BiTree *T, Status (*CompareData)(ElemData, ElemData), int select)
*@Description.....: 构建二叉树
*@Parameters......: T           : 二叉树根节点
*                   CompareData : 比较函数
*                   select      : 表示自动或手动
*@Return values...: OK：创建成功；FAIL：创建失败，原因是堆空间不足
*@PreCondition....：存在树
*@PostCondition...：无
*****************************************************************************************/
Status CreateBTree(BiTree *T, Status (*CompareData)(ElemData, ElemData), int select)
{
    int data;
    int num;

    if(1 == select)//自动
    {
        printf("输入 '0'退出！输入要创建的平衡二叉树的节点的数量：\n");
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
            InsertBTree(T, data, CompareData);
        }
    }

    if(2 == select)//手动
    {
        printf("end with \'-1\'\n");
        scanf("%d", &data);

        while(-1 != data)
        {
            InsertBTree(T, data, CompareData);
            scanf("%d", &data);
        }
    }

    if(!T)
        return FAIL;
    else
        return OK;
}

/*****************************************************************************************
*@Name............: static void DelLeftBalance(BiTree *p, Status *shorter)
*@Description.....: 左平衡旋转处理
*@Parameters......: p     : 二叉树的待旋转根节点
*                   shorte: 判断子树是否已经变矮
*@Return values...: void
*@PreCondition....：当删除节点，该函数被调用时要确认子树不是平衡状态了
*@PostCondition...：检查左子树平衡度并作相应处理
*****************************************************************************************/
static void DelLeftBalance(BiTree *p, Status *shorter)
{
	BiTree p1,p2;

	if((*p)->bf == LH) //(*p)结点的左子树高，删除结点后(*p)的bf减1,树变矮
	{
		(*p)->bf = EH;
		*shorter = TRUE;
	}
	else if((*p)->bf == EH)//(*p)结点左、右子树等高，删除结点后(*p)的bf减1,树高不变
	{
		(*p)->bf = RH;
		*shorter = FALSE;
	}
	else //(*p)结点的右子树高
	{
		p1 = (*p)->rchild;//p1指向p的右子树
		if(p1->bf == EH)//p1结点左、右子树等高,删除结点后p的bf为-2,进行左旋处理，树高不变
		{
            p1->bf = LH;
			(*p)->bf = RH;
			L_Rotate(p);
			*shorter = FALSE;
		}
		else if(p1->bf == RH)//p1的右子树高，左旋处理后，树变矮
		{
		    p1->bf = (*p)->bf = EH;
			L_Rotate(p);
			*shorter = TRUE;
		}
		else //p1的左子树高,进行双旋处理(先右旋后左旋)，树变矮
		{
            /*双旋处理*/
			p2 = p1->lchild;
//			p1->lchild = p2->rchild;
//			p2->rchild = p1;
//			(*p)->rchild = p2->lchild;
//			p2->lchild = *p;

			if(p2->bf == EH)
			{
				(*p)->bf = EH;
				p1->bf = EH;
			}
			else if(p2->bf == RH)
			{
				(*p)->bf = LH;
				p1->bf = EH;
			}
			else
			{
				(*p)->bf = EH;
				p1->bf = RH;
			}

			p2->bf = EH;
            /*双旋处理,先右后左*/
			R_Rotate(&(*p)->rchild);
			L_Rotate(p);
			*shorter = TRUE;
		}
	}
}

/*****************************************************************************************
*@Name............: static void DelRightBalance(BiTree *p, Status *shorter)
*@Description.....: 右平衡旋转处理
*@Parameters......: p     : 二叉树的待旋转根节点
*                   shorte: 判断子树是否已经变矮
*@PreCondition....：当删除节点，该函数被调用时要确认子树不是平衡状态了
*@PostCondition...：检查左子树平衡度并作相应处理
*****************************************************************************************/
static void DelRightBalance(BiTree *p, Status *shorter)
{
	BiTree p1, p2;
	if((*p)->bf == RH)//(*p)结点右子树高，删除结点后(*p)的bf减1,树变矮
	{
		(*p)->bf = EH;
		*shorter = TRUE;
	}
	else if((*p)->bf == EH)//(*p)结点左、右子树等高，删除结点后(*p)的bf减1,树高不变
	{
		(*p)->bf = LH;
		*shorter = FALSE;
	}
	else//(*p)结点的左子树高
	{
		p1 = (*p)->lchild;//p1指向p的左子树

		if(p1->bf == EH)//p1结点左、右子树等高,删除结点后p的bf为-2,进行右旋处理，树高不变
		{
		    p1->bf = RH;
			(*p)->bf = LH;
			R_Rotate(p);
			*shorter = FALSE;
		}
		else if(p1->bf == LH)//p1节点左子树高，进行右旋处理即平衡，树变矮
		{
            p1->bf = (*p)->bf = EH;
			R_Rotate(p);
			*shorter = TRUE;
		}
		else//p1的右子树高,进行双旋处理(先左旋后右旋)，树变矮
		{
		    /*双旋处理*/
			p2 = p1->rchild;
//			p1->rchild = p2->lchild;
//			p2->lchild = p1;
//			(*p)->lchild = p2->rchild;
//			p2->rchild = *p;

			if(p2->bf == EH)
			{
				(*p)->bf = EH;
				p1->bf = EH;
			}
			else if(p2->bf == LH)
			{
				(*p)->bf = RH;
				p1->bf = EH;
			}
			else
			{
				(*p)->bf = EH;
				p1->bf = LH;
			}

			p2->bf = EH;

			/*双旋处理,先左后右*/
			L_Rotate(&(*p)->lchild);
			R_Rotate(p);
			*shorter = TRUE;
		}
	}
}

/*****************************************************************************************
*@Name............: static void Delete(BiTree q, BiTree *r, Status *shorter)
*@Description.....: 删除节点操作
*@Parameters......: q     : 待删除节点
*                   r     : 节点q的左子树，作为普通删除操作的节点
*                   shorte: 判断子树是否已经变矮
*@PreCondition....：当删除节点，该函数被调用时要确认子树不是平衡状态了
*@PostCondition...：检查左子树平衡度并作相应处理
*****************************************************************************************/
static void Delete(BiTree q, BiTree *r, Status *shorter)
{
	if(NULL == (*r)->rchild)
	{
	    //与普通二叉树删除相同，删除最右子树
		q->data = (*r)->data;
		q = *r;
		*r = (*r)->lchild;
		free(q);
		*shorter = TRUE;
	}
	else
	{
	    //持续寻找最最右子树
		Delete(q, &(*r)->rchild, shorter);
		if(*shorter == TRUE)
			DelRightBalance(r, shorter);//平衡处理
	}
}

/*****************************************************************************************
*@Name............: static Status DeleteAVL(BiTree *p, ElemData data, Status *shorter)
*@Description.....: 删除节点操作
*@Parameters......: p     : 待删除节点
*                   data  : 含有该数据的节点将会被删除
*                   shorte: 判断子树是否已经变矮
*                   CompareData : 比较函数
*@return..........: OK:存在该关键字  FAIL:不存在该关键字
*@PreCondition....：当删除节点，该函数被调用时要确认子树不是平衡状态了
*@PostCondition...：检查左子树平衡度并作相应处理
*****************************************************************************************/
static Status DeleteAVL(BiTree *p, ElemData data, Status *shorter, Status (*CompareData)(ElemData, ElemData))
{
	Status status;
	BiTree q;
	if(*p == NULL)
	{
		printf("不存在要删除的关键字!!\n");
		return FAIL;
	}
	else if(GREATER == CompareData((*p)->data, data))//在p的左子树中进行删除
	{
		status = DeleteAVL(&((*p)->lchild), data, shorter, CompareData);

		if(*shorter == TRUE)
			DelLeftBalance(p, shorter);

		return status;
	}
	else if(LESS == CompareData((*p)->data, data))//在p的右子树中进行删除
	{
		status = DeleteAVL(&((*p)->rchild), data, shorter, CompareData);

		if(*shorter == TRUE)
			DelRightBalance(p, shorter);

		return status;
	}
	else
	{
		q = *p;
		if((*p)->rchild == NULL) //右子树空则只需重接它的左子树
		{
			*p = (*p)->lchild;
			free(q);
			*shorter = TRUE;
		}
		else if((*p)->lchild == NULL)//左子树空则只需重接它的右子树
		{
			(*p) = (*p)->rchild;
			free(q);
			*shorter = TRUE;
		}
		else//左右子树均不空
		{
			Delete(q, &(q->lchild), shorter);/*这里有bug，q与p指向同一地方，改变p后也改变q*/
			if(*shorter == TRUE)
				DelLeftBalance(p, shorter);

			//*p = q;
			/*bug已修复，因为平衡旋转后便无需再改变根节点的位置了*/
		}
		return OK;
	}
}

/*****************************************************************************************
*@Name............: Status DeleteBTreeNode(BiTree *T, ElemData data, Status (*CompareData)(ElemData, ElemData))
*@Description.....: 删除节点操作，外部接口
*@Parameters......: T     : 平衡二叉树根节点
*                   data  : 含有该数据的节点将会被删除
*                   CompareData : 比较函数
*@return..........: OK:存在该关键字  FAIL:不存在该关键字
*@PreCondition....：比较函数正确且树存在
*@PostCondition...：若关键字存在于树中则被删除，否则报错
*****************************************************************************************/
Status DeleteBTreeNode(BiTree *T, ElemData data, Status (*CompareData)(ElemData, ElemData))
{
    Status shorter = FALSE;
    return DeleteAVL(T, data, &shorter, CompareData);
}

/*****************************************************************************************
*@Name............: int GetBTreeDepth(BiTree T)
*@Description.....: 获取二叉树深度
*@Parameters......: T     : 平衡二叉树根节点
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
int GetBTreeDepth(BiTree T)
{
    int depthLeft, depthRight;

    if(!T)
        return 0;
    else
    {
        /*
        **分别获取左右子树深度
        */
        depthLeft = GetBTreeDepth(T->lchild);
        depthRight = GetBTreeDepth(T->rchild);

        return 1 + (depthLeft > depthRight ? depthLeft : depthRight);//取最深子树深度再加上自身即是总深度
    }
}

/*****************************************************************************************
*@Name............: static void InOrderK(BiTree T, int *count, int k, ElemData *data)
*@Description.....: 递归中序辅助获取第k大的元素
*@Parameters......: T     : 平衡二叉树根节点
*                   count : 辅助计数
*                   data  : 数据存储于此
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
static void InOrderK(BiTree T, int *count, int k, ElemData *data)
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
*@Name............: Status BGetNumberK(BiTree T, int k, ElemData *data)
*@Description.....: 获取第k大的元素
*@Parameters......: T     : 平衡二叉树根节点
*                   k     : 寻找的序数
*                   data  : 数据存储于此
*@return..........: OK: 找到该关键字 FAIL:参数输入有误
*@PreCondition....：树存在且k数目输入正确
*@PostCondition...：data获取到第k大的值
*****************************************************************************************/
Status BGetNumberK(BiTree T, int k, ElemData *data)
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
*@Name............: int GetNumOfBNode(BiTree T)
*@Description.....: 获取二叉树节点数
*@Parameters......: T     : 平衡二叉树根节点
*@PreCondition....：无
*@PostCondition...：返回节点数目
*****************************************************************************************/
int GetNumOfBNode(BiTree T)
{
    int leftNum, rightNum;

    if(!T)
        return 0;
    else
    {
        /*
        **分别获取左右子树的节点数
        */
        leftNum = GetNumOfBNode(T->lchild);
        rightNum = GetNumOfBNode(T->rchild);
    }

    return leftNum + rightNum + 1;//左右子树节点数加上自身即是总节点数
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
*@Name............: void FirstOrderTraverse(BiTree T, int layer, void (*visit)(ElemData data))
*@Description.....: 先序树状打印二叉树
*@Parameters......: T     : 平衡二叉树任意根节点
*                   layer : 层数
*                   visit : 访问函数
*@PreCondition....：无
*@PostCondition...：返回节点数目
*****************************************************************************************/
void FirstOrderTraverse(BiTree T, int layer, void (*visit)(ElemData data))
{
    if(!T)
        return ;

    printf("%d", layer);
    printf("|__");
    visit(T->data);
    printf(" (%d)\n", T->bf);

    if(T->lchild)//遍历左子树
    {
        PrintLayer(layer, 'L');
        FirstOrderTraverse(T->lchild, layer + 1, visit);
    }

    if(T->rchild)//遍历右子树
    {
        PrintLayer(layer, 'R');
        FirstOrderTraverse(T->rchild, layer + 1, visit);
    }
}

/*先序遍历*/
void PreOrderTraverse(BiTree T)
{
    if(NULL == T)
        return;

    printf("%d ", T->data);

    if(T->lchild)
        PreOrderTraverse(T->lchild);

    if(T->rchild)
        PreOrderTraverse(T->rchild);
}

/*中序遍历*/
void InOrderTraverse(BiTree T)
{
    if(NULL == T)
        return;
    if(T->lchild)
        InOrderTraverse(T->lchild);

    printf("%d ", T->data);

    if(T->rchild)
        InOrderTraverse(T->rchild);
}

/*倒序遍历*/
void BackTraverse(BiTree T)
{
    if(NULL == T)
        return ;
    if(T->lchild)
        BackTraverse(T->rchild);

    if(T->rchild)
        BackTraverse(T->lchild);

    printf("%d ", T->data);
}

/*****************************************************************************************
*@Name............: Status LocateBTree(BiTree T, ElemData key, struct TreeNodeAttribute* attribute, Status (*CompareData)(ElemData, ElemData))
*@Description.....: 定位二叉树，寻找关键字节点所在层数及位置
*@Parameters......: T            : 二叉树根节点
*                   attribute    : 节点属性
*@Return values...: OK   ：查找成功
*                   FAIL ：查找失败，不存在根节点
*@PreCondition....：存在树,layer默认为1
*@PostCondition...：无
*****************************************************************************************/
Status LocateBTree(BiTree T, ElemData key, struct TreeNodeAttribute* attribute, Status (*CompareData)(ElemData, ElemData))
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
