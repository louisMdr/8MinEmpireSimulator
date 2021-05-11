#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Map.h"


class MapLoader
{
private:
	void invalidMapFile(const std::string);
	void addMapEdges(Map&, std::vector<std::string>);
	bool validateFileExtension(const std::string&);
	bool validateFileData(const std::string&);
	std::vector<std::string> splitLine(std::string);
	std::vector<std::string> retriveAdjList(std::string);

public:
	MapLoader();
	MapLoader(const MapLoader& mapCopy);
	~MapLoader();
	MapLoader& operator=(const MapLoader&);
	friend std::ostream& operator<<(std::ostream&, const MapLoader&);
	Map* generateMap(const std::string&);
	void createRegion(const std::vector<std::string>, Map&);
	void createContinent(const std::vector<std::string>, Map&);
};
