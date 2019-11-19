////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CollisionInfo
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___CollisionInfo_h___
#define ___CollisionInfo_h___

enum
{
	MAP_TERRAIN_SOLID		= 0x01,
	MAP_TERRAIN_TOPDOWN		= 0x02,
};
enum
{
	COLLISION_FLAG_LEFT		= 0x01,
	COLLISION_FLAG_RIGHT	= 0x02,
	COLLISION_FLAG_TOP		= 0x04,
	COLLISION_FLAG_BOTTOM	= 0x08,
};

class CollisionInfo
{
public:
	unsigned int	flags;
//	Vector2f		position;
//	Vector2f		velocity;
public:
	CollisionInfo() : flags(0)
	{
	}
	CollisionInfo(const CollisionInfo& o) : flags(o.flags)
//	CollisionInfo(const CollisionInfo& o) : flags(o.flags), position(o.position), velocity(o.velocity)
	{
	}
public:
	CollisionInfo& operator = (const CollisionInfo& o)
	{
		flags = o.flags;
//		position = o.position;
//		velocity = o.velocity;
		return *this;
	}
};

#endif
