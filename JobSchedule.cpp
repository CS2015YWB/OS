/*********************************
*   ������ҵ�����㷨ģ��         *
*   ���ߣ����Ĳ�                  *
*********************************/
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>
#include<iostream>
#include<algorithm>
using namespace std;

typedef struct {
	char no;                       //��ҵ���
	int arrive;                    //����ʱ��
	int run;                       //����ʱ��
	int start;                     //��ʼִ��ʱ��
	int end;                       //���ʱ��
	int turnover;                  //��תʱ��
	float withweightturnover;      //��Ȩ��תʱ��
	int wait;                      //�ȴ�ʱ��
}JOBS;

//�ṹ���������
bool cmp(JOBS a, JOBS b)
{
	return a.arrive < b.arrive;
}

//������ҵ����
void JobSeq(JOBS *jobs, int n)
{
	cout << "������ҵ���У�"<<endl;
	for (int i = 0; i < n; i++)
	{
		cin >> jobs[i].no >> jobs[i].arrive >> jobs[i].run;
	}
}

//�����ȷ�������㷨
int FCFS(JOBS *jobs, int n)
{
	double sumturnover, sumwithweightturnover, avgturnover, avgwithweightturnover;
	sort(jobs, jobs + n, cmp);
	sumturnover = sumwithweightturnover = 0;
	jobs[0].start = jobs[0].arrive;
	jobs[0].end = jobs[0].arrive + jobs[0].run;
	for (int i = 1; i<n; i++)
	{
		if (jobs[i - 1].end>jobs[i].arrive)
		{
			jobs[i].start = jobs[i - 1].end;
			jobs[i].end = jobs[i - 1].end + jobs[i].run;
		}
		else
		{
			jobs[i].start = jobs[i].arrive;
			jobs[i].end = jobs[i].arrive + jobs[i].run;
		}
	}
	for (int j = 0; j<n; j++)
	{
		jobs[j].turnover = jobs[j].end - jobs[j].arrive;
		jobs[j].withweightturnover = jobs[j].turnover*1.0 / jobs[j].run*1.0;
		sumturnover += jobs[j].turnover;
		sumwithweightturnover += jobs[j].withweightturnover;
	}
	avgturnover = sumturnover / n;
	avgwithweightturnover = sumwithweightturnover / n;
	cout << "\n--------�����ȷ�������㷨---------\n" << endl;
	for (int i = 0; i < n; i++)
	{
		cout <<"No."<<(i+1)<<"  ��ţ�"<<jobs[i].no<< "  ��ʼʱ��: " << jobs[i].start << "\t��" << endl;
	}
	cout << "----------------------------------" << endl;
	cout << "ƽ����תʱ�䣺" << avgturnover << endl;
	cout << "ƽ����Ȩ��תʱ�䣺" << avgwithweightturnover << endl;
	return 0;
}

//����ҵ���ȵ����㷨
int SJF(JOBS *jobs, int n)
{
	double sumturnover, sumwithweightturnover, avgturnover, avgwithweightturnover;
	sort(jobs, jobs+n, cmp);
	for (int i = 0; i<n - 1; i++)
	{
		int k = 0;
		if (i == 0)
			jobs[i].end = jobs[i].arrive + jobs[i].run;
		else
			jobs[i].end = jobs[i].arrive + jobs[i - 1].end;
		for (int j = i + 1; j<n; j++)
		{
			if (jobs[j].arrive <= jobs[i].end)
				k++;
		}
		double minstime = jobs[i + 1].run;
		int flag = i + 1;
		for (int m = i + 1; m<i + k; m++)
		{
			if (jobs[m + 1].run <minstime)
			{
				minstime = jobs[m + 1].run;
				flag = m + 1;
			}
		}
		JOBS temp;
		temp = jobs[i + 1];
		jobs[i + 1] = jobs[flag];
		jobs[flag] = temp;
	}

	sumturnover = sumwithweightturnover = 0;
	jobs[0].start = jobs[0].arrive;
	jobs[0].end = jobs[0].arrive + jobs[0].run;
	for (int i = 1; i<n; i++)
	{
		if (jobs[i - 1].end>jobs[i].arrive)
		{
			jobs[i].start = jobs[i - 1].end;
			jobs[i].end = jobs[i - 1].end + jobs[i].run;
		}
		else
		{
			jobs[i].start = jobs[i].arrive;
			jobs[i].end = jobs[i].arrive + jobs[i].run;
		}
	}
	for (int j = 0; j<n; j++)
	{
		jobs[j].turnover = jobs[j].end - jobs[j].arrive;
		jobs[j].withweightturnover = jobs[j].turnover*1.0 / jobs[j].run*1.0;
		sumturnover += jobs[j].turnover;
		sumwithweightturnover += jobs[j].withweightturnover;
	}
	avgturnover = sumturnover / n;
	avgwithweightturnover = sumwithweightturnover / n;
	cout << "\n--------����ҵ���ȵ����㷨--------\n" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "No." << (i + 1) << "  ��ţ�" << jobs[i].no << "  ��ʼʱ��: " << jobs[i].start << "\t��" << endl;
	}
	cout << "----------------------------------" << endl;
	cout << "ƽ����תʱ�䣺" << avgturnover << endl;
	cout << "ƽ����Ȩ��תʱ�䣺" << avgwithweightturnover << endl;
	return 0;
}

//�����Ӧ�����ȵ����㷨
int HRN(JOBS *jobs, int n)
{
	double sumturnover, sumwithweightturnover, avgturnover, avgwithweightturnover;
	sort(jobs, jobs + n, cmp);
	for (int i = 0; i<n - 1; i++)
	{
		int k = 0;
		if (i == 0)
			jobs[i].end = jobs[i].arrive + jobs[i].run;

		else
			jobs[i].end = (jobs[i].run + jobs[i - 1].end);
		for (int j = i + 1; j<n; j++)
		{
			if (jobs[j].arrive <= jobs[i].end)
				k++;
		}
		double maxrratio = (jobs[i].end - jobs[i + 1].arrive) / (1.0*jobs[i + 1].run);
		int flag = i + 1;
		for (int m = i + 1; m<i + k; m++)
		{
			if ((jobs[i].end - jobs[m + 1].arrive) / jobs[m + 1].run >= maxrratio)
			{
				maxrratio = (jobs[i].end - jobs[m + 1].arrive) / (1.0*jobs[m + 1].run);
				flag = m + 1;
			}
		}
		JOBS temp;
		temp = jobs[i + 1];
		jobs[i + 1] = jobs[flag];
		jobs[flag] = temp;
	}
	sumturnover = sumwithweightturnover = 0;
	jobs[0].start = jobs[0].arrive;
	jobs[0].end = jobs[0].arrive + jobs[0].run;
	for (int i = 1; i<n; i++)
	{
		if (jobs[i - 1].end>jobs[i].arrive)
		{
			jobs[i].start = jobs[i - 1].end;
			jobs[i].end = jobs[i - 1].end + jobs[i].run;
		}
		else
		{
			jobs[i].start = jobs[i].arrive;
			jobs[i].end = jobs[i].arrive + jobs[i].run;
		}
	}
	for (int j = 0; j<n; j++)
	{
		jobs[j].turnover = jobs[j].end - jobs[j].arrive;
		jobs[j].withweightturnover = jobs[j].turnover*1.0 / jobs[j].run*1.0;
		sumturnover += jobs[j].turnover;
		sumwithweightturnover += jobs[j].withweightturnover;
	}
	avgturnover = sumturnover / n;
	avgwithweightturnover = sumwithweightturnover / n;
	cout << "\n------�����Ӧ�����ȵ����㷨------\n" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "No." << (i + 1) << "  ��ţ�" << jobs[i].no << "  ��ʼʱ��: " << jobs[i].start << "\t��" << endl;
	}
	cout << "----------------------------------" << endl;
	cout << "ƽ����תʱ�䣺" << avgturnover << endl;
	cout << "ƽ����Ȩ��תʱ�䣺" << avgwithweightturnover << endl;
	return 0;
}


int main(int argc, char const *argv[])
{
	int num; 
	cout << "�����ִ����ҵ��: ";
	cin >> num;
	JOBS *jobs = (JOBS *)malloc(num * sizeof(JOBS));
	//��ҵ�� | ��ҵ����ϵͳ��ʱ�� | ����ִ��ʱ��
	JobSeq(jobs, num);
	//������ҵ�����㷨
	FCFS(jobs, num);   //ִ��FCFS��ҵ�����㷨
	SJF(jobs, num);    //ִ�ж���ҵ������ҵ�����㷨
	HRN(jobs, num);    //ִ�������Ӧ��������ҵ�����㷨
	delete[] jobs;     //�ͷŶ�̬����
	jobs = NULL;
	system("pause");
	return 0;
}
