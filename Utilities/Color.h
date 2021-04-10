#ifndef COLOR_H
#define COLOR_H

/*******************************************************************
 * class - Color
 * 
 * A color is made up of 3 doubles to represent red, green, and blue.
 * 
 *******************************************************************/

class Color{
    public:
        double red, green, blue;

    public:
        Color();

        Color(double c);

        Color(double r, double g, double b);

        Color(const Color& c);

        ~Color();

        Color  operator+ (const Color& col) const;
        Color  operator* (const double scalar) const;
        Color  operator* (const Color& col) const;
        Color  operator/ (const double scalar) const;
        Color& operator= (const Color& col);
        Color& operator+=(const Color& col);
        Color& operator*=(const double scalar);
        Color& operator/=(const double scalar);
        bool   operator==(const Color& col) const;

        Color  powerColor(double power) const;
        double aveColor() const;

};

/*******************************************************************
 * Operator overrides for Colors
 * 
 * Overrides for +, *, /, =+, *=, /=, =, and ==
 * 
 *******************************************************************/

inline Color Color::operator+(const Color& c) const {
    return Color(red + c.red, green + c.green, blue + c.blue);
}

inline Color Color::operator*(const Color& c) const {
    return Color(red * c.red, green * c.green, blue * c.blue);
}

inline Color Color::operator*(double scalar) const {
    return Color(scalar*red, scalar*green, scalar*blue);
}

inline Color Color::operator/(double scalar) const {
    return Color(red/scalar,green/scalar,blue/scalar);
}

inline Color& Color::operator+= (const Color& c) {
	red += c.red; green += c.green; blue += c.blue;
    return (*this);
}

inline Color& Color::operator*= (const double scalar) {
	red *= scalar; green *= scalar; blue *= scalar;
	return (*this);
}

inline Color& Color::operator/= (const double scalar) {	
	red /= scalar; green /= scalar; blue /= scalar;
	return (*this);
}

inline bool Color::operator== (const Color& c) const {
	return (red == c.red && green == c.green && blue == c.blue);
}

inline Color& Color::operator=(const Color& rhs) {
    red = rhs.red; green = rhs.green; blue = rhs.blue;
    return (*this);
}

#endif