#pragma once
#include "ChordNode.h"
#include<map>

class ChordRing
{
	public:
		void Insert(string key, string value);//�����ӽڵ㹦�ܣ���ֵ��
		void Join(string ip);//������
		void leave(string ip);//����뿪
		ChordKeyNode* lookup(string key);//Ѱ��key���
		void Update(string key, string new_V);//��������
		void CoutAllNode();//��ʾ���нڵ�
		ChordNode* lookNode(string key);//Ѱ��key���ڵĽ��
		void displayAllTable(string key);//��ʾ�ã�key���ڵ�finger��
		void displayAllList(string key);//��ʾ�ã�key���ڵ��list��
		void displayAllkeyNode(string key);//��ʾ�ã�key���ڵ���ӽڵ�
		void displayAllketNode();//��ʾ�����ӽڵ�
		ChordNode* debuglook(string key);//��ʾ����·��
		void deleteRing();//ע����
	private:
		ChordNode * common_node = new ChordNode("yanglin");   //��������ʱ�㴴����ʼ���
		struct finger *fingertable;//finger��
		struct nodelist *list;//list��
		
	  //std::map<class ChordNode*, struct nodelist> key_node_list;
};