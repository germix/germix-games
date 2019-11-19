////////////////////////////////////////////////////////////////////////////////////////////////////
//
// AStar
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___AStar_h___
#define ___AStar_h___
#include <src/Direction.h>

#include <list>
#include <vector>

class Scene;
class CollisionMap;

class AStar
{
	struct NodeInfo
	{
		int f;
		int g;
		int h;
		int index;
		NodeInfo* parent;
		
		NodeInfo()
			: f(0)
			, g(0)
			, h(0)
			, index(-1)
			, parent(null)
		{
			AStar::nodesInfoCount++;
		}
		NodeInfo(int index, int g, int h)
		{
			this->index = index;
			this->g = g;
			this->h = h;
			this->f = g+h;
			AStar::nodesInfoCount++;
		}
		NodeInfo(NodeInfo* parent, int index, int g, int h)
		{
			this->index = index;
			this->g = g;
			this->h = h;
			this->f = g+h;
			this->parent = parent;
			AStar::nodesInfoCount++;
		}
		~NodeInfo()
		{
			AStar::nodesInfoCount--;
		}
		int getId() const { return index; }
		NodeInfo* getParent() const { return parent; }
		int getCostG() const { return g + ((parent != null) ? parent->g : 0); }
		int getCostH() const { return h + ((parent != null) ? parent->h : 0); }
	};
public:
	struct PathNode
	{
		int x;
		int y;
		PathNode() : x(0), y(0)
		{
		}
		PathNode(int _x, int _y) : x(_x), y(_y)
		{
		}
		PathNode(const PathNode& o) : x(o.x), y(o.y)
		{
		}
		PathNode& operator = (const PathNode& o)
		{
			x = o.x;
			y = o.y;
			return *this;
		}
	};
	CollisionMap*			cmap;
	int						width;
	int						height;
	int						startIndex;
	int						targetIndex;

	std::list<NodeInfo*>	openList;
	std::list<NodeInfo*>	closedList;
	
	static int nodesInfoCount;
public:
	AStar();
	~AStar();
public:
	std::vector<PathNode> find(Scene* scene, int startX, int startY, int targetX, int targetY, DIRECTION dir);
private:
	int getNodeX(NodeInfo* node) const { return (node->index%width); }
	int getNodeY(NodeInfo* node) const { return (node->index/width); }
	NodeInfo* getStart() const;
	std::list<NodeInfo*> getSuccessors(NodeInfo* N) const;
	
	std::vector<PathNode> generatePath();
	
	NodeInfo* findNode(const std::list<NodeInfo*>& list, int s) const;

	void clearList(std::list<NodeInfo*>& list) const
	{
		for(std::list<NodeInfo*>::const_iterator it = list.begin(); it != list.end(); it++)
			delete *it;
		list.clear();
	}
	
	int calcManhattanDistance(int index) const;
	
	int calcManhattanDistance(int source, int destination) const;
};

#endif

