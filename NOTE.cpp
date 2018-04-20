#include "Note.h"
#include <iostream>
using namespace std;
#define Threshold 0.8;


Note::Note()
{
}


Note::~Note()
{
	clear();
}

string Note::get_string(string::iterator begin, string::iterator end)
{
	//string get_string(string::iterator begin, string::iterator end)
	string s;
	for (; begin != end; begin++)
		s += *begin;
	return s;
}

void Note::clear()
{
	for (unsigned int i = 0; i < note.size(); i++)
		note[i].clear();
	//note.clear();
	//Note note2;
	//vector<ChildNote> note2;
	note.swap(vector<ChildNote>());
	//note.shrink_to_fit();
}


void Note::set_note(string str)
{
	if (str == "[]"||str=="None")
		return;
	str = get_string(str.begin()+1, str.end());
	string::iterator it = str.begin();
	string s;
	int number = 1;
	while (number != 0)
	{
		for (; it!=str.end()&& *it != '{'; it++);
		if (it == str.end())throw 1;
		int count = 1;
		it++;
		for (;it!=str.end(); it++)
		{
			if (*it == '\0')throw 'a';
			if (*it == '{')count++;
			if (*it == '}')count--;
			if (count == 0)break;
			s += *it;
		}
		ChildNote newNote;
		newNote.set_note(s);
		//note.insert(map<ChildNote,string>::value_type(newNote,newNote.get_name()));
		note.push_back(newNote);
		s.shrink_to_fit();
		if (it != str.end())
		{
			it++;
			while (it!=str.end()&& *it == ' ')
				it++;
			if (it == str.end())throw 2;
			if (*it == '[')number++;
			if (*it == ']')number--;
		}
		else throw 3;
	}
	sort_note();

	//str = str.c_str() + 1;
	//const char* p = str.c_str();
	//string s;
	//int number = 1;
	//while (number!=0)
	//{
	//	for (; *p != '{'; p++);
	//	int count = 1;
	//	p++;
	//	for (;; p++)
	//	{ 
	//		if (*p == '\0')throw'a';
	//		if (*p == '{')count++;
	//		if (*p == '}')count--;
	//		if (count == 0)break; 
	//		s += *p;
	//	}
	//	ChildNote newNote;
	//	newNote.set_note(s);
	//	//note.insert(map<ChildNote,string>::value_type(newNote,newNote.get_name()));
	//	note.push_back(newNote);
	//	s.clear();
	//	p++;
	//	while (*p == ' ')
	//		p++;
	//	if (*p == '[')number++;
	//	if (*p == ']')number--;
	//}
	//sort_note();
}

//��������note���ƶȵĺ���,��0��1
double Note::sml_num(Note nNote)
{
	/*
	���˼·:����note,ÿ��note�������ɵ�childnote,���Ȱ���Щchildnote�ϲ�,�ٸ������ƶ��������ֵ
	*/
	/*��������:�������nNote����ӱ�ǩ������thisNote���ӱ�ǩ�Ա�,������������*/
	vector<double>vecThis, vecNote;
	for (unsigned int i = 0; i < note.size(); i++)
	{
		ChildNote nChildNote;
		//cout << note[i].get_name();
		nChildNote = nNote.find_by_name(note[i].get_name());
		if (nChildNote.get_value() == nChildNote.get_name() && nChildNote.get_value() == "")//������ChileNoteֻ������thisNote��
		{
			vecThis.push_back(1); vecNote.push_back(-1);
		}
		else//������ChileNoteͬʱ������thisNote��nNote��
		{
			string str = max_same_string(note[i].get_value(), nChildNote.get_value());//��ȡnote[i]��nChildNote�����ͬ�Ӵ�
			if (str.size() / note[i].get_value().size() > 0.7&&str.size() / nChildNote.get_value().size() > 0.7)
			{
				vecThis.push_back(1); vecNote.push_back(1);
			}
			//��������vaule�Ĳ���ֵ
			//�Ѷ����ڴʷ�����
			else
			{
				double thisDouble, nDouble;
				thisDouble = 1 - (double)str.size() / note[i].get_value().size();
				nDouble = -(1 - (double)str.size() / nChildNote.get_value().size());
				vecThis.push_back(thisDouble); vecNote.push_back(nDouble);
			}
			str.clear();
		}
		nChildNote.clear();
	}
	for (unsigned int i = 0; i < (unsigned int)nNote.size(); i++)
	{
		ChildNote nChildNote;
		if (exist_name(nNote.note[i].get_name()) == 0)//��������thisNote��,��ֻ������nNote��
		{
			vecThis.push_back(-1); vecNote.push_back(1);
		}
	}
	/*�Ѿ������vecThis��vecNote������*/

	/*����vecThis��vecNote�����ƶ�*/
	double sml = degress(vecThis, vecNote);
	return sml;
}

void Note::sort_note()//��ChileMote�����ֵ���������
{
	sort(note.begin(),note.end());
}

string Note::max_same_string(const string& str1, const string& str2)//����str1��str2�������ͬ�Ӵ�
{
	string str;
	for (unsigned int i = 0; i<str2.length(); i++)
	{
		for (unsigned int j = i + 1; j<str2.length(); j++)
		{
			if (str1.find(str2.substr(i, j - i + 1)) != -1)
			{
				if (str.length()<str2.substr(i, j - i + 1).length())
					str = str2.substr(i, j - i + 1);
			}
			else
				break;
		}
	}
	return str;
}

bool Note::exist_name(string& name)
{
	for (unsigned int i = 0; i < note.size(); i++)
		if (name == note[i].get_name())return 1;
	return 0;
}

inline ChildNote Note::find_by_name(string& name)
{
	ChildNote childNote;
	for (unsigned int i = 0; i < note.size(); i++)
	{
		if (name == note[i].get_name())return note[i];
		//if (name > note[i].get_name())return childNote;
	}
	return childNote;
}

double Note::inner_product(vector<double> vec1, vector<double>vec2)
{
	if (vec1.size() == 0 || vec2.size() == 0)//�����һ������Ϊ0,�ͷ���Ϊ0
		return 0;
	if (vec1.size() != vec2.size())//�������������С��ͬ,���׳�"size flase"
		throw("size false");
	double sum = 0;
	for (unsigned int i = 0; i < vec1.size(); i++)
		sum += vec1[i] * vec2[i];
	return sum;
}

double Note::model(vector<double> vec)
{
	double num = inner_product(vec, vec);
	return sqrt(num);
}

double Note::degress(vector<double> vec1, vector<double> vec2)
{
	double inner = inner_product(vec1, vec2);
	double mod1 = model(vec1);
	double mod2 = model(vec2);
	if (mod1 > 1e-6 || mod1 < -1e-6)
	{
		if (mod2 > 1e-6 || mod2 < -1e-6)
			return inner / (mod1*mod2);
		return 0;
	}
	else return smlAverage;
}
/*
/*Group<string, string, Order> orderGroupByUserName;
for (unsigned int i = 0; i < orderGroup.get_size(); i++)
nOrderSet.add_order(orderGroup.get_order(i).get_ID(), orderGroup.get_order(i));*/
//cout << "���ڽ��밴��������ģʽ,�����������ѯ�ڼ�������,���Զ���ӡ���û�����Ϣ" << endl; read = 1;
//while (read)
//{
//	cout << "�������������ڼ�������" << endl;
//	unsigned int number; cin >> number;
//	if (number >= orderGroup.get_size())cout << "û�д˶���(���������̫��)" << endl;
//	else
//	{
//		cout << "orderID\tname\tuserID\tphone\taddress" << endl;
//		cout << orderGroup.get_order(number) << endl;
//	}
//	cout << "�Ƿ�Ҫ��������?����1������ȡ,����0ֹͣ����" << endl; cin >> read;
//}
//cout << "���ڽ�������ģʽ,�����������ѯ���û�����,���Զ���ӡ������Ϊ�û�����Ϣ" << endl; read = 1;
//while (read)
//{
//	cout << "���������������û�������" << endl;
//	string userName; cin >> userName;
//	vector<Order> nOrderGroup = orderGroup.get_order_by_userName(userName);
//	if (nOrderGroup.size() == 0) { cout << "�����ڴ��û�ID" << endl; }
//	else
//	{
//		//out << order.get_orderID() << "  " << order.get_name() << "  " << order.get_userID() << "  " << order.get_phone().get_number() << "  " << order.get_address().get_all();
//		cout << "orderID\tname\tuserID\tphone\taddress" << endl;
//		for (unsigned int i = 0; i < nOrderGroup.size(); i++)
//			cout << nOrderGroup[i] << endl;
//	}
//	userName.clear();cout<<"�Ƿ�Ҫ��������?����1������ȡ,����0ֹͣ����" << endl; cin >> read;
//}
/*Note note1, note2;
cout << "���ڽ���note�ȶ�ģʽ,������������λ��,������Ӧ�����ƶ�" << endl; read = 1;
double max = -1; double sml = 0;
while (read)
{

int i, j; cin >> i >> j;
note1 = orderGroup.get_order(i).get_note();
for (int k = 0; k < j; k++)
{
note2 = orderGroup.get_order(k).get_note();
sml = note1.sml_num(note2);
if (sml != smlAverage)
{
cout <<note1 << endl << note2<<"\t"<<k<< endl << "���ƶ�Ϊ:";
cout << sml << endl;
}
note2.clear();
if (sml > max)max = sml;
}
note1.clear();
cout << "�Ƿ����?" << endl; cin >> read;
}
cout << "������ƶ�Ϊ" <<max<<endl;*/
//system("pause");
//cout << nOrder << endl;
/*OrderTime order;
order.set_time("2017 12 2 3:45");
cout << order.get_year() << endl;
cout << order.get_month() << endl << order.get_day() << endl << order.get_hour() << endl << order.get_min() << endl;*/
/*ChildNote child;*/
/*string str = "          'name' : '��ɫ', 'value' : '����'";
for (const char* p = str.c_str(); *p != '\''; str=p)
p++;
cout << str;*/
//str.replace(" ", "", NULL);
//child.get_note("{ 'name' : '��ɫ', 'value' : '����'}");// , { 'name': '����', 'value' : '185' }]");
//cout << child.get_name() << endl << child.get_value() << endl;
/*Note note;
note.set_note("[{'name': '��ɫ', 'value'    : '����'},    {    'name'   : '����', 'value' : '185'  }   ]");
for (int i = 0; i < note.size(); i++)
{
ChildNote nNote = note.get_child_note(i);
cout << "Name:"<<nNote.get_name() << "\t" <<"Value"<< nNote.get_value() << endl;
}*/
/*Phone phoneTest;
phoneTest.set_number("86-123");
cout << phoneTest.get_number() << endl;*/
//string str = "������";
/*const char* p = str.c_str();
string s;
for (; *p != ' '; p++)
s += *p;
cout << s;*/
/*char a[9] = {-50,-46,-80,-82,-60,-29,0};
cout << a;*/
//string s = "      ��Ұ";//ǰ��Ķ��ǿո񣬲���Tab
//const char* p = s.c_str();
//for (; *p == ' '; p++);//Ŀ����ȥ�����еķǿո���ַ�
//s= p;//��pָ����ַ�����ֵ��s
//cout << p << endl;
/*Address address;
address.set_address("����ʡ ������ �彭���� �����ֵ� ������·������԰63-1���淿��������վ�����Ӱ�� ");
address.set_address("025-232-4220037");
cout << address.get_province() << address.get_city() << address.get_county() << address.get_town() << address.get_other() << endl;*/
/*Order order;
string s = "C5AB15DEB54711E781AD00155D88D822,67774385564773200.00 ,���յ���100Ԫ �Զ���ֵ���� �����䵽��,2017/10/13 22:07,���»��ѳ�ֵרӪ��,99.8,[],��ֵ�ɹ�,�Ų�,86-13921700873,����ʡ ̩���� ������ �����ֵ� ����·���͹�Ԣ3��301�� ,tzzbo52,2017/10/20 11:35,0,a316fcfbc7af618f389a2bbd828b701c,,,1";
order.set_order(s);
cout<<order.get_ID()<<endl;
cout << order.get_orderID() << endl;
cout << order.get_orderTime().get_day() << endl;
cout << order.get_seller() << endl;
cout << order.get_note() << endl;*/
//-50 -46 -80 -82 -60 -29

//��ȡ�ļ����� csv��","��Ϊ�ָ�,����"��"
//��ʹ��:getline(ifstream& inFile,string& s); ifstream::getline(char ch[],int maxCount);
/*ifstream inFile;
inFile.open("test.csv", ios::in);
if (!inFile) return -1;
string s1, s2, s3;
char s4[1000];
getline(inFile,s1);
cout << s1 << endl;
getline(inFile, s2);
cout << s2 << endl;
inFile.getline(s4,1000);
cout << s4 << endl;*/

//bool isPrime_3(int num)
//{
//	//������С�����⴦��  
//	if (num == 2 || num == 3)
//		return 1;
//	//����6�ı��������һ����������  
//	if (num % 6 != 1 && num % 6 != 5)
//		return 0;
//	int tmp = sqrt(num);
//	//��6�ı��������Ҳ���ܲ�������  
//	for (int i = 5; i <= tmp; i += 6)
//		if (num %i == 0 || num % (i + 2) == 0)
//			return 0;
//	//�ų����У�ʣ���������  
//	return 1;
//}
//#include <stdio.h>  
//#include <stdlib.h>  
//#include <math.h>  
//
//#define QUEEN 6     //�ʺ����Ŀ  
//#define INITIAL -10000   //���̵ĳ�ʼֵ  
//
//int a[QUEEN];    //һά�����ʾ����  
//
//void init()  //�����̽��г�ʼ��  
//{
//	int *p;
//	for (p = a; p < a + QUEEN; ++p)
//	{
//		*p = INITIAL;
//	}
//}
//
//int valid(int row, int col)    //�жϵ�row�е�col���Ƿ���Է��ûʺ�  
//{
//	int i;
//	for (i = 0; i < QUEEN; ++i)   //�����̽���ɨ��  
//	{
//		if (a[i] == col || abs(i - row) == abs(a[i] - col))   //�ж��г�ͻ��б���ϵĳ�ͻ  
//			return 0;
//	}
//	return 1;
//}
//
//void print()    //��ӡ���N�ʺ��һ���  
//{
//	int i, j;
//	for (i = 0; i < QUEEN; ++i)
//	{
//		for (j = 0; j < QUEEN; ++j)
//		{
//			if (a[i] != j)      //a[i]Ϊ��ʼֵ  
//				printf("%c ", '.');
//			else                //a[i]��ʾ�ڵ�i�еĵ�a[i]�п��Է��ûʺ�  
//				printf("%c ", '#');
//		}
//		printf("\n");
//	}
//	for (i = 0; i < QUEEN; ++i)
//		printf("%d ", a[i]);
//	printf("\n");
//	printf("--------------------------------\n");
//}
//

/*zhangmengyao woaini wojueode womenkeyizaiyiqi le wozhendeaide qingnijiugeiwo wozhendehenxihuani 
zhendezhende
ruguonikandaozhegezhushi 
qingni gaosuwo 
niaiwo
zhangmengyao woaini;
//void queen()      //N�ʺ����
//{
//	int n = 0;
//	int i = 0, j = 0;
//	while (i < QUEEN)
//	{
//		while (j < QUEEN)        //��i�е�ÿһ�н���̽�⣬���Ƿ���Է��ûʺ�
//		{
//			if (valid(i, j))      //��λ�ÿ��Է��ûʺ�
//			{
//				a[i] = j;        //��i�з��ûʺ�
//				j = 0;           //��i�з��ûʺ��Ժ���Ҫ����̽����һ�еĻʺ�λ�ã����Դ˴���j���㣬����һ�еĵ�0�п�ʼ����̽��
//				break;
//			}
//			else
//			{
//				++j;             //����̽����һ��
//			}
//		}
//		if (a[i] == INITIAL)         //��i��û���ҵ����Է��ûʺ��λ��
//		{
//			if (i == 0)             //���ݵ���һ�У���Ȼ�޷��ҵ����Է��ûʺ��λ�ã���˵���Ѿ��ҵ����еĽ⣬������ֹ
//				break;
//			else                    //û���ҵ����Է��ûʺ���У���ʱ��Ӧ�û���
//			{
//				--i;
//				j = a[i] + 1;        //����һ�лʺ��λ��������һ��
//				a[i] = INITIAL;      //����һ�лʺ��λ�����������̽��
//				continue;
//			}
//		}
//		if (i == QUEEN - 1)          //���һ���ҵ���һ���ʺ�λ�ã�˵���ҵ�һ���������ӡ����
//		{
//			printf("answer %d : \n", ++n);
//			print();
//			//�����ڴ˴�����������Ϊ����Ҫ�ҵ���N�ʺ���������н⣬��ʱӦ��������еĻʺ󣬴ӵ�ǰ���ûʺ���������һ�м���̽�⡣
//			//_sleep(600);
//			j = a[i] + 1;             //�����һ�з��ûʺ���������һ�м���̽��
//			a[i] = INITIAL;           //������һ�еĻʺ�λ��
//			continue;
//		}
//		++i;              //����̽����һ�еĻʺ�λ��
//	}
//}
//
//int main(void)
//{
//	init();
//	queen();
//	system("pause");
//	return 0;
//}
#define MaxNum 5
#define smlAverage 0.5;
//��δ����������
double inner_product(double vec1[MaxNum],double vec2[MaxNum])	//���������������ڻ�
{
	double sum = 0;
	for (int i = 0; i < MaxNum; i++)
		sum += vec1[i] * vec2[i];
	return sum;
}
double model(double vec[MaxNum])
{
	double num = inner_product(vec, vec);
	return sqrt(num);
}
double degress(double vec1[MaxNum], double vec2[MaxNum])
{
	double inner = inner_product(vec1, vec2);
	double mod1 = model(vec1);
	double mod2 = model(vec2);
	if (mod1 > 1e-6 || mod1 < -1e-6)
	{
		if (mod2 > 1e-6 || mod2 < -1e-6)
			return inner / (mod1*mod2);
	}
	else return smlAverage;	//�����һ��������ģ��0����ô���ǵ����ƶ���ƽ��ֵ���ݶ�Ϊ0.5��
	
}
*/