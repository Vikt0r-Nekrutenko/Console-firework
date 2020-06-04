#include "window.h"
#include "renderer.h"

ConsoleWindow *ConsoleWindowCreate()
{
    ConsoleWindow *wnd = (ConsoleWindow *)malloc(sizeof(ConsoleWindow));
    wnd->_wnd = GetConsoleWindow();
    wnd->_output = GetStdHandle(STD_OUTPUT_HANDLE);
    wnd->_input = GetStdHandle(STD_INPUT_HANDLE);

    ConsoleWindowEnableFullscreen(wnd);

    return wnd;
}

int ConsoleWindowProc(ConsoleWindow *wnd)
{
    INPUT_RECORD ir[32];
    DWORD n = 0;
    float dt = 0.f, elpsd_time = 0.f;
    uint64_t frames = 0ull;

    COORD fps_pos = { 0, wnd->_size.Y };
    SetConsoleCursorPosition(wnd->_output, fps_pos);

    while (TRUE)
    {
        if (elpsd_time > 1.f)
        {
            printf("%f\r", frames / elpsd_time);
            elpsd_time = frames = 0;
        }

        time_t begin = clock();

        ConsoleRendererClear(wnd->_rend);
        ConsoleWindowUpdateProc(wnd, dt);
        ConsoleRendererPresent(wnd, wnd->_rend);

        GetNumberOfConsoleInputEvents(wnd->_input, &n);
        if (n > 0)
        {
            ReadConsoleInputA(wnd->_input, ir, n, &n);
            for (DWORD i = 0; i < n; ++i)
            {
                switch (ir[i].EventType)
                {
                case MOUSE_EVENT: break;
                case KEY_EVENT:
                    if (ir[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
                    {
                        ConsoleRendererDelete(wnd->_rend);
                        free(wnd);
                        return 0;
                    }
                }
            }
        }

        dt = (clock() - begin) / 1000.f;
        elpsd_time += dt;
        ++frames;
    }
}

void ConsoleWindowSetSize(ConsoleWindow *wnd, short width, short height)
{
    CONSOLE_SCREEN_BUFFER_INFOEX csbiex;
    csbiex.cbSize = sizeof (CONSOLE_SCREEN_BUFFER_INFOEX);
    GetConsoleScreenBufferInfoEx(wnd->_output, &csbiex);
    csbiex.srWindow.Top = csbiex.srWindow.Left = 0;
    csbiex.dwSize.X = csbiex.dwMaximumWindowSize.X = csbiex.srWindow.Right = width;
    csbiex.dwSize.Y = csbiex.dwMaximumWindowSize.Y = csbiex.srWindow.Bottom = height;
    SetConsoleScreenBufferInfoEx(wnd->_output, &csbiex);
}

void ConsoleWindowEnableFullscreen(ConsoleWindow *wnd)
{
    wnd->_size = GetLargestConsoleWindowSize(wnd->_output);
    wnd->_size.X += 1; wnd->_size.Y += 1;
    wnd->_rend = ConsoleRendererCreate(wnd);

    COORD wnd_size = wnd->_size;
    wnd_size.X += 10; wnd_size.Y += 10;
    ConsoleWindowSetSize(wnd, wnd_size.X, wnd_size.Y);
    SetWindowLongPtrA(wnd->_wnd, GWL_STYLE, WS_CHILD);
    SetWindowPos(wnd->_wnd, HWND_TOPMOST, -2, -2, 0, 0, SWP_NOSIZE | SWP_FRAMECHANGED | SWP_SHOWWINDOW);
}
