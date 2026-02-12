#include <windows.h>
#include <windowsx.h>
#include <cmath>
#include <algorithm>
#include <afxres.h>
#include <winver.h>
#include <winsvc.h>

#define WINDOW_WIDTH  1080
#define WINDOW_HEIGHT 720

//--------------------------------- Structures ------------------------------
//
//---------------------------------------------------------------------------

struct Circle {
    int x;
    int y;
    int r;
    Circle(){}
    Circle(int x, int y, int r) {
        this->x = x;
        this->y = y;
        this->r = r;
    }
};

struct Point {
    int x;
    int y;
    Point() {}
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

//--------------------------------- Globals ------------------------------
//
//------------------------------------------------------------------------

const char *g_szApplicationName = "Task1";
const char *g_szWindowClassName = "MyWindowClass";
struct Circle C1, C2;
bool C1_set = false;
bool C2_set = false;
Point point1, point2, point3;
bool p1Set = false, p2Set = false, p3Set = false;

//--------------------------------- Helpers ------------------------------
//
//------------------------------------------------------------------------

void Draw8Points(HDC hdc,int xc,int yc, int a, int b,COLORREF color)
{
    SetPixel(hdc, xc+a, yc+b, color);
    SetPixel(hdc, xc-a, yc+b, color);
    SetPixel(hdc, xc-a, yc-b, color);
    SetPixel(hdc, xc+a, yc-b, color);
    SetPixel(hdc, xc+b, yc+a, color);
    SetPixel(hdc, xc-b, yc+a, color);
    SetPixel(hdc, xc-b, yc-a, color);
    SetPixel(hdc, xc+b, yc-a, color);
}

void DrawLine(HDC hdc, int xs, int ys, int xe, int ye, COLORREF color)
{
    if(xs > xe) std::swap(xs, xe), std::swap(ys, ye);
    int dx = xe - xs;
    int dy = ye - ys;
    int x = xs;
    int y = ys;
    int d = 2 * dx - dy;
    int change1 = 2 * (dx - dy);
    int change2 = 2 * dx;
    SetPixel(hdc, x, y, color);
    while(y < ye)
    {
        if(d > 0)
        {
            d += change1;
            x++;
        } else
        {
            d += change2;
        }

        y++;

        SetPixel(hdc, x, y, color);
    }
}

void DrawCircle(HDC hdc,int xc,int yc, int R,COLORREF color)
{
    int x=0,y=R;
    int d=1-R;
    int c1=3, c2=5-2*R;
    Draw8Points(hdc,xc,yc,x,y,color);
    while(x<y)
    {
        if(d<0)
        {
            d+=c1;
            c2+=2;
        }
        else
        {
            d+=c2;
            c2+=4;
            y--;
        }
        c1+=2;
        x++;
        Draw8Points(hdc,xc,yc,x,y,color);
        if(!C1_set) DrawLine(hdc, xc+x, yc+y, xc - x, yc - y, color);
    }
    C1_set = true;
}

int mulitplyTwoVectors(int v1[], int v2[], int size) {
    int ret = 0;
    for (int i = 0;i < size;i++)
        ret += v1[i] * v2[i];
    return ret;
}

void DrawCurve(HDC hdc, Point startPoint, Point endPoint, Point slopes, COLORREF color) {
    double beta1 = startPoint.x;
    double beta2 = startPoint.y;
    double alpha1 = slopes.x - startPoint.x;
    double alpha2 = slopes.y - startPoint.y;
    double gamma1 = endPoint.x;
    double gamma2 = endPoint.y;

    double dt = 1 / std::max(std::abs(alpha1), std::abs(alpha2));

    double x, y;
    double t = 0;
    int i = 0;
    while (i <= std::max(std::abs(alpha1), std::abs(alpha2)))
    {
        x = alpha1*t*t + beta1*t + gamma1;
        y = alpha2*t*t + beta2*t + gamma2;
        SetPixel(hdc, x, y, color);
        t += dt;
        i++;
    }
}

//---------------------------- WindowProc ---------------------------------   
//     
//  This is the callback function which handles all the windows messages   
//-------------------------------------------------------------------------   

LRESULT CALLBACK WindowProc (HWND   hwnd,
                             UINT   msg,
                             WPARAM wParam,
                             LPARAM lParam)
{

    switch (msg)
    {

        case WM_LBUTTONDOWN:
        {
            if(!p1Set) {
                p1Set = true;
                point1.x = GET_X_LPARAM(lParam);
                point1.y = GET_Y_LPARAM(lParam);
            } else if(!p2Set) {
                p2Set = true;
                point2.x = GET_X_LPARAM(lParam);
                point2.y = GET_Y_LPARAM(lParam);
            } else if(!p3Set) {
                p3Set = true;
                point3.x = GET_X_LPARAM(lParam);
                point3.y = GET_Y_LPARAM(lParam);

                DrawCurve(GetDC(hwnd), point1, point2, point3, RGB(0, 0, 0));
            }
            break;
        }

        case WM_RBUTTONDOWN:
        {
            break;
        }

            //A WM_CREATE msg is sent when your application window is first
            //created
        case WM_CREATE:
        {
//            PlaySound("window_open.wav", NULL, SND_FILENAME | SND_ASYNC);
        }

            break;

        case WM_KEYUP:
        {
            switch(wParam)
            {
                case VK_ESCAPE:
                {
                    PostQuitMessage(0);
                }
                    break;
            }
        }


        case WM_PAINT:
        {
            PAINTSTRUCT ps;

            BeginPaint (hwnd, &ps);

            //**this is where we do any drawing to the screen**

            EndPaint (hwnd, &ps);
        }

            break;

        case WM_DESTROY:
        {
            // kill the application, this sends a WM_QUIT message
            PostQuitMessage (0);
        }

            break;


    }//end switch

    //this is where all the messages not specifically handled by our
    //winproc are sent to be processed
    return DefWindowProc (hwnd, msg, wParam, lParam);
}

//-------------------------------- WinMain -------------------------------   
//   
//  The entry point of the windows program   
//------------------------------------------------------------------------   
int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR     szCmdLine,
                    int       iCmdShow)
{
    //handle to our window
    HWND                       hWnd;

    //our window class structure
    WNDCLASSEX     winclass;

    // first fill in the window class stucture
    winclass.cbSize        = sizeof(WNDCLASSEX);
    winclass.style         = CS_HREDRAW | CS_VREDRAW;
    winclass.lpfnWndProc   = WindowProc;
    winclass.cbClsExtra    = 0;
    winclass.cbWndExtra    = 0;
    winclass.hInstance     = hInstance;
    winclass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    winclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
    winclass.hbrBackground = (HBRUSH)GetStockObject (WHITE_BRUSH);
    winclass.lpszMenuName  = NULL;
    winclass.lpszClassName = g_szWindowClassName;
    winclass.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    //register the window class
    if (!RegisterClassEx(&winclass))
    {
        MessageBox(NULL, "Registration Failed!", "Error", 0);

        //exit the application
        return 0;
    }

    //create the window and assign its ID to hwnd
    hWnd = CreateWindowEx (DWORD(),                 // extended style
                           g_szWindowClassName,  // window class name
                           g_szApplicationName,  // window caption
                           WS_OVERLAPPEDWINDOW,  // window style
                           0,                    // initial x position
                           0,                    // initial y position
                           WINDOW_WIDTH,         // initial x size
                           WINDOW_HEIGHT,        // initial y size
                           NULL,                 // parent window handle
                           NULL,                 // window menu handle
                           hInstance,            // program instance handle
                           NULL);                // creation parameters

    //make sure the window creation has gone OK
    if(!hWnd)
    {
        MessageBox(NULL, "CreateWindowEx Failed!", "Error!", 0);
    }

    //make the window visible
    ShowWindow (hWnd, iCmdShow);
    UpdateWindow (hWnd);

    //this will hold any windows messages
    MSG msg;

    //entry point of our message handler
    while (GetMessage (&msg, NULL, 0, 0))
    {
        TranslateMessage (&msg);
        DispatchMessage (&msg);
    }

    return msg.wParam;
}   