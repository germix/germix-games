////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TmxMap
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TmxMap_h___
#define ___TmxMap_h___
#include <vector>
#include <map>
#include <string>

class TmxProperties;
class TmxImageLayer;
class TmxObjectLayer;
class TmxPatternLayer;
class TmxTilesetLayer;

namespace tinyxml2
{
	class XMLElement;
};

class TmxMap
{
	enum ORIENTATION
	{
		ORIENTATION_UNKNOWN = -1,
		ORIENTATION_ISOMETRIC = 1,
		ORIENTATION_ORTHOGONAL = 2,
	};
	int									orientation;
	int									mapWidth;
	int									mapHeight;
	int									tileWidth;
	int									tileHeight;
//	TmxProperties*						properties;
	std::map<std::string, std::string>	properties;
	std::vector<TmxImageLayer*>			imageLayers;
	std::vector<TmxObjectLayer*>		objectLayers;
	std::vector<TmxPatternLayer*>		patternLayers;
	std::vector<TmxTilesetLayer*>		tilesetLayers;
public:
	TmxMap(const char* fileName);
	~TmxMap();
public:
	inline int                                  getMapWidth() const { return mapWidth; }
	inline int                                  getMapHeight() const { return mapHeight; }
	inline int                                  getTileWidth() const { return tileWidth; }
	inline int                                  getTileHeight() const { return tileHeight; }
	inline int                                  getOrientation() const { return orientation; }
	const char*                                 getOrientationName() const;
	inline const std::vector<TmxImageLayer*>&   getImageLayers() const { return imageLayers; }
	inline const std::vector<TmxObjectLayer*>&  getObjectLayers() const { return objectLayers; }
	inline const std::vector<TmxPatternLayer*>& getPatternLayers() const { return patternLayers; }
	inline const std::vector<TmxTilesetLayer*>& getTilesetLayers() const { return tilesetLayers; }
	const TmxImageLayer*                        getImageLayer(const char* layerName) const;
	const TmxObjectLayer*                       getObjectLayer(const char* layerName) const;
	const TmxPatternLayer*                      getPatternLayer(const char* layerName) const;
	const TmxTilesetLayer*                      getTilesetLayer(const char* layerName) const;
	inline std::string                          getProperty(const char* name, const char* defValue = "") const
	{
		std::map<std::string,std::string>::const_iterator it = properties.find(name);
		if(it != properties.end())
			return it->second;
		return defValue;
	}
};

#endif
