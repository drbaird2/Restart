#include <iostream>
#include "Utilities/Scene.h"
//#include "Objects/BVH.h"
using namespace std;

int main()
{
    Scene wonderland;
	wonderland.build();
	//wonderland.objects = make_shared<BVH>(wonderland);
	wonderland.cameraPtr->renderScene(wonderland);
    wonderland.save_bmp("output.bmp");

	return 0;
}