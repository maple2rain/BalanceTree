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
*@Description.....: Ϊ�����������½ڵ�
*@Parameters......: T            :���������ڵ�
*                   data         :����������
*                   CompareData  : �ȽϺ���
*@Return values...: OK ������ɹ�
*                   FAIL ������ʧ�ܣ������ǽڵ��Ѿ����ڻ��߶ѿռ䲻��
*@PreCondition....�������������������½���
*@PostCondition...������ڵ�
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
*@Description.....: �����Ƿ���ڸ�����
*@Parameters......: T           :���������ڵ�
*                   key         :Ҫ���ҵĹؼ���
*                   CompareData : �ȽϺ���
*@Return values...: OK�����ҳɹ���FAIL������ʧ��
*@PreCondition....��������
*@PostCondition...����
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
*@Description.....: ���ٶ�����
*@Parameters......: T   :���������ڵ�
*@Return values...: ��
*@PreCondition....��������
*@PostCondition...����
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
*@Description.....: ����������
*@Parameters......: T           : ���������ڵ�
*                   CompareData : �ȽϺ���
*                   select      : ��ʾ�Զ����ֶ�
*@Return values...: OK�������ɹ���FAIL������ʧ�ܣ�ԭ���Ƕѿռ䲻��
*@PreCondition....��������
*@PostCondition...����
*****************************************************************************************/
Status CreateTree(BinaryTree *T, Status (*CompareData)(ElemData, ElemData), int select)
{
    int data;
    int num;

    if(1 == select)//�Զ�
    {
        printf("���� '0'�˳�������Ҫ��������ͨ�������Ľڵ��������\n");
        scanf("%d", &num);
        while(num < 1)
        {
            if(0 == num)
                break;

            printf("���������������������룡���� '0'�˳���\n");
            scanf("%d", &num);
        }

        int i;
        for(i = 0; i < num; ++i)
        {
            data = rand() % INT_MAX;
            InsertTree(T, data, CompareData);
        }
    }

    if(2 == select)//�ֶ�
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
*@Description.....: ��ȡ�������ڵ���
*@Parameters......: T     : ƽ����������ڵ�
*@PreCondition....����
*@PostCondition...�����ؽڵ���Ŀ
*****************************************************************************************/
int GetNumOfNode(BinaryTree T)
{
    int leftNum, rightNum;

    if(!T)
        return 0;
    else
    {
        /*
        **�ֱ��ȡ���������Ľڵ���
        */
        leftNum = GetNumOfNode(T->lchild);
        rightNum = GetNumOfNode(T->rchild);
    }

    return leftNum + rightNum + 1;//���������ڵ��������������ܽڵ���
}

/*****************************************************************************************
*@Name............: int GetTreeDepth(BinaryTree T)
*@Description.....: ��ȡ���������
*@Parameters......: T     : ƽ����������ڵ�
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
int GetTreeDepth(BinaryTree T)
{
    int depthLeft, depthRight;

    if(!T)
        return 0;
    else
    {
        /*
        **�ֱ��ȡ�����������
        */
        depthLeft = GetTreeDepth(T->lchild);
        depthRight = GetTreeDepth(T->rchild);

        return 1 + (depthLeft > depthRight ? depthLeft : depthRight);//ȡ������������ټ��������������
    }
}

/*****************************************************************************************
*@Name............: static void InOrderK(BinaryTree T, int *count, int k, ElemData *data)
*@Description.....: �ݹ���������ȡ��k���Ԫ��
*@Parameters......: T     : ƽ����������ڵ�
*                   count : ��������
*                   data  : ���ݴ洢�ڴ�
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
static void InOrderK(BinaryTree T, int *count, int k, ElemData *data)
{
    if(T->lchild)//����*count != 1���ж���������������Ч�ĵݹ�
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
*@Description.....: ��ȡ��k���Ԫ��
*@Parameters......: T     : ƽ����������ڵ�
*                   k     : Ѱ�ҵ�����
*                   data  : ���ݴ洢�ڴ�
*@return..........: OK: �ҵ��ùؼ��� FAIL:������������
*@PreCondition....����������k��Ŀ������ȷ
*@PostCondition...��data��ȡ����k���ֵ
*****************************************************************************************/
Status GetNumberK(BinaryTree T, int k, ElemData *data)
{
    if(!T)
    {
        printf("�ö����������ڣ�\n");
        return  FAIL;
    }

    if(k < 1)
    {
        printf("kȡֵ����Ӧ����0��\n");
        return FAIL;
    }

    int count = 1;
    InOrderK(T, &count, k, data);

    if(k > 1 && count <= k)//kֵ����
    {
        printf("kȡֵ����\n");
        return FAIL;
    }

    return OK;
}

/*****************************************************************************************
*@Name............: static void DeleteNode(BinaryTree *toDel)
*@Description.....: ����ɾ���ڵ�
*@Parameters......: toDel :Ҫɾ���Ľڵ�
*@return..........: void
*@PreCondition....��Ҫɾ���Ľڵ��Ѿ��ҵ���
*@PostCondition...��ɾ���и�ֵ�Ľڵ�
*****************************************************************************************/
static void DeleteNode(BinaryTree *toDel)
{
    BinaryTree tmp, front;
    if(NULL == (*toDel)->rchild)
    {
        tmp = *toDel;
        *toDel = (*toDel)->lchild;
        free(tmp);
    }//����������
    else if(NULL == (*toDel)->lchild)
    {
        tmp = *toDel;
        *toDel = (*toDel)->rchild;
        free(tmp);
    }//����������
    else
    {
        tmp = *toDel;
        front = (*toDel)->lchild;

        while(front->rchild)//��Ѱǰ��
        {
            tmp = front;
            front = front->rchild;
        }
        (*toDel)->data = front->data;

        if(tmp != (*toDel))//����������
            tmp->rchild = front->lchild;
        else
            tmp->lchild = front->lchild;

        free(front);
    }
}

/*****************************************************************************************
*@Name............: Status DeleteTreeNode(BinaryTree *T, ElemData data, Status (*CompareData)(ElemData, ElemData))
*@Description.....: ɾ������data�Ľڵ�
*@Parameters......: T     : ƽ����������ڵ�
*                   data  : ���и����ݵĽڵ㽫�ᱻɾ��
*                   CompareData : �ȽϺ���
*@return..........: OK:���ڸùؼ���  FAIL:�����ڸùؼ���
*@PostCondition...��ɾ���и�ֵ�Ľڵ�
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
    else if(GREATER == CompareData((*T)->data, data))//��������Ѱ��
        return DeleteTreeNode(&(*T)->lchild, data, CompareData);
    else
        return DeleteTreeNode(&(*T)->rchild, data, CompareData);
}


/*����������Ŀ�λ������λ��*/
static void PrintLayer(int layer, char pos)
{
    int i;
    for(i = 0; i < layer; ++i)
            printf("\t");

    printf("%c", pos);
}

/*****************************************************************************************
*@Name............: void FirstOrder(BinaryTree T, int layer, void (*visit)(ElemData data))
*@Description.....: ������״��ӡ������
*@Parameters......: T     : ƽ�������������ڵ�
*                   layer : ����
*                   visit : ���ʺ���
*@PreCondition....����
*@PostCondition...�����ؽڵ���Ŀ
*****************************************************************************************/
void FirstOrder(BinaryTree T, int layer, void (*visit)(ElemData data))
{
    if(!T)
        return ;

    printf("%d", layer);
    printf("|__");
    visit(T->data);
    printf("\n");

    if(T->lchild)//����������
    {
        PrintLayer(layer, 'L');
        FirstOrder(T->lchild, layer + 1, visit);
    }

    if(T->rchild)//����������
    {
        PrintLayer(layer, 'R');
        FirstOrder(T->rchild, layer + 1, visit);
    }
}

/*�������*/
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

/*�������*/
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

/*�������*/
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
*@Description.....: ��λ��������Ѱ�ҹؼ��ֽڵ����ڲ�����λ��
*@Parameters......: T            : ���������ڵ�
*                   attribute    : �ڵ�����
*@Return values...: OK   �����ҳɹ�
*                   FAIL ������ʧ�ܣ������ڸ��ڵ�
*@PreCondition....��������,layerĬ��Ϊ1
*@PostCondition...����
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
