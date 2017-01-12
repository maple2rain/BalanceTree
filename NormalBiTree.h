/***************************************************************************************
 *	File Name				:	NormalBiTree.h
 *	CopyRight				:	LPF
 *	ModuleName				:
 *
 *	CPU						:   Inter Core 7
 *	RTOS					:
 *
 *	Create Data				:	2015/11/20
 *	Author/Corportation		:	Li PeiFeng
 *
 *	Abstract Description	:	Declared the struct and function for NormalBiTree
 *
 *--------------------------------Revision History--------------------------------------
 *	No	version		Data		Revised By			Item			Description
 *
 *
 ***************************************************************************************/

/****************************************************************************************
*	Multi-Include-Prevent Section
****************************************************************************************/
#ifndef NORMALBITREE_H_INCLUDED
#define NORMALBITREE_H_INCLUDED

/*****************************************************************************************
*	Debug switch Section
*****************************************************************************************/
#define DEBUG
/*****************************************************************************************
*	Include File Section
*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "BalanceTree.h"

/*****************************************************************************************
*	Macro Define Section
*****************************************************************************************/
#define ElemData int
/*****************************************************************************************
*	Struct Define Section
*****************************************************************************************/
/*
**@type:            ƽ��������ڵ�ṹ��
**@name:            BinaryTNode, *BinaryTNode
**@data field:      data :�������洢������
**@pointer field:   *lchild:ָ������
**                  *rchild:ָ���Һ���
*/
typedef struct BinaryTNode
{
    ElemData data;
    struct BinaryTNode *lchild, *rchild;
}BinaryTNode, *BinaryTree;


///*
//**@type:            ö�����ͣ���ʾ����ִ��״̬�������������
//**@name:            Status
//**@data field       FALSE   :��ʾ����δ���߻�δ�䰫
//**                  TRUE    :��ʾ�������߻�䰫
//**                  OK      :��ʾ����ִ�гɹ�
//**                  FAIL    :��ʾ����ִ��ʧ��
//**                  GREATER :��ʾ����ֵ�Ƚ�ʱǰ�߽ϴ�
//**                  EQUAL   :��ʾ����ֵ�Ƚ�ʱ���
//**                  LESS    :��ʾ����ֵ�Ƚ�ʱǰ�߽�С
//*/
//typedef enum Status{
//    FALSE, TRUE, OK, FAIL, GREATER, EQUAL, LESS
//}Status;

/*****************************************************************************************
*	Prototype Declare Section
*****************************************************************************************/
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
Status InsertTree(BinaryTree *T, ElemData data, Status (*CompareData)(ElemData, ElemData));

/****************************************************************************************
*@Name............: Status SearchBTree(BinaryTree T, ElemData key, Status (*CompareData)(ElemData, ElemData))
*@Description.....: �����Ƿ���ڸ�����
*@Parameters......: T           :���������ڵ�
*                   key         :Ҫ���ҵĹؼ���
*                   CompareData : �ȽϺ���
*@Return values...: OK�����ҳɹ���FAIL������ʧ��
*@PreCondition....��������
*@PostCondition...����
*****************************************************************************************/
Status SearchTree(BinaryTree T, ElemData key, Status (*CompareData)(ElemData, ElemData));

/*****************************************************************************************
*@Name............: void DestroyTree(BinaryTree *T)
*@Description.....: ���ٶ�����
*@Parameters......: T   :���������ڵ�
*@Return values...: ��
*@PreCondition....��������
*@PostCondition...����
*****************************************************************************************/
void DestroyTree(BinaryTree *T);

/*****************************************************************************************
*@Name............: Status CreateTree(BinaryTree *T, Status (*CompareData)(ElemData, ElemData), int select)
*@Description.....: ����������
*@Parameters......: T           : ���������ڵ�
*                   CompareData : �ȽϺ���
*                   select      : ��ʾ�Զ����ֶ�
*@Return values...: TRUE�������ɹ���FALSE������ʧ�ܣ�ԭ���Ƕѿռ䲻��
*@PreCondition....��������
*@PostCondition...����
*****************************************************************************************/
Status CreateTree(BinaryTree *T, Status (*CompareData)(ElemData, ElemData), int select);

/*****************************************************************************************
*@Name............: int GetNumOfNode(BinaryTree T)
*@Description.....: ��ȡ�������ڵ���
*@Parameters......: T     : ƽ����������ڵ�
*@PreCondition....����
*@PostCondition...�����ؽڵ���Ŀ
*****************************************************************************************/
int GetNumOfNode(BinaryTree T);

/*****************************************************************************************
*@Name............: int GetTreeDepth(BinaryTree T)
*@Description.....: ��ȡ���������
*@Parameters......: T     : ƽ����������ڵ�
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
int GetTreeDepth(BinaryTree T);

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
Status GetNumberK(BinaryTree T, int k, ElemData *data);

/*****************************************************************************************
*@Name............: Status DeleteTreeNode(BinaryTree *T, ElemData data, Status (*CompareData)(ElemData, ElemData))
*@Description.....: ɾ������data�Ľڵ�
*@Parameters......: T     : ƽ����������ڵ�
*                   data  : ���и����ݵĽڵ㽫�ᱻɾ��
*                   CompareData : �ȽϺ���
*@return..........: OK:���ڸùؼ���  FAIL:�����ڸùؼ���
*@PostCondition...��ɾ���и�ֵ�Ľڵ�
*****************************************************************************************/
Status DeleteTreeNode(BinaryTree *T, ElemData data, Status (*CompareData)(ElemData, ElemData));

/*****************************************************************************************
*@Name............: void FirstOrder(BinaryTree T, int layer, void (*visit)(ElemData data))
*@Description.....: ������״��ӡ������
*@Parameters......: T     : ƽ�������������ڵ�
*                   layer : ����
*                   visit : ���ʺ���
*@PreCondition....����
*@PostCondition...�����ؽڵ���Ŀ
*****************************************************************************************/
void FirstOrder(BinaryTree T, int layer, void (*visit)(ElemData data));

/*�������*/
void PreOrderTraver(BinaryTree T);

/*�������*/
void InOrderTraver(BinaryTree T);

/*�������*/
void BackTraver(BinaryTree T);


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
Status LocateTree(BinaryTree T, ElemData key, struct TreeNodeAttribute* attribute, Status (*CompareData)(ElemData, ElemData));
#endif // NORMALBITREE_H_INCLUDED
