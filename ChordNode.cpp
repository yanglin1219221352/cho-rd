#include"ChordNode.h"
using namespace std;
ChordNode::ChordNode(string ip)    //构造函数
{
	this->ID = chord_hash(ip);
	this->IP = ip;
	this->succ = this;               
	this->presucc = this;
	this->znode = NULL;
	this->table = new struct finger[MAX];
	this->list = new struct nodelist[MAX];
	for (int i = 0; i < MAX; i++)   //初始化finger表
	{
		this->table[i].start = (this->ID + (1 << i)) % (1<<MAX);//需要申请内存
		this->table[i].end = (this->ID + (1 << (i + 1))) % (1<<MAX);
		this->table[i].node = this;
	}
	set_fingerlist();   //初始化list表
	cout << "已创建公共结点:" << ip;
}
ChordNode::ChordNode(){}//默认构造函数
class ChordNode *ChordNode::closest_pre_node(int k, class ChordNode* n)//通过寻找最接近k值的结点
{																	   //通过finger表查找
	for (int i = (MAX-1); i >= 0; i--)									//k代表key,n代表当前节点n
	{
		if (belongs_to_finger(n->ID, k, n->table[i].node->ID))//NID， key， n->tableID
		{
			if (n->table[i].node != NULL)  
				return n->table[i].node;
		}
	}
	return n;
}
class ChordNode *ChordNode::Successor_node(int K,ChordNode *L)//寻找K值的下一结点
{
	while (1)
	{


		if (belongs_to_node(L->ID, L->succ->ID, K))
			//if ((L->ID<K&&L->succ->ID>K&&L->ID < L->succ->ID) || L->ID > L->succ->ID&&K > L->ID||K<L->succ->ID)
		{
			if (K == L->succ->ID)
			{
				cout << L->getsucc()->IP;
				return L->succ;
				break;
			}
			else
			{
				cout << "没有此节点" << endl;
				return NULL;
			}
		}
		if (L->ID >= L->succ->ID&&L->succ->succ == L)
		{
			if (K == L->ID)

			{
				cout << L->IP;
				return L;
				break;
			}
			else
			{
				cout << "没有此节点" << endl;
				return NULL;
			}
		}
		ChordNode *n0 = L->closest_pre_node(K, L->succ);
		cout << n0->IP<<"----->";
		return Successor_node(K, n0);//递归函数，次数不超过log2 n，用于debug模式
	}
}//用于debug模式
class ChordNode *ChordNode::Successor(int K, ChordNode *L)//寻找K值的下一结点
{
	while (1)
	{

		//先判断下一结点是否是要找的结点
		if (belongs_to_node(L->ID, L->succ->ID, K))
			//if ((L->ID<K&&L->succ->ID>K&&L->ID < L->succ->ID) || L->ID > L->succ->ID&&K > L->ID||K<L->succ->ID)
		{
			return L->succ;
			break;
		}
		if (L->ID >= L->succ->ID&&L->succ->succ == L)
		{
			return L;
			break;
		}
		ChordNode *n0 = L->closest_pre_node(K, L->succ);
		return Successor(K, n0);//递归
	}
}
/*
void  ChordNode::update_others(ChordNode *t)
{
	for (int i = 0; i < MAX; i++)
		t->table[i].node = Successor(t->table[i].start, t);
}
*/
void  ChordNode::update_others()//更新finger信息，结点加入和离开时使用
{
	for (int i = 0; i < MAX; i++)
		table[i].node = Successor(table[i].start, this);
}
/*
void  ChordNode::set_fingerlist(ChordNode *t)
{
	ChordNode *p = t;

	for (int i = 0; i < MAX; i++)
	{
		t->list[i].number = i;
		t->list[i].numbernode = p->succ;
		p = p->succ;
	}
}
*/
void  ChordNode::set_fingerlist()
{
	ChordNode *p = this;   //创建list表
	for (int i = 0; i < MAX; i++)
	{
		p = p->succ;            //
		list[i].number = i;
		list[i].numbernode =p;
	}
}
void  ChordNode::uptada_otherslist()
{
	ChordNode *q = this->succ; //相当于结点遍历加结点更新
	do							//但其实不需要进行结点遍历，因为用不到那么多个
	{							//可以改成max个
		q->set_fingerlist();
		q = q->succ;
	} while (q != this->succ);
}
void ChordNode::Join(string NID,ChordNode *L)
{
	ChordNode *t = new ChordNode;
	t->ID = chord_hash(NID);
	t->IP = NID;
	t->znode = NULL;									//结点基础信息的输入
	struct finger *table = new struct finger[MAX];
	struct nodelist *list = new struct nodelist[MAX];
	ChordNode*p = t;
	t->table = table;
	t->list = list; 

		ChordNode *n=L->Successor(t->ID, L);   //寻找插入位置
		if (n->ID == t->ID)  
		{
			cout << "结点id重复" << endl;   //判断是NID是否重
			delete t;
		}
		else
		{
			t->presucc = n->presucc;
			t->succ = n;
			n->presucc->succ = t;   // 四行插入
			n->presucc = t;
			t->update_node(t);   //其他更新行为
		}
	
	
}
void ChordNode::leave()
{
		if (this->znode != NULL)
		{
			ChordKeyNode* p = znode;
			ChordKeyNode *buff = this->succ->znode;
			while (p->getNextKeyNode() != NULL)
				{
					p = p->getNextKeyNode();
					if (p == NULL)
					break;
				}
			p->ChangeKeyNode(buff);
			this->succ->znode = this->znode;
		}//子节点转移

	{
		ChordNode *p = this;
		p->presucc->succ = p->list[0].numbernode;
		p->succ->presucc = p->presucc;
		//p->list[0].numbernode->presucc = p->presucc;
		p = p->list[0].numbernode;//p为代注销节点的后一节点
		//	getnode(p);
		set_fingerlist();  //更新本身list表
		uptada_otherslist();  //更新其他list表
		ChordNode*q = p;
		do
		{
			q->update_others();   //更新finger表
			q = q->succ;
		} while (q != p);
		p = NULL;
	}//更新节点表
}
ChordKeyNode* ChordNode::lookup(string key, ChordNode *L)
{
	int RID = chord_hash(key);   
	ChordNode *P = L->Successor(RID, L);
	ChordKeyNode *znode = P->getznode();
	while (znode != NULL)
	{
		if (znode->getRID() == RID)
		{
			//cout <<"该关键字的值是:"<<znode->getValue()<<endl;
			return znode;
		}
		else
			znode = znode->getNextKeyNode();
	}
	return NULL;
}
void ChordNode::Update(string key, string new_V)  //下面一个一样的，这个没用到
{
	ChordKeyNode * p = lookup(key,this);
	if (p != NULL)
	{
		p->ChangeValue(new_V);
		cout << "Update success" << endl;
	}
	else
		cout << "not found rnode" << endl;

}
void ChordNode::displayAllTable()//展示此节点finger表
{

		for (int i = 0; i < MAX; i++)
		{
			cout <<this->table[i].start << "  " << this->table[i].end << "  " << this->table[i].node->ID << endl;
		}
		cout << endl;
}
void ChordNode::displayAllList()//展示此节点list表
{
	for (int i = 0; i < MAX; i++)
	{
		cout << this->list[i].number << "  " << this->list[i].numbernode->IP << "  " << endl;
	}
}
void ChordNode::update_node(ChordNode*t)   //join结点后的部分信息更新
{

	{
		for (int i = 0; i < MAX; i++)   
		{
			t->table[i].node = NULL;   //初始化
		}
		for (int i = 0; i < MAX; i++)   //本身finger表
		{
			t->table[i].start = (t->ID + (1 << i)) % (1 << MAX);//需要申请内存
			t->table[i].end = (t->ID + (1 << (i + 1))) % (1 << MAX);
			t->table[i].node = t->Successor(t->table[i].start, t);
		}
		t->set_fingerlist();
		t->uptada_otherslist();   //其他更新
		t->update_znode();
		//cout << "结点创建成功，ID为:" << t->ID << "    上节点ID为" << t->presucc->ID << "    下节点ID为" << t->succ->ID << endl;
		ChordNode *q = t->succ;
		while (q != t)
		{
			q->update_others();
			q = q->succ;
		}
	}
}
void ChordNode::displayAllKeyNode()   //展示该节点的所有子节点
{
	ChordKeyNode *P = this->znode;
	cout << "以下是" << this->IP << "的子结点信息" << endl;
	P->displayAllKeyNode();

}
void ChordNode::Insert(string key, string value)
{
	ChordKeyNode *p = new ChordKeyNode;
	int RID = chord_hash(key);
	p->ChangeKey(key);
	p->ChangeValue(value);    //创建子结点，并存放这些值
	p->ChangeRID(RID);
	p->ChangeKeyNode(NULL);
	if (this->znode == NULL)
	{
		this->znode = p;
		//cout << "添加成功" << "     ";
	}
	else
	{
		ChordKeyNode *beichaliang = this->znode;
		/*if (p->getRID() == q->getRID())
		{
			cout << "已存在相同key值的结点，添加失败（这种情况几乎不可能出现）";
		}
		else if (belongs_to_node(this->ID,q->getRID(), p->getRID()))
		{
			p->ChangeKeyNode(q);
			this->znode = p;//把我第一个代了//
		}
		*/
	/*	else if (belongs_to_node(this->ID, p->getRID(), q->getRID()))
		{
			 
		}
	*/
	//	else
		{
			ChordKeyNode *L = p->Insert(beichaliang, this->ID);
			if (L != NULL)
			{
				this->znode = L;    
				//cout << "添加成功" << endl;
			}
		}
	}
}
int ChordNode::update_znode()//更新子节点
{
	
	
	{
			//要考虑离开只剩一个结点的情况
		if (this->succ->znode == NULL)
			{
				return 0;
			}
		else
		{
			ChordKeyNode *next1 = this->succ->getznode();
			ChordKeyNode *next2 = this->succ->getznode();
			if (next1->getNextKeyNode() == NULL)
				{
				if (belongs_to_node(this->ID, this->succ->ID, next1->getRID()))
					{
						return 0;
					}
				else
					{
						this->znode = next1;
						this->succ->znode = NULL;
						return 0;
					}
				}
				while (!belongs_to_node(this->ID, this->succ->ID, next1->getNextKeyNode()->getRID()))
				{
					next1 = next1->getNextKeyNode();
					if (next1->getNextKeyNode() == NULL)
					{
						break;
					}
				}
			next2 = next1->getNextKeyNode();
			this->znode = this->succ->znode;   //这几行考虑下
			this->succ->znode = next2;
			next1->ChangeKeyNode(NULL);
		}
	}
}
//void ChordNode::arrayInsert(char *a[], char*b[])
//{
//	for (int i = 0; i < 100; i++)
//		Insert(a[i], b[i]);
//}
