////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ScreenManager
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <gamelib/ScreenManager.h>

#include <stdio.h>

ScreenManager::ScreenManager()
{
	stack = 0;
}
ScreenManager::~ScreenManager()
{
}
void ScreenManager::init(Machine* mach, Screen* s)
{
	// Insertar pantalla
	stack = new ScreenNode(s, stack);
	// Inicializar pantalla actual
	//stack->screen->show(mach);
}
bool ScreenManager::update(Machine* mach, double dt)
{
	Screen* next = 0;
	ScreenNode* node = 0;
	static ScreenNode* lastNode = 0;
	
#if 0
	//
	// Actualizar la pantalla actual
	//
	stack->screen->update(mach, dt);
	
	//
	// Pedir pantalla siguiente
	//
	next = stack->screen->getNext();
	
	//
	// Eliminar las pantallas removibles
	//
	while(stack && stack->screen->isRemovable())
	{
		node = stack;
		stack = stack->prev;
		node->screen->hide(mach);
		delete node;
	}
	//
	// Si hay una nueva pantalla, agregarla a la pila
	//
	if(next)
	{
		if(stack)
			stack->screen->hide(mach);

		stack = new ScreenNode(next, stack);
		stack->screen->show(mach);
	}
	else if(stack != current)
	{
		if(stack)
			stack->screen->show(mach);
	}
	//
	// Si no hay más pantallas, retornar false, caso contrario, true
	//
	if(!stack)
		return false;
	return true;
#else

	next = stack->screen->getNext();
	if(!next)
	{
		stack->screen->update(mach, dt);
		
		//
		// Eliminar las pantallas removibles
		//
		if(stack->screen->isRemovable())
		{
			next = stack->screen->getNext();
			while(stack && stack->screen->isRemovable())
			{
				// ...
				node = stack;
				stack = stack->prev;

				if(!next && stack)
				{
					// Pedir pantalla siguiente
					next = stack->screen->getNext();
				}
				node->screen->hide(mach);
				delete node;
			}
		}
		else
		{
			// Pedir pantalla siguiente
			next = stack->screen->getNext();
		}
		if(next)
			printf("NEXT: %p\n", next);
	}

	if(next)
	{
		Screen* subNext;
		if(stack && !node)
			stack->screen->hide(mach);

		while(null != (subNext = next->getNext()))
		{
			stack = new ScreenNode(next, stack);
			next = subNext;
		}

		stack = new ScreenNode(next, stack);
		stack->screen->show(mach);
	}
	else if(node)
	{
		if(stack)
			stack->screen->show(mach);
	}
	else
	{
		if(!lastNode)
			stack->screen->show(mach);
	}
	/*
	else if(node)
	{
		if(stack)
			stack->screen->show(mach);
	}
	*/
	lastNode = stack;

	//
	// Si no hay más pantallas, retornar false, caso contrario, true
	//
	if(!stack)
		return false;
	return true;
#endif
}
void ScreenManager::render(Machine* mach, Graphics* gr)
{
	stack->screen->render(mach, gr);
}
