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

        Color(float c);

        Color(float r, float g, float b);

        Color(const Color& c);

        ~Color();

        Color  operator+ (const Color& col) const;
        Color  operator* (const float scalar) const;
        Color  operator* (const Color& col) const;
        Color  operator/ (const float scalar) const;
        Color& operator= (const Color& col);
        Color& operator+=(const Color& col);
        Color& operator*=(const float scalar);
        Color& operator/=(const float scalar);
        bool   operator==(const Color& col) const;

        Color  powerColor(float power) const;
        float aveColor() const;

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

inline Color Color::operator*(float scalar) const {
    return Color(red*scalar, green*scalar, blue*scalar);
}

inline Color Color::operator/(float scalar) const {
    return Color(red/scalar,green/scalar,blue/scalar);
}

inline Color& Color::operator+= (const Color& c) {
	red += c.red; green += c.green; blue += c.blue;
    return (*this);
}

inline Color& Color::operator*= (const float scalar) {
	red *= scalar; green *= scalar; blue *= scalar;
	return (*this);
}

inline Color& Color::operator/= (const float scalar) {	
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

// inlined non-member function

// ----------------------------------------------------------------------- operator*
// multiplication by a float on the left

Color operator* (const float a, const Color& c);

inline Color operator* (const float a, const Color& c) {
	return (Color (a * c.red, a * c.green, a * c.blue));	
}

#endif