#pragma once
#include "ChordKeyNode.h"
class ChordNode
{
	public:
		ChordNode(string ip);
		ChordNode();
		class ChordNode *closest_pre_node(int k, class ChordNode* n);//k����key,n����ǰ�ڵ�n,
		                                                             //��n�ڵ��finger��������ӽ�kֵ�Ľ��
		class ChordNode *Successor(int K, class ChordNode *L);//������Kֵ�����һ���
		void leave();//�ýڵ��뿪
		void update_others();//�����������
		void set_fingerlist();//��øýڵ��list��
		int getNodeID() { return ID; }//���ظýڵ��IDֵ����NID��
		ChordNode *getsucc() { return succ; }//������һ����ַ
        static void Join(string NID, ChordNode *L);//
		void  uptada_otherslist();//������������list��
		ChordKeyNode* lookup(string key, ChordNode *L);//��L��㿪ʼѰ��key����Ӧ���ӽڵ�
		ChordKeyNode *getznode() { return znode; }//���ظýڵ���׸��ӽڵ�
		void changKeyNode(ChordKeyNode*p) { znode = p; }//���ø��ӽڵ���׽ڵ��ַ����p
		void Update(string key, string new_V);
		void displayAllTable();//��ʾ�ýڵ��fingertable
		void displayAllList();//��ʾ�ýڵ��list
		string getNodeIP() { return IP; }//���ظýڵ��ip
		class ChordNode *Successor_node(int K, ChordNode *L);
		void update_node(ChordNode*);//�����������
		void displayAllKeyNode();//չʾ�ýڵ�������ӽڵ�
		void Insert(string key, string value);//��ýڵ����ؼ���Ϊkey,ֵΪvalue���ӽڵ�
		int update_znode();//�����ӽڵ㣨����Join��
	//	void arrayInsert(char *a[], char*b[]);
	private:
		int ID;  //���ID��
		class ChordNode *succ; //����
		class ChordNode *presucc; //ǰ���
		class ChordKeyNode * znode; //��һ���ӽڵ�
		string IP;  //��ֵַ
		struct nodelist//list�ṹ��
		{
			int number; //list�����
			class ChordNode * numbernode;//list���Ŷ�Ӧ�Ľ��
		};
		nodelist *list;
		struct finger//finger�ṹ��
		{
			int start; //finger ͷ
			int end;   //finger β
			ChordNode *node; //������˳ʱ���������ĵ�һ�����
		};
		finger *table;
};