#pragma once
#include<iostream>
#include"hash.h"
#include"tool.h"
class ChordKeyNode
{
	public:
		int getRID() { return RID; }
		string getKey() { return key; }
		string getValue() { return value; }
		void ChangeRID(int R) { RID = R; }
		void ChangeKey(string k) { key = k; }
		void ChangeValue(string v) { value = v; }
		void setKeyNode() { next = NULL; }
		void ChangeKeyNode(ChordKeyNode* n) { next = n; }
		ChordKeyNode *getNextKeyNode() { return next; }
		void displayAllKeyNode();
		ChordKeyNode * Insert(ChordKeyNode* q,int );
		//ChordKeyNode* retain_key_node(int );
	
	private:
		int RID;   //子ID值
	    string key;  //关键词
	    string value; //内容
		ChordKeyNode *next;
};