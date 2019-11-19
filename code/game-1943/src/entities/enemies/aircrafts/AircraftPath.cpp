////////////////////////////////////////////////////////////////////////////////////////////////////
//
// AircraftPath
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/aircrafts/AircraftPath.h>
#include <src/Utils.h>

#include <mach/String.h>

AircraftPath::AircraftPath()
: refs(0)
, dataList()
, pathLength(0)
{
}
AircraftPath::~AircraftPath()
{
	for(unsigned int i = 0; i < dataList.size(); i++)
		delete dataList[i];
	dataList.clear();
}
double AircraftPath::length() const
{
	return pathLength;
}
bool AircraftPath::isEmpty() const
{
	return dataList.empty();
}
Vector2f AircraftPath::firstPoint() const
{
	return dataList.front()->pos;
}
AircraftPath::MOVE_DATA* AircraftPath::getDataFromDistance(double traveledDistance) const
{
	if(!dataList.empty())
	{
		MOVE_DATA* data = new MOVE_DATA();
		const PRIVATE_DATA* last = dataList.back();
		const PRIVATE_DATA* first = dataList.front();
		
		if(traveledDistance < 0.0)
		{
			data->pos = first->pos;
			data->angle = first->angle;
			return data;
		}
		else if(traveledDistance >= pathLength)
		{
			data->pos = Utils::getMoved(last->pos, last->angle, traveledDistance-pathLength);
			data->angle = last->angle;
			return data;
		}
		else
		{
			const PRIVATE_DATA* pd;		// prev data
			const PRIVATE_DATA* cd;		// current data
			double plen = 0.0;			// prev length
			double clen = 0.0;			// current length
			
			pd = first;
			for(unsigned int i = 1; i < dataList.size(); i++)
			{
				cd = dataList[i];
				clen += cd->length;
				if(traveledDistance >= plen && traveledDistance < clen)
				{
					data->pos = Utils::getMoved(pd->pos, cd->angle, traveledDistance-plen);
					data->angle = cd->angle;
					return data;
				}
				pd = cd;
				plen = clen;
			}
		}
		delete data;
	}
	return null;
}
void AircraftPath::addPoint(int x, int y)
{
	PRIVATE_DATA* data;
	
	if(dataList.empty())
		data = new PRIVATE_DATA(x, y);
	else
		data = new PRIVATE_DATA(x, y, dataList.back());

	dataList.push_back(data);
	pathLength += data->length;
}
AircraftPath* AircraftPath::createFromDescriptor(const String& strPoints, int dy)
{
	AircraftPath* path = new AircraftPath();
	std::vector<String> points = strPoints.split(" ");
	
	for(unsigned int i = 0; i < points.size(); i++)
	{
		std::vector<String> coords = points[i].split(",");
		
		if(coords.size() == 2)
		{
			path->addPoint(coords[0].toInt(), coords[1].toInt()+dy);
		}
		else
		{
			printf("Lista de punto del mapa no bien formado\n");
		}
	}
	return path;
}
AircraftPath* AircraftPath::createU(const Vector2f& initialPos, bool rightToLeft, int length, int width)
{
	AircraftPath* path = new AircraftPath();
	double degrees = 180;
	double tmp = 180/8;
	path->addPoint((int)initialPos.x,(int)initialPos.y);
	double endY = initialPos.y + length;
	double radius = width/2;
	
	if(rightToLeft)
	{
		Vector2f centerPos(initialPos.x - radius, endY);
		degrees = 0;
		while(degrees < 180)
		{
			double tx = centerPos.x + ((Math::cos(Math::toRadians(degrees))*radius));
			double ty = centerPos.y + ((Math::sin(Math::toRadians(degrees))*radius));
			path->addPoint((int)tx, (int)ty);
			
			degrees += tmp;
		}
		path->addPoint((int)(initialPos.x - radius*2), (int)initialPos.y);
	}
	else
	{
		Vector2f centerPos(initialPos.x + radius, endY);
		while(degrees > 0)
		{
			double tx = centerPos.x + ((Math::cos(Math::toRadians(degrees))*radius));
			double ty = centerPos.y + ((Math::sin(Math::toRadians(degrees))*radius));
			path->addPoint((int)tx, (int)ty);
			
			degrees -= tmp;
		}
		path->addPoint((int)(initialPos.x + radius*2), (int)initialPos.y);
	}
	return path;
}

