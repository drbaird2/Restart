#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdlib.h>
#include "../Utilities/Color.h"

const double 	PI 			= 3.1415926535897932384;
const double 	TWO_PI 		= 6.2831853071795864769;
const double 	PI_ON_180 	= 0.0174532925199432957;
const double 	invPI 		= 0.3183098861837906715;
const double 	invTWO_PI 	= 0.1591549430918953358;

const double 	kEpsilon 	= 0.0001; 
const double	kHugeValue	= 1.0E10;

const Color	black(0.0,0.0,0.0);
const Color	white(1.0,1.0,1.0);
const Color	solidred(1.0, 0.0, 0.0);
const Color solidgreen(0.0 ,1.0 ,0.0);
const Color solidblue(0.0 ,0.0 ,1.0);
const Color crimson(0.5, 0.25, 0.25);
const Color cerulean(0.0, 1.0, 1.0);
const Color gray(0.5, 0.5, 0.5);



const float 	invRAND_MAX = 1.0 / (float)RAND_MAX;

#endif