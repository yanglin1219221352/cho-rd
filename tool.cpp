#include"tool.h"
#include"string"
#include<iostream>
#include<fstream>
using namespace std;
bool belongs_to_finger(int start, int end, int key)//����finger���ж�
{
	if (start < end&&start <= key && key<end || start>end && (key >= start || key < end))
		return true;
	else
		return false;
}
bool belongs_to_node(int start, int end, int key)//�����ж�Kֵ��һ���//�ӽڵ���������//Ѱ��NIDΪkey�Ľ��
{
	if (start < end&&start <key && key <= end || start>end && (key > start || key <= end))
		return true;
	else
		return false;
}
void getArray(char *a[], char*b[])//�����ݴ��ı�����������
{
	string ccc;
	int count = 0;
	ifstream fi;
	fi.open("d:\\CIDIAN.txt", ios::in);      //��������ļ�
	if (!fi.is_open())
	{
		cout << "error" << endl;
	}
	else
		while (!fi.eof() && count < 20000)//�ж��ļ��Ƿ񵽵׻���count�ǲ��ǳ���
		{
			getline(fi, ccc);
			char aaa[90] = "aaa";
			char *aa = aaa;
			char *bbb = NULL;
			strcpy_s(aaa, strlen(ccc.data()) + 1, ccc.data());  // ��c��aaa
			bbb = strtok_s(NULL, "\t", &aa);//��\tΪ�ָ��� ǰ���aa ����bbb
			strcpy_s(a[count], strlen(bbb) + 1, bbb);   //��bbb���a[]
			strcpy_s(b[count], strlen(aa) + 1, aa);     //��aa���b[]
			count++;
		}
	fi.close();
}
