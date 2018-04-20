#pragma once
//����һ���Ƚϲ��ģ��,��������Group.h��
#include<vector>
#include"Order.h"
#include "OrderGroup.h"
#include <map>
using namespace std;
//ģ����,���ʵ�ֱ�����.h�ļ���
template<class ClassificationData> //��������
class OrderSet		//�и�ClassificationData�ı�ǩ,���ڴ�����һ�����ϵĴ���Ԫ��
{
private:
	ClassificationData representativeElement;//�����׼����
	vector<Order*> pOrderGroup;				  //�����Ķ�������,��"����",�����������
	map<ClassificationData, Order>orderMap;   //����map,���ڷ������,ClassificationData�ǹؼ���,������string������time������address
	//int number;
public:
	OrderSet() {};
	~OrderSet() {};
	ClassificationData get_representative_element() { return representativeElement; }
	//OrderSet(OrderGroup& nOrderGroup);//����OrderSet
	void set_representativeElement(ClassificationData nRepresentativeElement) { representativeElement = nRepresentativeElement; pOrderGroup.clear(); orderMap.clear(); }
	void add_order(ClassificationData representativeElement,Order nOrder);//����OrderSet
	bool exist_set(ClassificationData& representativeElement);//���order������set��
	int get_size() { return pOrderGroup.size(); }
};

template<class ClassificationData> //��������
void OrderSet<ClassificationData>::add_order(ClassificationData representativeElement,Order nOrder)
{
	if (!exist_set(representativeElement))
	{
		//orderMap.insert(map<Order, string>::value_type(nOrder, nOrder.get_ID()));
		orderMap.insert(map<ClassificationData, Order>::value_type(representativeElement,nOrder));
		pOrderGroup.push_back(&nOrder);
	}
}
template<class ClassificationData> //��������
bool OrderSet<ClassificationData> ::exist_set(ClassificationData& representativeElement)//���order������set��
{
	return orderMap.count(representativeElement);
}
;