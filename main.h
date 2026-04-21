#pragma once  

#include <windows.h>  
#include <iostream>  
#include <tchar.h>  
#include <atlstr.h>
#include <vector>

#define WM_THEME_ID (WM_APP + 0x0C00)  

#define THEME_DIR					_T("CdiResource\\themes\\")  

#define PRODUCT_NAME			_T("CrystalDiskInfo")

enum {
	SUISHO_AOI = 1,
	A1DATA_ERIKA,
	A1DATA,
	MSI_MEI,
	KUREI_KEI,
	SUISHO_SHIZUKU
} m_ThemeEdition;

CString m_Ini;

CString m_WindowTitle;


// Theme for SubClass
int;
CString m_ThemeDir;
CString m_CurrentTheme;
CString m_RandomThemeLabel;
UINT m_CurrentThemeID;

// Theme  
CString m_ThemeKeyName;
std::vector<CString> m_MenuArrayTheme;
