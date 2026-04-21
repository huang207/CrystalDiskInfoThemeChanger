#include "main.h"

static void InitInstance() {
	TCHAR* ptrEnd;
	//// Init m_Ini
	//TCHAR ini[MAX_PATH];

	//::GetModuleFileName(NULL, ini, MAX_PATH);
	//if ((ptrEnd = _tcsrchr(ini, '\\')) != NULL)
	//{
	//	*ptrEnd = '\0';
	//	m_Ini = ini;
	//}
	//m_Ini += _T("\\DiskInfoTC.ini");

	// Init m_ThemeDir
	TCHAR tmp[MAX_PATH] = {};

	GetModuleFileName(NULL, tmp, MAX_PATH);
	if ((ptrEnd = _tcsrchr(tmp, '\\')) != NULL) { *ptrEnd = '\0'; }
#ifdef _DEBUG
	_tcscpy_s(tmp, _T("C:\\Program Files\\CrystalDiskInfo\\"));
#endif
	m_ThemeDir.Format(_T("%s\\%s"), tmp, THEME_DIR);
}

static BOOL CheckThemeEdition(CString name)
{
	switch (m_ThemeEdition)
	{
	case SUISHO_AOI:
		if (name.Find(L"Aoi") == 0) { return TRUE; }
		break;
	case A1DATA_ERIKA:
		if (name.Find(L"A1DataErika") == 0) { return TRUE; }
		break;
	case A1DATA:
		if (name.Find(L"A1Data") == 0) { return TRUE; }
		break;
	case MSI_MEI:
		if (name.Find(L"MSIMei") == 0) { return TRUE; }
		break;
	case KUREI_KEI:
		if (name.Find(L"KureiKei") == 0) { return TRUE; }
		break;
	case SUISHO_SHIZUKU:
		if (name.Find(L"Shizuku") == 0) {return TRUE; }
		break;
	default:
		if (name.Find(L"Shizuku") != 0 && name.Find(L"KureiKei") != 0 && name.Find(L"Aoi") != 0 && name.Find(L"MSIMei") != 0 && name.Find(L"A1DataErika") != 0 && name.Find(L"A1Data") != 0 && name.Find(L".") != 0) { return TRUE; }
		break;
	}

	return FALSE;
}

static void SetThemeEdition(CString name)
{
	if (name.Find(L"Aoi Edition") >= 0) { m_ThemeEdition = SUISHO_AOI; }
	else if (name.Find(L"A1Data Erika Edition") >= 0) { m_ThemeEdition = A1DATA_ERIKA; }
	else if (name.Find(L"A1Data Edition") >= 0) { m_ThemeEdition = A1DATA; }
	else if (name.Find(L"MSI Mei Mihoshi Edition") >= 0) { m_ThemeEdition = MSI_MEI; }
	else if (name.Find(L"Kurei Kei Edition") >= 0) { m_ThemeEdition = KUREI_KEI; }
	else if (name.Find(L"Shizuku Edition") >= 0) { m_ThemeEdition = SUISHO_SHIZUKU; }
	else { m_ThemeEdition = SUISHO_SHIZUKU; }
}

static void InitMenu()
{
	UINT newItemID = 0;
	WIN32_FIND_DATA findData;

	HANDLE hFind;
	CString themePath;
	int i = 0;

	srand((unsigned int)std::time(NULL));

	themePath.Format(_T("%s\\*.*"), (LPCTSTR)m_ThemeDir);

	// Add Random as first choice.
	i++;
	m_MenuArrayTheme.push_back(m_RandomThemeLabel);

	hFind = ::FindFirstFile(themePath, &findData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		while (::FindNextFile(hFind, &findData) && i <= 0xFF)
		{
			if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				CString name = findData.cFileName;
				if (CheckThemeEdition(name))
				{
					// Add Theme
					newItemID = WM_THEME_ID + i;
					i++;
					m_MenuArrayTheme.push_back(findData.cFileName);
					if (m_CurrentTheme.Compare(findData.cFileName) == 0)
					{
						m_CurrentThemeID = newItemID;
#ifndef _DEBUG
						break;
#endif // !DEBUG
					}
				}
			}
		}
	}
	FindClose(hFind);
}

static HWND GetWindow(LPCWSTR title = NULL)
{
	if (title != NULL and title[0] != L'\0')
	{
		return FindWindow(NULL, title);

	}
	else
	{
		HWND hwnd = nullptr;
		EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL {
			CString windowTitle, titlePrefix;
			GetWindowText(hwnd, windowTitle.GetBuffer(MAX_PATH), MAX_PATH);
			windowTitle.ReleaseBuffer();
			titlePrefix.Format(_T(" %s"), PRODUCT_NAME);
			if (windowTitle.Find(titlePrefix) == 0) {
				*(HWND*)lParam = hwnd;
				m_WindowTitle = windowTitle;
				return FALSE;
			}
			return TRUE;
			}, (LPARAM)&hwnd);
		return hwnd;
	}
}

int wmain(int argc, wchar_t* argv[])
{
	m_CurrentThemeID = WM_THEME_ID;
	m_RandomThemeLabel = L"Random";
//#ifdef _DEBUG
//	m_ThemeEdition = SUISHO_AOI;
//	m_CurrentTheme = L"AoiDark~TenmuShinryuusai";
//	m_WindowTitle = L" CrystalDiskInfo 9.6.2 Aoi Edition x64";
//
//	if (argc < 2) {
//		return 1;
//	}
//	if (argc > 1) {
//		m_CurrentTheme = argv[1];
//	}
//#endif
	switch (argc)
	{
	case 1:
		return 1;
	case 2:
		// Use with only theme. Get window by enumeration.
		m_CurrentTheme = argv[1];
		break;
	case 3:
		// Use with specified window title.
		m_WindowTitle = argv[1];
		m_CurrentTheme = argv[2];
		break;
	case 4:
	default:
		// Use with PRODUCT_VERSION and PRODUCT_EDITION.
		m_WindowTitle.Format(_T(" %s %s %s"), PRODUCT_NAME, argv[1], argv[2]);
		m_CurrentTheme = argv[3];
		break;
	}

	HWND hwnd = GetWindow(m_WindowTitle);
	SetThemeEdition(m_WindowTitle);

	InitInstance();
	InitMenu();

#ifdef _DEBUG
	// Debug with theme list.
	for (size_t i = 0; i < m_MenuArrayTheme.size(); i++) {
		std::wcout << L"[" << i << L"] " << (LPCTSTR)m_MenuArrayTheme[i] << std::endl;
	}

#endif // DEBUG

	if (m_CurrentThemeID == WM_THEME_ID and m_CurrentTheme.Compare(m_RandomThemeLabel) != 0) {
		std::wcout << L"Theme not match current edition." << std::endl;
		return 1;
	}

	if (hwnd != NULL)
	{
		// Post Message to window that found.
		//WPARAM wParam = m_CurrentThemeID;
		//LPARAM lParam = 0;
		PostMessage(hwnd, WM_COMMAND, m_CurrentThemeID, 0);
	}
	else
	{
		std::wcout << L"Window not found£º" << m_WindowTitle << std::endl;
		return 1;
	}

	return 0;
}