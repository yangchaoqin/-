//stamp:092fc1068df18a51
/*<------------------------------------------------------------------------------------------------->*/
/*该文件由uiresbuilder生成，请不要手动修改*/
/*<------------------------------------------------------------------------------------------------->*/
#pragma once
#include <res.mgr/snamedvalue.h>
#define ROBJ_IN_CPP \
namespace SOUI \
{\
    const _R R;\
    const _UIRES UIRES;\
}
namespace SOUI
{
	class _UIRES{
		public:
		class _UIDEF{
			public:
			_UIDEF(){
				XML_INIT = _T("UIDEF:XML_INIT");
			}
			const TCHAR * XML_INIT;
		}UIDEF;
		class _LAYOUT{
			public:
			_LAYOUT(){
				XML_MAINWND = _T("LAYOUT:XML_MAINWND");
				XML_MODALDLG = _T("LAYOUT:XML_MODALDLG");
			}
			const TCHAR * XML_MAINWND;
			const TCHAR * XML_MODALDLG;
		}LAYOUT;
		class _values{
			public:
			_values(){
				string = _T("values:string");
				color = _T("values:color");
				skin = _T("values:skin");
			}
			const TCHAR * string;
			const TCHAR * color;
			const TCHAR * skin;
		}values;
		class _IMGX{
			public:
			_IMGX(){
				png_tab_left = _T("IMGX:png_tab_left");
			}
			const TCHAR * png_tab_left;
		}IMGX;
		class _IMG{
			public:
			_IMG(){
			}
		}IMG;
		class _ICON{
			public:
			_ICON(){
				ICON_LOGO = _T("ICON:ICON_LOGO");
			}
			const TCHAR * ICON_LOGO;
		}ICON;
	};
	const SNamedID::NAMEDVALUE namedXmlID[]={
		{L"_name_start",65535},
		{L"btn_close",65536},
		{L"btn_finish",65541},
		{L"btn_min",65538},
		{L"btn_restore",65537},
		{L"cbox_add_id",65542},
		{L"cbx_business",65539},
		{L"cbx_towhere",65540},
		{L"lv_input",65547},
		{L"lv_input_moomoo",65551},
		{L"prog_test",65554},
		{L"redit_def",65549},
		{L"redit_idBegin",65544},
		{L"redit_key",65543},
		{L"redit_language",65550},
		{L"redit_language_moomoo",65552},
		{L"tx_IdFeild",65553},
		{L"tx_lineno",65548},
		{L"tx_moomoo",65546},
		{L"tx_nn",65545}		};
	class _R{
	public:
		class _name{
		public:
		_name(){
			_name_start = namedXmlID[0].strName;
			btn_close = namedXmlID[1].strName;
			btn_finish = namedXmlID[2].strName;
			btn_min = namedXmlID[3].strName;
			btn_restore = namedXmlID[4].strName;
			cbox_add_id = namedXmlID[5].strName;
			cbx_business = namedXmlID[6].strName;
			cbx_towhere = namedXmlID[7].strName;
			lv_input = namedXmlID[8].strName;
			lv_input_moomoo = namedXmlID[9].strName;
			prog_test = namedXmlID[10].strName;
			redit_def = namedXmlID[11].strName;
			redit_idBegin = namedXmlID[12].strName;
			redit_key = namedXmlID[13].strName;
			redit_language = namedXmlID[14].strName;
			redit_language_moomoo = namedXmlID[15].strName;
			tx_IdFeild = namedXmlID[16].strName;
			tx_lineno = namedXmlID[17].strName;
			tx_moomoo = namedXmlID[18].strName;
			tx_nn = namedXmlID[19].strName;
		}
		 const wchar_t * _name_start;
		 const wchar_t * btn_close;
		 const wchar_t * btn_finish;
		 const wchar_t * btn_min;
		 const wchar_t * btn_restore;
		 const wchar_t * cbox_add_id;
		 const wchar_t * cbx_business;
		 const wchar_t * cbx_towhere;
		 const wchar_t * lv_input;
		 const wchar_t * lv_input_moomoo;
		 const wchar_t * prog_test;
		 const wchar_t * redit_def;
		 const wchar_t * redit_idBegin;
		 const wchar_t * redit_key;
		 const wchar_t * redit_language;
		 const wchar_t * redit_language_moomoo;
		 const wchar_t * tx_IdFeild;
		 const wchar_t * tx_lineno;
		 const wchar_t * tx_moomoo;
		 const wchar_t * tx_nn;
		}name;

		class _id{
		public:
		const static int _name_start	=	65535;
		const static int btn_close	=	65536;
		const static int btn_finish	=	65541;
		const static int btn_min	=	65538;
		const static int btn_restore	=	65537;
		const static int cbox_add_id	=	65542;
		const static int cbx_business	=	65539;
		const static int cbx_towhere	=	65540;
		const static int lv_input	=	65547;
		const static int lv_input_moomoo	=	65551;
		const static int prog_test	=	65554;
		const static int redit_def	=	65549;
		const static int redit_idBegin	=	65544;
		const static int redit_key	=	65543;
		const static int redit_language	=	65550;
		const static int redit_language_moomoo	=	65552;
		const static int tx_IdFeild	=	65553;
		const static int tx_lineno	=	65548;
		const static int tx_moomoo	=	65546;
		const static int tx_nn	=	65545;
		}id;

		class _string{
		public:
		const static int title	=	0;
		const static int ver	=	1;
		}string;

		class _color{
		public:
		const static int blue	=	0;
		const static int gray	=	1;
		const static int green	=	2;
		const static int red	=	3;
		const static int white	=	4;
		}color;

	};

#ifdef R_IN_CPP
	 extern const _R R;
	 extern const _UIRES UIRES;
#else
	 extern const __declspec(selectany) _R & R = _R();
	 extern const __declspec(selectany) _UIRES & UIRES = _UIRES();
#endif//R_IN_CPP
}
