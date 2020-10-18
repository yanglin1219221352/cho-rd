#include"ChordRing.h"
using namespace std;
ChordNode* ChordRing::lookNode(string ip)
{
	int NID = chord_hash(ip);
	ChordNode *P = common_node->Successor(NID, common_node);
	if (P->getNodeIP() == ip)
		return P;
	else
		return NULL;
}
void ChordRing::Join(string NID)
{
	ChordNode::Join(NID, common_node);
}
void ChordRing::Insert(string key, string value)
{
	int NID= chord_hash(key); 
	ChordNode* p = common_node->Successor(NID, common_node);
 	p->Insert(key, value);
	/*
	ChordNode *L = common_node;
	{
		//Ѱ�ҽ��
		ChordKeyNode *Znode1 = new ChordKeyNode;
		Znode1->ChangeRID(chord_hash(key));
		Znode1->ChangeValue(value);
		Znode1->ChangeKey(key);
		Znode1->setKeyNode();
		{
			L = L->Successor(Znode1->getRID(), L);
			if (L->getznode() == NULL)
			{
				L->changKeyNode(Znode1);
			}
			else
			{
				ChordKeyNode* linshi = L->getznode();
				while (linshi->getNextKeyNode() != NULL)
					linshi = linshi->getNextKeyNode();
					linshi->ChangeKeyNode(Znode1);
			}
		}
	}
	*/
}
void ChordRing::leave(string ip)
{
	{
		int NID = chord_hash(ip);
		ChordNode *leave_node = common_node->Successor(NID, common_node);
		if (leave_node->getNodeIP() == ip)
		{
			if (leave_node == common_node)
			{
				cout << "�ýڵ�Ϊ����ڵ㣬�޷�ע��          ";
			}
			else

			{
				leave_node->leave();
				cout << " ���ɹ��뿪      ";
			}
		}
		else
			cout << "δ�ҵ��ýڵ�       " ;
	}
}
ChordKeyNode* ChordRing::lookup(string key)
{
	ChordKeyNode*p= common_node->lookup(key,common_node); 
	if (p != NULL)
	{
		cout << "�ùؼ��ֵ�ֵΪ:" << p->getValue()<<"       ";
		return p;
	}
	else
		cout << "�޷����ҹؼ��֣���ȷ���Ƿ����" << "       ";
	return NULL; 
}
void ChordRing::Update(string key, string new_V)
{
	ChordKeyNode * p = common_node->lookup(key,common_node);//�ҵ������½ڵ�
	if (p != NULL)
	{
		p->ChangeValue(new_V);//���㷢����������
		cout << "�Ѿ����¸�ֵ������Ϊ" << p->getValue();
	}
	else
		cout << "���ӽڵ㲻���ڣ�����ʧ��";
}
void ChordRing::CoutAllNode()
{
		ChordNode *p;
		p = common_node;
		int i = 0;
		do
		{
			i++;
			cout << i <<"   "<< p->getNodeID()<<"     " << p->getNodeIP()<<"   " <<endl;
			p = p->getsucc();      //����
		} while (!(p == common_node));

}
void ChordRing::displayAllTable(string ip)
{
	ChordNode*P = lookNode(ip);
	if (P != NULL)
	{
		P->displayAllTable();
	}
	else
	{
		cout << "δ���ҵ��ýڵ㣬������ȷ��" << endl;
	}
}
void ChordRing::displayAllList(string key)
{
	ChordNode*P = lookNode(key);
	if (P != NULL)
	{
		P->displayAllList();      
	}
	else
	{
		cout << "δ���ҵ��ýڵ㣬������ȷ��" << endl;
	}
}
void ChordRing::displayAllkeyNode(string key)
{
	ChordNode*P = lookNode(key);   //����һ���
	P->displayAllKeyNode();
}
void ChordRing::displayAllketNode()
{
	ChordNode *P = new ChordNode;
	ChordNode *Q = new ChordNode;
	P = common_node;
	Q = common_node;
	do
	{
		P->displayAllKeyNode(); //ͨ�����������ӽڵ�������
		P = P->getsucc();
	} while (P != Q);
}
ChordNode* ChordRing::debuglook(string ip)//��Ϊ����IP��һ���������ȡ�����һ�ε�·������
{
	int NID = chord_hash(ip);
	cout << common_node->getNodeIP()<<"----->";
	if (NID == common_node->getNodeID()) 
	{
		return common_node;
	}
	else
	{
		//cout << common_node->getNodeIP() << "----->";
		ChordNode *P = common_node->Successor_node(NID, common_node);
		if (P!=NULL&&P->getNodeIP() == ip)
		{
			return P;
		}
		else
			return NULL;
	}
}
void ChordRing::deleteRing()
{
	ChordNode * S;
	ChordNode  *E;
	S = common_node->getsucc();
	while (S!=common_node)
	{
		E = S->getsucc();
		delete S;
		S = E;
	}
}