#pragma once
#ifndef TOOL_H
#define TOOL_H
#include<iostream>
#include<fstream>
bool belongs_to_finger(int start, int end, int key);
bool belongs_to_node(int start, int end, int key);
/*
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
*/
void getArray(char *a[], char*b[]);//将数据从文本导入数组中
#endif
