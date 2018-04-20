#pragma once
//����һ��ģ��
#include<vector>
#include <map>
#include <algorithm>//���STLģ���㷨
#include <iostream>
using namespace std;
//ģ����,���ʵ�ֱ�����.h�ļ���
//���������map
/**************
����һ��������÷�:
�����һ��������map��ģ��,������:��һ��ؼ�����ͬ�����ݸ��ϲ���һ��
�ֱ�����������:
			��һ������:��һ�����ݵĹؼ���(��Щ���ݵĹؼ��ʶ���ͬ)
			�ڶ�������:ÿ�����ݵ�����ֵ(Name),������������������������ݵ�Ԫ��
			����������:���ݱ���
����,����Ūһ��,������Ϊ"A"�Ķ����ļ���,��ô��Ӧ������һ�����ݵĹؼ���ΪA
										NameΪ��Щ������ID(������ID�Ƕ�һ�޶���,��������)
										DataΪ��������
����ؼ���AΪstring����,IDҲ��string����,��ô��Ӧ��ʵ����Ϊ:Group<string,string,Order> orderGroupByUserName;
**************/
template<class KeyWord,class Name,class Data> //��������
class Group
{
private:
	KeyWord keyWord;
	vector<Data*> dataGroup;
	map<Name,Data> dataMap;//��ֹ�ظ��ļ���,��һ�������洢
public:
	Group() {};
	Group(KeyWord nKeyWord) { clear(); keyWord = nKeyWord; }
	~Group() { clear(); };
	void clear(); 

	//set_keyword��������е���������
	void set_keyWord(KeyWord nKeyWord) { clear(); keyWord = nKeyWord; }

	KeyWord get_keyWord() { return keyWord; }

	//����������,���صĶ���Data������
	Data& find_data(int i) { if (i >= (int)dataGroup.size())throw"haven't"; return *dataGroup[i]; }
	Data& find_data(Name nName);

	//Name get_name(int i) { if (i >= (int)dataGroup.size())throw"haven't"; return dataGroup[i]}
	void add_data(KeyWord nKeyWord,Name nName,Data nData);

	//void add_childData();
	bool exist_group(Name nName) { return dataMap.count(nName); };

	unsigned int get_size() { return (unsigned int)dataGroup.size(); }

	//Ҫ����һ��[]�����

	//������,���ɱ����ʹ��ָ��,��Ϊ��һ��vector<Order*>�Ķ���
	void sort_by_function(int(*fcmp)(Data* pData1, Data* pData2));

	//�������Data�����ƶȵĺ���
	double sml_num(unsigned int i, unsigned int j);// { return (*Data[i]).sml_num((*Data[j])); }
	double sml_num(Name name1, Name name2) { return find_data(name1).sml_num(find_data(name2)); }


};

template<class KeyWord,class Name ,class Data>
void Group<KeyWord,Name,Data>::add_data(KeyWord nKeyWord,Name nName,Data nData)
{
	//cout << nKeyWord << endl;
	if (nKeyWord != keyWord) return;
	if (!exist_group(nName))
	{
		//dataMap.insert(map<Name, Data>::value_type(nName,nData));
		dataMap.insert(map<Name, Data>::value_type(nName,nData));
		if(exist_group(nName))
			dataGroup.push_back(&find_data(nName));
		else;
	}
}

template<class KeyWord, class Name, class Data>
void Group<KeyWord, Name, Data>::clear()
{
	for (unsigned int i = 0; i < dataGroup.size(); i++)
		(*dataGroup[i]).clear();
	//dataGroup.clear(); dataMap.clear();
	//dataGroup.swap(dataGroup);
	//dataMap.swap(dataMap);
	dataGroup.swap(vector<Data*>()); dataMap.swap(map<Name, Data>());
}

template<class KeyWord, class Name, class Data>
Data& Group<KeyWord, Name, Data>::find_data(Name nName)
{
	//map<Name, Data>::iterator it;
	//it = dataMap.find(nName);
	//if (res==dataMap.end())
	//	throw"haven't";//����Ҳ���,�ͷ���β��ָ��,�׳�"haven't"
	//return *res;
	//for(unsigned int i=0;i<)
	/*for(unsigned int i=0;i<dataGroup.size();i++)
		if(dataGroup[i])*/
	//throw 'a';
	/*map<Name, Data*>::iterator it = dataMap.find(nName);
	if(it==dataMap.end())
		throw"haven't";//����Ҳ���,�ͷ���β��ָ��,�׳�"haven't"
	else
	{
		return //*it.secend;
	}*/
	if (dataMap.count(nName))
	{
		return dataMap[nName];
	}
	else throw"haven't";//����Ҳ���,���׳�"haven't"
}

template<class KeyWord, class Name, class Data>
void Group<KeyWord, Name, Data>::sort_by_function(int(*fcmp)(Data* pData1, Data* pData2))
{
	//sort(dataGroup)
	sort(dataGroup.begin(), dataGroup.end(), fcmp);
}



//�ܳ��һ������,�����������ƶ�
template<class KeyWord, class Name, class Data>
double Group<KeyWord, Name, Data>::sml_num(unsigned int i, unsigned int j)
{
	
}


;