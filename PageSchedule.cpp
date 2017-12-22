/*********************************
*   ����ҳ������㷨ģ��         *
*   ���ߣ����Ĳ�                  *
*********************************/
#include<stdio.h>
#include<algorithm>
#include<iostream>
using namespace std;

//�����ȳ�FIFO
void FIFO(int *pages, int num, int block) {
	int *mem = (int *)malloc(block * sizeof(int));
	for (int i = 0; i < block; i++)
	{
		mem[i] = 0;
	}
	char *f = (char *)malloc(num * sizeof(char));
	int q, sum = 0;
	char flag;
	int ** List = new int *[block];
	for (int i = 0; i < block; i++)
	{
		List[i] = new int[num];
	}
	for (int i = 0; i < block; i++)
	{
		for (int j = 0; j < num; j++)
		{
			List[i][j] = 0;
		}
	}
	for (int i = 0; i<num; i++)               //��ҳ�����Ƿ�ȱҳ
	{
		q = 0;
		while ((pages[i] != mem[q]) && (q != block))
			q++;
		if (q == block)
			flag = '*';                       //ȱҳ�����ñ�־flagΪ'*'
		else
			flag = ' ';
		if (flag == '*')
		{
			for (int j = block - 1; j > 0; j--) //��̭���ȵ����ҳ����뵱ǰ���ʵ�
			{
				mem[j] = mem[j - 1];
			}
			mem[0] = pages[i];
		}
		for (int j = 0; j<block; j++)
			List[j][i] = mem[j];
		f[i] = flag;
	}
	cout << "\n----------------FIFO----------------" << endl;
	for (int i = 0; i<block; i++)
	{
		for (int j = 0; j<num; j++)
			cout << List[i][j] << "  ";
		cout << endl;
	}
	for (int i = 0; i<num; i++)
	{
		if (f[i] == '*')
			sum++;
		cout << f[i] << "  ";
	}
	cout << "\n-----------------------------------" << endl;
	cout << "ȱҳ����:" << sum << '\t' << "ȱҳ��:" << (float)sum / num * 100.0 << "%" << endl;
	for (int i = 0; i<block; ++i)
		delete[] List[i];
	delete[] List;
}

//������δʹ��LRU
void LRU(int *pages, int num, int block) {
	int *mem = (int *)malloc(block * sizeof(int));
	for (int i = 0; i < block; i++)
	{
		mem[i] = 0;
	}
	char *f = (char *)malloc(num * sizeof(char));
	int q, sum = 0;
	char flag;
	int ** List = new int *[block];
	for (int i = 0; i < block; i++)
	{
		List[i] = new int[num];
	}
	for (int i = 0; i < block; i++)
	{
		for (int j = 0; j < num; j++)
		{
			List[i][j] = 0;
		}
	}
	for (int i = 0; i<num; i++)         //��ҳ�����Ƿ�ȱҳ
	{
		q = 0;
		while ((pages[i] != mem[q]) && (q != block))
			q++;
		if (q == block)
			flag = '*';                 //ȱҳ�����ñ�־flagΪ'*'
		else
			flag = ' ';
		for (int j = q; j>0; j--)
			mem[j] = mem[j - 1];
		mem[0] = pages[i];
		for (int j = 0; j<block; j++)
		{
			List[j][i] = mem[j];
		}
		f[i] = flag;
	}
	cout << "\n----------------LRU-----------------" << endl;
	for (int i = 0; i<block; i++)
	{
		for (int j = 0; j<num; j++)
			cout << List[i][j] << "  ";
		cout << endl;
	}
	for (int i = 0; i<num; i++)
	{
		if (f[i] == '*')
			sum++;
		cout << f[i] << "  ";
	}
	cout << "\n-----------------------------------" << endl;
	cout << "ȱҳ����:" << sum << '\t' << "ȱҳ��:" << (float)sum / num * 100 << "%" << endl;
	for (int i = 0; i<block; ++i)
		delete[] List[i];
	delete[] List;
}

int main(int argc, char const *argv[]) {
	int num, block;
	cout << "������ҳ��������";
	cin >> num;
	int *pages = (int *)malloc(num * sizeof(int));
	for (int i = 0; i < num; i++) {
		cin >> pages[i];     
	}
	cout << "����������ڴ������";
	cin >> block;
	//����ҳ������㷨
	FIFO(pages, num, block);  //�����ȳ� FIFO
	LRU(pages, num, block);   //������δʹ�� LRU
	delete[] pages;
	pages = NULL;
	cout << endl;
	system("pause");
	return 0;
}