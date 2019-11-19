////////////////////////////////////////////////////////////////////////////////////////////////////
//
// AStar
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/pathfinding/AStar.h>
#include <src/Scene.h>
#include <src/CollisionMap.h>

#include <mach/Math.h>

#include <algorithm>

int AStar::nodesInfoCount = 0;	// TODO

AStar::AStar()
{
}
AStar::~AStar()
{
}
std::vector<AStar::PathNode> AStar::find(Scene* scene, int startX, int startY, int targetX, int targetY, DIRECTION dir)
{
	cmap = scene->getCollisionMap();
	width = cmap->getWidth();
	height = cmap->getHeight();
	startIndex = cmap->getTileIndex8x8(startX, startY);
	targetIndex = cmap->getTileIndex8x8(targetX, targetY);
	
	//
	// ...
	//
	NodeInfo* A;
	NodeInfo* N;
	bool exit = false;
	bool firstMove = true;
	
	// ...
	nodesInfoCount = 0;
	
	//
	// Etapa 1: Inicializar
	//
	A = getStart();
	openList.push_back(A);
	
	while(!exit)
	{
		//
		// Etapa 2: Detectar fallo
		//
		if(openList.empty())
		{
			exit = true;
		}
		else
		{
			//
			// Etapa 3: Seleccionar el nodo 'N' con el coste mínimo, el que tenga el menor valor de 'f'
			//          Mover 'N' de la lista abierta 'openList' a la lista cerrada 'closedList'
			//
			{
				N = null;
				for(std::list<NodeInfo*>::const_iterator it = openList.begin(); it != openList.end(); it++)
				{
					NodeInfo* tmp = *it;
					if(N == null) N = tmp;
					else if(tmp->f < N->f) N = tmp;
				}
				openList.remove(N);
				closedList.push_back(N);
			}
			//
			// Etapa 4: Si 'N' coincide con el nodo final, finalizar correctamente
			//
			if(N->index == targetIndex)
			{
				exit = true;
				
				if(!closedList.empty())
				{
					return generatePath();
				}
			}
			else
			{
				//
				// Etapa 5: Expandir para cada sucesor 'S' de 'N'
				//
				std::list<NodeInfo*> successors = getSuccessors(N);
				
				for(std::list<NodeInfo*>::const_iterator it = successors.begin(); it != successors.end(); it++)
				{
					NodeInfo* S = *it;
					if(firstMove)
					{
						if(getNodeY(S) > getNodeY(N)) if(dir == DIRECTION_UP) { delete S; continue; }
						if(getNodeY(S) < getNodeY(N)) if(dir == DIRECTION_DOWN) { delete S; continue; }
						if(getNodeX(S) > getNodeX(N)) if(dir == DIRECTION_LEFT) { delete S; continue; }
						if(getNodeX(S) < getNodeX(N)) if(dir == DIRECTION_RIGHT) { delete S; continue; }
					}
					int possibleG = S->getCostG();
					
					NodeInfo* inOpenListS = findNode(openList, S->index);
					NodeInfo* inClosedListS = findNode(closedList, S->index);
					
					if(inOpenListS || inClosedListS)
					{
						if(inOpenListS != null)
						{
							if(possibleG < inOpenListS->g)
							{
								openList.remove(inOpenListS);
								delete inOpenListS;
							}
						}
						else if(inClosedListS != null)
						{
							if(possibleG < inClosedListS->g)
							{
								closedList.remove(inClosedListS);
								delete inClosedListS;
							}
						}
						delete S;
					}
					else
					{
						openList.push_back(S);
					}
				}
				firstMove = false;
			}
		}
	}
	clearList(openList);
	clearList(closedList);
	return std::vector<PathNode>();
}
AStar::NodeInfo* AStar::getStart() const
{
	return new NodeInfo(null, startIndex, 0, calcManhattanDistance(startIndex));
}
std::list<AStar::NodeInfo*> AStar::getSuccessors(NodeInfo* N) const
{
	//
	// Obtener los sucesores de N, o sea, los vecinos
	//
	std::list<NodeInfo*> successors;
	
	int blockX = getNodeX(N);
	int blockY = getNodeY(N);
	int blockIndex = -1;
	
	for(int dx = -1; dx <= 1; dx++)
	{
		for(int dy = -1; dy <= 1; dy++)
		{
			//
			// Evitar movimiento en el mismo bloque
			//
			if(dx == 0 && dy == 0) continue;
			
			//
			// Evitar movimientos en los bloques diagonales
			//
			if(dx != 0 && dy != 0) continue;
			
			if(-1 != (blockIndex = cmap->getWalkable(blockX+dx, blockY+dy, 0x1)))
			{
				successors.push_back(
						new NodeInfo(
								N,
								blockIndex,
								calcManhattanDistance(N->index, blockIndex),
								calcManhattanDistance(blockIndex, targetIndex)));
			}
		}
	}
	return successors;
}
std::vector<AStar::PathNode> AStar::generatePath()
{
	std::vector<PathNode> path;
	NodeInfo* n = closedList.back();
	int       ts = cmap->getTileSize();
	while(n->getParent() != null)
	{
		NodeInfo* p = findNode(closedList, n->getParent()->getId());
		int       px = getNodeX(p);
		int       py = getNodeY(p);
		
		path.push_back(PathNode(px*ts, py*ts));
		n = p;
	}
	std::reverse(path.begin(), path.end());
	
	printf("openList.size(): %d\n", openList.size());
	printf("closedList.size(): %d\n", closedList.size());
	printf("AAA: nodesInfoCount=%d\n", nodesInfoCount);
	
	clearList(openList);
	clearList(closedList);
	
	printf("BBB: nodesInfoCount=%d\n", nodesInfoCount);

	printf("\n");

	
	return path;
#if 0


#endif
}
AStar::NodeInfo* AStar::findNode(const std::list<NodeInfo*>& list, int s) const
{
	for(std::list<NodeInfo*>::const_iterator it = list.begin(); it != list.end(); it++)
	{
		NodeInfo* tmp = *it;
		if(tmp->index == s)
		{
			return tmp;
		}
	}
	return null;
}
int AStar::calcManhattanDistance(int index) const
{
	//
	// http://es.wikipedia.org/wiki/Geometr%C3%ADa_del_taxista
	// http://xlinux.nist.gov/dads//HTML/manhattanDistance.html
	//
	int srcX = index%width;
	int srcY = index/width;
	int dstX = targetIndex%width;
	int dstY = targetIndex/width;

	return Math::abs(srcX-dstX) + Math::abs(srcY-dstY);
}
int AStar::calcManhattanDistance(int source, int destination) const
{
	//
	// http://es.wikipedia.org/wiki/Geometr%C3%ADa_del_taxista
	// http://xlinux.nist.gov/dads//HTML/manhattanDistance.html
	//
	int srcX = source%width;
	int srcY = source/width;
	int dstX = destination%width;
	int dstY = destination/width;

	return Math::abs(srcX-dstX) + Math::abs(srcY-dstY);
}
