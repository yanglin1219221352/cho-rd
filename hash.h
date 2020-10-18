#ifndef HASH_H
#define HASH_H
#include <iostream>
#include <vector>   //����vector����
#include <string>   //��¼��Ϣ
#define MAX 15     //�������󳤶���2��MAX�η�
using namespace std;

const int NUM = 8;   //һ������32����(����8��16������)
const int BIT = 512;  //��Ϣ��֤��Ҫ��512����һ��

//����SHA1(��ȫ��ϣ�㷨)��
class SHA1
{
public:
	//��һ���ַ�����ʽ����ת��Ϊvector����
	vector<int> hex_into_dec(string word);

	//��vectorת��Ϊstring�ַ�����ʽ
	string num_into_message(vector<int> A);

	//������X��Y���߼�"��"
	vector<int> word_AND(vector<int> A, vector<int> B);

	//������X��Y���߼�"��"
	vector<int> word_OR(vector<int> A, vector<int> B);

	//������X��Y���߼�"���"
	vector<int> word_XOR(vector<int> A, vector<int> B);

	//������X��Y���߼�"��"
	vector<int> word_COMPLEMENT(vector<int> A);

	//������X��Y����2^32������
	vector<int> word_ADD(vector<int> A, vector<int> B);

	//����Xѭ������s��λ��
	vector<int> ROTL(vector<int> A, int s);

	//SHA-1����䷽��,�����趨msg��ASCII�����
	vector<vector<int> > SHA_1_PAD(string msg);

	//��SHA-1ѹ������Ϊ��λ
	vector<vector<vector<int> > > compress(vector<vector<int> > result);

	//����ft������ÿ��ft��������B,C,D��������Ϊ���룬������һ������Ϊ���
	vector<int> Ft(int t, vector<int> B, vector<int> C, vector<int> D);

	//�����ֳ���K
	vector<int> K(int t);

	//��ʼ����SHA-1(��ȫHash�㷨)�ļ���
	vector<vector<int> > SHA_1(string msg);

};
int chord_hash(string ip);
#endif
