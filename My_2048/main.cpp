#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<graphics.h>
#include<conio.h>
#define L 5
int Check_Game_Over = 0;
int Code[L][L] = { 0 };   //Code用来存放16个数字；
int temp[L] = { 0 };    //用来存放临时的一维数组；
int Max = 0;   //用来记录最大数字；
int Score = 0;  //用来记录得分；
int n = 0;   //操作次数；
int disX = 0, disY = 200;
IMAGE picture[16];  //游戏过程中用到的图片；
IMAGE StartAndEnd[3];
//检查游戏是否结束
void check_game_over()
{
	int i, j;
	//检查游戏是否结束的原理：相邻的两个数据不相等，即Code[i][j]!=Code[i][j+1]&&Code[i][j+1]!=Code[i+1][j];
	for (i = 0; i < L; i++)
	{
		if (i == 3)
		{
			for (j = 0; j < L - 1; j++)
			{
				if (Code[i][j] == Code[i - 1][j] || Code[i][j] == Code[i][j + 1])
				{
					Check_Game_Over = 0;
					return;
				}

			}
		}
		for (j = 0; j < L - 1; j++)
		{
			if ((Code[i][j] == Code[i][j + 1] || Code[i][j] == Code[i + 1][j])||Code[i][j]==Code[i][j+1])
			{
				Check_Game_Over = 0;
				return;
			}
		}
	}
	Check_Game_Over = 1;
	return;
}
//计录最大数字;
int MaxNum()
{
	int i, k;
	Max = Code[0][0];
	for (i = 0; i < L; i++)
	{
		//求出最大数；
		for (k = 0; k < L; k++)
		{
			if (Max < Code[i][k])
			{
				Max = Code[i][k];
			}
		}
	}
	return Max;
}
void Interface()
{
	int i, j, k;
	printf("\n\n\t\tMy 2048\n\n");
	printf("\n\t游戏规则：W--上，S--下，A--左，D--右\n\n");
	if (n == 0)
		printf("\n最大数字：%4d\t得分：%4d\t\n\n", 0, 0);
	else
		printf("\n最大数字：%4d\t得分：%4d\t\n\n", MaxNum(), Score);
	printf("|");
	for (j = 0; j < L; j++)
	{
		if (j == L - 1)
			printf("\b");
		printf("-----");
	}
	printf("|\n");
	for (i = 0; i <= L - 1; i++)
	{
		for (k = 0; k <= L - 1; k++)
		{
			if (Code[i][k] == 0)
				printf("|    ");
			else
				printf("|%4d", Code[i][k]);
		}
		printf("|\n|");
		for (k = 0; k < L; k++)
		{
			if (k == L - 1)
				printf("\b");
			printf("-----");
		}
		printf("|\n");
	}


}

//产生随机数；
void Srand()
{
	int num[] = { 2,4 };    //产生随机数2和4的数组；
	int SranNum = 0;        //产生随机数对应在随机数组中的下标；
	int x = 0, y = 0, count = 0;
	srand((unsigned)time(NULL));
	SranNum = rand() % (sizeof(num) / sizeof(num[0]));
	x = rand() % L;
	y = rand() % L;
	while (count<L*L)
	{
		if (Code[x][y] == 0)
		{
			Code[x][y] = num[SranNum];
			break;
		}
		count++;
		y++;
		if (y == L)
		{
			y = 0;
			x++;
			if (x == L)
				x = 0;
		}
	}
}

//加载图片；
void LoadPictureGui()
{

	//加载游戏结束后的两张图片：开始和结束；
	loadimage(&StartAndEnd[1], _T("2048资源\\资源图片\\Win.jpg"), 700, 700);
	loadimage(&StartAndEnd[2], _T("2048资源\\资源图片\\Lose.jpg"), 700, 700);

	//加载游戏过程中所用的图片；
	initgraph(700, 700);
	loadimage(&picture[1], _T("2048资源\\资源图片\\0.jpg"), 100, 100);
	loadimage(&picture[2], _T("2048资源\\资源图片\\2.jpg"), 100, 100);
	loadimage(&picture[3], _T("2048资源\\资源图片\\4.jpg"), 100, 100);
	loadimage(&picture[4], _T("2048资源\\资源图片\\8.jpg"), 100, 100);
	loadimage(&picture[5], _T("2048资源\\资源图片\\16.jpg"), 100, 100);
	loadimage(&picture[6], _T("2048资源\\资源图片\\32.jpg"), 100, 100);
	loadimage(&picture[7], _T("2048资源\\资源图片\\64.jpg"), 100, 100);
	loadimage(&picture[8], _T("2048资源\\资源图片\\128.jpg"), 100, 100);
	loadimage(&picture[9], _T("2048资源\\资源图片\\256.jpg"), 100, 100);
	loadimage(&picture[10], _T("2048资源\\资源图片\\512.jpg"), 100, 100);
	loadimage(&picture[11], _T("2048资源\\资源图片\\1024.jpg"), 100, 100);
	loadimage(&picture[12], _T("2048资源\\资源图片\\2048.jpg"), 100, 100);
	loadimage(&picture[13], _T("2048资源\\资源图片\\score.jpg"), 100, 100);
	loadimage(&picture[14], _T("2048资源\\资源图片\\首页.jpg"), 400, 200);
	loadimage(&picture[15], _T("2048资源\\资源图片\\侧面.jpg"), 200, 700);

	putimage(0, 0, &picture[14]);
	putimage(400, 0, &picture[13]);
	putimage(500, 0, &picture[15]);
	putimage(400, 100, &picture[1]);

	//初始化界面；
	int X = 0, Y = 200;
	for (int i = 1; i <= 25; i++)
	{
		putimage(X, Y, &picture[1]);
		X += 100;
		if (i % 5 == 0)
		{
			X = 0;
			Y += 100;
			putimage(X, Y, &picture[1]);
		}
	}
}

//输出变换结果；
void Change_Interface()
{
	Max = MaxNum();  	
	//输出得分
	switch (Max)
	{
	case 0:
		putimage(400, 100, &picture[1]);
		break;
	case 2:
		putimage(400, 100, &picture[2]);
		break;
	case 4:
		putimage(400, 100, &picture[3]);
		break;
	case 8:
		putimage(400, 100, &picture[4]);
		break;
	case 16:
		putimage(400, 100, &picture[5]);
		break;
	case 32:
		putimage(400, 100, &picture[6]);
		break;
	case 64:
		putimage(400, 100, &picture[7]);
		break;
	case 128:
		putimage(400, 100, &picture[8]);
		break;
	case 256:
		putimage(400, 100, &picture[9]);
		break;
	case 512:
		putimage(400, 100, &picture[10]);
		break;
	case 1024:
		putimage(400, 100, &picture[11]);
		break;
	case 2048:
		putimage(400, 100, &picture[12]);
		return;
	default:
		break;
	}

	int X, Y;
	int count;
	int i,j,m = 0, n = 0;
	X = 0, Y = 200;
	for (i = 0; i <L; i++)
	{
		for (j = 0; j <L; j++)
		{	
			switch (Code[i][j])
			{
			case 0:
			{
				putimage(X, Y , &picture[1]);
				X += 100;
				//putimage(i*100, Y+j*100, &picture[1]);
				////X =100*count;

			}
			break;
			case 2:
			{
				putimage(X, Y, &picture[2]);
				X += 100;
				//putimage(i * 100, Y + j * 100, &picture[2]);
				////X =100*count;
			}
			break;
			case 4:
			{
				putimage(X, Y, &picture[3]);
				X += 100;
				//putimage(i * 100, Y + j * 100, &picture[3]);
				////X =100*count;
			}
			break;
			case 8:
			{
				putimage(X, Y, &picture[4]);
				X += 100;
			//	putimage(i * 100, Y + j * 100, &picture[4]);
			////X =100*count;
			}
			break;
			case 16:
			{
				putimage(X, Y, &picture[5]);
				X += 100;
				//putimage(i * 100, Y + j * 100, &picture[5]);
				//X =100*count;
			}
			break;
			case 32:
			{
				putimage(X, Y, &picture[6]);
				X += 100;
				//putimage(i * 100, Y + j * 100, &picture[6]);
			//X =100*count;
			}
			break;
			case 64:
			{
				putimage(X, Y, &picture[7]);
				X += 100;
				//putimage(i * 100, Y + j * 100, &picture[7]);
				//X =100*count;
			}
			break;
			case 128:
			{
				putimage(X, Y, &picture[8]);
				X += 100;
				//putimage(i * 100, Y + j * 100, &picture[8]);
				//X =100*count;
			}
			break;
			case 256:
			{
				putimage(X, Y, &picture[9]);
				X += 100;
				//putimage(i * 100, Y + j * 100, &picture[9]);
				//X =100*count;
			}
			break;
			case 512:
			{
				putimage(X, Y, &picture[10]);
				X += 100;
				//putimage(i * 100, Y + j * 100, &picture[10]);
				//X =100*count;
			}
			break;
			case 1024:
			{
				putimage(X, Y, &picture[11]);
				X += 100;
				//putimage(i * 100, Y + j * 100, &picture[11]);
				//X =100*count;
			}
			break;
			case 2048:
			{
				putimage(X, Y, &picture[12]);
				X += 100;
				//putimage(i * 100, Y + j * 100, &picture[12]);
				//X =100*count;
			}
			break;
			default:
				break;
			}
		}
		if (j % 5 == 0)
		{
			X = 0;
			Y += 100;
		}
	}
}

//左移；
void Left()
{
	int i, j, k, m;
	int t1; //记录数组temp中出现第一个 非0数字；
	int t2 = 0;  //记录数组temp中出现第二个 非0数字；
	for (i = 0; i < L; i++)
	{
		//把每一行的5个数放入临时一维数组中及逆行操作；
		for (j = 0; j < L; j++)
		{
			temp[j] = Code[i][j];
		}
		//对temp数组中的元素进行求和；
		for (j = 1, k = 0; j < L; j++)
		{
			if (temp[j] > 0)    //找出k后面第一个不为0的项，下标为j；之后分三种情况；
			{
				//第一中i情况，相邻两个数可相加；
				if (temp[k] == temp[j])
				{
					temp[k] += temp[j];
					Score += temp[k];
					temp[j] = 0;
					k++;
					break;
				}
				//第二种情况：数组的项temp[j]>0,temp[k]=0,只需将temp[j]前移到，temp[k]=temp[j],temp[j]=0;
				else if (temp[k] == 0)
				{
					temp[k] = temp[j];
					temp[j] = 0;
				}
				//第三种情况乱；数组的temp[k]!=0&&temp[j]!=0&&temp[j]!=temp[k];
				else
				{
					temp[k + 1] = temp[j];
					if (j != k + 1)
					{
						temp[j] = 0;
					}
					k = k + 1;
				}
			}

		}
		for (k = 0; k < L; k++)
		{
			Code[i][k] = temp[k];
		}
	}
}

//右移；
void Right()
{
	int i, j, k, m;
	int t1; //记录数组temp中出现第一个 非0数字；
	int t2 = 0;  //记录数组temp中出现第二个 非0数字；
	for (i = 0; i < L; i++)
	{
		//把每一行的5个数放入临时一维数组中及逆行操作；
		for (j = 0; j < L; j++)
		{
			temp[j] = Code[i][L - j - 1];
		}
		//对temp数组中的元素进行求和；
		for (j = 1, k = 0; j < L; j++)
		{
			if (temp[j] > 0)    //找出k后面第一个不为0的项，下标为j；之后分三种情况；
			{
				//第一中i情况，相邻两个数可相加；
				if (temp[k] == temp[j])
				{
					temp[k] += temp[j];
					Score += temp[k];
					temp[j] = 0;
					k++;
					break;
				}
				//第二种情况：数组的项temp[j]>0,temp[k]=0,只需将temp[j]前移到，temp[k]=temp[j],temp[j]=0;
				else if (temp[k] == 0)
				{
					temp[k] = temp[j];
					temp[j] = 0;
				}
				//第三种情况乱；数组的temp[k]!=0&&temp[j]!=0&&temp[j]!=temp[k];
				else
				{
					temp[k + 1] = temp[j];
					if (j != k + 1)
					{
						temp[j] = 0;
					}
					k = k + 1;
				}
			}

		}
		for (k = 0; k < L; k++)
		{
			Code[i][L - 1 - k] = temp[k];
		}
	}
}

//上移；
void Up()
{
	int i, j, k, m;
	int t1; //记录数组temp中出现第一个 非0数字；
	int t2 = 0;  //记录数组temp中出现第二个 非0数字；
	for (i = 0; i < L; i++)
	{
		//把每一行的5个数放入临时一维数组中及逆行操作；
		for (j = 0; j < L; j++)
		{
			temp[j] = Code[j][i];
		}
		//对temp数组中的元素进行求和；
		for (j = 1, k = 0; j < L; j++)
		{
			if (temp[j] > 0)    //找出k后面第一个不为0的项，下标为j；之后分三种情况；
			{
				//第一中i情况，相邻两个数可相加；
				if (temp[k] == temp[j])
				{
					temp[k] += temp[j];
					Score += temp[k];
					temp[j] = 0;
					k++;
					break;
				}
				//第二种情况：数组的项temp[j]>0,temp[k]=0,只需将temp[j]前移到，temp[k]=temp[j],temp[j]=0;
				else if (temp[k] == 0)
				{
					temp[k] = temp[j];
					temp[j] = 0;
				}
				//第三种情况乱；数组的temp[k]!=0&&temp[j]!=0&&temp[j]!=temp[k];
				else
				{
					temp[k + 1] = temp[j];
					if (j != k + 1)
					{
						temp[j] = 0;
					}
					k = k + 1;
				}
			}

		}
		for (k = 0; k < L; k++)
		{
			Code[k][i] = temp[k];
		}
	}
}

//下移；
void Down()
{
	int i, j, k, m;
	int t1; //记录数组temp中出现第一个 非0数字；
	int t2 = 0;  //记录数组temp中出现第二个 非0数字；
	for (i = 0; i < L; i++)
	{
		//把每一行的5个数放入临时一维数组中及逆行操作；
		for (j = 0; j < L; j++)
		{
			temp[j] = Code[L - 1 - j][i];
		}
		//对temp数组中的元素进行求和；
		for (j = 1, k = 0; j < L; j++)
		{
			if (temp[j] > 0)    //找出k后面第一个不为0的项，下标为j；之后分三种情况；
			{
				//第一中i情况，相邻两个数可相加；
				if (temp[k] == temp[j])
				{
					temp[k] += temp[j];
					Score += temp[k];
					temp[j] = 0;
					k++;
					break;
				}
				//第二种情况：数组的项temp[j]>0,temp[k]=0,只需将temp[j]前移到，temp[k]=temp[j],temp[j]=0;
				else if (temp[k] == 0)
				{
					temp[k] = temp[j];
					temp[j] = 0;
				}
				//第三种情况乱；数组的temp[k]!=0&&temp[j]!=0&&temp[j]!=temp[k];
				else
				{
					temp[k + 1] = temp[j];
					if (j != k + 1)
					{
						temp[j] = 0;
					}
					k = k + 1;
				}
			}

		}
		for (k = 0; k < L; k++)
		{
			Code[L - 1 - k][i] = temp[k];
		}
	}
}

//检查格子中是否右空格；
int Get_Null_Black()
{
	int i, j;
	int Null_Black_count = 0;
	for (i = 0; i < L; i++)
	{
		for (j = 0; j < L; j++)
		{
			if (Code[i][j] == 0)
				Null_Black_count++;
		}
	}
	return Null_Black_count;
}
//移动；
void Move()
{
	char c;
	int i = 0;
	char s[10] = "";
	//int t;  //用来存放判断游戏是否结束函数的返回值；
	int m = 0;   //用来记录空格数；
	Srand();
	Srand();
	//Interface();
	LoadPictureGui();
	fflush(stdin);
	c = getch();
	while (1)
	{

		switch (c)
		{
		case 'w':
		case'W':
		case 72:
			Up();
			break;
		case 'S':
		case 's':
		case 80:
			Down();
			break;
		case 'A':
		case 'a':
		case 75:
			Left();
			break;
		case 'd':
		case 'D':
		case 77:
			Right();
			break;
		default:
		{
			s[i++] = c;
			break;
		}
		}
		n++;      //记录得分的次数；
		m = Get_Null_Black();
		if (m == 0)
		{
			check_game_over();
			if (Check_Game_Over)
				return;
		}
		system("cls");
		Srand();
	//	Interface();
		Change_Interface();
		fflush(stdin);
		c = getch();
	}
}
int main(void)
{
	
	Move();
	if (Max >= 2048)
	{
		putimage(0,0, &StartAndEnd[1]);
	//	printf("Excellent！\n");
		Sleep(10000);
	}
	else
	{
		putimage(0, 0, &StartAndEnd[2]);
	//	printf("You are Lose!\n");
		Sleep(10000);
	}
	//getch();



	getch();
	closegraph();
	return 0;
}

