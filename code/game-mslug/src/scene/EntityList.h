////////////////////////////////////////////////////////////////////////////////////////////////////
//
// EntityList
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___EntityList_h___
#define ___EntityList_h___
#include <src/scene/Entity.h>

class Entity;
class EntityNode;

class EntityNode
{
public:
	EntityNode*	prev;
	EntityNode*	next;
	Entity*		entity;
	Entity*		backof;
public:
	EntityNode(Entity* e) : prev(0), next(0), entity(e), backof(null)
	{
	}
	~EntityNode()
	{
		if(entity)
			delete entity;
	}
};

class EntityList
{
public:
	EntityNode*		head;
	EntityNode*		tail;
public:
	EntityList();
	~EntityList();
public:
	//!
	//! Comprobar si la lista está vacío
	//!
	//! \return true|false
	//!
	bool empty() const
	{
		return (head == null);
	}
	//!
	//! Vaciar lista
	//!
	void clear();
	
	//!
	//! Buscar entidad
	//!
	//! \param e		Entidad
	//!
	//! \return			Node de la entidad
	//!
	EntityNode* find(Entity* e);
	
	//!
	//! Agregar una entidad a la lista
	//!
	//! \param e		Entidad
	//!
	void append(Entity* e);

	//!
	//! Agregar una entidad a la lista
	//!
	//! \param e		Entidad
	//! \param o		Entidad sobre la nueva entidad
	//!
	void append(Entity* e, Entity* o);
	
	//!
	//! Agregar las entidades de otra lista
	//!
	//! \param other	Lista
	//!
	void append(EntityList& other);

	//!
	//! Agregar una entidad a la lista desde otra lista
	//!
	//! \param other	Lista
	//! \paran node		Nodo
	//!
	//! \return			Nodo siguiente al nodo agregado con respecto a la lista 'other'
	//!
	EntityNode* append(EntityList& other, EntityNode* node);
};

#endif
