////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ArtScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___ArtScreen_h___
#define ___ArtScreen_h___
#include <gamelib/Screen.h>

class Font;
class Texture;

class ArtScreen : public Screen
{
	bool			removable;
	Font*			font;
	Font*			fontTitle;
	Texture*		textures[12];
	int				currentTexture;
public:
	ArtScreen();
	~ArtScreen();
public:
	virtual Screen* getNext();
	virtual bool    isRemovable();
	virtual void    show(Machine* mach);
	virtual void    hide(Machine* mach);
	virtual void    update(Machine* mach, double dt);
	virtual void    render(Machine* mach, Graphics* gr);
};

#endif
