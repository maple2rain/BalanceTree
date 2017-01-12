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
*@Description.....: ��������
*@Parameters......: p   :�������Ĵ���ת���ڵ�
*@Return values...: void
*@PreCondition....����
*@PostCondition...����������ʱ�����ڵ������������������Ϊ���ڵ����������
*                   Ȼ����ڵ���Ϊ���ڵ����������������
*                   �����ڵ�������ָ��ԭ�����ڵ��������
*****************************************************************************************/
static void R_Rotate(BiTree *p)
{
    BiTree L;

    L = (*p)->lchild;           //Lָ��p���������ĸ��ڵ�
    (*p)->lchild = L->rchild;   //L����������Ϊp��������
    L->rchild = (*p);           //p��ΪL��������
    *p = L;                     //pָ���µĽڵ�
}

/*****************************************************************************************
*@Name............: static void L_Rotate(BiTree *p)
*@Description.....: ��������
*@Parameters......: p   :�������Ĵ���ת���ڵ�
*@Return values...: void
*@PreCondition....����
*@PostCondition...����������ʱ�����ڵ������������������Ϊ���ڵ����������
*                   Ȼ����ڵ���Ϊ���ڵ����������������
*                   �����ڵ�������ָ��ԭ�����ڵ��������
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
*@Description.....: ��ƽ����ת����
*@Parameters......: T   :�������Ĵ���ת���ڵ�
*@Return values...: void
*@PreCondition....��������ʱ�Ѿ�ȷ����������ƽ��״̬��
*@PostCondition...�����������ƽ��Ȳ�����Ӧ����
*****************************************************************************************/
static void LeftBalance(BiTree *T)
{
    BiTree L, Lr;

    L = (*T)->lchild;       //Lָ��T�����������ڵ�

    switch(L->bf)//���T����������ƽ��ȣ�������Ӧ��ƽ�⴦��
    {
        case LH:            //�½�������T�����ӵ��������ϣ�������������
            (*T)->bf = L->bf = EH;
            R_Rotate(T);
            break;

        case RH:
            Lr = L->rchild;//Lrָ��T�����ӵ���������
            switch(Lr->bf)
            {
                case LH://�����������ߣ���ת��ýڵ�ȸߣ����ڵ��Ҹ�
                    (*T)->bf = RH;
                    L->bf = EH;
                    break;

                case EH://�����ȸߣ���ת���Եȸ�
                    (*T)->bf = L->bf = EH;
                    break;

                case RH://�����Ҹߣ���ת��ýڵ�ȸߣ����ڵ����
                    (*T)->bf = EH;
                    L->bf = LH;
                    break;
            }

            Lr->bf = EH;
			/*������������*/
            L_Rotate(&(*T)->lchild);
            R_Rotate(T);
    }
}

/*****************************************************************************************
*@Name............: static void ReftBalance(BiTree *T)
*@Description.....: ��ƽ����ת����
*@Parameters......: T   :�������Ĵ���ת���ڵ�
*@Return values...: void
*@PreCondition....��������ʱ�Ѿ�ȷ����������ƽ��״̬��
*@PostCondition...�����������ƽ��Ȳ�����Ӧ����
*****************************************************************************************/
static void RightBalance(BiTree *T)
{
    BiTree R, Rl;

    R = (*T)->rchild;

    switch(R->bf)//���T����������ƽ��ȣ�������Ӧ��ƽ�⴦��
    {
        case RH://�½ڵ������������Һ����ϣ�������������
            (*T)->bf = R->bf = EH;
            L_Rotate(T);
            break;

        case LH:
            Rl = R->lchild;//Rlָ��T���Һ��ӵ�����
            switch(Rl->bf)
            {
                case RH://�����������ߣ���ת��ýڵ�ȸߣ����ڵ����
                    (*T)->bf = LH;
                    R->bf = EH;
                    break;

                case EH://�����ȸߣ���ת���Եȸ�
                    (*T)->bf = R->bf = EH;
                    break;

                case LH:
                    (*T)->bf = EH;
                    R->bf = RH;
                    break;
            }

        Rl->bf = EH;
		/*������������*/
        R_Rotate(&(*T)->rchild);
        L_Rotate(T);
    }
}

/****************************************************************************************
*@Name............: static Status InsertAVL(BiTree *T, ElemData data, Status *taller, Status (*CompareData)(ElemData, ElemData))
*@Description.....: ����ڵ����
*@Parameters......: T           : �������Ĵ���ת���ڵ�
*                   data        : ����������
*                   taller      : �ж����Ƿ�����
*                   CompareData : �ȽϺ���
*@Return values...: OK ����ɹ� FAIL:����ʧ��
*@PreCondition....��������ʱ�Ѿ�ȷ����������ƽ��״̬��
*@PostCondition...�����������ƽ��Ȳ�����Ӧ����
*****************************************************************************************/
static Status InsertAVL(BiTree *T, ElemData data, Status *taller, Status (*CompareData)(ElemData, ElemData))
{
    if(!*T)
    {//�����½ڵ㣬�����ߣ���tallerΪTRUE
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
            if(FAIL == InsertAVL(&(*T)->lchild, data, taller, CompareData))//�������������в���
                return FAIL;

            if(TRUE == *taller)
            {
                switch((*T)->bf)
                {
                    case LH:
                        LeftBalance(T);//ԭ�����������������ߣ���Ҫ����ƽ�⴦��
                        *taller = FALSE;
                        break;

                    case EH:
                        (*T)->bf = LH;//ԭ�����������ȸߣ�������������
                        *taller = TRUE;
                        break;

                    case RH:
                        (*T)->bf = EH;//ԭ���������Ƚϸߣ������������ȸ�
                        *taller = FALSE;
                        break;
                }
            }//end of "if(TRUE == *taller)"
        }//end of "else if(data < (*T)->data)"
        else
        {//���������н�������
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
*@Description.....: Ϊƽ������������½ڵ�
*@Parameters......: T            :���������ڵ�
*                   data         :����������
*                   CompareData  : �ȽϺ���
*@Return values...: OK ������ɹ�
*                   FAIL ������ʧ�ܣ������ǽڵ��Ѿ����ڻ��߶ѿռ䲻��
*@PreCondition....�������������������½���
*@PostCondition...������ڵ�
*****************************************************************************************/
Status InsertBTree(BiTree *T, ElemData data, Status (*CompareData)(ElemData, ElemData))
{
    Status taller = FALSE;
    return InsertAVL(T, data, &taller, CompareData);
}
/****************************************************************************************
*@Name............: Status SearchBTree(BiTree T, ElemData key, Status (*CompareData)(ElemData, ElemData))
*@Description.....: �����Ƿ���ڸ�����
*@Parameters......: T           :���������ڵ�
*                   key         :Ҫ���ҵĹؼ���
*                   CompareData : �ȽϺ���
*@Return values...: OK�����ҳɹ���FAIL������ʧ��
*@PreCondition....��������
*@PostCondition...����
*****************************************************************************************/
Status SearchBTree(BiTree T, ElemData key, Status (*CompareData)(ElemData, ElemData))
{
    while(T)
    {
        if(EQUAL == CompareData(T->data, key))
            return OK;
        else if(GREATER == CompareData(T->data, key))//���ڵ����ݴ���������������
            T = T->lchild;
        else//����������������
            T = T->rchild;
    }

    return FAIL;
}

/*****************************************************************************************
*@Name............: void DestroyBTree(BiTree *T)
*@Description.....: ���ٶ�����
*@Parameters......: T   :���������ڵ�
*@Return values...: ��
*@PreCondition....��������
*@PostCondition...����
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
*@Description.....: ����������
*@Parameters......: T           : ���������ڵ�
*                   CompareData : �ȽϺ���
*                   select      : ��ʾ�Զ����ֶ�
*@Return values...: OK�������ɹ���FAIL������ʧ�ܣ�ԭ���Ƕѿռ䲻��
*@PreCondition....��������
*@PostCondition...����
*****************************************************************************************/
Status CreateBTree(BiTree *T, Status (*CompareData)(ElemData, ElemData), int select)
{
    int data;
    int num;

    if(1 == select)//�Զ�
    {
        printf("���� '0'�˳�������Ҫ������ƽ��������Ľڵ��������\n");
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
            InsertBTree(T, data, CompareData);
        }
    }

    if(2 == select)//�ֶ�
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
*@Description.....: ��ƽ����ת����
*@Parameters......: p     : �������Ĵ���ת���ڵ�
*                   shorte: �ж������Ƿ��Ѿ��䰫
*@Return values...: void
*@PreCondition....����ɾ���ڵ㣬�ú���������ʱҪȷ����������ƽ��״̬��
*@PostCondition...�����������ƽ��Ȳ�����Ӧ����
*****************************************************************************************/
static void DelLeftBalance(BiTree *p, Status *shorter)
{
	BiTree p1,p2;

	if((*p)->bf == LH) //(*p)�����������ߣ�ɾ������(*p)��bf��1,���䰫
	{
		(*p)->bf = EH;
		*shorter = TRUE;
	}
	else if((*p)->bf == EH)//(*p)������������ȸߣ�ɾ������(*p)��bf��1,���߲���
	{
		(*p)->bf = RH;
		*shorter = FALSE;
	}
	else //(*p)������������
	{
		p1 = (*p)->rchild;//p1ָ��p��������
		if(p1->bf == EH)//p1������������ȸ�,ɾ������p��bfΪ-2,���������������߲���
		{
            p1->bf = LH;
			(*p)->bf = RH;
			L_Rotate(p);
			*shorter = FALSE;
		}
		else if(p1->bf == RH)//p1���������ߣ�������������䰫
		{
		    p1->bf = (*p)->bf = EH;
			L_Rotate(p);
			*shorter = TRUE;
		}
		else //p1����������,����˫������(������������)�����䰫
		{
            /*˫������*/
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
            /*˫������,���Һ���*/
			R_Rotate(&(*p)->rchild);
			L_Rotate(p);
			*shorter = TRUE;
		}
	}
}

/*****************************************************************************************
*@Name............: static void DelRightBalance(BiTree *p, Status *shorter)
*@Description.....: ��ƽ����ת����
*@Parameters......: p     : �������Ĵ���ת���ڵ�
*                   shorte: �ж������Ƿ��Ѿ��䰫
*@PreCondition....����ɾ���ڵ㣬�ú���������ʱҪȷ����������ƽ��״̬��
*@PostCondition...�����������ƽ��Ȳ�����Ӧ����
*****************************************************************************************/
static void DelRightBalance(BiTree *p, Status *shorter)
{
	BiTree p1, p2;
	if((*p)->bf == RH)//(*p)����������ߣ�ɾ������(*p)��bf��1,���䰫
	{
		(*p)->bf = EH;
		*shorter = TRUE;
	}
	else if((*p)->bf == EH)//(*p)������������ȸߣ�ɾ������(*p)��bf��1,���߲���
	{
		(*p)->bf = LH;
		*shorter = FALSE;
	}
	else//(*p)������������
	{
		p1 = (*p)->lchild;//p1ָ��p��������

		if(p1->bf == EH)//p1������������ȸ�,ɾ������p��bfΪ-2,���������������߲���
		{
		    p1->bf = RH;
			(*p)->bf = LH;
			R_Rotate(p);
			*shorter = FALSE;
		}
		else if(p1->bf == LH)//p1�ڵ��������ߣ�������������ƽ�⣬���䰫
		{
            p1->bf = (*p)->bf = EH;
			R_Rotate(p);
			*shorter = TRUE;
		}
		else//p1����������,����˫������(������������)�����䰫
		{
		    /*˫������*/
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

			/*˫������,�������*/
			L_Rotate(&(*p)->lchild);
			R_Rotate(p);
			*shorter = TRUE;
		}
	}
}

/*****************************************************************************************
*@Name............: static void Delete(BiTree q, BiTree *r, Status *shorter)
*@Description.....: ɾ���ڵ����
*@Parameters......: q     : ��ɾ���ڵ�
*                   r     : �ڵ�q������������Ϊ��ͨɾ�������Ľڵ�
*                   shorte: �ж������Ƿ��Ѿ��䰫
*@PreCondition....����ɾ���ڵ㣬�ú���������ʱҪȷ����������ƽ��״̬��
*@PostCondition...�����������ƽ��Ȳ�����Ӧ����
*****************************************************************************************/
static void Delete(BiTree q, BiTree *r, Status *shorter)
{
	if(NULL == (*r)->rchild)
	{
	    //����ͨ������ɾ����ͬ��ɾ����������
		q->data = (*r)->data;
		q = *r;
		*r = (*r)->lchild;
		free(q);
		*shorter = TRUE;
	}
	else
	{
	    //����Ѱ������������
		Delete(q, &(*r)->rchild, shorter);
		if(*shorter == TRUE)
			DelRightBalance(r, shorter);//ƽ�⴦��
	}
}

/*****************************************************************************************
*@Name............: static Status DeleteAVL(BiTree *p, ElemData data, Status *shorter)
*@Description.....: ɾ���ڵ����
*@Parameters......: p     : ��ɾ���ڵ�
*                   data  : ���и����ݵĽڵ㽫�ᱻɾ��
*                   shorte: �ж������Ƿ��Ѿ��䰫
*                   CompareData : �ȽϺ���
*@return..........: OK:���ڸùؼ���  FAIL:�����ڸùؼ���
*@PreCondition....����ɾ���ڵ㣬�ú���������ʱҪȷ����������ƽ��״̬��
*@PostCondition...�����������ƽ��Ȳ�����Ӧ����
*****************************************************************************************/
static Status DeleteAVL(BiTree *p, ElemData data, Status *shorter, Status (*CompareData)(ElemData, ElemData))
{
	Status status;
	BiTree q;
	if(*p == NULL)
	{
		printf("������Ҫɾ���Ĺؼ���!!\n");
		return FAIL;
	}
	else if(GREATER == CompareData((*p)->data, data))//��p���������н���ɾ��
	{
		status = DeleteAVL(&((*p)->lchild), data, shorter, CompareData);

		if(*shorter == TRUE)
			DelLeftBalance(p, shorter);

		return status;
	}
	else if(LESS == CompareData((*p)->data, data))//��p���������н���ɾ��
	{
		status = DeleteAVL(&((*p)->rchild), data, shorter, CompareData);

		if(*shorter == TRUE)
			DelRightBalance(p, shorter);

		return status;
	}
	else
	{
		q = *p;
		if((*p)->rchild == NULL) //����������ֻ���ؽ�����������
		{
			*p = (*p)->lchild;
			free(q);
			*shorter = TRUE;
		}
		else if((*p)->lchild == NULL)//����������ֻ���ؽ�����������
		{
			(*p) = (*p)->rchild;
			free(q);
			*shorter = TRUE;
		}
		else//��������������
		{
			Delete(q, &(q->lchild), shorter);/*������bug��q��pָ��ͬһ�ط����ı�p��Ҳ�ı�q*/
			if(*shorter == TRUE)
				DelLeftBalance(p, shorter);

			//*p = q;
			/*bug���޸�����Ϊƽ����ת��������ٸı���ڵ��λ����*/
		}
		return OK;
	}
}

/*****************************************************************************************
*@Name............: Status DeleteBTreeNode(BiTree *T, ElemData data, Status (*CompareData)(ElemData, ElemData))
*@Description.....: ɾ���ڵ�������ⲿ�ӿ�
*@Parameters......: T     : ƽ����������ڵ�
*                   data  : ���и����ݵĽڵ㽫�ᱻɾ��
*                   CompareData : �ȽϺ���
*@return..........: OK:���ڸùؼ���  FAIL:�����ڸùؼ���
*@PreCondition....���ȽϺ�����ȷ��������
*@PostCondition...�����ؼ��ִ�����������ɾ�������򱨴�
*****************************************************************************************/
Status DeleteBTreeNode(BiTree *T, ElemData data, Status (*CompareData)(ElemData, ElemData))
{
    Status shorter = FALSE;
    return DeleteAVL(T, data, &shorter, CompareData);
}

/*****************************************************************************************
*@Name............: int GetBTreeDepth(BiTree T)
*@Description.....: ��ȡ���������
*@Parameters......: T     : ƽ����������ڵ�
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
int GetBTreeDepth(BiTree T)
{
    int depthLeft, depthRight;

    if(!T)
        return 0;
    else
    {
        /*
        **�ֱ��ȡ�����������
        */
        depthLeft = GetBTreeDepth(T->lchild);
        depthRight = GetBTreeDepth(T->rchild);

        return 1 + (depthLeft > depthRight ? depthLeft : depthRight);//ȡ������������ټ��������������
    }
}

/*****************************************************************************************
*@Name............: static void InOrderK(BiTree T, int *count, int k, ElemData *data)
*@Description.....: �ݹ���������ȡ��k���Ԫ��
*@Parameters......: T     : ƽ����������ڵ�
*                   count : ��������
*                   data  : ���ݴ洢�ڴ�
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
static void InOrderK(BiTree T, int *count, int k, ElemData *data)
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
*@Name............: Status BGetNumberK(BiTree T, int k, ElemData *data)
*@Description.....: ��ȡ��k���Ԫ��
*@Parameters......: T     : ƽ����������ڵ�
*                   k     : Ѱ�ҵ�����
*                   data  : ���ݴ洢�ڴ�
*@return..........: OK: �ҵ��ùؼ��� FAIL:������������
*@PreCondition....����������k��Ŀ������ȷ
*@PostCondition...��data��ȡ����k���ֵ
*****************************************************************************************/
Status BGetNumberK(BiTree T, int k, ElemData *data)
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
*@Name............: int GetNumOfBNode(BiTree T)
*@Description.....: ��ȡ�������ڵ���
*@Parameters......: T     : ƽ����������ڵ�
*@PreCondition....����
*@PostCondition...�����ؽڵ���Ŀ
*****************************************************************************************/
int GetNumOfBNode(BiTree T)
{
    int leftNum, rightNum;

    if(!T)
        return 0;
    else
    {
        /*
        **�ֱ��ȡ���������Ľڵ���
        */
        leftNum = GetNumOfBNode(T->lchild);
        rightNum = GetNumOfBNode(T->rchild);
    }

    return leftNum + rightNum + 1;//���������ڵ��������������ܽڵ���
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
*@Name............: void FirstOrderTraverse(BiTree T, int layer, void (*visit)(ElemData data))
*@Description.....: ������״��ӡ������
*@Parameters......: T     : ƽ�������������ڵ�
*                   layer : ����
*                   visit : ���ʺ���
*@PreCondition....����
*@PostCondition...�����ؽڵ���Ŀ
*****************************************************************************************/
void FirstOrderTraverse(BiTree T, int layer, void (*visit)(ElemData data))
{
    if(!T)
        return ;

    printf("%d", layer);
    printf("|__");
    visit(T->data);
    printf(" (%d)\n", T->bf);

    if(T->lchild)//����������
    {
        PrintLayer(layer, 'L');
        FirstOrderTraverse(T->lchild, layer + 1, visit);
    }

    if(T->rchild)//����������
    {
        PrintLayer(layer, 'R');
        FirstOrderTraverse(T->rchild, layer + 1, visit);
    }
}

/*�������*/
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

/*�������*/
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

/*�������*/
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
*@Description.....: ��λ��������Ѱ�ҹؼ��ֽڵ����ڲ�����λ��
*@Parameters......: T            : ���������ڵ�
*                   attribute    : �ڵ�����
*@Return values...: OK   �����ҳɹ�
*                   FAIL ������ʧ�ܣ������ڸ��ڵ�
*@PreCondition....��������,layerĬ��Ϊ1
*@PostCondition...����
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
