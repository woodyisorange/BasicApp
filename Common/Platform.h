#pragma once

#include <stdint.h>
#include <stdio.h>

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

typedef int8_t  int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

inline void Platform_DebugLog(const char* Message)
{
#if PLATFORM_DEBUG
    puts(Message);
#endif
}

struct platform_app
{
    bool Quit;
    struct
    {
        int32 Width;
        int32 Height;
    } Window;
};

inline void Platform_Init(platform_app* App)
{
}

inline void Platform_Update(platform_app* App)
{
    App->Quit = true;
}

