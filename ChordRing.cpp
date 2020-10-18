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
		//寻找结点
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
				cout << "该节点为接入节点，无法注销          ";
			}
			else

			{
				leave_node->leave();
				cout << " 结点成功离开      ";
			}
		}
		else
			cout << "未找到该节点       " ;
	}
}
ChordKeyNode* ChordRing::lookup(string key)
{
	ChordKeyNode*p= common_node->lookup(key,common_node); 
	if (p != NULL)
	{
		cout << "该关键字的值为:" << p->getValue()<<"       ";
		return p;
	}
	else
		cout << "无法查找关键字，请确认是否存在" << "       ";
	return NULL; 
}
void ChordRing::Update(string key, string new_V)
{
	ChordKeyNode * p = common_node->lookup(key,common_node);//找到待更新节点
	if (p != NULL)
	{
		p->ChangeValue(new_V);//向结点发出更新请求
		cout << "已经更新该值，更新为" << p->getValue();
	}
	else
		cout << "该子节点不存在，更新失败";
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
			p = p->getsucc();      //遍历
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
		cout << "未能找到该节点，请重新确认" << endl;
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
		cout << "未能找到该节点，请重新确认" << endl;
	}
}
void ChordRing::displayAllkeyNode(string key)
{
	ChordNode*P = lookNode(key);   //找下一结点
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
		P->displayAllKeyNode(); //通过结点遍历和子节点遍历完成
		P = P->getsucc();
	} while (P != Q);
}
ChordNode* ChordRing::debuglook(string ip)//因为是找IP下一个结点所以取除最后一次的路径即可
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