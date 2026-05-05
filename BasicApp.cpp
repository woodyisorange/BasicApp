#include "Common/Platform.h"

platform_app App;

int main()
{
    App.Window.Width = 800;
    App.Window.Height = 600;
    Platform_Init(&App);

    while (!App.Quit)
    {
        Platform_Update(&App);
    }

    return 0;
}

