//
// Created by cloquet on 04/05/16.
//

#include "Main.hpp"

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

int main()
{
  new Bomberman::Main();
}
