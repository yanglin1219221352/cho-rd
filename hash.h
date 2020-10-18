#ifndef HASH_H
#define HASH_H
#include <iostream>
#include <vector>   //定义vector数组
#include <string>   //记录消息
#define MAX 15     //数组的最大长度是2的MAX次方
using namespace std;

const int NUM = 8;   //一个字由32比特(或者8个16进制数)
const int BIT = 512;  //消息认证码要以512比特一组

//定义SHA1(安全哈希算法)类
class SHA1
{
public:
	//将一个字符串形式的字转化为vector数组
	vector<int> hex_into_dec(string word);

	//将vector转化为string字符串形式
	string num_into_message(vector<int> A);

	//两个字X和Y的逻辑"和"
	vector<int> word_AND(vector<int> A, vector<int> B);

	//两个字X和Y的逻辑"或"
	vector<int> word_OR(vector<int> A, vector<int> B);

	//两个字X和Y的逻辑"异或"
	vector<int> word_XOR(vector<int> A, vector<int> B);

	//两个字X和Y的逻辑"补"
	vector<int> word_COMPLEMENT(vector<int> A);

	//两个字X和Y的摸2^32整数加
	vector<int> word_ADD(vector<int> A, vector<int> B);

	//将字X循环左移s个位置
	vector<int> ROTL(vector<int> A, int s);

	//SHA-1的填充方案,我们设定msg由ASCII码组成
	vector<vector<int> > SHA_1_PAD(string msg);

	//将SHA-1压成以字为单位
	vector<vector<vector<int> > > compress(vector<vector<int> > result);

	//定义ft函数，每个ft函数都有B,C,D三个字作为输入，并产生一个字作为输出
	vector<int> Ft(int t, vector<int> B, vector<int> C, vector<int> D);

	//定义字常数K
	vector<int> K(int t);

	//开始进行SHA-1(安全Hash算法)的加密
	vector<vector<int> > SHA_1(string msg);

};
int chord_hash(string ip);
#endif
