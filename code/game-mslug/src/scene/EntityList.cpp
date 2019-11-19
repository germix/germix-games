////////////////////////////////////////////////////////////////////////////////////////////////////
//
// EntityList
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/scene/EntityList.h>

EntityList::EntityList()
: head(0)
, tail(0)
{
}
EntityList::~EntityList()
{
	clear();
}
void EntityList::clear()
{
	EntityNode* next;
	EntityNode* node;
	
	for(node = head; node != null; node = next)
	{
		next = node->next;
		delete node;
	}
	head = null;
	tail = null;
}
void EntityList::append(Entity* e)
{
	append(e, null);
}
void EntityList::append(Entity* e, Entity* o)
{
	EntityNode* node = new EntityNode(e);
	node->backof = o;
	
	if(head == null)
	{
		head = node;
		tail = node;
	}
	else
	{
		node->prev = tail;
		tail->next = node;
		tail = node;
	}
}
EntityNode* EntityList::find(Entity* e)
{
	EntityNode* node;
	for(node = head; node != null; node = node->next)
	{
		if(node->entity == e)
			return node;
	}
	return null;
}
void EntityList::append(EntityList& other)
{
	EntityNode* next;
	EntityNode* node;
	for(node = other.head; node != null; node = next)
	{
		next = append(other, node);
	}
}
EntityNode* EntityList::append(EntityList& other, EntityNode* node)
{
	EntityNode* next = node->next;
	
	//
	// Desenlazar de la otra lista
	//
	if(node->prev)
		node->prev->next = node->next;
	if(node->next)
		node->next->prev = node->prev;
	if(other.head == node)
		other.head = other.head->next;
	if(other.tail == node)
		other.tail = other.tail->prev;
	
#if 0
	//
	// Insertar en ésta lista
	//
	if(head == null)
	{
		node->next = null;
		node->prev = null;
		head = node;
		tail = node;
	}
	else
	{
		node->next = null;
		node->prev = tail;
		tail->next = node;
		tail = node;
	}
#else
	//
	// Insertar en ésta lista
	//
	if(head == null)
	{
		node->next = null;
		node->prev = null;
		head = node;
		tail = node;
	}
	else
	{
		EntityNode* backof = null;
		if(node->backof != null)
		{
			EntityNode* aux;
			for(aux = head; aux != null; aux = aux->next)
			{
				if(node->backof == aux->entity)
				{
					backof = aux;
					break;
				}
			}
		}
		if(backof == null)
		{
			node->next = null;
			node->prev = tail;
			tail->next = node;
			tail = node;
		}
		else
		{
			if(backof == head)
				head = node;
			if(backof->prev)
				backof->prev->next = node;
			node->prev = backof->prev;
			node->next = backof;
			backof->prev = node;
		}
	}
	node->backof = null;
#endif
	// ...
	return next;
}

