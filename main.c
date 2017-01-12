#include "BalanceTree.h"
#include <windows.h>
#include "draw.h"
#include "NormalBiTree.h"
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include "Queue.h"


/*访问节点函数*/
void visit(ElemData data)
{
    printf("%d", data);
}

/*比较函数*/
Status CompareData(ElemData NodeData, ElemData data)
{
    if(NodeData > data)
        return GREATER;
    else if(NodeData < data)
        return LESS;
    else
        return EQUAL;
}

/*设置光标位置*/
void gotoxy(int x, int y)
{
	COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void End(void)
{
    system("cls");
    printf("\n\n\n\t\t\tThanks for testing!\n\n\n");
    Sleep(1500);
}

void LayerVisit(BiTree T, void (*visit)(ElemData data))
{
    if(T)
    {
        LQueue Q;
        InitQueue(&Q);
        int row = GetBTreeDepth(T);//获取树的深度，决定打印多少个'\t'
        int i,j,k;//偶数时打印'/',奇数时打印'\'

        EnQueue(&Q, T);//根进队
        for(i = 0; i < row; ++i)//层序遍历，分层打印
        {
            /*
            **打印数据
            */
            for(k = 0; k < pow(2,i); ++k)//根据满二叉树性质层次输出数据，每一行的数据个数为2^i个
            {
                for(j = 0; j < (pow(2, row - i - 1) - 1); ++j)//从第一行开始缩进2^(row - i -1) - 1个间隔
                    printf("     ");

                DeQueue(&Q, &T);//出队

                if(T)
                {
                    printf("%5d",T->data);//当出队的结点存在时打印p->data
                    EnQueue(&Q, T->lchild);
                    EnQueue(&Q, T->rchild);
                }
                else
                    printf("  @  ");//当结点不存在时打印@


                for(j = 0; j < (pow(2,row - i - 1)); ++j)
                    printf("     ");
            }
            printf("\n");//每打完一层换行

//            /*
//            **打印斜杠
//            */
//            for(k = 0; k < pow(2, i); ++k)
//            {
//                if(i == row - 1)
//                    break;
//                for(j = 0; j < (pow(2, row - i - 1) - 2); ++j)//从第一行开始缩进2^(row - i -1) - 1个空格
//                    printf("     ");
//
//                printf("  /  ");
//
//                for(j = 0; j < (pow(2,row - i - 2) - 1); ++j)
//                    printf("     ");
//
//                printf("  \\  ");
//
//            }
//            printf("\n");
        }
    }
}

int main()
{
    BiTree T = NULL;//平衡二叉树根节点
    BinaryTree NT = NULL;//普通二叉树根节点
    int select;//用户选择
    int flag = 0;//展示二叉树标志
    ElemData key;//关键字
    struct TreeNodeAttribute attribute = {1, '0'};//初始化为层数为1，非左右子树
    unsigned int seed;//随机数种子

    LARGE_INTEGER  num;
    long long start, end, freq;
    QueryPerformanceFrequency(&num);
    freq = num.QuadPart;//时钟频率

    int a = log(8) / log(2);
    printf("%d\n", a);

    do{
    lable:
        system("cls");
        drawFrame();
        gotoxy(33,18);
        scanf("%d", &select);
        system("cls");

        if(select < 1 || select > 13)
        {
            printf("选择有误!请重新输入您的选择!\n");
            Sleep(1500);
            goto lable;
        }

        switch(select)
        {
            case 1:
                seed = (unsigned)time(NULL);
                srand(seed);
                if(OK == CreateBTree(&T, CompareData, 1))
                    printf("平衡二叉树创建成功\n");

                srand(seed);
                if(OK == CreateTree(&NT, CompareData, 1))
                    printf("普通二叉树创建成功\n");
                break;

            case 2:
                printf("end with \'-1\'\n");
                scanf("%d", &key);

                while(-1 != key)
                {
                    InsertBTree(&T, key, CompareData);
                    InsertTree(&NT, key, CompareData);
                    scanf("%d", &key);
                }
                break;

            case 3:
                printf("当前平衡二叉树节点数目为 %d\n", GetNumOfBNode(T));
                printf("当前普通二叉树节点数目为 %d\n", GetNumOfNode(NT));
                break;

            case 4:
                printf("当前平衡二叉树的深度为 %d\n", GetBTreeDepth(T));
                printf("当前普通二叉树的深度为 %d\n", GetTreeDepth(NT));
                break;

            case 5:
                printf("请输入您想要查找的关键字:");
                scanf("%d", &key);

//                QueryPerformanceCounter(&num);
//                start = num.QuadPart;
//                QueryPerformanceCounter(&num);
//                end = num.QuadPart;



                printf("\n普通二叉树:\n");
                QueryPerformanceCounter(&num);
                start = num.QuadPart;
                if(OK == SearchTree(NT, key, CompareData))
                {
                    LocateTree(NT, key, &attribute, CompareData);
                    printf("\t关键字存在!它位于第%d层", attribute.layer);

                    if(attribute.layer != 1)//非根节点需判断为左右子树
                        printf("的%c", attribute.LorR);

                    attribute.layer = 1;//层数重置为1
                    printf("!\n");
                }
                else
                    printf("\t关键字不存在!\n");

                QueryPerformanceCounter(&num);
                end = num.QuadPart;
                printf("\t普通二叉树搜索所需时间: %ld 微秒\n", (end - start) * 1000000 / freq);

                printf("平衡二叉树:\n");
                QueryPerformanceCounter(&num);
                start = num.QuadPart;//获取开始时间
                if(OK == SearchBTree(T, key, CompareData))
                {
                    LocateBTree(T, key, &attribute, CompareData);
                    printf("\t关键字存在!它位于第%d层", attribute.layer);

                    if(attribute.layer != 1)//非根节点需判断为左右子树
                        printf("的%c", attribute.LorR);

                    attribute.layer = 1;//层数重置为1
                    printf("!\n");
                }
                else
                    printf("\t关键字不存在!\n");

                QueryPerformanceCounter(&num);
                end = num.QuadPart;//获取结束时间
                printf("\t平衡二叉树搜索所需时间: %ld 微秒\n", (end - start) * 1000000 / freq);

                break;

            case 6:
                printf("请输入您想要删除的关键字:");
                scanf("%d", &key);
                printf("在平衡二叉树中:");
                if(OK == DeleteBTreeNode(&T, key, CompareData))
                    printf("\t该关键字已经被删除!\n");
                else
                    printf("\t关键字不存在!\n");

                printf("在普通二叉树中:");
                if(OK == DeleteTreeNode(&NT, key, CompareData))
                    printf("\t该关键字已经被删除!\n");
                else
                    printf("\t关键字不存在!\n");
                break;

            case 7:
                printf("请输入k的值:");
                int k;
                scanf("%d",&k);
                if(OK == BGetNumberK(T, k, &key))
                {
                    printf("平衡二叉树中排第k的值为:");
                    visit(key);
                    printf("\n");
                }
                if(OK == GetNumberK(NT, k, &key))
                {
                    printf("普通二叉树中排第k的值为:");
                    visit(key);
                    printf("\n");
                }
                break;

            case 8:
                printf("请输入要插入节点的关键字:\n");
                scanf("%d", &key);
                printf("平衡二叉树");
                if(OK == InsertBTree(&T, key, CompareData))
                    printf("插入成功!\n");
                else
                    printf("插入失败，关键字已经存在!\n");

                printf("普通二叉树");
                if(OK == InsertTree(&NT, key, CompareData))
                    printf("插入成功!\n");
                else
                    printf("插入失败，关键字已经存在!\n");
                break;

            case 9:
                DestroyBTree(&T);
                DestroyTree(&NT);
                printf("销毁成功!\n");
                break;

            case 10:
                printf("遍历平衡二叉树:\n");
                FirstOrderTraverse(T, 1, visit);
                //LayerVisit(T, visit);
                printf("\n遍历普通二叉树:\n");
                FirstOrder(NT, 1, visit);
                break;

            case 11:
                do{
                    printf("需要展示请按'1',不需要请按'0'");
                    scanf("%d", &flag);
                    if(1 == flag)
                        printf("您设置了每次操作都会执行展示二叉树!\n");
                    else if(0 == flag)
                    {
                        printf("您设置了每次操作将不会执行展示二叉树!\n");
                    }
                    else{
                        printf("您的选择有误，请重新选择!\n");
                        Sleep(1500);
                        system("cls");
                    }
                }while(flag != 1 && flag != 0);
                break;

            case 12:
                End();//终止程序画图
                return(0);

        }

        if(1 == flag && select != 10 && select != 11)//设置后及手动展示时不需要自动展示
        {
            FirstOrderTraverse(T, 1, visit);
            FirstOrder(NT, 1, visit);
        }

        printf("输入'q'退出或者按任意键继续!");
        if(getch() == 'q')
            break;

    }while(1);

    End();
    return 0;
}
