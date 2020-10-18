#pragma once
#include "ChordNode.h"
#include<map>

class ChordRing
{
	public:
		void Insert(string key, string value);//插入子节点功能（插值）
		void Join(string ip);//加入结点
		void leave(string ip);//结点离开
		ChordKeyNode* lookup(string key);//寻找key结点
		void Update(string key, string new_V);//更新数据
		void CoutAllNode();//显示所有节点
		ChordNode* lookNode(string key);//寻找key所在的结点
		void displayAllTable(string key);//显示该（key）节点finger表
		void displayAllList(string key);//显示该（key）节点的list表
		void displayAllkeyNode(string key);//显示该（key）节点的子节点
		void displayAllketNode();//显示所有子节点
		ChordNode* debuglook(string key);//显示查找路径
		void deleteRing();//注销环
	private:
		ChordNode * common_node = new ChordNode("yanglin");   //建立对象时便创建初始结点
		struct finger *fingertable;//finger表
		struct nodelist *list;//list表
		
	  //std::map<class ChordNode*, struct nodelist> key_node_list;
};