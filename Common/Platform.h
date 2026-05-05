#pragma once

#if defined(_WIN64)
    #define PLATFORM_WINDOWS 1
    #define PLATFORM_LINUX   0
#elif defined(__linux__)
    #define PLATFORM_WINDOWS 0
    #define PLATFORM_LINUX   1
#else
    #error "Unsupported platform"
#endif

#if defined(NDEBUG)
    #define PLATFORM_DEBUG   0
    #define PLATFORM_RELEASE 1
#else
    #define PLATFORM_DEBUG   1
    #define PLATFORM_RELEASE 0
#endif

#include <stdint.h>
#include <stdio.h>

#if PLATFORM_LINUX
#include <X11/Xlib.h>
#endif

typedef int8_t  int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

struct platform_app
{
    bool Quit;
    struct
    {
        int32 Width;
        int32 Height;
    } MainWindow;

#if PLATFORM_LINUX
    struct
    {
        Display* Connection;
        Window MainWindow;
        Atom DeleteWindowEvent;
    } X11;
#endif
};

#if PLATFORM_LINUX
inline void Platform_FatalError(const char* Message)
{
    __builtin_debugtrap();
    fputs(Message, stderr);
    __builtin_trap();
}

inline void Platform_Init(platform_app* App)
{
    App->X11.Connection = XOpenDisplay(nullptr);
    if (!App->X11.Connection)
    {
        Platform_FatalError("Failed to open X11 display");
        return;
    }

    int32 Screen = DefaultScreen(App->X11.Connection);
    Window Root = RootWindow(App->X11.Connection, Screen);

    App->X11.MainWindow = XCreateSimpleWindow(App->X11.Connection, Root, 0, 0, App->MainWindow.Width, App->MainWindow.Height, 0, 0, 0);

    App->X11.DeleteWindowEvent = XInternAtom(App->X11.Connection, "WM_DELETE_WINDOW", false);
    XSetWMProtocols(App->X11.Connection, App->X11.MainWindow, &App->X11.DeleteWindowEvent, 1);

    XMapWindow(App->X11.Connection, App->X11.MainWindow);
}

inline void Platform_Update(platform_app* App)
{
    while (XPending(App->X11.Connection))
    {
        XEvent Event;
        XNextEvent(App->X11.Connection, &Event);

        switch (Event.type)
        {
            case ClientMessage:
            {
                if ((Atom)Event.xclient.data.l[0] == App->X11.DeleteWindowEvent)
                {
                    App->Quit = true;
                }
            } break;
        }
    }
}

inline void Platform_Cleanup(platform_app* App)
{
    XDestroyWindow(App->X11.Connection, App->X11.MainWindow);
    XCloseDisplay(App->X11.Connection);
}
#endif

