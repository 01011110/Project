#include "OrderGroup.h"
#include <fstream>
#include <string>
#include <streambuf>
//ֻ��Ϊ�˲�����
#include <ctime>
#include <iostream>
using namespace std;

OrderGroup::OrderGroup()
{
}


OrderGroup::~OrderGroup()
{
	clear();
}

bool OrderGroup::order_right(const Order& nOrder)
{
#ifdef filtration
	if (nOrder.get_userName() == "δ�ҵ��û���" || nOrder.get_userName() == "����Ҫ�ջ���")
		return 0;
#endif // filtration
	return 1;
}

void OrderGroup::clear()
{
	/*vector<Order> orderGroup;//�������� �о������deque����Ҳ����,����ûʲô��Ҫ,deque��������������β��ɾԪ��
	list<Order>orderList;//orderList,���ڳ�ʼ������
	//����,����,����!����û����... Ӧ����map<string ,Order>
	map<Order, string>orderMap;//��order.ID��Ϊ����ֵorderMap*/
	for (unsigned int i = 0; i < orderGroup.size(); i++)
		orderGroup[i].clear();
	list<Order>::iterator it = orderList.begin();
	for (; it != orderList.end(); )
	{
		list<Order>::iterator nIt = it;
		it++;
		nIt->clear();
	}
	//for(unsigned int i=0;i<orderMap.size();i++)orderMap[i].cl
	map<string, Order>::iterator Mit = orderMap.begin();
	for (; Mit != orderMap.end();)
	{
		map<string, Order>::iterator nMit = Mit;
		Mit++;
		nMit->second.clear();
		//nMit->first().clear();
		//(nMit->first).clear();
	}
	orderGroup.swap(vector<Order>()); orderList.swap(list<Order>()); orderMap.swap(map<string,Order>());
}

//ȥ������ָ���ַ�Redundancy
string OrderGroup::delete_char(string sNewTag, char cRddcy)
{
	unsigned int begin = 0;
	begin = (unsigned int)sNewTag.find(cRddcy, begin);  //���ҿո���str�е�һ�γ��ֵ�λ��
	while (begin != -1)  //��ʾ�ַ����д��ڿո�
	{
		sNewTag.replace(begin, 1, "");  // �ÿմ��滻str�д�begin��ʼ��1���ַ�
		begin = (unsigned int)sNewTag.find(cRddcy, begin);  //���ҿո����滻���str�е�һ�γ��ֵ�λ��
	}
	return sNewTag;
}

//��ȡ��p0��end���ַ���
//������string::substring(start,end)�Ĺ��ܺ����һ��
string OrderGroup::get_string(string::iterator p, string::iterator end)const
{
	string s;
	for (; p != end; p++)
	{
		s += *p;
	}
	return s;
}

//ȥ������һ��c֮ǰ���ַ�
void OrderGroup::delete_child_string(string& str, char c)
{
	string::iterator p = str.begin();
	while (*p != c&&p!=str.end())
	{
		p++;
	}
	if (p == str.end())
		return;
	p++;
	str = get_string(p, str.end());
}

//�ж�һ��Order�Ƿ��Ѿ����������OrderGroup��
bool OrderGroup::exist_group(Order& order)const
{
	for (unsigned int i = 0; i < orderGroup.size(); i++)
	{
		if (order == orderGroup[i])
			return 1;
	}
	return 0;
}


//��ȡ���ַ�'c'�ָ�������
string OrderGroup::get_child(string& str, char c)
{
	string s;
	string::iterator p = str.begin();
	int number = 0;
	//��ȡ��*p����һ��","������
	for (; *p != c || number % 2 == 1; p++)
	{
		s += *p;
		if (*p == '\"')number++;
	}
	p++;
	str = get_string(p, str.end());
	return s;
}



//���ĺ���,��ȡ�ļ�
int OrderGroup::set_group(string fileName)
{
	ifstream inFile;
	inFile.open(fileName,ios::in);
	if (!inFile) { throw(1); return -1; }
	//���ж�ȡ��Ϣ,�����г�ʼ��
	//log.csv�ĸ�ʽ�ǵ�һ����"ID WP_ID"��Щ,�ӵڶ��п�ʼÿ���ĵ�һ�����Ӷ���"�ڼ�������",ûʲô��Ϣ
	string s;	//��ȡ��string
	Order nOrder;//�Ӷ���
	//std::ifstream t("file.txt");
	//std::string str((std::istreambuf_iterator<char>(inFile)),std::istreambuf_iterator<char>());
	//s = get_child(str, '\n');
	//inFile>>s;
	//cout << str << endl; exit(-1);
	//if (!inFile)cout << "victory" << endl; exit(-1);

	getline(inFile, s);
	//cout << s << endl; inFile.close(); return 0;
	//s.clear();//ȥ����һ��,��Ϊû��...
	//���ڲ�֪���ļ�ĩβ�᲻���л���,�����������׵ķ�ʽ,�����������ȥ������⵫���ܱ�֤���������һ�����ݺ���û�л��з����ܶ�ȡ��ȷ,��Ȼlog.csv�ļ�ȷʵ��û��������������������������ǿ��վͿ���,Ҳ���Խ����޸�
	
	//s = get_child(str, '\n'); 
	getline(inFile, s);
	int number = 0;
	time_t in_time, out_time; time(&in_time);
	//"cannot dereference string iterator because it is out of range (e.g. an end iterator)"
	while (!inFile.fail()&&number<=1000000)
	{
		//cout << number << endl;
		delete_child_string(s, ',');//cout << s << endl;
		try
		{
			nOrder << s;//�ѽ������������ַ������뵽һ���¶�����
		}
		catch (char)
		{
			nOrder.clear();//s.clear();
			getline(inFile, s);//s = get_child(str, '\n');
			continue;
		}
		catch (char*)
		{
			nOrder.clear();//s.clear();
			getline(inFile, s);//s = get_child(str, '\n');
			continue;
		}
		catch (int)
		{
			cout << "��������:" << number << endl;
			nOrder.clear();//s.clear();
			getline(inFile, s);//s = get_child(str, '\n');
			continue;
		}
		//catch
		//catch("")
		/*if (!exist_group(nOrder))	//��ֹ�ظ�����������//���д�����vector����Ԫ��!!!����ظ���������ɾ޴��ʱ���˷�
		{
			//���֮Դ
			//������ٶ�����ԭ��...��nOrder���뵽orderGroup��ʱ��,���ԭ������ȫ�����Ƶ�һ������ĵط���...
			//��ʵ������ͦ����һ��list�����д洢��,ȫ�洢�����ٸ���list�Ĵ�С������Ӧ��vector����(vector��������ñ������й涨��ʼ��С,����vector<Order> ordegGroup[100];����vector<Order> ordegGroup[count];count�Ǹ�����)
			orderGroup.push_back(nOrder);
			number++;
		}*/
		if (!exist_list(nOrder.get_ID()))//�������û���ظ���ô�Ͱ������뵽����
		{
			//orderMap.insert(map<string, Order>::value_type(nOrder.get_ID()),nOrder);
			orderMap.insert(map<string,Order>::value_type(nOrder.get_ID(),nOrder));
			orderList.push_back(nOrder); number++;
		}
		if (number % 1000== 0&&number!=0) { time(&out_time); cout << "�Ѿ���ȡ" << number << "��" << "\t��ʱ" << out_time - in_time << "s" << endl;time(&in_time); }
		nOrder.clear();//s.clear();//s = get_child(str, '\n');
		getline(inFile, s);
	}
	list_to_vector();
	//��������,ʹ��lamda���ʽ
	inFile.close();
	return 0;
}

//��Listת�Ƶ�vector
void OrderGroup::list_to_vector()
{
	//��ֱ�ӵĺ���
	//��ʵӦ���ж�һ���Ƿ����ظ�����...����������д...
	//vector<Order>nOrderGroup(orderList.size());
	orderGroup.insert(orderGroup.end(),orderList.begin(),orderList.end());
	orderList.swap(list<Order>());//���
}

//��ȡĳ��order
Order OrderGroup::get_order(int i)
{
	if ((unsigned)i >= orderGroup.size())
		throw("i is so large");
	return orderGroup[i];
}

//�����û�������ȡĳȺorder
vector<Order> OrderGroup::get_order_by_userName(string userName)
{
	vector<Order> cOrderGroup;
	for (unsigned int i = 0; i < orderGroup.size(); i++)
	{
		if (orderGroup[i].get_userName() == userName)
		{
			Order nOrder = orderGroup[i];
			cOrderGroup.push_back(nOrder);//�������������µ���Դ,ֱ����cOrderGroup.push_back(orderGroup[i])���������Դ(����new�Ķ���)������ָ��ָ��,����ȫ,���Զ�����һ����ֵ(�������������Դ,һ��������"="������(��Ż��...))
		}
	}
	return cOrderGroup;
}

//������List��
bool OrderGroup::exist_list(string& str)const
{
	/*list<Order>::const_iterator pOrder;
	//_List_const_iterator<Order> pOrder;
	for (pOrder = orderList.begin(); pOrder != orderList.end(); pOrder++)
		if (order==*pOrder)return 1;
	return 0;*/
	//�����Ǵ���ķ���,������������ľ����Ǻ�����...
	//Ӧ����map(map��ʵ�־�����)
	//int i = orderMap.find(order.get_ID());
	return orderMap.count(str);
}


bool OrderGroup::exist_string(const string& str1, const string& str2)
{
	if (str2.size() > str1.size())return 0;
	for (unsigned int i = 0; i <= str1.size() - str2.size(); i++)
	{
		string s;
		for (unsigned int j = 0; j < str2.size(); j++)
		{
			s += str1[i + j];
		}
		if (s == str2)return 1;
		s = "";
	}
	return 0;
}