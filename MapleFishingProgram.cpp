#define WINVER 0x0500
#include <windows.h>
#include <stdio.h>
#define ID_BUTTON_1 1
#define ID_BUTTON_2 2
#define ID_BUTTON_3 3


HANDLE g_hEvent= CreateEvent(NULL,FALSE,FALSE, "qqq");
DWORD WINAPI Fun1Proc(LPVOID lpParameter){

	HWND firstwindow = FindWindowEx(NULL, NULL, NULL, NULL);
    HWND window = firstwindow;
    TCHAR windowtext[MAX_PATH];
     
    // We need to get the console title in case we
    // accidentally match the search word with it
    // instead of the intended target window.
    TCHAR consoletitle[MAX_PATH];
    GetConsoleTitle(consoletitle, MAX_PATH);
     
    while(1)
    {
        //fprintf(stderr, ".");
         
        // Check window title for a match
        GetWindowText(window, windowtext, MAX_PATH);
        if (strstr(windowtext, "MapleStory") != NULL &&
            strcmp(windowtext, consoletitle) != 0) break;
         
        // Get next window
        window = FindWindowEx(NULL, window, NULL, NULL);
        if (window == NULL || window == firstwindow)
        {
            fprintf(stderr, "Window not found\n");
            system("pause");
            return 0;
        }
    }
    
    
    //SetForegroundWindow(window);
    
    while(1){
    	//puts("wait for signal");
		WaitForSingleObject(g_hEvent,INFINITE);
		SetEvent(g_hEvent);
		PostMessage(window, WM_KEYDOWN, 0x0D, 0);//enter
	    Sleep(1);
    	PostMessage(window, WM_KEYDOWN, 0x25, 0);//left
    	Sleep(1);
    	PostMessage(window, WM_KEYDOWN, 0x28, 0);//down
    	Sleep(1);
		PostMessage(window, WM_KEYDOWN, 0x20, 0);//space
	    Sleep(1);
		for(int i=0;i<50;i++){
		  PostMessage(window, WM_KEYDOWN, 0x25, 0);//left
    	  Sleep(1);
    	  PostMessage(window, WM_KEYDOWN, 0x28, 0);//down
    	  Sleep(1);
        }
        PostMessage(window, WM_KEYDOWN, 0x20, 0);//space
	    Sleep(1);
	    for(int i=0;i<70;i++){
		    PostMessage(window, WM_KEYDOWN, 0x25, 0);//left
    	    Sleep(1);
    	    PostMessage(window, WM_KEYDOWN, 0x28, 0);//down
    	    Sleep(1);
        }
        for(int i=0;i<14;i++){
        	PostMessage(window, WM_KEYDOWN, 0x0D, 0);//enter
	        Sleep(1);
		}
		for(int i=0;i<120;i++){
		    PostMessage(window, WM_KEYDOWN, 0x27, 0);//right
    	    Sleep(1);
    	    PostMessage(window, WM_KEYDOWN, 0x28, 0);//down
    	    Sleep(1);
        }
        for(int i=0;i<10;i++){
        	PostMessage(window, WM_KEYDOWN, 0x0D, 0);//enter
	        Sleep(1);
		}
		PostMessage(window, WM_KEYDOWN, 0x20, 0);//space
	    Sleep(10);
    }
    return 0;
}


HWND button1,button2,button3;
HANDLE hThread1=CreateThread(NULL, 0, Fun1Proc, NULL, 0, NULL);
    //CloseHandle(hThread1);
    
/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    char text[100];
    HDC hdc;
    PAINTSTRUCT ps;
	
	switch(Message) {
		case WM_CREATE:
		    button1=CreateWindow(TEXT("button"), TEXT("START"),
			WS_VISIBLE | WS_CHILD,
			10,10,80,25,
			hwnd,(HMENU) ID_BUTTON_1,NULL,NULL
			);
			button2=CreateWindow(TEXT("button"), TEXT("PAUSE"),
			WS_VISIBLE | WS_CHILD,
			100,10,80,25,
			hwnd,(HMENU) ID_BUTTON_2,NULL,NULL
			);
			button3=CreateWindow(TEXT("button"), TEXT("EXIT"),
			WS_VISIBLE | WS_CHILD,
			190,10,80,25,
			hwnd,(HMENU) ID_BUTTON_3,NULL,NULL
			);
		    break;
		case WM_COMMAND:
			if(LOWORD(wParam)==ID_BUTTON_1){
				ZeroMemory(text, sizeof(text));
			    wsprintf(text,"START");
			    hdc = GetDC(hwnd);
				SetTextColor(hdc,RGB(255, 0, 0));         
                TextOut(hdc, 115, 50, text, strlen(text));
                ReleaseDC(hwnd,hdc);
				SetEvent(g_hEvent);
			}
			if(LOWORD(wParam)==ID_BUTTON_2){
				ResetEvent(g_hEvent);
				ZeroMemory(text, sizeof(text));
			    wsprintf(text,"PAUSE");
			    hdc = GetDC(hwnd);
				SetTextColor(hdc,RGB(255, 0, 0));         
                TextOut(hdc, 115, 50, text, strlen(text));
                ReleaseDC(hwnd,hdc);
                
				
			}
			if(LOWORD(wParam)==ID_BUTTON_3){
				CloseHandle(g_hEvent);
				PostQuitMessage(0);
				exit(0);
			}
			break;
		case WM_PAINT:
		    ZeroMemory(text, sizeof(text));
            wsprintf(text,"MapleStory Fishing Program");
	        hdc = BeginPaint(hwnd,&ps);
	        SetTextColor(hdc,0x480C6B);          
            TextOut(hdc, 45, 75, text, strlen(text));
            ZeroMemory(text, sizeof(text));
            wsprintf(text,"--Made by Kagetsuki--");
            TextOut(hdc, 65, 110, text, strlen(text));
            EndPaint(hwnd,&ps);	
            break;
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			exit(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","MapleFishing",WS_VISIBLE|WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME|WS_MINIMIZEBOX,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		300, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}

	return msg.wParam;
}

