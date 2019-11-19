////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SpriteSheetLoader
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <gamelib-sprites/SpriteSheetLoader.h>

#include <tinyxml2/tinyxml2.h>
#include <mach/TextureLoader.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteImage.h>
#include <gamelib-sprites/SpriteFrame.h>
#include <gamelib-sprites/SpriteSheet.h>

#include <string.h>

using namespace tinyxml2;

static char* getPath(const char* fname, char* path)
{
	char* p;
	
	p = (char*)strrchr(fname, '/');
	if(p == null)
		p = (char*)strrchr(fname, '\\');
	if(p == null)
	{
		p = path;
	}
	else
	{
		char* dst = path;
		const char* src = fname;
		while(src <= p)
		{
			*dst++ = *src++;
		}
		p = dst;
	}
	return p;
}
static void readImages(SpriteSheet* sheet, XMLElement* elem, const char* fname)
{
	char  path[256];
	char* p = getPath(fname, path);

	for(elem = elem->FirstChildElement("Image"); elem != null; elem = elem->NextSiblingElement())
	{
		const char* value;
		SpriteImage* image = new SpriteImage();
		
		elem->QueryStringAttribute("file", &value);
		strcpy(p, value);
		image->texture = TextureLoader::load(path);
		
		elem->QueryStringAttribute("anchor", &value);
		image->anchor = Point(value);
		
		image->x = 0;
		image->y = 0;
		image->width = image->texture->getWidth();
		image->height = image->texture->getHeight();
		
		sheet->images.push_back(image);
	}
}
static void readAnimations(SpriteSheet* sheet, XMLElement* elem)
{
	const char* value;
	Sprite*     sprite = new Sprite();
	
	elem->QueryStringAttribute("name", &value);
	sprite->name = value;
	
	for(elem = elem->FirstChildElement("AnimationFrame"); elem != null; elem = elem->NextSiblingElement())
	{
		SpriteFrame* frame = new SpriteFrame();
		int          index;
		
		elem->QueryStringAttribute("index", &value);
		index = atoi(value);
		frame->image = sheet->images[index];
		
		sprite->frames.push_back(frame);
	}
	sheet->sprites.push_back(sprite);
}
static void readRectangle(const char* p, SpriteImage* image)
{
	image->x = atoi(p);
	while(isalnum(*p)) p++;		// Digitos
	p++;						// ','
	image->y = atoi(p);
	while(isalnum(*p)) p++;		// Digitos
	p++;						// ','
	image->width = atoi(p);
	while(isalnum(*p)) p++;		// Digitos
	p++;						// ','
	image->height = atoi(p);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// SpriteSheet 1.0
////////////////////////////////////////////////////////////////////////////////////////////////////
static void readAttachedPoints(XMLElement* elem, Sprite* sprite)
{
	for(elem = elem->FirstChildElement("AttachedPoint"); elem != null; elem = elem->NextSiblingElement())
	{
		const char* value;
		Point point;
		
		elem->QueryStringAttribute("point", &value);
		point = Point(value);
		
		elem->QueryStringAttribute("name", &value);
		
		sprite->attachedPoints[value] = point;
	}
}
static void readAttachedPoints(XMLElement* elem, SpriteImage* image)
{
	for(elem = elem->FirstChildElement("AttachedPoint"); elem != null; elem = elem->NextSiblingElement())
	{
		const char* value;
		Point point;
		
		elem->QueryStringAttribute("point", &value);
		point = Point(value);
		
		elem->QueryStringAttribute("name", &value);
		
		image->attachedPoints[value] = point;
	}
}
static void readAttachedRectangles(XMLElement* elem, Sprite* sprite)
{
	for(elem = elem->FirstChildElement("AttachedRectangle"); elem != null; elem = elem->NextSiblingElement())
	{
		const char* value;
		Rectangle rect;
		
		elem->QueryStringAttribute("rectangle", &value);
		rect = Rectangle(value);
		
		elem->QueryStringAttribute("name", &value);
		
		sprite->attachedRectangles[value] = rect;
	}
}
static void readAttachedRectangles(XMLElement* elem, SpriteImage* image)
{
	for(elem = elem->FirstChildElement("AttachedRectangle"); elem != null; elem = elem->NextSiblingElement())
	{
		const char* value;
		Rectangle rect;
		
		elem->QueryStringAttribute("rectangle", &value);
		rect = Rectangle(value);
		
		elem->QueryStringAttribute("name", &value);
		
		image->attachedRectangles[value] = rect;
	}
}
static SpriteSheet* readSpriteSheet_1_0(XMLElement* root, const char* fname)
{
	XMLDocument doc;
	XMLElement* elem;
	SpriteSheet* sheet = new SpriteSheet();
	char  path[256];
	char* semiPath = getPath(fname, path);

	for(elem = root->FirstChildElement("Sprite"); elem != null; elem = elem->NextSiblingElement())
	{
		const char* value;
		Sprite* sprite = new Sprite();
		int count;
		Point anchor;
		Texture* texture;
		
		// Cargar la textura
		elem->QueryStringAttribute("image", &value);
//		strcpy(semiPath, "sprites/");
		strcpy(semiPath, value);
		texture = TextureLoader::load(path);
		sheet->textures.push_back(texture);
		
		// Nombre del sprite
		elem->QueryStringAttribute("name", &value);
		sprite->name = value;
		
		// Cantidad de marcos en la textura
		elem->QueryStringAttribute("count", &value);
		count = atoi(value);
		
		// Leer anchor
		elem->QueryStringAttribute("anchor", &value);
		anchor = Point(value);

		// Generar subimagenes
		int firstImage = (int)sheet->images.size();
		int imageX = 0;
		int imageWidth = texture->getWidth()/count;
#if 0
		for(int i = 0; i < count; i++)
		{
			SpriteImage* image = new SpriteImage();
			image->anchor = anchor;
			image->x = imageX;
			image->y = 0;
			image->width = imageWidth;
			image->height = texture->getHeight();
			image->texture = texture;
			
			imageX += imageWidth;
			sheet->images.push_back(image);
		}
#else
		XMLElement* elemFrame = elem->FirstChildElement("Frame");
		for(int i = 0; i < count; i++)
		{
			SpriteImage* image = new SpriteImage();
			if(elemFrame)
			{
				if(XML_SUCCESS == elemFrame->QueryStringAttribute("anchor", &value) && *value != '\0')
				{
					anchor = Point(value);
				}
				readAttachedPoints(elemFrame, image);
				readAttachedRectangles(elemFrame, image);
				elemFrame = elemFrame->NextSiblingElement();
			}
			image->anchor = anchor;
			image->x = imageX;
			image->y = 0;
			image->width = imageWidth;
			image->height = texture->getHeight();
			image->texture = texture;
			
			imageX += imageWidth;
			sheet->images.push_back(image);
		}
#endif
		SpriteFrame* frame;
		if(XML_SUCCESS != elem->QueryStringAttribute("indexes", &value) || *value == '\0')
		{
			for(int i = 0; i < count; i++)
			{
				frame = new SpriteFrame();
				frame->image = sheet->images[firstImage+i];
				sprite->frames.push_back(frame);
			}
		}
		else
		{
			const char* s = value;
			while(*s != '\0')
			{
				int idx = atoi(s);
				while(isalnum(*s)) s++;		// Digitos
				if(*s == ',') s++;			// ','
				frame = new SpriteFrame();
				frame->image = sheet->images[firstImage+idx];
				sprite->frames.push_back(frame);
			}
		}
		// Leer puntos
		readAttachedPoints(elem, sprite);
		
		// Leer rectangles
		readAttachedRectangles(elem, sprite);
		
		// ...
		sheet->sprites.push_back(sprite);
	}
	return sheet;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// SpriteSheet 1.1
////////////////////////////////////////////////////////////////////////////////////////////////////
static SpriteSheet* readSpriteSheet_1_1(XMLElement* root, const char* fname)
{
	XMLElement* elem;
	SpriteSheet* sheet = new SpriteSheet();
	
	if(null != (elem = root->FirstChildElement("ImageList")))
	{
		readImages(sheet, elem, fname);
	}
	if(null != (elem = root->FirstChildElement("AnimationList")))
	{
		for(elem = elem->FirstChildElement("Animation"); elem != null; elem = elem->NextSiblingElement())
		{
			readAnimations(sheet, elem);
		}
	}
	return sheet;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// SpriteSheet 1.2
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <mach/String.h>
static SpriteSheet* readSpriteSheet_1_2(XMLElement* root, const char* fname)
{
	XMLElement* elem;
	SpriteSheet* sheet = new SpriteSheet();
	const char* s;
	char  path[256];
	char* semiPath = getPath(fname, path);

	// Imagen
	root->QueryStringAttribute("image", &s);
	strcpy(semiPath, s);
	Texture* texture = TextureLoader::load(path);
	sheet->textures.push_back(texture);

	if(null != (elem = root->FirstChildElement("ImageList")))
	{
		for(elem = elem->FirstChildElement("Image"); elem != null; elem = elem->NextSiblingElement())
		{
			SpriteImage* image = new SpriteImage();
			
			elem->QueryStringAttribute("anchor", &s);
			image->anchor = Point(s);
			
			elem->QueryStringAttribute("rectangle", &s);
			Rectangle r(s);
			image->x = r.getX();
			image->y = r.getY();
			image->width = r.getWidth();
			image->height = r.getHeight();

			image->texture = texture;

			readAttachedPoints(elem, image);
			readAttachedRectangles(elem, image);

			sheet->images.push_back(image);
		}
	}
	if(null != (elem = root->FirstChildElement("SpriteList")))
	{
		for(elem = elem->FirstChildElement("Sprite"); elem != null; elem = elem->NextSiblingElement())
		{
			Sprite* sprite = new Sprite();
			
			elem->QueryStringAttribute("name", &s);
			sprite->name = s;
			
			elem->QueryStringAttribute("indexes", &s);
			StringList indexes = String(s).split(",");

			for(unsigned int i = 0; i < indexes.size(); i++)
			{
				SpriteFrame* frame = new SpriteFrame();
				frame->image = sheet->images[indexes[i].toInt()];
				
				sprite->frames.push_back(frame);
			}
			sheet->sprites.push_back(sprite);
			
			readAttachedPoints(elem, sprite);
			readAttachedRectangles(elem, sprite);
		}
	}
	return sheet;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
SpriteSheet* SpriteSheetLoader::load(const char* fname)
{
	XMLError err;
	XMLDocument doc;
	XMLElement* root;
	XMLElement* elem;
	SpriteSheet* sheet = null;
	
	err = doc.LoadFile(fname);
	if(err != XML_SUCCESS)
		return null;
	
	if(null != (root = doc.FirstChildElement("Sprite")))
	{
		char  path[256];
		char* p = getPath(fname, path);
		const char* value;
		Sprite* sprite = new Sprite();
		Texture* texture;
		
		sheet = new SpriteSheet();
		sheet->sprites.push_back(sprite);
		
		// Imagen
		root->QueryStringAttribute("image", &value);
		strcpy(p, value);
		texture = TextureLoader::load(path);
		sheet->textures.push_back(texture);
		
		// Versión
		root->QueryStringAttribute("version", &value);
		
		if(0 == strcmp(value, "1.0"))
		{
			int count;
			Point anchor;

			// Anchor
			root->QueryStringAttribute("anchor", &value);
			anchor = Point(value);

			// Cantidad de frames
			root->QueryStringAttribute("frames", &value);
			count = atoi(value);

			int x = 0;
			int width = texture->getWidth()/count;
			
			for(elem = root->FirstChildElement("Frame"); elem != null; elem = elem->NextSiblingElement())
			{
				SpriteImage* image = new SpriteImage();
				SpriteFrame* frame = new SpriteFrame();
				
				// Anchor
				if(XML_SUCCESS == elem->QueryStringAttribute("anchor", &value) && *value != '\0')
				{
					anchor = Point(value);
				}
				
				image->x = x;
				image->y = 0;
				image->width = width;
				image->height = texture->getHeight();
				
				// ...
				image->anchor = anchor;
				image->texture = texture;
				frame->image = image;
				sheet->images.push_back(image);
				sprite->frames.push_back(frame);
				// ...
				x += width;
			}
			readAttachedPoints(root, sprite);
			readAttachedRectangles(root, sprite);
		}
		else if(0 == strcmp(value, "1.1"))
		{
			if(null != (elem = root->FirstChildElement("FrameList")))
			{
				int count;
				int index = 0;
				
				// Cantidad de frames
				elem->QueryStringAttribute("frames", &value);
				count = atoi(value);
				
				for(elem = elem->FirstChildElement("Frame"); elem != null; elem = elem->NextSiblingElement())
				{
					SpriteImage* image = new SpriteImage();
					SpriteFrame* frame = new SpriteFrame();
					Point anchor;
					
					// Anchor
					elem->QueryStringAttribute("anchor", &value);
					anchor = Point(value);
					
					// Rectángulo
					elem->QueryStringAttribute("rectangle", &value);
					readRectangle(value, image);
					
					// ...
					image->anchor = anchor;
					image->texture = texture;
					frame->image = image;
					sheet->images.push_back(image);
					sprite->frames.push_back(frame);
				}
			}
		}
	}
	else if(null != (root = doc.FirstChildElement("SpriteSheet")))
	{
		const char* value;
		
		root->QueryStringAttribute("version", &value);
		if(0 == strcmp(value, "1.0"))
		{
			return readSpriteSheet_1_0(root, fname);
		}
		else if(0 == strcmp(value, "1.1"))
		{
			return readSpriteSheet_1_1(root, fname);
		}
		else if(0 == strcmp(value, "1.2"))
		{
			return readSpriteSheet_1_2(root, fname);
		}
	}
	return sheet;
}
