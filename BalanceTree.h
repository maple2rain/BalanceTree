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
**@type:            枚举类型，表示平衡二叉树因子
**@name:            BalanceType
**@data field:      LH :表示左子树高
**                  EH :表示左右子树等高
**                  RH :表示右子树高
*/
typedef enum BalanceType{
    LH = 1,
    EH = 0,
    RH = -1
}BalanceType;

/*
**@type:            平衡二叉树节点结构体
**@name:            BiTNode, *BiTree
**@data field:      data :二叉树存储的数据
**                  bf   :平衡因子
**@pointer field:   *lchild:指向左孩子
**                  *rchild:指向右孩子
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
**@type:            枚举类型，表示函数执行状态或子树增高与否
**@name:            Status
**@data field       FALSE   :表示子树未增高或未变矮
**                  TRUE    :表示子树增高或变矮
**                  OK      :表示函数执行成功
**                  FAIL    :表示函数执行失败
**                  GREATER :表示两个值比较时前者较大
**                  EQUAL   :表示两个值比较时相等
**                  LESS    :表示两个值比较时前者较小
*/
typedef enum Status{
    FALSE, TRUE, OK, FAIL, GREATER, EQUAL, LESS
}Status;

/*****************************************************************************************
*	Prototype Declare Section
*****************************************************************************************/
/*****************************************************************************************
*@Name............: Status InsertBTree(BiTree *T, ElemData data, Status (*CompareData)(ElemData, ElemData))
*@Description.....: 为平衡二叉树插入新节点
*@Parameters......: T            :二叉树根节点
*                   data         :待插入数据
*                   CompareData  : 比较函数
*@Return values...: OK ：插入成功
*                   FAIL ：插入失败，可能是节点已经存在或者堆空间不足
*@PreCondition....：存在树
*@PostCondition...：无
*****************************************************************************************/
Status InsertBTree(BiTree *T, ElemData data, Status (*CompareData)(ElemData, ElemData));

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
Status SearchBTree(BiTree T, ElemData key, Status (*CompareData)(ElemData, ElemData));

/*****************************************************************************************
*@Name............: void DestroyTree(BiTree *T)
*@Description.....: 销毁二叉树
*@Parameters......: T   :二叉树根节点
*@Return values...: 无
*@PreCondition....：存在树
*@PostCondition...：无
*****************************************************************************************/
void DestroyBTree(BiTree *T);

/*****************************************************************************************
*@Name............: Status CreateBTree(BiTree *T, Status (*CompareData)(ElemData, ElemData))
*@Description.....: 构建二叉树
*@Parameters......: T           :二叉树根节点
*                   CompareData :比较函数
*@Return values...: OK：创建成功；FAIL：创建失败，原因是堆空间不足
*@PreCondition....：存在树
*@PostCondition...：无
*****************************************************************************************/
Status CreateBTree(BiTree *T, Status (*CompareData)(ElemData, ElemData), int select);

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
Status DeleteBTreeNode(BiTree *T, ElemData data, Status (*CompareData)(ElemData, ElemData));

/*****************************************************************************************
*@Name............: int GetBTreeDepth(BiTree T)
*@Description.....: 获取二叉树深度
*@Parameters......: T     : 平衡二叉树根节点
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
int GetBTreeDepth(BiTree T);

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
Status BGetNumberK(BiTree T, int k, ElemData *data);

/*****************************************************************************************
*@Name............: int GetNumOfNode(BiTree T)
*@Description.....: 获取二叉树节点数
*@Parameters......: T     : 平衡二叉树根节点
*@PreCondition....：无
*@PostCondition...：返回节点数目
*****************************************************************************************/
int GetNumOfBNode(BiTree T);

/*****************************************************************************************
*@Name............: void FirstOrderTraverse(BiTree T, int layer, void (*visit)(ElemData data))
*@Description.....: 先序树状打印二叉树
*@Parameters......: T     : 平衡二叉树任意根节点
*                   layer : 层数
*                   visit : 访问函数
*@PreCondition....：无
*@PostCondition...：返回节点数目
*****************************************************************************************/
void FirstOrderTraverse(BiTree T, int layer, void (*visit)(ElemData data));

/*先序遍历*/
void PreOrderTraverse(BiTree T);

/*中序遍历*/
void InOrderTraverse(BiTree T);

/*倒序遍历*/
void BackTraverse(BiTree T);
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
Status LocateBTree(BiTree T, ElemData key, struct TreeNodeAttribute* attribute, Status (*CompareData)(ElemData, ElemData));
#endif // BALANCETREE_H_INCLUDED
