#include "stdafx.h"
#include "AddAll.h"

AddAll::AddAll(){
	mydef = new MyDefine;
	myini = new MyIni;
	isInsert == false;

}

AddAll::~AddAll(){
	delete mydef;
	delete myini;
}

//��ʼ��Ҫд������ݣ�����������ţţ�İ���moomoo�İ���ҵ���ߡ�д���λ��
bool AddAll::Init(list<wstring> listDef, list<wstring> listlang, list<wstring> listlangmoomoo, string business, string towhere){

	//��Ҫ�洢��Ϣ��������ʼ��
	vDef.clear();
	spchinese.clear();
	tdchinese.clear();
	english.clear();
	spchinesemm.clear();
	tdchinesemm.clear();
	englishmm.clear();

	//�̶��洢�����Ĵ�С����������
	vDef.resize(listDef.size());
	int i = 0;
	for (list<wstring>::iterator itr = listDef.begin(); itr != listDef.end();itr++){
		vDef[i] = *itr;
		i++;
	}
	int Vsize = listlang.size();
	spchinese.resize(Vsize);
	tdchinese.resize(Vsize);
	english.resize(Vsize);
	i = 0;
	for (list<wstring>::iterator itr = listlang.begin(); itr != listlang.end(); itr++){
		string lines = UnicodeToUTF8(*itr);
		istringstream is(lines);
		//�����е��İ�ϸ�ֳɼ�Ӣ������Ϣ
		string line;
		getline(is, line);
		DeleteRet(line);
		spchinese[i]=UTF8ToUnicode(line);
		getline(is, line);
		DeleteRet(line);
		tdchinese[i]=UTF8ToUnicode(line);
		getline(is, line);
		DeleteRet(line);
		english[i]=UTF8ToUnicode(line);
		i++;
	}
	int Vsizemm = listlangmoomoo.size();
	spchinesemm.resize(Vsizemm);
	tdchinesemm.resize(Vsizemm);
	englishmm.resize(Vsizemm);
	i = 0;
	for (list<wstring>::iterator itr = listlangmoomoo.begin(); itr != listlangmoomoo.end(); itr++){
		string lines = UnicodeToUTF8(*itr);
		istringstream is(lines);
		//��moomoo�������İ���ȡ�ɼ�Ӣ������Ϣ
		string line;
		getline(is, line);
		DeleteRet(line);
		spchinesemm[i] = UTF8ToUnicode(line);
		getline(is, line);
		DeleteRet(line);
		tdchinesemm[i] = UTF8ToUnicode(line);
		getline(is, line);
		DeleteRet(line);
		englishmm[i] = UTF8ToUnicode(line);
		i++;
	}
	this->Business = business;
	this->Towhere = towhere;
	return true;
}

bool AddAll::WriteAll(string path_Def, string path_Lang, HWND m_hWnd){
	string bdef = "";
	string fName = "";
	//�ж�ҵ���ߣ�Ϊ�������ǰ׺
	if (this->Business == "Quote")	{
		bdef = "IDS_QT_";
		fName = this->Business;
	} 
	else if (this->Business == "Trade") {
		bdef = "IDS_Trade_";
		fName = "Trader";
	}

	//��ͷ�ļ�д�����еĺ�
	int res = mydef->ReadDefine(path_Def + "//Define//CommResDefine_Strings_" + Business + ".h");
	if (res == 0)	return false;
	mydef->SetBusiness(this->Business);
	key.clear();
	key.resize(vDef.size());
	int num=0;
	if (this->isInsert){
		num = stoi(insertKey);
	}
	for (int i = 0; i < vDef.size(); i++){
		if (this->isInsert){
			key[i] = UTF8ToUnicode(to_string(num));
			num++;
			mydef->SetKey(key[i]);
		}
		else{
			key[i] = mydef->GetKey();
		}
		wstring def_name = vDef[i];
		wstring spC = spchinese[i];
		if (spC.size()>80){
			spC = spC.substr(0, 80) + L"...";
		}
		if (!mydef->SetDefine(bdef, UnicodeToUTF8(def_name), UnicodeToUTF8(spC)))	return false;
	}
	mydef->WriteDefine(path_Def + "//Define//CommResDefine_Strings_" + Business + ".h");
	bool nn = true;
	bool moomoo = true;
	//ͨ��д���λ���ж��Ƿ�д��ţţ��moomoo�İ��ļ�
	if (this->Towhere == "Both"){
		nn = true;
		moomoo = true;
	}
	else if (this->Towhere == "NN"){
		nn = true;
		moomoo = false;
	}
	else if (this->Towhere == "MooMoo"){
		nn = false;
		moomoo = true;
	}
	else if (this->Towhere == "nnDiffermoomoo"){
		nn = true;
		moomoo = true;
	}
	int nowcount = 0;
	int totalcount = 0;
	if (nn)	totalcount += 3;
	if (moomoo)	totalcount += 3;
	if (nn){
		
		//ֱ�����ÿ⺯��WritePrivateProfileString����д��ini�ļ�
		string spcPath = path_Lang + "//Debug//Languages//SimplifiedChinese//" + fName + ".ini";
		myini->ReadIni(spcPath);
		for (int i = 0; i < spchinese.size(); i++){
			myini->SetValue(key[i], spchinese[i]);
		}
		myini->WriteIni(spcPath);
		myini->releseIni();
		nowcount++;
		::SendMessage(m_hWnd, WM_DRAWPROG, (WPARAM)nowcount, (LPARAM)totalcount);

		string tdcPath = path_Lang + "//Debug//Languages//TraditionalChinese//" + fName + ".ini";
		myini->ReadIni(tdcPath);
		for (int i = 0; i < tdchinese.size(); i++){
			myini->SetValue(key[i], tdchinese[i]);
		}
		myini->WriteIni(tdcPath);
		myini->releseIni();
		nowcount++;
		::SendMessage(m_hWnd, WM_DRAWPROG, (WPARAM)nowcount, (LPARAM)totalcount);

		string eglPath = path_Lang + "//Debug//Languages//English//" + fName + ".ini";
		myini->ReadIni(eglPath);
		for (int i = 0; i < english.size(); i++){
			myini->SetValue(key[i], english[i]);
		}
		myini->WriteIni(eglPath);
		myini->releseIni();
		nowcount++;
		::SendMessage(m_hWnd, WM_DRAWPROG, (WPARAM)nowcount, (LPARAM)totalcount);
		
	}
	if (moomoo){
		string spcPathmm = path_Lang + "//MMDebug//Languages//SimplifiedChinese//" + fName + ".ini";
		myini->ReadIni(spcPathmm);
		for (int i = 0; i < spchinesemm.size(); i++){
			myini->SetValue(key[i], spchinesemm[i]);
		}
		myini->WriteIni(spcPathmm);
		myini->releseIni();
		nowcount++;
		::SendMessage(m_hWnd, WM_DRAWPROG, (WPARAM)nowcount, (LPARAM)totalcount);

		string tdcPathmm = path_Lang + "//MMDebug//Languages//TraditionalChinese//" + fName + ".ini";
		myini->ReadIni(tdcPathmm);
		for (int i = 0; i < tdchinesemm.size(); i++){
			myini->SetValue(key[i], tdchinesemm[i]);
		}
		myini->WriteIni(tdcPathmm);
		myini->releseIni();
		nowcount++;
		::SendMessage(m_hWnd, WM_DRAWPROG, (WPARAM)nowcount, (LPARAM)totalcount);

		string eglPathmm = path_Lang + "//MMDebug//Languages//English//" + fName + ".ini";
		myini->ReadIni(eglPathmm);
		for (int i = 0; i < englishmm.size(); i++){
			myini->SetValue(key[i], englishmm[i]);
		}
		myini->WriteIni(eglPathmm);
		myini->releseIni();
		nowcount++;
		::SendMessage(m_hWnd, WM_DRAWPROG, (WPARAM)nowcount, (LPARAM)totalcount);
	}
	return true;
}

bool AddAll::SetKey(wstring key, bool isInst){
	this->isInsert = isInst;
	if (this->isInsert){
		int k_int = stoi(UnicodeToUTF8(key));
		k_int++;
		this->insertKey = to_string(k_int);
	}
	
	return true;
}

bool AddAll::ReleaseAll(){
	isInsert = false;
	return true;
}

//ɾ��string�Ļس���\r
void DeleteRet(string &line){
	string::size_type position = line.find("\r");
	if (line.npos != position)
	{
		line = line.substr(0, position);
	}
	return;
}