#include "ChordKeyNode.h"
using namespace std;
void ChordKeyNode::displayAllKeyNode()
{
	ChordKeyNode *p = this; 
	while (p != NULL)  //��������
	{
		cout << p->RID << "  " << p->key << "    " << p->value << endl;  //���RID key value ��ֵ
		p = p->next;
	}
}
ChordKeyNode* ChordKeyNode::Insert(ChordKeyNode *yuanlai,int ID)
{
	if (yuanlai->next == NULL)//�����һ�ӽڵ����һ���==NULL
	{
		if (this->RID == yuanlai->getRID())
		{
			cout << "�Ѵ�����ͬkeyֵ�Ľ�㣬���ʧ�ܣ�����������������ܳ��֣�";
			return NULL;
		}
		if (belongs_to_node(this->getRID(), ID,yuanlai->getRID()))//���yuanlaiλ��AddRID�м䣬��IDΪ�����㣨Kֵ����һ��㣩
		{
			this->next = yuanlai;  //��Add����NID ��yuanlai�м�
			return this;
		}
		else
		{
			yuanlai->next = this; //��Add������yuanlai������
			cout << "��ӳɹ�" << endl;
			return NULL;
		}
	}
	else
	{
		if (this->RID == yuanlai->getRID())
		{
			cout << "�Ѵ�����ͬkeyֵ�Ľ�㣬���ʧ�ܣ�����������������ܳ��֣�";
			return NULL;
		}
		if (belongs_to_node(this->getRID(), ID, yuanlai->getRID()))
		{
			this->next = yuanlai;    //��next��=null��״̬�£��жϲ������Ƿ�Ҫ���ڵ�һ�ӽڵ�λ��
			return this;
		}
	}
	while (yuanlai->next!= NULL)
	{
		if (this->RID == yuanlai->next->getRID())
		{
			cout << "�Ѵ�����ͬkeyֵ�Ľ�㣬���ʧ�ܣ�����������������ܳ��֣�";
			return NULL;
		}
		if (belongs_to_node(yuanlai->RID, yuanlai->next->RID, this->RID))//Add���λ��yuanlai����������һ���֮��
		{
			this->next = yuanlai->next;    //��Add�����������������м�
			yuanlai->next = this;
			cout << "��ӳɹ�" << endl;
			return NULL;
		}
		else
		{
			yuanlai = yuanlai->next;   //yuanlai������
		}

	}
	if (yuanlai->next == NULL)     //��ԭ����һ���Ϊ��
	{
		this->next = NULL;         //��Add������yuanlai����
		yuanlai->next = this;
		cout << "��ӳɹ�" << endl;
		return NULL;
	}
	/*
	if (yuanlai->next == NULL)
	{
		if (this->RID ==yuanlai->getRID())
		{
			cout << "�Ѵ�����ͬkeyֵ�Ľ�㣬���ʧ�ܣ�����������������ܳ��֣�";
			return NULL;
		}
		else if (belongs_to_node(ID,yuanlai->getRID(), this->getRID()))
		{
			this->ChangeKeyNode(yuanlai);
			return this;
		}
		yuanlai->next = this;
		return NULL;
		
	}
	else
	{

		while (!belongs_to_node(yuanlai->RID,yuanlai->next->RID,this->RID))
		{
				yuanlai = yuanlai->next;
				if (yuanlai->next == NULL)
				{
					yuanlai->next = this;
				}
		}
		if(belongs_to_node(yuanlai->RID, yuanlai->next->RID, this->RID))//��߿϶�������
		{
		this->next = yuanlai->next;
		yuanlai->next = this;
		return NULL;
		
		}
	}*/
}

/*
ChordKeyNode* ChordKeyNode::retain_key_node(int ID)
{
	ChordKeyNode *T = this;
	while (T!=NULL&&T->RID <= ID)
	{
		T = T->next;
	}
	return T;
}
*/
/*
ChordKeyNode* ChordKeyNode::move_key_node(int ID,ChordKeyNode*next1)
{
	ChordKeyNode *T = this;
	if (T->RID < ID)
	{
		while (belongs_to_node(,T->getRID,))
		{
			T = T->next;
		}
		next1 = T->next;
		T->next = NULL;
		return this;
	}
	else
		return NULL;
}
*/