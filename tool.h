#pragma once
#ifndef TOOL_H
#define TOOL_H
#include<iostream>
#include<fstream>
bool belongs_to_finger(int start, int end, int key);
bool belongs_to_node(int start, int end, int key);
/*
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
*/
void getArray(char *a[], char*b[]);//�����ݴ��ı�����������
#endif
