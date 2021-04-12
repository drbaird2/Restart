#include <iostream>
#include "Utilities/Scene.h"
using namespace std;

int main()
{
    Scene wonderland;
	wonderland.build();
	wonderland.cameraPtr->renderScene(wonderland);
    wonderland.save_bmp("output.bmp");

	return 0;
}