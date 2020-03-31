#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 存储学生成绩的数据结构
typedef struct student{
	char name[20];
	char stuId[14];
	int math;
	int English;
	int politics;
	int specCourse;
	int totalScore;
}Student;

typedef Student ElemType;
// 链表结点
typedef struct node{
	ElemType data;
	struct node *next;
}ListNode;

// 创建链表
ListNode *creatList()
{
	ListNode *head = (ListNode*)calloc(1, sizeof(ListNode));
	return head;
}
// 创建结点
ListNode *creatNode(ElemType data)
{
	ListNode *newNode = (ListNode*)calloc(1, sizeof(ListNode));
	strcpy(newNode->data.name, data.name);
	strcpy(newNode->data.stuId, data.stuId);
	newNode->data.English = data.English;
	newNode->data.math = data.math;
	newNode->data.politics = data.politics;
	newNode->data.specCourse = data.specCourse;
	newNode->data.totalScore = data.totalScore;
	newNode->next = NULL;
	return newNode;
}

// 插入结点
void insertNode(ListNode *head, ElemType data)
{
	ListNode *p = creatNode(data);
	p->next = head->next;
	head->next = p;
	++(head->data.totalScore); // 存储总人数
}

// 删除结点
void deleteNode(ListNode *head, char *name)
{
	ListNode *pre = head, *p = head->next;
	if(p == NULL)
	{
		printf("暂未录入学生信息，删除失败！\n");
		return;
	}
	while(p && strcmp(p->data.name, name) != 0)
	{
		pre = p;
		p = p->next;
	}
	if(p == NULL)
	{
		printf("未找到该学生信息，删除失败！\n");
		return;
	}
	pre->next = p->next;
	--(head->data.totalScore);
	free(p);
}

// 查找结点
ListNode *searchNode(ListNode *head, char *name)
{
	ListNode *p = head->next;
	while(p && strcmp(p->data.name, name))
	{
		p = p->next;
	}
	if(p == NULL)
	{
		printf("未找到该学生信息！\n");
	}
	return p;
}

// 链表排序-->按学号
void sortListById(ListNode *head)
{
	ListNode *q, *tmp, *pre, *p = head->next;
	head->next = NULL;
	while(p)
	{
		q = p->next;
		pre = head;
		tmp = head->next;
		while(tmp && strcmp(tmp->data.stuId, p->data.stuId) < 0)
		{
			pre = tmp;
			tmp = tmp->next;
		}
		p->next = pre->next;
		pre->next = p;
		p = q;
	}
}

// 链表排序-->按总分
void sortListBySore(ListNode *head)
{
	ListNode *q, *tmp, *pre, *p = head->next;
	head->next = NULL;
	while(p)
	{
		q = p->next;
		pre = head;
		tmp = head->next;
		while(tmp && tmp->data.totalScore < p->data.totalScore)
		{
			pre = tmp;
			tmp = tmp->next;
		}
		p->next = pre->next;
		pre->next = p;
		p = q;
	}
}

// 打印链表
void printList(ListNode *head)
{
	ListNode *p = head->next;
	if(p == NULL) 
	{
		printf("还未录入学生成绩\n");
		return;
	}
	printf("学号\t姓名\t英语\t政治\t数学\t专业课\t总分\n");
	while(p)
	{
		printf("\n%s\t%s\t%d\t%d\t%d\t%d\t%d\n", p->data.stuId, p->data.name, p->data.English, p->data.politics, p->data.math, p->data.specCourse, p->data.totalScore);
		p = p->next;
	}
	printf("----------------------------------------------------------\n");
	printf("共计 %d 人\n", head->data.totalScore);
}

// 文件读操作
void readInfoFromFile(ListNode *head, char *fileName)
{
	FILE *fp;
	ElemType data;
	fp = fopen(fileName, "r");
	if(fp == NULL)
	{
		fp = fopen(fileName, "w+");
	}
	while(fscanf(fp, "%s\t%s\t%d\t%d\t%d\t%d\t%d\n", data.stuId, data.name, &data.English, &data.politics, &data.math, &data.specCourse, &data.totalScore) != EOF)
	{
		insertNode(head, data);
	}
	fclose(fp);
}

// 文件写操作
void writeInfoToFile(ListNode *head, char *fileName)
{
	FILE *fp;
	ListNode *p = head->next;
	fp = fopen(fileName, "w");
	while(p)
	{
		fprintf(fp, "%s\t%s\t%d\t%d\t%d\t%d\t%d\n", p->data.stuId, p->data.name, p->data.English, p->data.politics, p->data.math, p->data.specCourse, p->data.totalScore);
		p = p->next;
	}
	fclose(fp);
}
// 初始界面
void menu()
{
	printf("*********************学生成绩管理系统*********************\n\n");
	printf("\t\t\t0.退出系统\n\n");
	printf("\t\t\t1.显示全部\n\n");
	printf("\t\t\t2.添加成绩\n\n");
	printf("\t\t\t3.删除成绩\n\n");
	printf("\t\t\t4.修改成绩\n\n");
	printf("\t\t\t5.查找成绩\n\n");
	printf("**********************************************************\n");
}

// 按键操作 0 - 5
void keyDown(ListNode *head)
{
	int flag = 1, op, sortOp;
	char name[20] = {0};
	ElemType stu;
	ListNode *p;
	printf("请输入要执行的操作（0 - 5）：");
	scanf("%d", &op);
	switch (op)
	{
	case 0:
		exit(0);
		break;
	case 1:
		printf("*************************显示全部*************************\n");
		while(flag)
		{
			printf("请输入（1.按学号排序 2.按总分排序 3.其他）：");
			scanf("%d", &sortOp);
			printf("**********************************************************\n");
			if(sortOp == 1)
				sortListById(head);
			if(sortOp == 2)
				sortListBySore(head);
			printList(head);
			printf("----------------------------------------------------------\n");
			printf("请输入（0.回到主界面 1.继续查看）：");
			scanf("%d", &flag);
			while(flag != 1 && flag != 0)
			{
				printf("输入不合法，请重新输入：");
				scanf("%d", &flag);
			}
			printf("----------------------------------------------------------\n");
		}
		break;
	case 2:
		printf("*************************添加成绩*************************\n");
		while(flag)
		{
			printf("请输入学生学号：");
			fflush(stdin);
			scanf("%s", stu.stuId);
			printf("请输入学生姓名：");
			fflush(stdin);
			scanf("%s", stu.name);
			printf("请输入英语成绩：");
			scanf("%d", &(stu.English));
			printf("请输入政治成绩：");
			scanf("%d", &(stu.politics));
			printf("请输入数学成绩：");
			scanf("%d", &(stu.math));
			printf("请输入专业成绩：");
			scanf("%d", &(stu.specCourse));
			stu.totalScore = stu.English + stu.math + stu.politics + stu.specCourse;
			insertNode(head, stu);
			printf("----------------------------------------------------------\n");
			printf("请输入（0.添加结束 1.继续添加）：");
			scanf("%d", &flag);
			while(flag != 1 && flag != 0)
			{
				printf("输入不合法，请重新输入：");
				scanf("%d", &flag);
			}
			printf("----------------------------------------------------------\n");
		}
		printf("添加成功!\n");
		printf("----------------------------------------------------------\n");
		break;
	case 3:
		printf("*************************删除成绩*************************\n");
		while(flag)
		{
			printf("请输入要删除的学生姓名：");
			scanf("%s", &name);
			deleteNode(head, name);
			printf("----------------------------------------------------------\n");
			printf("请输入（0.删除结束 1.继续删除）：");
			scanf("%d", &flag);
			while(flag != 1 && flag != 0)
			{
				printf("输入不合法，请重新输入：");
				scanf("%d", &flag);
			}
			printf("----------------------------------------------------------\n");
		}
		printf("删除成功!\n");
		printf("----------------------------------------------------------\n");
		break;
	case 4:
		printf("*************************修改成绩*************************\n");
		while(flag)
		{
			printf("请输入要修改的学生姓名：");
			fflush(stdin);
			scanf("%s", &name);
			p = searchNode(head, name);
			if(p)
			{
				printf("请输入修改后的英语成绩（不修改则输入-1）：");
				scanf("%d", &(stu.English));
				p->data.English = stu.English != -1 ? stu.English : p->data.English;
				printf("请输入修改后的政治成绩（不修改则输入-1）：");
				scanf("%d", &(stu.politics));
				p->data.politics = stu.politics != -1 ? stu.politics : p->data.politics;
				printf("请输入修改后的数学成绩（不修改则输入-1）：");
				scanf("%d", &(stu.math));
				p->data.math = stu.math != -1 ? stu.math : p->data.math;
				printf("请输入修改后的专业成绩（不修改则输入-1）：");
				scanf("%d", &(stu.specCourse));
				p->data.specCourse = stu.specCourse != -1 ? stu.specCourse : p->data.specCourse;
				p->data.totalScore = p->data.English + p->data.math + p->data.politics + p->data.specCourse;
			}
			printf("----------------------------------------------------------\n");
			printf("请输入（0.修改结束 1.继续修改）：");
			scanf("%d", &flag);
			while(flag != 1 && flag != 0)
			{
				printf("输入不合法，请重新输入：");
				scanf("%d", &flag);
			}
			printf("----------------------------------------------------------\n");
		}
		printf("修改成功！\n");
		printf("----------------------------------------------------------\n");
		break;
	case 5:
		printf("*************************查找成绩*************************\n");
		while(flag)
		{
			printf("请输入要查找的学生姓名：");
			fflush(stdin);
			scanf("%s", name);
			printf("----------------------------------------------------------\n");
			p = searchNode(head, name);
			if(p)
			{
				printf("学号\t姓名\t英语\t政治\t数学\t专业课\t总分\n");
				printf("\n%s\t%s\t%d\t%d\t%d\t%d\t%d\n", p->data.stuId, p->data.name, p->data.English, p->data.politics, p->data.math, p->data.specCourse, p->data.totalScore);
			}
			printf("----------------------------------------------------------\n");
			printf("请输入（0.查找结束 1.继续查找）：");
			scanf("%d", &flag);
			while(flag != 1 && flag != 0)
			{
				printf("输入不合法，请重新输入：");
				scanf("%d", &flag);
			}
			printf("----------------------------------------------------------\n");
		}
		break;
	default:
		printf("----------------------------------------------------------\n");
		printf("输入错误，请重新输入！\n");
		printf("----------------------------------------------------------\n");
		system("pause");
		break;
	}
	writeInfoToFile(head, "student.text");
}

void main()
{
	// 创建空白学生表
	ListNode *head = creatList();
	readInfoFromFile(head, "student.text");
	while(1)
	{
		// 打印主界面
		menu();
		// 用户交互
		keyDown(head);
		system("pause");
		system("cls");
	}
	system("pause");
}
