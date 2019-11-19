////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Color
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <mach/Color.h>

#include <ctype.h>
#include <stdlib.h>

Color::Color(const char* s)
{
	int r,g,b,a;
	
	r = atoi(s);
	if(*s == '-') s++;
	while(isalnum(*s)) s++;				// Digitos
	s++;								// ','
	g = atoi(s);
	if(*s == '-') s++;
	while(isalnum(*s)) s++;				// Digitos
	s++;								// ','
	b = atoi(s);
	while(isalnum(*s)) s++;				// Digitos
	if(*s == ',') s++;					// ','
	a = isalnum(*s) ? atoi(s) : 255;

	rgba = ((r&0xFF)|((g&0xFF)<<8)|((b&0xFF)<<16)|((a&0xFF)<<24));
}
