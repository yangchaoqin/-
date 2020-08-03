#include "stdafx.h"
#include "MyDefine.h"

MyDefine::MyDefine(){
	isBlank = false;
}

MyDefine::~MyDefine(){

}


//��ȡͷ�ļ�����ÿһ�д��list������
int MyDefine::ReadDefine(string path){
	ifstream infile(path.c_str());
	if (!infile)	return 0;
	string str_line = "";
	while (getline(infile, str_line)){
		list_def.push_back(str_line);
	}
	infile.close();
	infile.clear();
	return 1;
}

//��list���������ݰ�˳��д���ļ�
int MyDefine::WriteDefine(string path){
	ofstream outfile(path.c_str());
	if (!outfile)	return 0;
	for (list<string>::iterator itr = list_def.begin(); itr != list_def.end(); ++itr){
		outfile << *itr << endl;
	}
	outfile.close();
	outfile.clear();
	return 1;
}

//�ں��ʵ�λ�ò���������һ�����ݣ�#define +����+ID��+�������ı�ע��
//��ִ�иú���ǰ����Ҫ��ִ��GetKey�����ҵ���ǰ��ʹ�õ�ID��
bool MyDefine::SetDefine(string def,string def_name,string SpChinese){
	
/*	for (list<string>::iterator itr = list_def.begin(); itr != list_def.end(); ++itr){
		if (string::npos != itr->find(def_name) || string::npos != itr->find(key))
			return false;
	}*/
	
	list<string>::iterator insert_itr = FindInsertLocation();
	if (isBlank){
		string blank_line = "";
		list_def.insert(insert_itr, blank_line);
		this->isBlank = false;

	}
	string prefix = "#define " + def + def_name;
	string blank = " ";
	for (int i = prefix.size(); i < 59; i++){
		blank += ' ';
	}
	string insert_line = prefix + blank + key + " //" + SpChinese;
	list_def.insert(insert_itr, insert_line);
	return true;
}

//��ʱû�õ��Ľӿڣ������޸ĵĲ���
bool MyDefine::RsetDefine(string def, string def_name,  string SpChinese){
	string insert_line = "#define " + def + def_name + "        " + key + " //" + SpChinese;
	for (list<string>::iterator itr = list_def.begin(); itr != list_def.end(); ++itr){
		if (string::npos != itr->find(def_name) || string::npos != itr->find(key))
			{
				*itr = insert_line;
				return true;
		}
	}
	return false;
}

//���ڲ��ҵ�ǰ���ʵĲ���λ�ã����غ���λ�õĵ�����
list<string>::iterator MyDefine::FindInsertLocation(){
	int k = std::stoi(key);
	int nextK = k;
	while (k > 0){
		k--;
		string last_key = to_string(k);
		for (list<string>::iterator itr = list_def.begin(); itr != list_def.end(); ++itr){
			if (string::npos != itr->find(last_key)){
				if (nextK > k + 1)	this->isBlank = true;
				itr++;
				return itr;
			}
		}
	}
	
	return list_def.end();
}

//���ڻ�ȡ��ǰ���µ�ID��
wstring MyDefine::GetKey(){
	string insert_flag = "";
	if (this->business == "Quote")	insert_flag = "This is a symbol to find the key in quote header";
	else if (this->business == "Trade")	insert_flag = "This is a symbol to find the key in trade header";
	for (list<string>::iterator itr = list_def.begin(); itr != list_def.end(); ++itr){
		if (string::npos != itr->find(insert_flag)){
			while (itr!=list_def.begin()){
				itr--;
				if (string::npos != itr->find("#")){
					string s = *itr;
					string::size_type position = s.find("//");
					if (string::npos != position){
						position--;
						while (isblank(s[position] )&&position>=0)	position--;
						string::size_type pend = position;
						while (!isblank(s[position]) && position >= 0)	position--;
						string::size_type pstart = position;
						key = s.substr(pstart + 1, pend - pstart);
					}
					else{
						position = s.size() - 1;
						while (isblank(s[position]) && position >= 0)	position--;
						string::size_type pend = position;
						while (!isblank(s[position]) && position >= 0)	position--;
						string::size_type pstart = position;
						key = s.substr(pstart + 1, pend - pstart);
					}
					int k = std::stoi(key);
					k++;
					key = to_string(k);
					return UTF8ToUnicode(key);
				}
			}

		}
	}
	return L"";
}

//���õ�ǰ��ҵ����
void MyDefine::SetBusiness(string bsn){
	this->business = bsn;
	return;
}

bool MyDefine::SetKey(wstring k){
	this->key = UnicodeToUTF8(k);
	return true;
}

//��stringת��wstring
std::wstring UTF8ToUnicode(const std::string & str)
{
	int nWideCodeSize = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, NULL);
	WCHAR *wStr = new WCHAR[nWideCodeSize];
	ZeroMemory(wStr, nWideCodeSize *sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.length(), wStr, nWideCodeSize);
	wStr[nWideCodeSize - 1] = L'\0';
	std::wstring result = wStr;
	delete[] wStr;
	return result;
}

//��wstringת��string
std::string UnicodeToUTF8(const std::wstring & str)
{
	int nCharCodeSize = WideCharToMultiByte(CP_UTF8, 0, str.c_str(), -1, NULL, NULL, NULL, NULL);
	char *utf8Str = new char[nCharCodeSize];
	ZeroMemory(utf8Str, nCharCodeSize);
	WideCharToMultiByte(CP_UTF8, 0, str.c_str(), (int)str.length(), utf8Str, nCharCodeSize, NULL, NULL);
	std::string result = utf8Str;
	delete[] utf8Str;
	return result;
}
