#include <cmath>
#include "Color.h"

using std::pow;
/*******************************************************************
 * Color constructors
 * 
 * Color() - defaults to Black
 * 
 * Color(double col) - takes a single double (col) and returns a col
 *                     with all 3 values == to (col)
 * 
 * Color(double r, double g, double b) - takes 3 doubles and returns
 *                     that color
 * 
 * Color(Color&) - Takes a color and returns a copy
 * 
 *******************************************************************/

Color::Color():
    red(0.0),
    green(0.0),
    blue(0.0)
{}

Color::Color(float col):
    red(col),
    green(col),
    blue(col)
{}

Color::Color(float r, float g, float b):
    red(r),
    green(g),
    blue(b)
{}

Color::Color(const Color& col):
    red(col.red),
    green(col.green),
    blue(col.blue)
{}

Color::~Color()
{}

/*******************************************************************
 * powerColor(double power) - Takes a double and returns the color
 *                      multiplied to the power of power
 * 
 *******************************************************************/
Color Color::powerColor(float power)const {
    return (Color(pow(red,power),pow(green,power),pow(blue,power)));
}

/*******************************************************************
 * aveColor() - returns the average of the 3 components of color or
 *             the brightness.
 * 
 *******************************************************************/
float Color::aveColor() const{
    return (0.333333333333 * (red+green+blue));
}
