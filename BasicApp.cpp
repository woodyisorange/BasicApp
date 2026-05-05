#include "Common/Platform.h"

platform_app App;

int main()
{
    App.MainWindow.Width = 800;
    App.MainWindow.Height = 600;
    Platform_Init(&App);

    while (!App.Quit)
    {
        Platform_Update(&App);
    }

    Platform_Cleanup(&App);
    return 0;
}

