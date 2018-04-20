#pragma once
#include <string>
#include <fstream>
using namespace std;
class ChildNote
{
private:
	string Name;//�������� ����"��ɫ����" "��ɫ"��
	string Value;
	string get_child_note(string& str);
	string get_string(string::iterator begin, string::iterator end);
public:
	ChildNote();
	~ChildNote();
	void set_note(string str);
	bool same_name(const ChildNote& nChildNote)const;
	bool operator==(const ChildNote& nChileNote)const { return nChileNote.Name == Name; }
	bool operator>(const ChildNote& nChildNote)const { return Name > nChildNote.Name; }
	bool operator<(const ChildNote& nChildNote)const { return Name < nChildNote.Name; }
	bool operator>=(const ChildNote& nChildNote)const { return Name >= nChildNote.Name; }
	bool operator<=(const ChildNote& nChildNote)const { return Name <= nChildNote.Name; }
	void operator=(ChildNote& nChileNote) { Name = nChileNote.Name; Value = nChileNote.Value; }
	void operator<<(string str) { set_note(str); }
	friend fstream& operator<<(fstream& outFile, ChildNote& childNote);
	friend ostream& operator<<(ostream& outFile, ChildNote& childNote);
	void clear() { Name.shrink_to_fit(); Value.shrink_to_fit(); }//Name.swap(Name); Value.swap(Value); }
	string get_name() { return Name; }
	string get_value() { return Value; }
	//������Կ��Ǽ���һ�����ƺ������ж�����Ƿ����ƻ�����ͬ��������ɫʲô�ģ�Ҳ����ϸ����������ChildNote̫����

};
static fstream& operator<<(fstream& outFile, ChildNote& childNote)
{
	outFile <<"{"<<childNote.Name << ":" << childNote.Value<<"}";
	return outFile;
}

static ostream& operator<<(ostream& outFile, ChildNote& childNote)
{
	outFile << "{" << childNote.Name << ":" << childNote.Value << "}";
	return outFile;
}
;