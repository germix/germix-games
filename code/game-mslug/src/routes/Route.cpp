////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Route | Ruta
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/routes/Route.h>
#include <ctype.h>
#include <mach/Math.h>
#include <src/routes/RouteCoordinate.h>

class Route::Segment
{
public:
	double px;
	double py;
	double angle;
	double length;
public:
	Segment(int x, int y, Segment* last)
	{
		this->px = x;
		this->py = y;
		if(!last)
		{
			this->angle = 0;
			this->length = 0;
		}
		else
		{
			double dx = (px - last->px);
			double dy = (py - last->py);
			this->angle = Math::atan2(dy, dx);
			this->length = Math::sqrt((dx*dx)+(dy*dy));
		}
	}
};

Route::Route(int dx, int dy, const char* coords)
{
	int x;
	int y;
	Segment* seg = null;
	const char* ptr = coords;
	
	routeLength = 0;
	while(*ptr != '\0')
	{
		x = atoi(ptr);
		if(*ptr == '-') ptr++;
		while(isalnum(*ptr)) ptr++;		// Digitos
		ptr++;							// ','
		y = atoi(ptr);
		if(*ptr == '-') ptr++;
		while(isalnum(*ptr)) ptr++;		// Digitos
		
		while(*ptr == ' ') ptr++;

		routeSegments.push_back(seg = new Segment(dx+x, dy+y, seg));
		routeLength += seg->length;
	}
}
Route::~Route()
{
	for(unsigned int i = 0; i < routeSegments.size(); i++)
		delete routeSegments[i];

	routeSegments.clear();
}
bool Route::getFirstCoordinate(RouteCoordinate* coord) const
{
	if(!isEmpty())
	{
		Segment* seg = routeSegments[0];
		coord->x = seg->px;
		coord->y = seg->py;
		coord->angle = seg->angle;
		coord->distance = 0;
		coord->finished = false;
		return true;
	}
	return false;
}
bool Route::getCoordinate(int segment, RouteCoordinate* coord) const
{
	Segment* seg = routeSegments[segment];
	double   dist = 0;
	
	for(int i = 0; i <= segment; i++)
		dist += routeSegments[i]->length;

	coord->x = seg->px;
	coord->y = seg->py;
	coord->angle = seg->angle;
	coord->distance = dist;
	coord->finished = false;
	return true;
}
bool Route::getCoordinateFromTraveled(double traveledDistance, RouteCoordinate* coord) const
{
	if(!isEmpty())
	{
		if(traveledDistance < 0.0)
		{
			//
			// Caso 1: Antes de comenzar la ruta
			//
			Segment* seg = routeSegments[0];
			
			coord->x = seg->px;
			coord->y = seg->py;
			coord->angle = seg->angle;
			coord->distance = 0;
			coord->finished = false;
			return true;
		}
		else if(traveledDistance >= routeLength)
		{
			//
			// Caso 2: Cuando se sale de la ruta
			//
			Segment* seg = routeSegments[routeSegments.size()-1];
			
			double l = (traveledDistance-routeLength);
			double x = seg->px + (Math::cos(seg->angle)*l);
			double y = seg->py + (Math::sin(seg->angle)*l);
			
			coord->x = x;
			coord->y = y;
			coord->angle = seg->angle;
			coord->distance = traveledDistance;
			coord->finished = true;
			return true;
		}
		else
		{
			//
			// Caso 3: Dentro de la ruta
			//
			Segment* pseg;			// prev segment
			Segment* cseg;			// current segment
			double plen = 0.0;		// prev length
			double clen = 0.0;		// current length
			
			pseg = routeSegments[0];
			for(unsigned int i = 1; i < routeSegments.size(); i++)
			{
				cseg = routeSegments[i];
				clen += cseg->length;
				if(traveledDistance >= plen && traveledDistance < clen)
				{
					double l = (traveledDistance-plen);
					double x = pseg->px + (Math::cos(cseg->angle)*l);
					double y = pseg->py + (Math::sin(cseg->angle)*l);
					
					coord->x = x;
					coord->y = y;
					coord->angle = cseg->angle;
					coord->distance = traveledDistance;
					coord->finished = false;
					return true;
				}
				pseg = cseg;
				plen = clen;
			}
		}
	}
	return false;
}