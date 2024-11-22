#include<stdio.h>
#include<process.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#define WIDTH 60
#define HEIGHT 20
enum direction
{
	LEFT, RIGHT, UP, DOWN
};
struct structFood
{
	int x;
	int y;
};

struct structNode
{
	int x;
	int y;
	struct structNode* pNext;
};

struct structSnake
{
	int length;
	enum direction dir;
};

struct structFood* pFood;

struct structSnake* pSnake;
struct structNode* pNode, * pTail;
int speech = 250;
double score = 0;
double lastscore = 0;

char level = 'F';
double maxeat = 0;
int smark = 0;
int stop = 0;
int counttime = 0;
int countfood = 0;
time_t start, end;
void hideCursor(void);
void gotoXY(int x, int y);
void initSnake(void);
void addNode(int x, int y);

void	initFood(void);
void	homePage(void);
void	keybordHit(void);
void	move(void);
void	draw(void);
void	eatFood(void);
void	addTail(void);
void	showresult(void);
void	record(void);
void	getlastscoreandlevel(void);

int main(void)
{
	start = time(NULL);
	homePage();
	while (stop == 0)
	{
		keybordHit();
		move();
		draw();
		Sleep(speech);
	}
	return 0;
}

void hideCursor(void)
{
	CONSOLE_CURSOR_INFO cursorInfo = { 1,0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void gotoXY(int x, int y)
{
	COORD pos;

	pos.X = x - 1;
	pos.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void addNode(int x, int y)
{
	struct structNode* newnode = (struct structNode*)malloc(sizeof(struct structNode));
	struct structNode* p = pNode;
	newnode->pNext = pNode;
	newnode->x = x;
	newnode->y = y;
	pNode = newnode;
	if (x < 2 || x >= WIDTH || y < 2 || y >= HEIGHT)
	{
		stop = 1;
		gotoXY(21, 21);
		printf("ײǽ,��Ϸ����,��������˳�!");
		getch();
		free(pNode);
		free(pSnake);
		showresult();
		exit(0);
	}

	while (p != NULL)
	{
		if (p->pNext != NULL)
		{
			if ((p->x == x) && (p->y == y))
			{
				stop = 1;
				gotoXY(21, 21);
				printf("ײ��?? ,��Ϸ����,��������˳�!");
				getch();
				free(pNode);
				free(pSnake);
				showresult();
				exit(0);
			}
		}
		p = p->pNext;
	}
}


void initSnake(void)
{
	int i;
	pSnake = (struct structSnake*)malloc(sizeof(struct structSnake));
	pFood = (struct structFood*)malloc(sizeof(struct structFood));
	pSnake->length = 5;
	pSnake->dir = RIGHT;
	for (i = 2;i <= pSnake->length + 2;i++)
		addNode(i, 2);
}

void homePage(void)
{
	hideCursor();
	printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");

	printf("x\t\t\t\t\t\t\t	x\n");
	printf("x\t\t\t\t\t\t\t	x\n");
	printf("x\t\t\t\t\t\t\t	x\n");
	printf("x\t\t\t\t\t\t\t	x\n");
	printf("x\t\t\t\t\t\t\t	x\n");
	printf("x\t\t\t\t\t\t\t	x\n");
	printf("x\t\t\t\t\t\t\t	x\n");
	printf("x\t\t\t\t\t\t\t	x\n");
	printf("x\t\t\t\t\t\t\t	x\n");
	printf("x\t\t\t\t\t\t\t	x\n");
	printf("x\t\t\t\t\t\t\t	x\n");
	printf("x\t\t\t\t\t\t\t	x\n");
	printf("x\t\t\t\t\t\t\t	x\n");
	printf("x\t\t\t\t\t\t\t	x\n");
	printf("x\t\t\t\t\t\t\t	x\n");
	printf("x\t\t\t\t\t\t\t	x\n");
	printf("x\t\t\t\t\t\t\t	x\n");
	printf("x\t\t\t\t\t\t\t	x\n");
	printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
	gotoXY(5, 13);
	printf("���������ʼ��Ϸ!�� W ��A ��S ��D ����?��");
	getch();
	initSnake();
	initFood();
	gotoXY(5, 13);
	printf("                                                                      ");
}

void keybordHit(void)
{
	char ch;
	if (kbhit())
	{
		ch = getch();
		switch (ch)
		{
		case 'W':
		case 'w':
		{
			if (pSnake->dir == DOWN)
				break;
			else
				pSnake->dir = UP;
		}break;
		case 'A':
		case 'a':
		{
			if (pSnake->dir == RIGHT)
				break;
			else
				pSnake->dir = LEFT;
		}break;
		case 'S':
		case 's':
		{
			if (pSnake->dir == UP)
				break;
			else
				pSnake->dir = DOWN;
		}break;
		case 'D':
		case 'd':
		{
			if (pSnake->dir == LEFT)
				break;
			else
				pSnake->dir = RIGHT;
		}break;
		case 'O':
		case 'o':
		{
			if (speech >= 110)

				speech = speech - 10;
		}break;
		case 'P':
		case 'p':
		{
			if (speech <= 490)
				speech = speech + 10;
		}break;
		case 27:
		{
			gotoXY(25, 22);
			printf("��Ϸ����");
			showresult();
			exit(0);
		}

		case ' ':
		{
			gotoXY(25, 22);
			printf("��Ϸ����ͣ����������ָ���Ϸ");
			system("pause>nul");
			gotoXY(25, 22);
			printf("                                                     ");
		}break;
		default:break;
		}
	}
}

void initFood(void)
{
	struct structNode* p = pNode;
	int mark = 1;
	srand((unsigned)time(NULL));
	while (1)
	{
		pFood->x = rand() % (WIDTH - 2) + 2;
		pFood->y = rand() % (HEIGHT - 2) + 2;
		if (pFood->x == 1 || pFood->x == 2 || pFood->x == 3 || pFood->y == 1 || pFood->y == 2 || pFood->y = = 3)
			mark = 0;
		if (pFood->x == WIDTH - 1 || pFood->x == WIDTH - 2 || pFood->x == WIDTH -
			3 || pFood->y == HEIGHT - 1 || pFood->y == HEIGHT - 2 || pFood->y == HEIGHT - 3) mark = 0;

		while (p != NULL)
		{
			if ((pFood->x == p->x) && (pFood->y == p->y))
			{
				mark = 0;
				break;
			}
			p = p->pNext;
		}
		if (mark == 1)
		{
			gotoXY(pFood->x, pFood->y);
			printf("%c", 'f');
			break;
		}
		mark = 1;
		p = pNode;
	}
}

void move(void)
{
	struct structNode* q, * p = pNode;
	if (pSnake->dir == RIGHT)
	{
		addNode(p->x + 1, p->y);
		if (smark == 0)
		{
			while (p->pNext != NULL)
			{
				q = p;
				p = p->pNext;
			}
			q->pNext = NULL;
			free(p);
		}
	}
	if (pSnake->dir == LEFT)
	{
		addNode(p->x - 1, p->y);
		if (smark == 0)
		{
			while (p->pNext != NULL)
			{

				q = p;
				p = p->pNext;
			}
			q->pNext = NULL;
			free(p);
		}
	}
	if (pSnake->dir == UP)
	{
		addNode(p->x, p->y - 1);
		if (smark == 0)
		{
			while (p->pNext != NULL)
			{
				q = p;
				p = p->pNext;
			}
			q->pNext = NULL;
			free(p);
		}
	}
	if (pSnake->dir == DOWN)
	{
		addNode(p->x, p->y + 1);
		if (smark == 0)
		{
			while (p->pNext != NULL)
			{
				q = p;
				p = p->pNext;
			}
			q->pNext = NULL;
			free(p);
		}
	}
}

void draw(void)
{
	struct structNode* p = pNode;
	while (p != NULL)
	{
		gotoXY(p->x, p->y);
		printf("%c", 'c');

		pTail = p;
		p = p->pNext;
	}
	if (pNode->x == pFood->x && pNode->y == pFood->y)
	{
		smark = 1;
		eatFood();
		initFood();
	}
	if (smark == 0)
	{
		gotoXY(pTail->x, pTail->y);
		printf("%c", ' ');
	}
	else
	{
		gotoXY(pTail->x, pTail->y);
		printf("%c", ' ');
		smark = 0;
	}
	gotoXY(70, 3);
	printf("̰����?��Ϸ");
	gotoXY(70, 17);
	printf("��?����:%.2lf", maxeat);
	gotoXY(70, 13);
	end = time(NULL);
	counttime = (int)difftime(end = time(NULL), start);
	printf("ʱ��:%ds", counttime);
	gotoXY(70, 5);
	printf("����:%.0lf(%.2lf)", score, score);
	gotoXY(70, 9);
	printf("�Թ���?��:%d", countfood);
	gotoXY(70, 7);
	printf("        ��         ��        ��         ?        ��         ��        ��         ��        ��         :%.2lf", (((500 - speech) / 80.0) * ((countfood + 30.0) / 30.0) * ((counttime + 150.0) / 150.0) * ((score + 100.0) / 100.0)) + 1);
	gotoXY(70, 11);
	printf("�ٶ�:%d", speech);
	gotoXY(25, 24);
	printf("�� o ������");
	gotoXY(25, 25);
	printf("�� p ������");
	gotoXY(25, 26);
	printf("�ٶ��� 100(��)-500(��)֮��");
	gotoXY(25, 27);


	printf("���ո����ͣ");
	gotoXY(25, 28);
	printf("�� esc ���˳�");
	gotoXY(70, 15);
	printf("?��:%02d,%02d", pFood->x, pFood->y);
}

void eatFood(void)
{
	double scoreup;
	addTail();
	countfood++;
	scoreup = (((500 -
		speech) / 80.0) * ((countfood + 30.0) / 30.0) * ((counttime + 150.0) / 150.0) * ((score + 100.0) / 100.0)) + 1;
	score += scoreup;
	if (scoreup >= maxeat)
		maxeat = scoreup;
}

void addTail(void)
{
	struct structNode* newnode = (struct structNode*)malloc(sizeof(struct structNode)); struct structNode* p = pNode;
	pTail->pNext = newnode;
	newnode->x = 70;
	newnode->y = 30;
	newnode->pNext = NULL;
	pTail = newnode;
}

void showresult()
{
	system("cls");
	getlastscoreandlevel();
	gotoXY(20, 3);
	printf("��Ϸ���");
	gotoXY(20, 11);
	end = time(NULL);
	counttime = (int)difftime(end = time(NULL), start);
	printf("��Ϸʱ��:%ds", counttime);
	gotoXY(20, 5);
	printf("��Ϸ����:%.0lf(%.2lf)", score, score);
	gotoXY(20, 9);

	printf("�ܹ�?��:%d", countfood);
	gotoXY(20, 7);
	printf("��?����:%.2lf", maxeat);
	gotoXY(20, 17);
	printf("�밴���������...");
	gotoXY(20, 13);
	printf("��Ϸ����:%.2lf", lastscore);
	gotoXY(20, 15);
	printf("��Ϸ����:%c", level);
	record();
	getch();
}

void record(void)
{
	FILE* fp;
	fp = fopen("data.txt", "a");
	fprintf(fp, "%-16s|%-16s|%-20s|%-16s|%-40s", "��Ϸʱ��", "�ܹ�?��", "����", "����", "��Ϸ����"); fprintf(fp, "\n");
	fprintf(fp, "%-16d|%-16d|%-20.1lf|%-16c|%-40.2lf", counttime, countfood, lastscore, level, score); fprintf(fp, "\n");
	fclose(fp);
}

void getlastscoreandlevel(void)
{
	int time = counttime, food = countfood;
	int i = 0;
	if (score == 0)
		i = i + 0;
	else if (score > 0 && score <= 10)
		i = i + 10;
	else if (score > 10 && score <= 100)
		i = i + 20;
	else if (score > 100 && score <= 1000)
		i = i + 30;
	else if (score > 1000 && score <= 10000)
		i = i + 40;
	else if (score > 10000 && score <= 100000)
		i = i + 50;
	else if (score > 100000 && score <= 1000000)
		i = i + 60;
	else if (score > 1000000 && score <= 10000000)

	else if (score > 10000000 && score <= 100000000)
		i = i + 80;
	else if (score > 100000000 && score <= 1000000000)
		i = i + 90;
	else
		i = i + 100;
	i = i + food;
	if (time == 0)
		i = i + 0;
	else if (time > 0 && time < 60)
		i = i + 40;
	else if (time > 0 && time < 180)
		i = i + 30;
	else if (time > 0 && time < 600)
		i = i + 20;
	else
		i = i + 10;
	if (score == 0)
		i = 0;
	lastscore = (double)(i / 10.0);
	if (lastscore == 0)
		level = 'F';
	else if (lastscore > 0 && lastscore <= 3)
		level = 'E';
	else if (lastscore > 3 && lastscore <= 6)
		level = 'D';
	else if (lastscore > 6 && lastscore <= 9)
		level = 'C';
	else if (lastscore > 9 && lastscore <= 12)
		level = 'B';
	else if (lastscore > 12 && lastscore <= 15)
		level = 'A';
	else
		level = 'S';
	��
		�ο�����δ��ɲ���

}