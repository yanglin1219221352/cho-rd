#pragma once
#include "ChordKeyNode.h"
class ChordNode
{
	public:
		ChordNode(string ip);
		ChordNode();
		class ChordNode *closest_pre_node(int k, class ChordNode* n);//k代表key,n代表当前节点n,
		                                                             //从n节点的finger表中找最接近k值的结点
		class ChordNode *Successor(int K, class ChordNode *L);//搜索比K值大的下一结点
		void leave();//该节点离开
		void update_others();//更新其他结点
		void set_fingerlist();//获得该节点的list表
		int getNodeID() { return ID; }//返回该节点的ID值即（NID）
		ChordNode *getsucc() { return succ; }//返回下一结点地址
        static void Join(string NID, ChordNode *L);//
		void  uptada_otherslist();//更新其他结点的list表
		ChordKeyNode* lookup(string key, ChordNode *L);//从L结点开始寻找key所对应的子节点
		ChordKeyNode *getznode() { return znode; }//返回该节点的首个子节点
		void changKeyNode(ChordKeyNode*p) { znode = p; }//将该个子节点的首节点地址换成p
		void Update(string key, string new_V);
		void displayAllTable();//显示该节点的fingertable
		void displayAllList();//显示该节点的list
		string getNodeIP() { return IP; }//返回该节点的ip
		class ChordNode *Successor_node(int K, ChordNode *L);
		void update_node(ChordNode*);//更新其他结点
		void displayAllKeyNode();//展示该节点的所有子节点
		void Insert(string key, string value);//向该节点插入关键字为key,值为value的子节点
		int update_znode();//更新子节点（用于Join）
	//	void arrayInsert(char *a[], char*b[]);
	private:
		int ID;  //结点ID；
		class ChordNode *succ; //后结点
		class ChordNode *presucc; //前结点
		class ChordKeyNode * znode; //第一个子节点
		string IP;  //地址值
		struct nodelist//list结构体
		{
			int number; //list表序号
			class ChordNode * numbernode;//list表存放对应的结点
		};
		nodelist *list;
		struct finger//finger结构体
		{
			int start; //finger 头
			int end;   //finger 尾
			ChordNode *node; //该区域顺时针所遇到的第一个结点
		};
		finger *table;
};