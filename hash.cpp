#pragma once
#include"hash.h"
string H0 = "67452301";
string H1 = "EFCDAB89";
string H2 = "98BADCFE";
string H3 = "10325476";
string H4 = "C3D2E1F0";
//��vectorת��Ϊstring�ַ�����ʽ
string SHA1::num_into_message(vector<int> A)
{
	int i;
	string msg = "";
	for (i = 0; i < A.size(); i++)
	{
		if (A[i] >= 0 && A[i] <= 9)
			msg += '0' + A[i];
		else if (A[i] >= 10 && A[i] <= 15)
			msg += 'A' + (A[i] - 10);
	}
	return msg;
}

//��һ���ַ�����ʽ����ת��Ϊvector����
vector<int> SHA1::hex_into_dec(string word)
{
	int i;
	vector<int> result(NUM, 0);
	for (i = 0; i < NUM; i++)
	{
		if (word[i] >= '0' && word[i] <= '9')
		{
			result[i] = word[i] - '0';
		}
		else if (word[i] >= 'A' && word[i] <= 'F')
		{
			result[i] = 10 + word[i] - 'A';
		}
	}
	return result;
}

//������X��Y���߼�"��"
vector<int> SHA1::word_AND(vector<int> A, vector<int> B)
{
	vector<int> result(NUM, 0);
	int i;
	for (i = 0; i < NUM; i++)
	{
		result[i] = A[i] & B[i];
	}
	return result;
}

//������X��Y���߼�"��"
vector<int> SHA1::word_OR(vector<int> A, vector<int> B)
{
	vector<int> result(NUM, 0);
	int i;
	for (i = 0; i < NUM; i++)
	{
		result[i] = A[i] | B[i];
	}
	return result;
}

//������X��Y���߼�"���"
vector<int> SHA1::word_XOR(vector<int> A, vector<int> B)
{
	vector<int> result(NUM, 0);
	int i;
	for (i = 0; i < NUM; i++)
	{
		result[i] = A[i] ^ B[i];
	}
	return result;
}

//������X��Y���߼�"��"
vector<int> SHA1::word_COMPLEMENT(vector<int> A)
{
	vector<int> result(NUM, 0);
	int i;
	for (i = 0; i < NUM; i++)
	{
		result[i] = 15 - A[i];
	}
	return result;
}

//������X��Y����2^32������
vector<int> SHA1::word_ADD(vector<int> A, vector<int> B)
{
	vector<int> result(NUM, 0);
	int i;
	for (i = NUM - 1; i >= 0; i--)
	{
		result[i] = A[i] + B[i];
		if (i != 0)
		{
			int temp = result[i] / 16;
			result[i - 1] += temp;
		}
		result[i] %= 16;
	}
	return result;
}

//����Xѭ������s��λ��
vector<int> SHA1::ROTL(vector<int> A, int s)
{
	vector<int> result = A;
	vector<int> temp(NUM, 0);
	int i, j;
	for (i = 0; i < s; i++)
	{
		for (j = NUM - 1; j >= 0; j--)
		{
			if (result[j] / 8 >= 1)
			{
				temp[j] = 1;
				result[j] <<= 1;
				result[j] %= 16;
				if (j < NUM - 1)
					result[j] += temp[j + 1];
			}
			else if (result[j] / 8 == 0)
			{
				temp[j] = 0;
				result[j] <<= 1;
				result[j] %= 16;
			}
		}
		result[NUM - 1] += temp[0];
	}
	return result;
}

//SHA-1����䷽��,�����趨msg��ASCII�����
vector<vector<int> > SHA1::SHA_1_PAD(string msg)
{
	int len = msg.length();
	int bit_num = len * 8;
	int i, j;
	int num, lest = bit_num % 512;
	if (lest != 0)   //����Ϣ�����Ƿ񳬹�512�ֽڣ�������Ҫ��������512�ı���
		num = bit_num / 512 + 1;
	else
		num = bit_num / 512;
	//����������8λ�ֽ�Ϊһ�鱣�浽vector���棬512����Ϊһ�飬��һ��������64λԪ��
	vector<vector<int> > result;
	result.resize(num);
	for (i = 0; i < num; i++)
	{
		result[i].resize(64);
	}
	for (i = 0; i < num; i++)
	{
		for (j = 0; j < 64 && i * 64 + j < len; j++)
		{
			result[i][j] = msg[i * 64 + j];
		}
	}
	//���濪ʼΪδ��512���ص���Ϣ������в����Ȳ���
	if (lest != 0) {
		int x = num - 1, last_len = lest / 8;
		result[x][last_len] = 128;   //�Ȳ�һ��"1"
		for (i = last_len + 1; i < 56; i++)
		{
			result[x][i] = 0;
		}
		int last_l = lest;
		j = 63;
		while (j >= 56)
		{
			result[x][j] = last_l % 128;
			last_l /= 128;
			j--;
		}
	}
	return result;
}

//��SHA-1ѹ������Ϊ��λ(��ά�����е㸴��)
vector<vector<vector<int> > > SHA1::compress(vector<vector<int> > result)
{
	vector<vector<int> > rr;
	rr.resize(result.size());
	int i, j;
	for (i = 0; i < rr.size(); i++)
	{
		rr[i].resize(128);
	}
	for (i = 0; i < result.size(); i++)
	{
		for (j = 0; j < result[i].size(); j++)
		{
			rr[i][2 * j] = result[i][j] / 16;
			rr[i][2 * j + 1] = result[i][j] % 16;
		}
	}
	vector<vector<vector<int> > > rrr;
	rrr.resize(result.size());
	for (i = 0; i < rrr.size(); i++)
	{
		rrr[i].resize(16);
	}
	for (i = 0; i < rrr.size(); i++)
	{
		for (j = 0; j < 16; j++)
		{
			rrr[i][j].resize(8);
		}
	}
	for (i = 0; i < rr.size(); i++)
	{
		for (j = 0; j < rr[i].size(); j++)
		{
			rrr[i][j / 8][j % 8] = rr[i][j];
		}
	}
	return rrr;
}

//����ft������ÿ��ft��������B,C,D��������Ϊ���룬������һ������Ϊ���
vector<int> SHA1::Ft(int t, vector<int> B, vector<int> C, vector<int> D)
{
	vector<int> result;
	if (t >= 0 && t <= 19)
	{
		vector<int> a1 = word_AND(B, C);
		vector<int> a2 = word_AND(word_COMPLEMENT(B), D);
		result = word_OR(a1, a2);
	}
	else if ((t >= 20 && t <= 39) || (t >= 60 && t <= 79))
	{
		vector<int> a1 = word_XOR(B, C);
		result = word_XOR(a1, D);
	}
	else if (t >= 40 && t <= 59)
	{
		vector<int> a1 = word_AND(B, C);
		vector<int> a2 = word_AND(B, D);
		vector<int> a3 = word_AND(C, D);
		vector<int> a4 = word_OR(a1, a2);
		result = word_OR(a4, a3);
	}
	return result;
}

//�����ֳ���K
vector<int> SHA1::K(int t)
{
	vector<int> result;
	if (t >= 0 && t <= 19)
	{
		result = hex_into_dec("5A827999");
	}
	else if (t >= 20 && t <= 39)
	{
		result = hex_into_dec("6ED9EBA1");
	}
	else if (t >= 40 && t <= 59)
	{
		result = hex_into_dec("8F1BBCDC");
	}
	else if (t >= 60 && t <= 79)
	{
		result = hex_into_dec("CA62C1D6");
	}
	return result;
}

//��ʼ����SHA-1(��ȫHash�㷨)�ļ���
vector<vector<int> > SHA1::SHA_1(string msg)
{
	vector<int> h0 = hex_into_dec(H0);
	vector<int> h1 = hex_into_dec(H1);
	vector<int> h2 = hex_into_dec(H2);
	vector<int> h3 = hex_into_dec(H3);
	vector<int> h4 = hex_into_dec(H4);

	vector<vector<int> > result1 = SHA_1_PAD(msg);
	vector<vector<vector<int> > > result2 = compress(result1);
	int n = result2.size();
	int i, j;
	for (i = 0; i < n; i++)
	{
		vector<vector<int> > W;
		W.resize(80);
		for (j = 0; j < 16; j++)
		{
			W[j] = result2[i][j];
		}
		for (j = 16; j < 80; j++)
		{
			vector<int> a1 = word_XOR(W[j - 3], W[j - 8]);
			vector<int> a2 = word_XOR(a1, W[j - 14]);
			vector<int> a3 = word_XOR(a2, W[j - 16]);
			W[j] = ROTL(a3, 1);
		}

		//��stringת��Ϊvector����
		vector<int> A = hex_into_dec(H0);
		vector<int> B = hex_into_dec(H1);
		vector<int> C = hex_into_dec(H2);
		vector<int> D = hex_into_dec(H3);
		vector<int> E = hex_into_dec(H4);

		for (j = 0; j < 80; j++)
		{
			vector<int> a1 = ROTL(A, 5);
			vector<int> a2 = Ft(j, B, C, D);
			vector<int> a3 = word_ADD(a1, a2);
			vector<int> a4 = word_ADD(a3, E);
			vector<int> a5 = word_ADD(a4, W[j]);
			vector<int> temp = word_ADD(a5, K(j));
			E = D;
			D = C;
			C = ROTL(B, 30);
			B = A;
			A = temp;
		}

		h0 = word_ADD(h0, A);
		h1 = word_ADD(h1, B);
		h2 = word_ADD(h2, C);
		h3 = word_ADD(h3, D);
		h4 = word_ADD(h4, E);
	}

	//���ؽ��(H0||H1||H2||H3||H4)
	vector<vector<int> > result;
	result.push_back(h0);
	result.push_back(h1);
	result.push_back(h2);
	result.push_back(h3);
	result.push_back(h4);

	return result;
}
int chord_hash(string ip)//��hash���IDֵ
{
	SHA1 sha1;   //����SHA1�㷨��
	vector<vector<int> > result;
	string s;
	int max = 1 <<MAX;
	result = sha1.SHA_1(ip);
	s = sha1.num_into_message(result[1]);
	s = s.substr(0, 5); //ǰ��λ�ַ���
	int a = stoi(s, 0, 16);//���ַ���ת����int 16λ.
	return a % max;

}