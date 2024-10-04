#include <iostream>

#include "OM_Engine.hpp"

int main()
{
    // Initialisation
    Application app;
    if(!app.Initialisation())
    {
        app.Destroy();
        return 1;
    }

    // Game loop
    while (!app.Window_Should_Close())
    {
        app.Update();
        app.Render();
    }

    // Clean
    app.Destroy();
    
    return 0;
}
