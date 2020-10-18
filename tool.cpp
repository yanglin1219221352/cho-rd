#include"tool.h"
#include"string"
#include<iostream>
#include<fstream>
using namespace std;
bool belongs_to_finger(int start, int end, int key)//用于finger表判断
{
	if (start < end&&start <= key && key<end || start>end && (key >= start || key < end))
		return true;
	else
		return false;
}
bool belongs_to_node(int start, int end, int key)//用于判断K值下一结点//子节点可能用这个//寻找NID为key的结点
{
	if (start < end&&start <key && key <= end || start>end && (key > start || key <= end))
		return true;
	else
		return false;
}
void getArray(char *a[], char*b[])//将数据从文本导入数组中
{
	string ccc;
	int count = 0;
	ifstream fi;
	fi.open("d:\\CIDIAN.txt", ios::in);      //输入输出文件
	if (!fi.is_open())
	{
		cout << "error" << endl;
	}
	else
		while (!fi.eof() && count < 20000)//判断文件是否到底或者count是不是超数
		{
			getline(fi, ccc);
			char aaa[90] = "aaa";
			char *aa = aaa;
			char *bbb = NULL;
			strcpy_s(aaa, strlen(ccc.data()) + 1, ccc.data());  // 将c给aaa
			bbb = strtok_s(NULL, "\t", &aa);//设\t为分隔符 前半给aa 后半给bbb
			strcpy_s(a[count], strlen(bbb) + 1, bbb);   //将bbb存进a[]
			strcpy_s(b[count], strlen(aa) + 1, aa);     //将aa存进b[]
			count++;
		}
	fi.close();
}
