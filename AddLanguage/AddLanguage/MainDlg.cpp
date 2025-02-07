// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MainDlg.h"	
#include <iostream>

using namespace std;

CMainDlg::CMainDlg() : SHostWnd(_T("LAYOUT:XML_MAINWND"))
{
	m_bLayoutInited = FALSE;
	def.resize(20);
	language.resize(20);
	languagemoomoo.resize(20);
}

CMainDlg::~CMainDlg()
{
	
}

int CMainDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetMsgHandled(FALSE);
	return 0;
}

BOOL CMainDlg::OnInitDialog(HWND hWnd, LPARAM lParam)
{
	m_bLayoutInited = TRUE;
	SListView *pLstViewFix = FindChildByName2<SListView>("lv_input");
	if (pLstViewFix)
	{
		ILvAdapter *pAdapter = new CLVAdapterFix;
		pLstViewFix->SetAdapter(pAdapter);
		pAdapter->Release();
	}
	SListView *pLstViewFixmoomoo = FindChildByName2<SListView>("lv_input_moomoo");
	if (pLstViewFixmoomoo)
	{
		ILvAdapter *pAdapter = new CLVAdapterFixMooMoo;
		pLstViewFixmoomoo->SetAdapter(pAdapter);
		pAdapter->Release();
	}
	SComboBox * pCbx_business = FindChildByName2<SComboBox>(L"cbx_business");
	if (pCbx_business)
	{
		OnCbxBusiness(pCbx_business);
		pCbx_business->GetEventSet()->subscribeEvent(SOUI::EVT_CB_SELCHANGE, Subscriber(&CMainDlg::OnCbxBusinessChange, this));
	}
	SComboBox * pCbx_towhere = FindChildByName2<SComboBox>(L"cbx_towhere");
	if (pCbx_towhere)
	{
		OnCbxTowhere(pCbx_towhere);
		pCbx_towhere->GetEventSet()->subscribeEvent(SOUI::EVT_CB_SELCHANGE, Subscriber(&CMainDlg::OnCbxTowhereChange, this));
	}
	OnCheckChecked();
	return 0;
}
//TODO:消息映射
void CMainDlg::OnClose()
{
	CSimpleWnd::DestroyWindow();
}


void CMainDlg::OnRestore()
{
	SendMessage(WM_SYSCOMMAND, SC_RESTORE);
}
void CMainDlg::OnMinimize()
{
	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE);
}

void CMainDlg::OnSize(UINT nType, CSize size)
{
	SetMsgHandled(FALSE);
	if (!m_bLayoutInited) return;
	
	SWindow *pBtnMax = FindChildByName(L"btn_max");
	SWindow *pBtnRestore = FindChildByName(L"btn_restore");
	if(!pBtnMax || !pBtnRestore) return;
	
	if (nType == SIZE_MAXIMIZED)
	{
		pBtnRestore->SetVisible(TRUE);
		pBtnMax->SetVisible(FALSE);
	}
	else if (nType == SIZE_RESTORED)
	{
		pBtnRestore->SetVisible(FALSE);
		pBtnMax->SetVisible(TRUE);
	}
}

void CMainDlg::OnButtonClick()
{
//	CmodalDlg mDlg;
//	mDlg.DoModal();
//	mDlg.OnClose();
	//根据选项判断是否牛牛和moomoo有差异文案，选择载入不同的listview数据
	if (towhere == "nnDiffermoomoo"){
		SListView *pLstViewFixmm = FindChildByName2<SListView>("lv_input_moomoo");
		if (pLstViewFixmm){
			CLVAdapterFixMooMoo *pAdapter = (CLVAdapterFixMooMoo*)pLstViewFixmm->GetAdapter();
			pAdapter->GetRicheditText(def, language, languagemoomoo);
		}
	}
	else{
		SListView *pLstViewFix = FindChildByName2<SListView>("lv_input");
		if (pLstViewFix){
			CLVAdapterFix *pAdapter = (CLVAdapterFix*)pLstViewFix->GetAdapter();		
			pAdapter->GetRicheditText(def, language);		
			for (int i = 0; i < language.size(); i++){
				languagemoomoo[i] = language[i];
			}
		}
	}
	string tw = this->towhere;
	string bn = this->business;

	//用3个list容器保留有意义的信息，去掉空vector容器的信息
	list<wstring> listDef;
	list<wstring> listLang;
	list<wstring> listLangmm;
	listDef.clear();
	listLang.clear();
	listLangmm.clear();
	bool ifWrite = true;
	int nulltimes = 0;
	for (int i = 0; i < def.size(); i++){
		if (!def[i].empty() && !language[i].empty()&&!languagemoomoo[i].empty()){
			listDef.push_back(def[i]);
			wistringstream isnn(language[i]);
			int nntimes = 0;
			wstring line = L"";
			while (getline(isnn, line))	nntimes++;
			wistringstream ismoomoo(languagemoomoo[i]);
			int moomootimes = 0;
			wstring linemm = L"";
			while (getline(ismoomoo, linemm))	moomootimes++;
			//判断文案的行数是否正确
			if (nntimes != 3||moomootimes!=3){
				ifWrite = false;
				SMessageBox(NULL, SStringT().Format(_T("第 %d 行设置有问题"), i + 1), _T("警告"), MB_OK);
				listDef.clear();
				listLang.clear();
				listLangmm.clear();
			}
			else
			{
				listLang.push_back(language[i]);
				listLangmm.push_back(languagemoomoo[i]);
			}
			
		}
		else if (def[i].empty() && language[i].empty()&&languagemoomoo[i].empty()){
			nulltimes++;
		}
		else{
			ifWrite = false;
			SMessageBox(NULL, SStringT().Format(_T("第 %d 行设置有问题"), i + 1), _T("警告"), MB_OK);
			listDef.clear();
			listLang.clear();
			listLangmm.clear();
		}
	}
	//判断是否20行信息都为空
	if (nulltimes >= 20){
		ifWrite = false;
		SMessageBox(NULL, SStringT().Format(_T("请输入文案！！！")), _T("警告"), MB_OK);
	}	
	//判断输入无误后写入信息
	if (ifWrite){
		wstring key;
		SRichEdit *pEdit = FindChildByName2<SRichEdit>("redit_key");
		if (pEdit){
			key = pEdit->GetWindowTextW();
		}
		bool ischeck = false;
		SCheckBox *pCheck = FindChildByName2<SCheckBox>("cbox_add_id");
		if (pCheck){
			ischeck = pCheck->IsChecked();
		}
		std::thread t(WriteDate, key, ischeck, tw, bn, listDef, listLang, listLangmm, m_hWnd);
		t.detach();
		SComboBox * pCbx_business = FindChildByName2<SComboBox>(L"cbx_business");
		if (pCbx_business)
		{
			OnCbxBusiness(pCbx_business);
		}
		
		
	}
	return;
}

bool CMainDlg::OnCbxBusinessChange(EventCBSelChange *pEvt){
	SComboBox *pCbx = sobj_cast<SComboBox>(pEvt->sender);
	OnCbxBusiness(pCbx);
	return true;
}

bool CMainDlg::OnCbxBusiness(SComboBox *pCbx){
	
	cbx_business = pCbx->GetCurSel();
	if (cbx_business == 0)
	{
		business = "Quote";
		SStatic* txIdFeild = FindChildByName2<SStatic>("tx_IdFeild");
		txIdFeild->SetWindowTextW(_T("行情ID范围为200000-399999"));
	}
	else if (cbx_business == 1){
		business = "Trade";
		SStatic* txIdFeild = FindChildByName2<SStatic>("tx_IdFeild");
		txIdFeild->SetWindowTextW(_T("交易ID范围为100000-199999"));
	}
	MyDefine *mydef = new MyDefine;
	mydef->ReadDefine("..//..//FTNN//FTUIKit//FTCommonRes//Define//CommResDefine_Strings_" + business + ".h");
	mydef->SetBusiness(business);
	key = mydef->GetKey();
	delete mydef;
	int new_key = stoi(UnicodeToUTF8(key));
	new_key--;
	SRichEdit *pEdit = FindChildByName2<SRichEdit>("redit_idBegin");
	if (pEdit){
		wstring wstr_new_id = L"当前已使用最大的ID号为：" + UTF8ToUnicode(to_string(new_key));
		pEdit->SetWindowTextW(wstr_new_id.c_str());
	}
	return true;
}

bool CMainDlg::OnCbxTowhereChange(EventCBSelChange *pEvt){
	SComboBox *pCbx = sobj_cast<SComboBox>(pEvt->sender);
	OnCbxTowhere(pCbx);
	return true;
}

bool CMainDlg::OnCbxTowhere(SComboBox *pCbx){
	cbx_towhere = pCbx->GetCurSel();
	//依据选项来选择显示对应的listview
	if (cbx_towhere == 3){
		towhere = "nnDiffermoomoo";
		SStatic *pTx = FindChildByName2<SStatic>("tx_moomoo");
		if (pTx){
			pTx->SetWindowTextW(SStringT().Format(_T("moomoo的差异文案（简繁英）")));
		}
		//调整窗口大小
		::MoveWindow(m_hWnd, 450, 70, 1250, 900, TRUE);
		SListView *pLstViewFix = FindChildByName2<SListView>("lv_input");
		if (pLstViewFix){
			pLstViewFix->SetVisible(false);
		}
		SListView *pLstViewFixmoomoo = FindChildByName2<SListView>("lv_input_moomoo");
		if (pLstViewFixmoomoo){
			pLstViewFixmoomoo->SetVisible(true);
		}

	}
	else{
		SStatic *pTx = FindChildByName2<SStatic>("tx_moomoo");
		if (pTx){
			pTx->SetWindowTextW(SStringT().Format(_T(" ")));
		}
		::MoveWindow(m_hWnd, 535, 70, 850, 900, TRUE);
		SListView *pLstViewFix = FindChildByName2<SListView>("lv_input");
		if (pLstViewFix){
			pLstViewFix->SetVisible(true);
		}
		SListView *pLstViewFixmoomoo = FindChildByName2<SListView>("lv_input_moomoo");
		if (pLstViewFixmoomoo){
			pLstViewFixmoomoo->SetVisible(false);
		}
		if (cbx_towhere == 0){
			towhere = "Both";
		}
		else if (cbx_towhere == 1){
			towhere = "NN";
		}
		else if (cbx_towhere == 2){
			towhere = "MooMoo";
		}
	}
	return true;
}


bool CMainDlg::OnCheckChecked(){
	SCheckBox *pCheck = FindChildByName2<SCheckBox>("cbox_add_id");
	bool checked = pCheck->IsChecked();
	if (checked){
		SRichEdit *pedit = FindChildByName2<SRichEdit>("redit_key");
		if (pedit){
			pedit->SetReadOnly(FALSE);
			pedit->SetAttribute(L"enable", L"1", TRUE);

		}
	}
	else{
		SRichEdit *pedit = FindChildByName2<SRichEdit>("redit_key");
		if (pedit){
			pedit->SetWindowTextW(L"");
			pedit->SetReadOnly(TRUE);
			pedit->SetAttribute(L"enable", L"0", TRUE);
		}
	}
	return true;
}

int WriteDate(wstring key, bool ischeck, string tw, string bn, list<wstring> Def, list<wstring> Lang, list<wstring> Langmm, HWND m_hWnd){
	::SendMessage(m_hWnd, WM_ISDRAW, 0, 0);
	AddAll *addAll = new AddAll;
	if (ischeck){
		if (key == L"")	{
			SMessageBox(NULL, SStringT().Format(_T("勾选后请输入ID起点！！！")), _T("写入失败"), MB_OK);
			return 0;
		}
		
	}
	addAll->SetKey(key, ischeck);
	addAll->Init(Def,Lang,Langmm,bn,tw);
	if (addAll->WriteAll("..//..//FTNN//FTUIKit//FTCommonRes", "..//..//FTNN//Bin",m_hWnd)){
		SMessageBox(NULL, SStringT().Format(_T("写入成功！！！")), _T("写入成功"), MB_OK);
	}
	else{
		SMessageBox(NULL, SStringT().Format(_T("写入失败！！！")), _T("错误"), MB_OK);
	}
	addAll->ReleaseAll();
	::SendMessage(m_hWnd, WM_ISDRAW, 1, 0);
	return 0;
}

LRESULT CMainDlg::OnDrawProg(UINT uMsg, WPARAM wp, LPARAM lp, BOOL & bHandled)
{
	SProgress *pProg = SOUI::SWindow::FindChildByName2<SProgress>("prog_test");
	int nowcount = (int)wp;
	int totalcount = (int)lp;
	pProg->SetValue(100 * nowcount / totalcount);
	return 0;
}

LRESULT CMainDlg::IsDraw(UINT uMsg, WPARAM wp, LPARAM lp, BOOL & bHandled)
{
	SButton *pbtn = FindChildByName2<SButton>("btn_finish");
	SProgress *pProg = SOUI::SWindow::FindChildByName2<SProgress>("prog_test");
	if (wp == 0){
		if (pbtn){
			pbtn->SetAttribute(L"enable", L"0", TRUE);
		}
		pProg->SetValue(0);
	}
	else if (wp == 1){
		if (pbtn){
			pbtn->EnableWindow(TRUE);
		}
	}
	return 0;
}
