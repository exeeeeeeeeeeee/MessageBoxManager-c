#pragma once

#include <Windows.h>
#include <string>

class MessageBoxManager {
private:
    typedef LRESULT(CALLBACK* HookProc)(int nCode, WPARAM wParam, LPARAM lParam);
    typedef BOOL(CALLBACK* EnumChildProc)(HWND hWnd, LPARAM lParam);

    static const int MBOK;
    static const int MBCancel;
    static const int MBAbort;
    static const int MBRetry;
    static const int MBIgnore;
    static const int MBYes;
    static const int MBNo;

    static const int MBIcon;

    static HHOOK hHook;
    static HookProc hookProc;
    static EnumChildProc enumProc;
    static int nButton;

    static LRESULT CALLBACK MessageBoxHookProc(int nCode, WPARAM wParam, LPARAM lParam);
    static BOOL CALLBACK MessageBoxEnumProc(HWND hWnd, LPARAM lParam);

public:
    static std::wstring OK;
    static std::wstring Cancel;
    static std::wstring Abort;
    static std::wstring Retry;
    static std::wstring Ignore;
    static std::wstring Yes;
    static std::wstring No;

    static HICON hIcon;

    MessageBoxManager();

    static void Register();
    static void Unregister();
};
