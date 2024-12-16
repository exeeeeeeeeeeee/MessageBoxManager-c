/*
Usage:

#include <Windows.h>
#include "MessageBoxManager.h"

int main() {
	MessageBoxManager m;

	m.Yes = L"Yes?"; <= Change the text of the Yes button
	m.No = L"No?"; <= Change the text of the No button

	***MUST 32x32***
	m.hIcon = (HICON)LoadImage(NULL, L"Youricon.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE); <= Change message box icon

	m.Register(); <= Enable hooking

	MessageBoxW(0, L"Custom messagebox test!", L"in c++", MB_ICONWARNING, | MB_YESNO);

	m.Unregister(); <= Disable hooking
}
*/

#include <Windows.h>
#include <string>
#include "MessageBoxManager.h"

const int MessageBoxManager::MBOK = 1;
const int MessageBoxManager::MBCancel = 2;
const int MessageBoxManager::MBAbort = 3;
const int MessageBoxManager::MBRetry = 4;
const int MessageBoxManager::MBIgnore = 5;
const int MessageBoxManager::MBYes = 6;
const int MessageBoxManager::MBNo = 7;
const int MessageBoxManager::MBIcon = 20;

// OK text
std::wstring MessageBoxManager::OK = L"&OK";
// Cancel text
std::wstring MessageBoxManager::Cancel = L"&Cancel";
// Abort text
std::wstring MessageBoxManager::Abort = L"&Abort";
// Retry text
std::wstring MessageBoxManager::Retry = L"&Retry";
// Ignore text
std::wstring MessageBoxManager::Ignore = L"&Ignore";
// Yes text
std::wstring MessageBoxManager::Yes = L"&Yes";
// No text
std::wstring MessageBoxManager::No = L"&No";

// Icon handle
// MUST 32x32
HICON MessageBoxManager::hIcon = NULL;

HHOOK MessageBoxManager::hHook;
MessageBoxManager::HookProc MessageBoxManager::hookProc;
MessageBoxManager::EnumChildProc MessageBoxManager::enumProc;

int MessageBoxManager::nButton;

MessageBoxManager::MessageBoxManager() {
	hookProc = &MessageBoxHookProc;
	enumProc = &MessageBoxEnumProc;
	hHook = NULL;
}

LRESULT CALLBACK MessageBoxManager::MessageBoxHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode < 0) {
		return CallNextHookEx(hHook, nCode, wParam, lParam);
	}

	CWPRETSTRUCT msg;
	memcpy(&msg, (void*)lParam, sizeof(CWPRETSTRUCT));
	HHOOK hook = hHook;

	if (msg.message == WM_INITDIALOG) {
		int nLength = GetWindowTextLengthW(msg.hwnd);

		wchar_t className[256];
		GetClassNameW(msg.hwnd, className, sizeof(className) / sizeof(wchar_t));
		if (wcscmp(className, L"#32770") == 0) {
			nButton = 0;

			EnumChildWindows(msg.hwnd, enumProc, NULL);
			if (nButton == 1) {
				HWND hButton = GetDlgItem(msg.hwnd, MBCancel);
				if (hButton != NULL) {
					SetWindowTextW(hButton, OK.c_str());
				}
			}

			if (hIcon != NULL) {
				HWND hwndIcon = GetDlgItem(msg.hwnd, MBIcon);
				if (hwndIcon != NULL) {
					SendMessageW(hwndIcon, STM_SETICON, (WPARAM)hIcon, NULL);
				}
			}
		}
	}

	return CallNextHookEx(hook, nCode, wParam, lParam);
}

BOOL CALLBACK MessageBoxManager::MessageBoxEnumProc(HWND hWnd, LPARAM lParam) {
	wchar_t className[256];
	GetClassNameW(hWnd, className, sizeof(className) / sizeof(wchar_t));
	if (wcscmp(className, L"Button") == 0) {
		int ctlId = GetDlgCtrlID(hWnd);
		switch (ctlId)
		{
			case MBOK:
				SetWindowText(hWnd, OK.c_str());
				break;

			case MBCancel:
				SetWindowText(hWnd, Cancel.c_str());
				break;

			case MBAbort:
				SetWindowText(hWnd, Abort.c_str());
				break;

			case MBRetry:
				SetWindowText(hWnd, Retry.c_str());
				break;

			case MBIgnore:
				SetWindowText(hWnd, Ignore.c_str());
				break;

			case MBYes:
				SetWindowText(hWnd, Yes.c_str());
				break;

			case MBNo:
				SetWindowText(hWnd, No.c_str());
				break;
		}
		nButton++;
	}
	return TRUE;
}

void MessageBoxManager::Register() {
	if (hHook != NULL) {
		MessageBoxW(0, L"One hook per thread allowed.", L"Error", MB_ICONWARNING);
	}

	hHook = SetWindowsHookExW(WH_CALLWNDPROCRET, (HOOKPROC)hookProc, NULL, GetCurrentThreadId());
}

void MessageBoxManager::Unregister() {
	if (hHook != NULL) {
		UnhookWindowsHookEx((HHOOK)hHook);
		hHook = NULL;
	}
}
