////////////////////////////////////////////////////////////////////////////////////////////////////
//
// FontLoader
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <gamelib/FontLoader.h>
#include <gamelib/Font.h>
#include <tinyxml2/tinyxml2.h>
#include <mach/TextureLoader.h>

using namespace tinyxml2;

Font* FontLoader::load(const char* fname)
{
	XMLError err;
	XMLDocument doc;
//	XMLNode* root;
	XMLElement* elem;
	const char* fontImage;
	int fontWidth;
	int fontHeight;
//	int fontLastChar;
	int fontFirstChar;
	
	err = doc.LoadFile(fname);
	if(err != XML_SUCCESS)
		return null;
	
#if 1
	elem = doc.FirstChildElement("Font");
#else
	root = doc.FirstChild();
	if(root == null)
		return null;
	
	elem = root->FirstChildElement("Font");
#endif
	if(elem == null)
		return null;
	
	err = elem->QueryStringAttribute("image", &fontImage);
	if(err != XML_SUCCESS)
		return null;
	
	err = elem->QueryIntAttribute("width", &fontWidth);
	if(err != XML_SUCCESS)
		return null;
	
	err = elem->QueryIntAttribute("height", &fontHeight);
	if(err != XML_SUCCESS)
		return null;
	
#if 0
	err = elem->QueryIntAttribute("last", &fontLastChar);
	if(err != XML_SUCCESS)
		return null;
#else
#endif

	err = elem->QueryIntAttribute("first", &fontFirstChar);
	if(err != XML_SUCCESS)
		return null;
	
	const char* p;
	char buf[256];
	Texture* tex;
	
	p = strrchr(fname, '/');
	if(p == null)
		p = strrchr(fname, '\\');
	if(p == null)
	{
		strcpy(buf, fontImage);
	}
	else
	{
		char* dst = buf;
		const char* src = fname;
		while(src <= p)
		{
			*dst++ = *src++;
		}
		strcpy(dst, fontImage);
	}
	tex = TextureLoader::load(buf);
	if(tex == null)
		return null;

	Font* font = new Font();
	font->tex = tex;
	font->width = fontWidth;
	font->height = fontHeight;
	font->lastChar = fontFirstChar + (tex->getWidth()/fontWidth);
	font->firstChar = fontFirstChar;
	return font;
}
