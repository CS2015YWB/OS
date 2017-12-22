/*********************************
*   ���򣺷���ʽ�洢����ģ��       *
*   ���ߣ����Ĳ�                  *
*********************************/
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>
#include<iostream>
#include<algorithm>
using namespace std;

typedef struct {
	int no;         //�������
	int pos;        //����λ��
	int size;       //������С
	int req[50];    //��¼�ÿ��з����ķ�������
}RAM;

typedef struct {
	int size;       //������С
	bool find;     //�ж��Ƿ����ҵ����з���
}Request;

//�����ڴ���з�������
void RAMSeq(RAM *ram, int m, RAM *copy)
{
	for (int i = 0; i < m; i++)
	{
		ram[i].no = i+1;
		cin >> ram[i].pos >> ram[i].size;
	}
	for (int i = 0; i < m; i++)
	{
		
		copy[i].pos = ram[i].pos;
		copy[i].size = ram[i].size;
	}
}

//������������
void ReqSeq(Request *request,int n)
{
	for (int i = 0; i < n; i++)
	{
		cin >> request[i].size;
		request[i].find = 0;
	}
}

//�ṹ���������,�Ӵ�С
bool cmp1(RAM a, RAM b) 
{
	return a.size < b.size;
}
bool cmp2(RAM a, RAM b)
{
	return a.size > b.size;
}
bool cmp3(RAM a, RAM b)
{
	return a.no < b.no;
}

//������Ӧ�㷨   num ���з�������    n ������������
void FirstFit(int num, RAM *ram, int n, Request *request, RAM *copy1)
{
	int flag;
	for (int i = 0; i < num; i++)
	{
		flag = 0;
		for (int j = 0; j < n;)
		{
			if (request[j].size <= ram[i].size && !request[j].find)
			{
				ram[i].size -= request[j].size;
				request[j].find = 1;
				ram[i].req[flag] = request[j].size;
				flag++;
				j++;
			}
			else
			{
				j++;
			}
		}
	}
	cout << "-------------Answer--------------" << endl;
	cout <<"No." << '\t' << "begin" << '\t' << "free" << '\t' << "result" << endl;
	for (int i = 0; i < num; i++)
	{
		cout << ram[i].no << '\t' << (ram[i].pos + copy1[i].size - ram[i].size) << '\t' << ram[i].size << '\t';
		for (int j = 0; j < n; j++)
		{
			if (ram[i].req[j] > 0) 
			{
				cout << ram[i].req[j] << ' ';
			}
		}
		cout << endl;
	}
	for (int j = 0; j < n; j++)
	{
		if (!request[j].find)
		{
			cout << "Not satisfied��" << request[j].size << " ";
		}
	}
	cout << endl;
}

//�����Ӧ�㷨
void BestFit(int num, RAM *ram1, int n, Request *request1, RAM *copy2)
{
	sort(ram1, ram1 + num, cmp1);
	int flag;
	for (int i = 0; i < num; i++)
	{
		flag = 0;
		for (int j = 0; j < n;)
		{
			if (request1[j].size <= ram1[i].size && !request1[j].find)
			{
				ram1[i].size -= request1[j].size;
				request1[j].find = 1;
				ram1[i].req[flag] = request1[j].size;
				flag++;
				j++;
			}
			else
			{
				j++;
			}
		}
	}
	sort(ram1, ram1 + num, cmp3);
	cout << "-------------Answer--------------" << endl;
	cout << "No." << '\t' << "begin" << '\t' << "free" << '\t' << "result" << endl;
	for (int i = 0; i < num; i++)
	{
		cout << ram1[i].no << '\t' << (ram1[i].pos + copy2[i].size - ram1[i].size) << '\t' << ram1[i].size << '\t';
		for (int j = 0; j < n; j++)
		{
			if (ram1[i].req[j] > 0)
			{
				cout << ram1[i].req[j] << ' ';
			}
		}
		cout << endl;
	}
	for (int j = 0; j < n; j++)
	{
		if (!request1[j].find)
		{
			cout << "Not satisfied��" << request1[j].size << " ";
		}
	}
	cout << endl;
}

//���Ӧ�㷨
void WorstFit(int num, RAM *ram2, int n, Request *request2, RAM *copy3)
{
	sort(ram2, ram2 + num, cmp2);
	int flag;
	for (int i = 0; i < num; i++)
	{
		flag = 0;
		for (int j = 0; j < n;)
		{
			if (request2[j].size <= ram2[i].size && !request2[j].find)
			{
				ram2[i].size -= request2[j].size;
				request2[j].find = 1;
				ram2[i].req[flag] = request2[j].size;
				flag++;
				j++;
			}
			else
			{
				j++;
			}
		}
	}
	sort(ram2, ram2 + num, cmp3);
	cout << "-------------Answer--------------" << endl;
	cout << "No." << '\t' << "begin" << '\t' << "free" << '\t' << "result" << endl;
	for (int i = 0; i < num; i++)
	{
		cout << ram2[i].no << '\t' << (ram2[i].pos + copy3[i].size-ram2[i].size) << '\t' << ram2[i].size << '\t';
		for (int j = 0; j < n; j++)
		{
			if (ram2[i].req[j] > 0)
			{
				cout << ram2[i].req[j] << ' ';
			}
		}
		cout << endl;
	}
	for (int j = 0; j < n; j++)
	{
		if (!request2[j].find)
		{
			cout << "Not satisfied��" << request2[j].size << " ";
		}
	}
	cout << endl;
}

int main(int argc, char const *argv[])
{
	int num1, num2, num3, n1, n2, n3;    //num1 num2 num3���з�������   n1 n2 n3����������������
	//���ַ����洢�����㷨
	//------------------------------------------
	cout << "--------------�״���Ӧ�㷨--------------" << endl;
	cout << "�����ڴ���з�������: ";
	cin >> num1;
	RAM *ram = (RAM *)malloc(num1 * sizeof(RAM));
	RAM *copy1 = (RAM *)malloc(num1 * sizeof(RAM));
	cout << "�����ڴ���з������У�" << endl;
	//���з���λ�� | ���з�����С
	RAMSeq(ram, num1,copy1);
	cout << "����������������: ";
	cin >> n1;
	Request *request = (Request *)malloc(n1 * sizeof(Request));
	cout << "��������������У�" << endl;
	//������������ | 
	ReqSeq(request, n1);
	FirstFit(num1, ram, n1, request,copy1);   //�״���Ӧ�㷨
	//-----------------------------------------
	cout << endl << "--------------�����Ӧ�㷨--------------" << endl;
	cout << "�����ڴ���з�������: ";
	cin >> num2;
	RAM *ram1 = (RAM *)malloc(num2 * sizeof(RAM));
	RAM *copy2 = (RAM *)malloc(num1 * sizeof(RAM));
	cout << "�����ڴ���з������У�" << endl;
	//���з���λ�� | ���з�����С
	RAMSeq(ram1, num2,copy2);
	cout << "����������������: ";
	cin >> n2;
	Request *request2 = (Request *)malloc(n2 * sizeof(Request));
	cout << "��������������У�" << endl;
	//������������ | 
	ReqSeq(request2, n2);
	BestFit(num2, ram1, n2, request2,copy2);    //�����Ӧ�㷨
	//-----------------------------------------
	cout << endl << "--------------���Ӧ�㷨--------------" << endl;
	cout << "�����ڴ���з�������: ";
	cin >> num3;
	RAM *ram2 = (RAM *)malloc(num3 * sizeof(RAM));
	RAM *copy3 = (RAM *)malloc(num3 * sizeof(RAM));
	cout << "�����ڴ���з������У�" << endl;
	//���з���λ�� | ���з�����С
	RAMSeq(ram2, num3, copy3);
	cout << "����������������: ";
	cin >> n3;
	Request *request3 = (Request *)malloc(n3 * sizeof(Request));
	cout << "��������������У�" << endl;
	//������������ | 
	ReqSeq(request3, n3);
	WorstFit(num3, ram2, n3, request3, copy3);   //���Ӧ�㷨
	//-----------------------------------------
	delete[] ram;      //�ͷŶ�̬����
	ram = NULL;
	delete[] request;  //�ͷŶ�̬����
	request = NULL;
	system("pause");
	return 0;
}