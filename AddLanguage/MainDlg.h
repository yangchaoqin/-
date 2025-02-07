// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////
#pragma once
#include <helper/SAdapterBase.h>
#include <list>
#include <vector>
#include <thread>
#include "AddAll.h"
#include "modalDlg.h"
#include <cstring>

#define WM_DRAWPROG (WM_USER+100)
#define WM_ISDRAW (WM_USER+200)

using namespace std;
class CMainDlg : public SHostWnd
{
public:
	CMainDlg();
	~CMainDlg();

	void OnClose();
	void OnRestore();
	void OnMinimize();
	void OnSize(UINT nType, CSize size);
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);
	void OnButtonClick();
	bool OnCbxBusinessChange(EventCBSelChange *pEvt);
	bool OnCbxBusiness(SComboBox *pCbx);
	bool OnCbxTowhereChange(EventCBSelChange *pEvt);
	bool OnCbxTowhere(SComboBox *pCbx);
	bool OnCheckChecked();	
	LRESULT OnDrawProg(UINT uMsg, WPARAM wp, LPARAM lp, BOOL & bHandled);
	LRESULT IsDraw(UINT uMsg, WPARAM wp, LPARAM lp, BOOL & bHandled);

protected:
	//soui消息
	EVENT_MAP_BEGIN()
		EVENT_NAME_COMMAND(L"btn_close", OnClose)
		EVENT_NAME_COMMAND(L"btn_min", OnMinimize)
		EVENT_NAME_COMMAND(L"btn_restore", OnRestore)
		EVENT_NAME_COMMAND(L"btn_finish",OnButtonClick)
		EVENT_NAME_COMMAND(L"cbox_add_id", OnCheckChecked)
	EVENT_MAP_END()
		
	//HostWnd真实窗口消息处理
	BEGIN_MSG_MAP_EX(CMainDlg)
		MESSAGE_HANDLER(WM_DRAWPROG, OnDrawProg)
		MESSAGE_HANDLER(WM_ISDRAW, IsDraw)
		MSG_WM_CREATE(OnCreate)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_CLOSE(OnClose)
		MSG_WM_SIZE(OnSize)
		CHAIN_MSG_MAP(SHostWnd)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()
private:
	BOOL			m_bLayoutInited;	
	vector<wstring> def;
	vector<wstring> language;
	vector<wstring> languagemoomoo;
	
	int cbx_business;
	
	int cbx_towhere;
	wstring key;
	string towhere;
	string business;
	
	
	
	
};



int WriteDate(wstring key, bool ischeck, string tw, string bn, list<wstring> Def, list<wstring> Lang, list<wstring> Langmm, HWND m_hWnd);

class CLVAdapterFix : public SAdapterBase
{
private:
	vector<wstring> edit_def;
	vector<wstring> edit_language;
protected:
	
public:
	CLVAdapterFix()
	{
		edit_def.resize(getCount());
		edit_language.resize(getCount());
	}

	~CLVAdapterFix()
	{

	}

	virtual int getCount()
	{
		return 20;
	}

	virtual void getView(int position, SWindow * pItem, pugi::xml_node xmlTemplate)
	{
		if (pItem->GetChildrenCount() == 0){
			pItem->InitFromXml(xmlTemplate);
		}
		SStatic *pTx = pItem->FindChildByName2<SStatic>(L"tx_lineno");
		if (pTx){
			pTx->SetWindowTextW(SStringT().Format(_T("#%d"),position+1));
		}
		SRichEdit *pEdit_def = pItem->FindChildByName2<SRichEdit>(L"redit_def");
		if (pEdit_def)
		{
			pEdit_def->SetWindowTextW( edit_def[position].c_str());
			pEdit_def->GetRoot()->SetUserData(position);
			pEdit_def->GetEventSet()->subscribeEvent(SOUI::EventRENotify::EventID, Subscriber(&CLVAdapterFix::OnReditDefineChange, this));
		}
		
		SRichEdit *pEdit_language = pItem->FindChildByName2<SRichEdit>(L"redit_language");
		if (pEdit_language)
		{
			pEdit_language->SetWindowTextW(edit_language[position].c_str());
			pEdit_language->GetRoot()->SetUserData(position);
			pEdit_language->GetEventSet()->subscribeEvent(SOUI::EventRENotify::EventID, Subscriber(&CLVAdapterFix::OnReditLanguageChange, this));
		}

		
	}

	

	bool OnReditDefineChange(EventCmd *pEvt){
		SRichEdit* pEdit_def = sobj_cast<SRichEdit>(pEvt->sender);
		int iItem = pEdit_def->GetRoot()->GetUserData();
		wstring str_def = pEdit_def->GetWindowTextW();
		if (edit_def[iItem] != str_def){
			edit_def[iItem] = str_def;
			return true;
		}
			
		else return true;
	}

	bool OnReditLanguageChange(EventCmd *pEvt){
		SRichEdit* pEdit_lang = sobj_cast<SRichEdit>(pEvt->sender);
		int iItem = pEdit_lang->GetRoot()->GetUserData();
		wstring str_lang = pEdit_lang->GetWindowTextW();
		if (edit_language[iItem] != str_lang){
			edit_language[iItem] = str_lang;
			return true;
		}
			
		else return true;
	}
	void GetRicheditText(vector<wstring> &def, vector<wstring> &language){
		for (int i = 0; i < getCount(); i++){
			def[i]=edit_def[i];
			language[i]=edit_language[i];
		}
		return;
	}

};
class CLVAdapterFixMooMoo : public SAdapterBase
	{
	private:
		vector<wstring> edit_def;
		vector<wstring> edit_language;
		vector<wstring> edit_language_moomoo;
	protected:

	public:
		CLVAdapterFixMooMoo()
		{
			edit_def.resize(getCount());
			edit_language.resize(getCount());
			edit_language_moomoo.resize(getCount());
		}

		~CLVAdapterFixMooMoo()
		{

		}

		virtual int getCount()
		{
			return 20;
		}

		virtual void getView(int position, SWindow * pItem, pugi::xml_node xmlTemplate)
		{
			if (pItem->GetChildrenCount() == 0){
				pItem->InitFromXml(xmlTemplate);
			}
			SStatic *pTx = pItem->FindChildByName2<SStatic>(L"tx_lineno");
			if (pTx){
				pTx->SetWindowTextW(SStringT().Format(_T("#%d"), position + 1));
			}
			SRichEdit *pEdit_def = pItem->FindChildByName2<SRichEdit>(L"redit_def");
			if (pEdit_def)
			{
				pEdit_def->SetWindowTextW(edit_def[position].c_str());
				pEdit_def->GetRoot()->SetUserData(position);
				pEdit_def->GetEventSet()->subscribeEvent(SOUI::EventRENotify::EventID, Subscriber(&CLVAdapterFixMooMoo::OnReditDefineChange, this));
			}

			SRichEdit *pEdit_language = pItem->FindChildByName2<SRichEdit>(L"redit_language");
			if (pEdit_language)
			{
				pEdit_language->SetWindowTextW(edit_language[position].c_str());
				pEdit_language->GetRoot()->SetUserData(position);
				pEdit_language->GetEventSet()->subscribeEvent(SOUI::EventRENotify::EventID, Subscriber(&CLVAdapterFixMooMoo::OnReditLanguageChange, this));
			}
			SRichEdit *pEdit_languagemoomoo = pItem->FindChildByName2<SRichEdit>(L"redit_language_moomoo");
			if (pEdit_languagemoomoo)
			{
				pEdit_languagemoomoo->SetWindowTextW(edit_language_moomoo[position].c_str());
				pEdit_languagemoomoo->GetRoot()->SetUserData(position);
				pEdit_languagemoomoo->GetEventSet()->subscribeEvent(SOUI::EventRENotify::EventID, Subscriber(&CLVAdapterFixMooMoo::OnReditLanguagemoomooChange, this));
			}


		}
		bool OnReditDefineChange(EventCmd *pEvt){
			SRichEdit* pEdit_def = sobj_cast<SRichEdit>(pEvt->sender);
			int iItem = pEdit_def->GetRoot()->GetUserData();
			wstring str_def = pEdit_def->GetWindowTextW();
			if (edit_def[iItem] != str_def){
				edit_def[iItem] = str_def;
				return true;
			}

			else return true;
		}

		bool OnReditLanguageChange(EventCmd *pEvt){
			SRichEdit* pEdit_lang = sobj_cast<SRichEdit>(pEvt->sender);
			int iItem = pEdit_lang->GetRoot()->GetUserData();
			wstring str_lang = pEdit_lang->GetWindowTextW();
			if (edit_language[iItem] != str_lang){
				edit_language[iItem] = str_lang;
				return true;
			}

			else return true;
		}
		bool OnReditLanguagemoomooChange(EventCmd *pEvt){
			SRichEdit* pEdit_lang = sobj_cast<SRichEdit>(pEvt->sender);
			int iItem = pEdit_lang->GetRoot()->GetUserData();
			wstring str_langmoomoo = pEdit_lang->GetWindowTextW();
			if (edit_language_moomoo[iItem] != str_langmoomoo){
				edit_language_moomoo[iItem] = str_langmoomoo;
				return true;
			}

			else return true;
		}
		void GetRicheditText(vector<wstring> &def, vector<wstring> &language,vector<wstring>&languagemoomoo){
			for (int i = 0; i < getCount(); i++){
				def[i] = edit_def[i];
				language[i] = edit_language[i];
				languagemoomoo[i] = edit_language_moomoo[i];
			}
			return;
		}

};