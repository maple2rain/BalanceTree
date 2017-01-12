/***************************************************************************************
 *	File Name				:	BalanceTree.h
 *	CopyRight				:	LPF
 *	ModuleName				:	BalanceTree
 *
 *	CPU						:   Inter Core 7
 *	RTOS					:
 *
 *	Create Data				:	2015/11/20
 *	Author/Corportation		:	Li PeiFeng
 *
 *	Abstract Description	:	Declared the struct and function for BalanceTree
 *
 *--------------------------------Revision History--------------------------------------
 *	No	version		Data		Revised By			Item			Description
 *
 *
 ***************************************************************************************/

/****************************************************************************************
*	Multi-Include-Prevent Section
****************************************************************************************/
#ifndef BALANCETREE_H_INCLUDED
#define BALANCETREE_H_INCLUDED

/*****************************************************************************************
*	Debug switch Section
*****************************************************************************************/
#define DEBUG
/*****************************************************************************************
*	Include File Section
*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

/*****************************************************************************************
*	Macro Define Section
*****************************************************************************************/
#define ElemData int
/*****************************************************************************************
*	Struct Define Section
*****************************************************************************************/
/*
**@type:            ö�����ͣ���ʾƽ�����������
**@name:            BalanceType
**@data field:      LH :��ʾ��������
**                  EH :��ʾ���������ȸ�
**                  RH :��ʾ��������
*/
typedef enum BalanceType{
    LH = 1,
    EH = 0,
    RH = -1
}BalanceType;

/*
**@type:            ƽ��������ڵ�ṹ��
**@name:            BiTNode, *BiTree
**@data field:      data :�������洢������
**                  bf   :ƽ������
**@pointer field:   *lchild:ָ������
**                  *rchild:ָ���Һ���
*/
typedef struct BiTNode
{
    ElemData data;
    BalanceType bf;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;


struct TreeNodeAttribute{
    int layer;
    char LorR;
};
/*
**@type:            ö�����ͣ���ʾ����ִ��״̬�������������
**@name:            Status
**@data field       FALSE   :��ʾ����δ���߻�δ�䰫
**                  TRUE    :��ʾ�������߻�䰫
**                  OK      :��ʾ����ִ�гɹ�
**                  FAIL    :��ʾ����ִ��ʧ��
**                  GREATER :��ʾ����ֵ�Ƚ�ʱǰ�߽ϴ�
**                  EQUAL   :��ʾ����ֵ�Ƚ�ʱ���
**                  LESS    :��ʾ����ֵ�Ƚ�ʱǰ�߽�С
*/
typedef enum Status{
    FALSE, TRUE, OK, FAIL, GREATER, EQUAL, LESS
}Status;

/*****************************************************************************************
*	Prototype Declare Section
*****************************************************************************************/
/*****************************************************************************************
*@Name............: Status InsertBTree(BiTree *T, ElemData data, Status (*CompareData)(ElemData, ElemData))
*@Description.....: Ϊƽ������������½ڵ�
*@Parameters......: T            :���������ڵ�
*                   data         :����������
*                   CompareData  : �ȽϺ���
*@Return values...: OK ������ɹ�
*                   FAIL ������ʧ�ܣ������ǽڵ��Ѿ����ڻ��߶ѿռ䲻��
*@PreCondition....��������
*@PostCondition...����
*****************************************************************************************/
Status InsertBTree(BiTree *T, ElemData data, Status (*CompareData)(ElemData, ElemData));

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
Status SearchBTree(BiTree T, ElemData key, Status (*CompareData)(ElemData, ElemData));

/*****************************************************************************************
*@Name............: void DestroyTree(BiTree *T)
*@Description.....: ���ٶ�����
*@Parameters......: T   :���������ڵ�
*@Return values...: ��
*@PreCondition....��������
*@PostCondition...����
*****************************************************************************************/
void DestroyBTree(BiTree *T);

/*****************************************************************************************
*@Name............: Status CreateBTree(BiTree *T, Status (*CompareData)(ElemData, ElemData))
*@Description.....: ����������
*@Parameters......: T           :���������ڵ�
*                   CompareData :�ȽϺ���
*@Return values...: OK�������ɹ���FAIL������ʧ�ܣ�ԭ���Ƕѿռ䲻��
*@PreCondition....��������
*@PostCondition...����
*****************************************************************************************/
Status CreateBTree(BiTree *T, Status (*CompareData)(ElemData, ElemData), int select);

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
Status DeleteBTreeNode(BiTree *T, ElemData data, Status (*CompareData)(ElemData, ElemData));

/*****************************************************************************************
*@Name............: int GetBTreeDepth(BiTree T)
*@Description.....: ��ȡ���������
*@Parameters......: T     : ƽ����������ڵ�
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
int GetBTreeDepth(BiTree T);

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
Status BGetNumberK(BiTree T, int k, ElemData *data);

/*****************************************************************************************
*@Name............: int GetNumOfNode(BiTree T)
*@Description.....: ��ȡ�������ڵ���
*@Parameters......: T     : ƽ����������ڵ�
*@PreCondition....����
*@PostCondition...�����ؽڵ���Ŀ
*****************************************************************************************/
int GetNumOfBNode(BiTree T);

/*****************************************************************************************
*@Name............: void FirstOrderTraverse(BiTree T, int layer, void (*visit)(ElemData data))
*@Description.....: ������״��ӡ������
*@Parameters......: T     : ƽ�������������ڵ�
*                   layer : ����
*                   visit : ���ʺ���
*@PreCondition....����
*@PostCondition...�����ؽڵ���Ŀ
*****************************************************************************************/
void FirstOrderTraverse(BiTree T, int layer, void (*visit)(ElemData data));

/*�������*/
void PreOrderTraverse(BiTree T);

/*�������*/
void InOrderTraverse(BiTree T);

/*�������*/
void BackTraverse(BiTree T);
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
Status LocateBTree(BiTree T, ElemData key, struct TreeNodeAttribute* attribute, Status (*CompareData)(ElemData, ElemData));
#endif // BALANCETREE_H_INCLUDED
