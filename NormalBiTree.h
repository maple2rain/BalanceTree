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
**@type:            平衡二叉树节点结构体
**@name:            BinaryTNode, *BinaryTNode
**@data field:      data :二叉树存储的数据
**@pointer field:   *lchild:指向左孩子
**                  *rchild:指向右孩子
*/
typedef struct BinaryTNode
{
    ElemData data;
    struct BinaryTNode *lchild, *rchild;
}BinaryTNode, *BinaryTree;


///*
//**@type:            枚举类型，表示函数执行状态或子树增高与否
//**@name:            Status
//**@data field       FALSE   :表示子树未增高或未变矮
//**                  TRUE    :表示子树增高或变矮
//**                  OK      :表示函数执行成功
//**                  FAIL    :表示函数执行失败
//**                  GREATER :表示两个值比较时前者较大
//**                  EQUAL   :表示两个值比较时相等
//**                  LESS    :表示两个值比较时前者较小
//*/
//typedef enum Status{
//    FALSE, TRUE, OK, FAIL, GREATER, EQUAL, LESS
//}Status;

/*****************************************************************************************
*	Prototype Declare Section
*****************************************************************************************/
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
Status InsertTree(BinaryTree *T, ElemData data, Status (*CompareData)(ElemData, ElemData));

/****************************************************************************************
*@Name............: Status SearchBTree(BinaryTree T, ElemData key, Status (*CompareData)(ElemData, ElemData))
*@Description.....: 查找是否存在该数据
*@Parameters......: T           :二叉树根节点
*                   key         :要查找的关键字
*                   CompareData : 比较函数
*@Return values...: OK：查找成功；FAIL：查找失败
*@PreCondition....：存在树
*@PostCondition...：无
*****************************************************************************************/
Status SearchTree(BinaryTree T, ElemData key, Status (*CompareData)(ElemData, ElemData));

/*****************************************************************************************
*@Name............: void DestroyTree(BinaryTree *T)
*@Description.....: 销毁二叉树
*@Parameters......: T   :二叉树根节点
*@Return values...: 无
*@PreCondition....：存在树
*@PostCondition...：无
*****************************************************************************************/
void DestroyTree(BinaryTree *T);

/*****************************************************************************************
*@Name............: Status CreateTree(BinaryTree *T, Status (*CompareData)(ElemData, ElemData), int select)
*@Description.....: 构建二叉树
*@Parameters......: T           : 二叉树根节点
*                   CompareData : 比较函数
*                   select      : 表示自动或手动
*@Return values...: TRUE：创建成功；FALSE：创建失败，原因是堆空间不足
*@PreCondition....：存在树
*@PostCondition...：无
*****************************************************************************************/
Status CreateTree(BinaryTree *T, Status (*CompareData)(ElemData, ElemData), int select);

/*****************************************************************************************
*@Name............: int GetNumOfNode(BinaryTree T)
*@Description.....: 获取二叉树节点数
*@Parameters......: T     : 平衡二叉树根节点
*@PreCondition....：无
*@PostCondition...：返回节点数目
*****************************************************************************************/
int GetNumOfNode(BinaryTree T);

/*****************************************************************************************
*@Name............: int GetTreeDepth(BinaryTree T)
*@Description.....: 获取二叉树深度
*@Parameters......: T     : 平衡二叉树根节点
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
int GetTreeDepth(BinaryTree T);

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
Status GetNumberK(BinaryTree T, int k, ElemData *data);

/*****************************************************************************************
*@Name............: Status DeleteTreeNode(BinaryTree *T, ElemData data, Status (*CompareData)(ElemData, ElemData))
*@Description.....: 删除含有data的节点
*@Parameters......: T     : 平衡二叉树根节点
*                   data  : 含有该数据的节点将会被删除
*                   CompareData : 比较函数
*@return..........: OK:存在该关键字  FAIL:不存在该关键字
*@PostCondition...：删除有该值的节点
*****************************************************************************************/
Status DeleteTreeNode(BinaryTree *T, ElemData data, Status (*CompareData)(ElemData, ElemData));

/*****************************************************************************************
*@Name............: void FirstOrder(BinaryTree T, int layer, void (*visit)(ElemData data))
*@Description.....: 先序树状打印二叉树
*@Parameters......: T     : 平衡二叉树任意根节点
*                   layer : 层数
*                   visit : 访问函数
*@PreCondition....：无
*@PostCondition...：返回节点数目
*****************************************************************************************/
void FirstOrder(BinaryTree T, int layer, void (*visit)(ElemData data));

/*先序遍历*/
void PreOrderTraver(BinaryTree T);

/*中序遍历*/
void InOrderTraver(BinaryTree T);

/*倒序遍历*/
void BackTraver(BinaryTree T);


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
Status LocateTree(BinaryTree T, ElemData key, struct TreeNodeAttribute* attribute, Status (*CompareData)(ElemData, ElemData));
#endif // NORMALBITREE_H_INCLUDED
