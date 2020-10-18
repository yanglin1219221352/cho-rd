#include"ChordNode.h"
using namespace std;
ChordNode::ChordNode(string ip)    //���캯��
{
	this->ID = chord_hash(ip);
	this->IP = ip;
	this->succ = this;               
	this->presucc = this;
	this->znode = NULL;
	this->table = new struct finger[MAX];
	this->list = new struct nodelist[MAX];
	for (int i = 0; i < MAX; i++)   //��ʼ��finger��
	{
		this->table[i].start = (this->ID + (1 << i)) % (1<<MAX);//��Ҫ�����ڴ�
		this->table[i].end = (this->ID + (1 << (i + 1))) % (1<<MAX);
		this->table[i].node = this;
	}
	set_fingerlist();   //��ʼ��list��
	cout << "�Ѵ����������:" << ip;
}
ChordNode::ChordNode(){}//Ĭ�Ϲ��캯��
class ChordNode *ChordNode::closest_pre_node(int k, class ChordNode* n)//ͨ��Ѱ����ӽ�kֵ�Ľ��
{																	   //ͨ��finger�����
	for (int i = (MAX-1); i >= 0; i--)									//k����key,n����ǰ�ڵ�n
	{
		if (belongs_to_finger(n->ID, k, n->table[i].node->ID))//NID�� key�� n->tableID
		{
			if (n->table[i].node != NULL)  
				return n->table[i].node;
		}
	}
	return n;
}
class ChordNode *ChordNode::Successor_node(int K,ChordNode *L)//Ѱ��Kֵ����һ���
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
				cout << "û�д˽ڵ�" << endl;
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
				cout << "û�д˽ڵ�" << endl;
				return NULL;
			}
		}
		ChordNode *n0 = L->closest_pre_node(K, L->succ);
		cout << n0->IP<<"----->";
		return Successor_node(K, n0);//�ݹ麯��������������log2 n������debugģʽ
	}
}//����debugģʽ
class ChordNode *ChordNode::Successor(int K, ChordNode *L)//Ѱ��Kֵ����һ���
{
	while (1)
	{

		//���ж���һ����Ƿ���Ҫ�ҵĽ��
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
		return Successor(K, n0);//�ݹ�
	}
}
/*
void  ChordNode::update_others(ChordNode *t)
{
	for (int i = 0; i < MAX; i++)
		t->table[i].node = Successor(t->table[i].start, t);
}
*/
void  ChordNode::update_others()//����finger��Ϣ����������뿪ʱʹ��
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
	ChordNode *p = this;   //����list��
	for (int i = 0; i < MAX; i++)
	{
		p = p->succ;            //
		list[i].number = i;
		list[i].numbernode =p;
	}
}
void  ChordNode::uptada_otherslist()
{
	ChordNode *q = this->succ; //�൱�ڽ������ӽ�����
	do							//����ʵ����Ҫ���н���������Ϊ�ò�����ô���
	{							//���Ըĳ�max��
		q->set_fingerlist();
		q = q->succ;
	} while (q != this->succ);
}
void ChordNode::Join(string NID,ChordNode *L)
{
	ChordNode *t = new ChordNode;
	t->ID = chord_hash(NID);
	t->IP = NID;
	t->znode = NULL;									//��������Ϣ������
	struct finger *table = new struct finger[MAX];
	struct nodelist *list = new struct nodelist[MAX];
	ChordNode*p = t;
	t->table = table;
	t->list = list; 

		ChordNode *n=L->Successor(t->ID, L);   //Ѱ�Ҳ���λ��
		if (n->ID == t->ID)  
		{
			cout << "���id�ظ�" << endl;   //�ж���NID�Ƿ���
			delete t;
		}
		else
		{
			t->presucc = n->presucc;
			t->succ = n;
			n->presucc->succ = t;   // ���в���
			n->presucc = t;
			t->update_node(t);   //����������Ϊ
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
		}//�ӽڵ�ת��

	{
		ChordNode *p = this;
		p->presucc->succ = p->list[0].numbernode;
		p->succ->presucc = p->presucc;
		//p->list[0].numbernode->presucc = p->presucc;
		p = p->list[0].numbernode;//pΪ��ע���ڵ�ĺ�һ�ڵ�
		//	getnode(p);
		set_fingerlist();  //���±���list��
		uptada_otherslist();  //��������list��
		ChordNode*q = p;
		do
		{
			q->update_others();   //����finger��
			q = q->succ;
		} while (q != p);
		p = NULL;
	}//���½ڵ��
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
			//cout <<"�ùؼ��ֵ�ֵ��:"<<znode->getValue()<<endl;
			return znode;
		}
		else
			znode = znode->getNextKeyNode();
	}
	return NULL;
}
void ChordNode::Update(string key, string new_V)  //����һ��һ���ģ����û�õ�
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
void ChordNode::displayAllTable()//չʾ�˽ڵ�finger��
{

		for (int i = 0; i < MAX; i++)
		{
			cout <<this->table[i].start << "  " << this->table[i].end << "  " << this->table[i].node->ID << endl;
		}
		cout << endl;
}
void ChordNode::displayAllList()//չʾ�˽ڵ�list��
{
	for (int i = 0; i < MAX; i++)
	{
		cout << this->list[i].number << "  " << this->list[i].numbernode->IP << "  " << endl;
	}
}
void ChordNode::update_node(ChordNode*t)   //join����Ĳ�����Ϣ����
{

	{
		for (int i = 0; i < MAX; i++)   
		{
			t->table[i].node = NULL;   //��ʼ��
		}
		for (int i = 0; i < MAX; i++)   //����finger��
		{
			t->table[i].start = (t->ID + (1 << i)) % (1 << MAX);//��Ҫ�����ڴ�
			t->table[i].end = (t->ID + (1 << (i + 1))) % (1 << MAX);
			t->table[i].node = t->Successor(t->table[i].start, t);
		}
		t->set_fingerlist();
		t->uptada_otherslist();   //��������
		t->update_znode();
		//cout << "��㴴���ɹ���IDΪ:" << t->ID << "    �Ͻڵ�IDΪ" << t->presucc->ID << "    �½ڵ�IDΪ" << t->succ->ID << endl;
		ChordNode *q = t->succ;
		while (q != t)
		{
			q->update_others();
			q = q->succ;
		}
	}
}
void ChordNode::displayAllKeyNode()   //չʾ�ýڵ�������ӽڵ�
{
	ChordKeyNode *P = this->znode;
	cout << "������" << this->IP << "���ӽ����Ϣ" << endl;
	P->displayAllKeyNode();

}
void ChordNode::Insert(string key, string value)
{
	ChordKeyNode *p = new ChordKeyNode;
	int RID = chord_hash(key);
	p->ChangeKey(key);
	p->ChangeValue(value);    //�����ӽ�㣬�������Щֵ
	p->ChangeRID(RID);
	p->ChangeKeyNode(NULL);
	if (this->znode == NULL)
	{
		this->znode = p;
		//cout << "��ӳɹ�" << "     ";
	}
	else
	{
		ChordKeyNode *beichaliang = this->znode;
		/*if (p->getRID() == q->getRID())
		{
			cout << "�Ѵ�����ͬkeyֵ�Ľ�㣬���ʧ�ܣ�����������������ܳ��֣�";
		}
		else if (belongs_to_node(this->ID,q->getRID(), p->getRID()))
		{
			p->ChangeKeyNode(q);
			this->znode = p;//���ҵ�һ������//
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
				//cout << "��ӳɹ�" << endl;
			}
		}
	}
}
int ChordNode::update_znode()//�����ӽڵ�
{
	
	
	{
			//Ҫ�����뿪ֻʣһ���������
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
			this->znode = this->succ->znode;   //�⼸�п�����
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
