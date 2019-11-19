////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Route | Ruta
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Route_h___
#define ___Route_h___
#include <vector>

struct RouteCoordinate;

class Route
{
	class Segment;

	double routeLength;
	std::vector<Segment*> routeSegments;
public:
	Route(int dx, int dy, const char* coords);
	~Route();
public:
	bool   isEmpty() const { return routeSegments.empty(); }
	double getLength() const { routeLength; }
	bool   getFirstCoordinate(RouteCoordinate* coord) const;
	bool   getCoordinate(int segment, RouteCoordinate* coord) const;
	bool   getCoordinateFromTraveled(double traveledDistance, RouteCoordinate* coord) const;
};

#endif
