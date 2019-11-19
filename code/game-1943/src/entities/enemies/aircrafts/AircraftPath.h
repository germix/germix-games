////////////////////////////////////////////////////////////////////////////////////////////////////
//
// AircraftPath
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___AircraftPath_h___
#define ___AircraftPath_h___
#include <vector>

#include <mach/Math.h>
#include <mach/Vector2f.h>

class String;

class AircraftPath
{
public:
	struct MOVE_DATA
	{
		Vector2f	pos;
		double		angle;
	};
private:
	struct PRIVATE_DATA
	{
		Vector2f	pos;
		double		angle;
		double		length;
		
		PRIVATE_DATA(int x, int y)
			: pos(x, y)
			, angle(0)
			, length(0)
		{
		}
		PRIVATE_DATA(int x, int y, const PRIVATE_DATA* last)
			: pos(x, y)
		{
			double dx = (pos.x - last->pos.x);
			double dy = (pos.y - last->pos.y);
			angle = Math::atan2(dy, dx);
			length = Math::sqrt((dx*dx)+(dy*dy));
		}
	};
	int							refs;
	std::vector<PRIVATE_DATA*>	dataList;
	double						pathLength;
private:
	AircraftPath();
	~AircraftPath();
public:
	void ref()
	{
		refs++;
	}
	void unref()
	{
		if(--refs == 0)
			delete this;
	}
	double length() const;
	bool isEmpty() const;
	Vector2f firstPoint() const;
	AircraftPath::MOVE_DATA* getDataFromDistance(double traveledDistance) const;
private:
	void addPoint(int x, int y);
public:
	static AircraftPath* createFromDescriptor(const String& strPoints, int dy);
	static AircraftPath* createU(const Vector2f& initialPos, bool rightToLeft, int length, int width);
};

#endif
