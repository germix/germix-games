////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Color
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Color_h___
#define ___Color_h___

class Color
{
	unsigned int rgba;
public:
	Color() : rgba(0xFF000000)
	{
	}
	Color(const char* c);
	Color(const Color& c) : rgba(c.rgba)
	{
	}
	Color(int r, int g, int b, int a = 255) : rgba((r&0xFF)|((g&0xFF)<<8)|((b&0xFF)<<16)|((a&0xFF)<<24))
	{
	}
public:
	Color& operator = (const Color& c)
	{
		rgba = c.rgba;
		return *this;
	}
	bool operator == (const Color& c) const
	{
		return (rgba == c.rgba);
	}
public:
	unsigned char red()		const { return (rgba&0xFF); }
	unsigned char green()	const { return ((rgba>>8)&0xFF); }
	unsigned char blue()	const { return ((rgba>>16)&0xFF); }
	unsigned char alpha()	const { return ((rgba>>24)&0xFF); }

};

#endif
