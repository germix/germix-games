////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ResourceList
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___ResourceList_h___
#define ___ResourceList_h___

enum
{
	RESOURCE_TYPE_FONT,
	RESOURCE_TYPE_SOUND,
	RESOURCE_TYPE_MUSIC,
	RESOURCE_TYPE_TEXTURE,
	RESOURCE_TYPE_SPRITESHEET,
};

struct ResourceNode
{
//	int				ref;
	void*			res;
	int				type;
	ResourceNode*	next;
	char			name[1];
};

class ResourceList
{
public:
	ResourceNode* head;
	ResourceNode* tail;
public:
	ResourceList();
	~ResourceList();
public:
	void* get(const char* fname) const;
	void* insert(const char* fname, void* res, int type);
};

#endif
