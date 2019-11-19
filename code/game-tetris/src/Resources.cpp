////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Resources
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/Resources.h>
#include <mach/TextureLoader.h>
#include <gamelib/FontLoader.h>
#include <string>

enum
{
	RESOURCE_TYPE_FONT,
	RESOURCE_TYPE_TEXTURE,
};

struct ResourceNode
{
	void*			res;
	int				type;
	ResourceNode*	next;
	char			name[1];
};
struct ResourceList
{
	ResourceNode* head;
	ResourceNode* tail;
public:
	ResourceList() : head(0), tail(0)
	{
	}
	~ResourceList()
	{
		ResourceNode* node;
		ResourceNode* next;
		
		for(node = head; node != null; node = next)
		{
			next = node->next;
			switch(node->type)
			{
				case RESOURCE_TYPE_FONT:	delete ((Font*)node->res);		break;
				case RESOURCE_TYPE_TEXTURE:	delete ((Texture*)node->res);	break;
			}
			free(node);
		}
	}
public:
	void* get(const char* fname)
	{
		ResourceNode* node;
		for(node = head; node != null; node = node->next)
		{
			if(0 == strcmp(node->name, fname))
				return node->res;
		}
		return null;
	}
	void* insert(const char* fname, void* res, int type)
	{
		if(res)
		{
			ResourceNode* node;
			
			//
			// Crear nuevo nodo
			//
			node = (ResourceNode*)malloc(sizeof(ResourceNode) + strlen(fname));
			node->res = res;
			node->type = type;
			node->next = null;
			strcpy(node->name, fname);
			
			//
			// Agregar a la lista
			//
			if(head == 0)
			{
				head = node;
				tail = node;
			}
			else
			{
				tail->next = node;
				tail = node;
			}
			return res;
		}
		return null;
	}
};

static ResourceList ___fontList;
static ResourceList ___textureList;

Font* Resources::loadFont(const char* fname)
{
	void* ptr = ___fontList.get(fname);
	if(ptr)
		return (Font*)ptr;
	std::string str = (std::string("tetris/fonts/") + fname);
	return (Font*)___fontList.insert(str.c_str(), FontLoader::load(str.c_str()), RESOURCE_TYPE_FONT);
}
Texture* Resources::loadTexture(const char* fname)
{
	void* ptr = ___textureList.get(fname);
	if(ptr)
		return (Texture*)ptr;
	std::string str = (std::string("tetris/images/") + fname);
	return (Texture*)___textureList.insert(str.c_str(), TextureLoader::load(str.c_str()), RESOURCE_TYPE_TEXTURE);
}

