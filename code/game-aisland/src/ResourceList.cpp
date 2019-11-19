////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ResourceList
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/ResourceList.h>
#include <mach/Mixer.h>
#include <mach/Texture.h>
#include <gamelib/Font.h>
#include <gamelib-sprites/SpriteSheet.h>

#include <string.h>
#include <stdlib.h>

ResourceList::ResourceList() : head(0), tail(0)
{
}
ResourceList::~ResourceList()
{
	ResourceNode* node;
	ResourceNode* next;
	
	for(node = head; node != null; node = next)
	{
		next = node->next;
		switch(node->type)
		{
			case RESOURCE_TYPE_FONT:			delete ((Font*)node->res);				break;
			case RESOURCE_TYPE_SOUND:			Mixer::freeSound((Sound*)node->res);	break;
			case RESOURCE_TYPE_MUSIC:			Mixer::freeMusic((Music*)node->res);	break;
			case RESOURCE_TYPE_TEXTURE:			delete ((Texture*)node->res);			break;
			case RESOURCE_TYPE_SPRITESHEET:		delete ((SpriteSheet*)node->res);		break;
		}
		free(node);
	}
}
void* ResourceList::get(const char* fname) const
{
	ResourceNode* node;
	for(node = head; node != null; node = node->next)
	{
		if(0 == strcmp(node->name, fname))
			return node->res;
	}
	return null;
}
void* ResourceList::insert(const char* fname, void* res, int type)
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
