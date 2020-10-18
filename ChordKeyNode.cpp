#include "ChordKeyNode.h"
using namespace std;
void ChordKeyNode::displayAllKeyNode()
{
	ChordKeyNode *p = this; 
	while (p != NULL)  //基础遍历
	{
		cout << p->RID << "  " << p->key << "    " << p->value << endl;  //输出RID key value 三值
		p = p->next;
	}
}
ChordKeyNode* ChordKeyNode::Insert(ChordKeyNode *yuanlai,int ID)
{
	if (yuanlai->next == NULL)//如果第一子节点的下一结点==NULL
	{
		if (this->RID == yuanlai->getRID())
		{
			cout << "已存在相同key值的结点，添加失败（这种情况几乎不可能出现）";
			return NULL;
		}
		if (belongs_to_node(this->getRID(), ID,yuanlai->getRID()))//如果yuanlai位于AddRID中间，此ID为插入结点（K值的下一结点）
		{
			this->next = yuanlai;  //将Add插在NID 和yuanlai中间
			return this;
		}
		else
		{
			yuanlai->next = this; //将Add结点插在yuanlai结点后面
			cout << "添加成功" << endl;
			return NULL;
		}
	}
	else
	{
		if (this->RID == yuanlai->getRID())
		{
			cout << "已存在相同key值的结点，添加失败（这种情况几乎不可能出现）";
			return NULL;
		}
		if (belongs_to_node(this->getRID(), ID, yuanlai->getRID()))
		{
			this->next = yuanlai;    //是next！=null的状态下，判断插入结点是否要放在第一子节点位置
			return this;
		}
	}
	while (yuanlai->next!= NULL)
	{
		if (this->RID == yuanlai->next->getRID())
		{
			cout << "已存在相同key值的结点，添加失败（这种情况几乎不可能出现）";
			return NULL;
		}
		if (belongs_to_node(yuanlai->RID, yuanlai->next->RID, this->RID))//Add结点位于yuanlai结点和它的下一结点之间
		{
			this->next = yuanlai->next;    //将Add结点插入这两个结点的中间
			yuanlai->next = this;
			cout << "添加成功" << endl;
			return NULL;
		}
		else
		{
			yuanlai = yuanlai->next;   //yuanlai结点后移
		}

	}
	if (yuanlai->next == NULL)     //若原来下一结点为空
	{
		this->next = NULL;         //将Add结点插入yuanlai的面
		yuanlai->next = this;
		cout << "添加成功" << endl;
		return NULL;
	}
	/*
	if (yuanlai->next == NULL)
	{
		if (this->RID ==yuanlai->getRID())
		{
			cout << "已存在相同key值的结点，添加失败（这种情况几乎不可能出现）";
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
		if(belongs_to_node(yuanlai->RID, yuanlai->next->RID, this->RID))//这边肯定有问题
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