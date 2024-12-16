# MessageBoxManager-c
C++ code that allows you to change the button name and icon of the message box.

![running-image](https://github.com/user-attachments/assets/06228139-ebd5-4bae-a68a-3222861e46eb)
## Features
**Customizable Button Text**  
The following button texts can be customized using the `MessageBoxManager` properties:
-   `m.Yes` – Text for the **Yes** button.
-   `m.No` – Text for the **No** button.
-   `m.Abort` – Text for the **Abort** button.
-   `m.Retry` – Text for the **Retry** button.
-   `m.Ignore` – Text for the **Ignore** button.
-   `m.OK` – Text for the **OK** button.
-   `m.Cancel` – Text for the **Cancel** button.
```c
m.Yes = L"Yes"; <= Change the text of the Yes button
m.No = L"Yes"; <= Change the text of the No button
```
**Custom Icon Support**  
You can assign a custom icon to the message box using the `m.hIcon` property.  
The icon must be in `.ico` format and should be **32x32 pixels** for
```c
m.hIcon = (HICON)LoadImage(NULL, L"YourIcon.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE); <= Change message box icon
```
**Hook Management**
- **Enable the Hook**: Use `m.Register()` before displaying the message box.
- **Disable the Hook**: Always call `m.Unregister()` after displaying the message box to avoid issues.
```C
m.Register(); <= Enable hooking
//Show message box
m.Unregister(); <= Disable hooking
```

## Example
```c
MessageBoxManager m;

m.Yes = L"Yes"; <= Change the text of the Yes button
m.No = L"Yes"; <= Change the text of the No button

***MUST 32x32***
m.hIcon = (HICON)LoadImage(NULL, L"YourIcon.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE) <= Change message box icon

m.Register(); <= Enable hooking

MessageBoxW(0, L"Are you imposter?", L"in c++", MB_ICONWARNING, | MB_YESNO);

m.Unregister(); <= Disable hooking
```
