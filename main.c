#include "BalanceTree.h"
#include <windows.h>
#include "draw.h"
#include "NormalBiTree.h"
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include "Queue.h"


/*���ʽڵ㺯��*/
void visit(ElemData data)
{
    printf("%d", data);
}

/*�ȽϺ���*/
Status CompareData(ElemData NodeData, ElemData data)
{
    if(NodeData > data)
        return GREATER;
    else if(NodeData < data)
        return LESS;
    else
        return EQUAL;
}

/*���ù��λ��*/
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
        int row = GetBTreeDepth(T);//��ȡ������ȣ�������ӡ���ٸ�'\t'
        int i,j,k;//ż��ʱ��ӡ'/',����ʱ��ӡ'\'

        EnQueue(&Q, T);//������
        for(i = 0; i < row; ++i)//����������ֲ��ӡ
        {
            /*
            **��ӡ����
            */
            for(k = 0; k < pow(2,i); ++k)//���������������ʲ��������ݣ�ÿһ�е����ݸ���Ϊ2^i��
            {
                for(j = 0; j < (pow(2, row - i - 1) - 1); ++j)//�ӵ�һ�п�ʼ����2^(row - i -1) - 1�����
                    printf("     ");

                DeQueue(&Q, &T);//����

                if(T)
                {
                    printf("%5d",T->data);//�����ӵĽ�����ʱ��ӡp->data
                    EnQueue(&Q, T->lchild);
                    EnQueue(&Q, T->rchild);
                }
                else
                    printf("  @  ");//����㲻����ʱ��ӡ@


                for(j = 0; j < (pow(2,row - i - 1)); ++j)
                    printf("     ");
            }
            printf("\n");//ÿ����һ�㻻��

//            /*
//            **��ӡб��
//            */
//            for(k = 0; k < pow(2, i); ++k)
//            {
//                if(i == row - 1)
//                    break;
//                for(j = 0; j < (pow(2, row - i - 1) - 2); ++j)//�ӵ�һ�п�ʼ����2^(row - i -1) - 1���ո�
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
    BiTree T = NULL;//ƽ����������ڵ�
    BinaryTree NT = NULL;//��ͨ���������ڵ�
    int select;//�û�ѡ��
    int flag = 0;//չʾ��������־
    ElemData key;//�ؼ���
    struct TreeNodeAttribute attribute = {1, '0'};//��ʼ��Ϊ����Ϊ1������������
    unsigned int seed;//���������

    LARGE_INTEGER  num;
    long long start, end, freq;
    QueryPerformanceFrequency(&num);
    freq = num.QuadPart;//ʱ��Ƶ��

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
            printf("ѡ������!��������������ѡ��!\n");
            Sleep(1500);
            goto lable;
        }

        switch(select)
        {
            case 1:
                seed = (unsigned)time(NULL);
                srand(seed);
                if(OK == CreateBTree(&T, CompareData, 1))
                    printf("ƽ������������ɹ�\n");

                srand(seed);
                if(OK == CreateTree(&NT, CompareData, 1))
                    printf("��ͨ�����������ɹ�\n");
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
                printf("��ǰƽ��������ڵ���ĿΪ %d\n", GetNumOfBNode(T));
                printf("��ǰ��ͨ�������ڵ���ĿΪ %d\n", GetNumOfNode(NT));
                break;

            case 4:
                printf("��ǰƽ������������Ϊ %d\n", GetBTreeDepth(T));
                printf("��ǰ��ͨ�����������Ϊ %d\n", GetTreeDepth(NT));
                break;

            case 5:
                printf("����������Ҫ���ҵĹؼ���:");
                scanf("%d", &key);

//                QueryPerformanceCounter(&num);
//                start = num.QuadPart;
//                QueryPerformanceCounter(&num);
//                end = num.QuadPart;



                printf("\n��ͨ������:\n");
                QueryPerformanceCounter(&num);
                start = num.QuadPart;
                if(OK == SearchTree(NT, key, CompareData))
                {
                    LocateTree(NT, key, &attribute, CompareData);
                    printf("\t�ؼ��ִ���!��λ�ڵ�%d��", attribute.layer);

                    if(attribute.layer != 1)//�Ǹ��ڵ����ж�Ϊ��������
                        printf("��%c", attribute.LorR);

                    attribute.layer = 1;//��������Ϊ1
                    printf("!\n");
                }
                else
                    printf("\t�ؼ��ֲ�����!\n");

                QueryPerformanceCounter(&num);
                end = num.QuadPart;
                printf("\t��ͨ��������������ʱ��: %ld ΢��\n", (end - start) * 1000000 / freq);

                printf("ƽ�������:\n");
                QueryPerformanceCounter(&num);
                start = num.QuadPart;//��ȡ��ʼʱ��
                if(OK == SearchBTree(T, key, CompareData))
                {
                    LocateBTree(T, key, &attribute, CompareData);
                    printf("\t�ؼ��ִ���!��λ�ڵ�%d��", attribute.layer);

                    if(attribute.layer != 1)//�Ǹ��ڵ����ж�Ϊ��������
                        printf("��%c", attribute.LorR);

                    attribute.layer = 1;//��������Ϊ1
                    printf("!\n");
                }
                else
                    printf("\t�ؼ��ֲ�����!\n");

                QueryPerformanceCounter(&num);
                end = num.QuadPart;//��ȡ����ʱ��
                printf("\tƽ���������������ʱ��: %ld ΢��\n", (end - start) * 1000000 / freq);

                break;

            case 6:
                printf("����������Ҫɾ���Ĺؼ���:");
                scanf("%d", &key);
                printf("��ƽ���������:");
                if(OK == DeleteBTreeNode(&T, key, CompareData))
                    printf("\t�ùؼ����Ѿ���ɾ��!\n");
                else
                    printf("\t�ؼ��ֲ�����!\n");

                printf("����ͨ��������:");
                if(OK == DeleteTreeNode(&NT, key, CompareData))
                    printf("\t�ùؼ����Ѿ���ɾ��!\n");
                else
                    printf("\t�ؼ��ֲ�����!\n");
                break;

            case 7:
                printf("������k��ֵ:");
                int k;
                scanf("%d",&k);
                if(OK == BGetNumberK(T, k, &key))
                {
                    printf("ƽ����������ŵ�k��ֵΪ:");
                    visit(key);
                    printf("\n");
                }
                if(OK == GetNumberK(NT, k, &key))
                {
                    printf("��ͨ���������ŵ�k��ֵΪ:");
                    visit(key);
                    printf("\n");
                }
                break;

            case 8:
                printf("������Ҫ����ڵ�Ĺؼ���:\n");
                scanf("%d", &key);
                printf("ƽ�������");
                if(OK == InsertBTree(&T, key, CompareData))
                    printf("����ɹ�!\n");
                else
                    printf("����ʧ�ܣ��ؼ����Ѿ�����!\n");

                printf("��ͨ������");
                if(OK == InsertTree(&NT, key, CompareData))
                    printf("����ɹ�!\n");
                else
                    printf("����ʧ�ܣ��ؼ����Ѿ�����!\n");
                break;

            case 9:
                DestroyBTree(&T);
                DestroyTree(&NT);
                printf("���ٳɹ�!\n");
                break;

            case 10:
                printf("����ƽ�������:\n");
                FirstOrderTraverse(T, 1, visit);
                //LayerVisit(T, visit);
                printf("\n������ͨ������:\n");
                FirstOrder(NT, 1, visit);
                break;

            case 11:
                do{
                    printf("��Ҫչʾ�밴'1',����Ҫ�밴'0'");
                    scanf("%d", &flag);
                    if(1 == flag)
                        printf("��������ÿ�β�������ִ��չʾ������!\n");
                    else if(0 == flag)
                    {
                        printf("��������ÿ�β���������ִ��չʾ������!\n");
                    }
                    else{
                        printf("����ѡ������������ѡ��!\n");
                        Sleep(1500);
                        system("cls");
                    }
                }while(flag != 1 && flag != 0);
                break;

            case 12:
                End();//��ֹ����ͼ
                return(0);

        }

        if(1 == flag && select != 10 && select != 11)//���ú��ֶ�չʾʱ����Ҫ�Զ�չʾ
        {
            FirstOrderTraverse(T, 1, visit);
            FirstOrder(NT, 1, visit);
        }

        printf("����'q'�˳����߰����������!");
        if(getch() == 'q')
            break;

    }while(1);

    End();
    return 0;
}
