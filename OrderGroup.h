#pragma once
#include "Order.h"
#include <vector>
#include <deque>
#include <list>
#include <map>
#define filtration
//#include <fstream>
//���ж����ķ����������Ƽ�ʹ��map���з�ֹ�����ظ�
using namespace std;
class OrderGroup
{
private:
	vector<Order> orderGroup;//�������� �о������deque����Ҳ����,����ûʲô��Ҫ,deque��������������β��ɾԪ��
	list<Order>orderList;//orderList,���ڳ�ʼ������
	//����,����,����!����û����... Ӧ����map<string ,Order>
	map<string,Order>orderMap;//��order.ID��Ϊ����ֵorderMap
	string delete_char(string sNewTag,char cRddcy);	//ȥ����һ���е�ĳЩ�ַ�
	void delete_child_string(string& str,char c);
	string get_string(string::iterator p, string::iterator end)const;
	string get_child(string& str, char c);
	bool exist_string(const string& str1, const string& str2);
	void list_to_vector();
	bool exist_list(string& str)const;
public:
	OrderGroup();
	~OrderGroup();
	void clear();
	bool order_right(const Order& nOrder);
	bool exist_group(Order& order)const;//�ж�һ��order�Ƿ������������
	//���ж���ͳ�Ƽ�����
	//��ȡ�ļ�,���з���
	int set_group(string fileName);
	unsigned int get_size() { return (unsigned int)orderGroup.size(); }
	Order get_order(int i);//��ȡĳ��order
	vector<Order> get_order_by_userName(string userName);//ͨ���û��������ĳȺorder
};

