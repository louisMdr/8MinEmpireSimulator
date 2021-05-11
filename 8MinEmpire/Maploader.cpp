#include "MapLoader.h"
#include <iostream>
#include <string>
#include <ostream>
#include <vector>

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::getline;
using std::ifstream;
using std::ostream;

//Nothing to initialize
MapLoader::MapLoader()
{
	cout << "The Default Constructor has been called" << endl;
}

//Nothing to copy
MapLoader::MapLoader(const MapLoader& mapCopy)
{
	cout << "The Copy Constructor has been called" << endl;
}

//Nothing to copy
MapLoader& MapLoader::operator=(const MapLoader& mapCopy)
{
	cout << "The equals operator has been called" << endl;
	return *this;
}

//Nothing to delete
MapLoader::~MapLoader()
{

}

//Overrides the ostream << operator to print default message
ostream& operator<<(ostream& output, const MapLoader& map)
{
	output << "This is a MapLoader Object..." << endl;

	return output;
}

//Makes initial checks to see if the file is valid
//Goes through file information and checks for validity (ADD WHEN MAP IS DONE)
//Returns reference to a Map Object (NEED TO ADD ONCE MAP IS DONE)
Map* MapLoader::generateMap(const string& file)
{
	Map * map = new Map();

	string line;
	ifstream inputStream;
	vector<string> rawData;
	vector<string> adjTerritories;

	//REMOVE LATER (for testing)
	cout << endl << "Attempting to open: " << file << endl;

	//Confirms that input file is valid.
	if (file.empty())
	{
		invalidMapFile("ERROR: No File Detected");
	}
	else if (!validateFileExtension(file))
	{
		invalidMapFile("ERROR: File Extension Is Invalid Or Name Contains a '.'");
	}
	else
	{
		inputStream.open(file);
	}

	//Checks if file is empty on open.
	//Reads normally otherwise.
	if (inputStream.peek() == EOF)
	{
		invalidMapFile("ERROR: Map File Is Empty Or Does Not Exist");
	}
	else
	{
		while (!inputStream.eof())
		{
			getline(inputStream, line);


			if (!validateFileData(line))
			{
				invalidMapFile("ERROR: The Format Of The File Does Not Follow Conventions");
			}

			//data is retrived here
			rawData = splitLine(line);

			if (rawData.empty())
			{
				continue;
			}


			if (rawData.front() == "true")
			{
				if (rawData.size() != 6)
				{
					invalidMapFile("ERROR: Insufficient Or Too Much Data To Create Map");
				}

				adjTerritories.push_back(rawData.back());

				createRegion(rawData, *map);

				//THIS IS FOR TESTING
				//cout << map.getVectorOfTerritories()->back()->getCountry() << endl;
			}
			else
			{

				if (rawData.size() != 2)
				{
					invalidMapFile("ERROR: Insufficient Or Too Much Data To Create Map");
				}

				createContinent(rawData, *map);

				//THIS IS FOR TESTING
				//cout << map.getVectorOfContinents()->back()->getContinent() << endl;
			}

		}
	}

	cout << endl << "Map object has successfully been created\n" << endl;

	inputStream.close();

	//At this point all of the continents and territories and continents have been created
	//All that is left is to create the edges between eeach region
	if (adjTerritories.size() != map->getVectorOfTerritories()->size())
	{
		invalidMapFile("ERROR: Adjacent Nodes are not set for at least one node");
	}
	else
	{
		addMapEdges(*map, adjTerritories);
	}

	if (map->validate())
	{
		return map;
	}
	else
	{
		invalidMapFile("ERROR: The created map is not a valid!!!");
	}
}

//Method Called if map file is invalid.
//Prints error and then terminates program.
void MapLoader::invalidMapFile(const string error)
{
	cout << "\n" << error << endl;
	cout << "Exiting the game..." << endl;
	exit(0);
}

//Method checks if the map file has the correct file type extension.
bool MapLoader::validateFileExtension(const string& fileName)
{
	int extensionPos(fileName.find("."));
	string fileExtension(fileName.substr(extensionPos + 1));

	if (fileExtension != "MAP")
	{
		return false;
	}

	return true;
}

//Checks each line of the input file for valid formatting
bool MapLoader::validateFileData(const string& lineData)
{
	int tagSeperator(lineData.find("/"));
	string tag(lineData.substr(0, tagSeperator));

	if (tag != "INFO" && tag != "CON" && tag != "REG")
	{
		return false;
	}

	return true;
}

//Breaks up each of the lines in the map file
vector<string> MapLoader::splitLine(string lineData)
{
	vector<string> data;
	int tagSeperator(lineData.find("/"));
	string tag(lineData.substr(0, tagSeperator));

	//Takes the tag and decides if it is a territory or continent
	if (tag == "CON")
	{
		data.push_back("false");
	}
	else if (tag == "REG")
	{
		data.push_back("true");
	}
	else
	{
		return vector<string>();
	}


	lineData.erase(0, tagSeperator + 1);

	//Takes apart the rest of the data to see what is up
	int dataSeperator = lineData.find_first_of(';', 1);
	string placeholder = lineData.substr(0, dataSeperator);

	while (placeholder != "")
	{
		data.push_back(placeholder);

		lineData.erase(0, dataSeperator + 1);
		dataSeperator = lineData.find_first_of(";");
		placeholder = lineData.substr(0, dataSeperator);
	}


	return data;
}

void MapLoader::createRegion(const vector<string> rawData, Map& map)
{
	string regionName = rawData[1];
	string regionContinentName = rawData[2];
	string regionOwnername = rawData[4];

	string regionArmyCountStr = rawData[3];
	int regionArmyCountInt = stoi(regionArmyCountStr);

	map.addToMap(new Territory(new bool(true), new string(regionName), new string(regionContinentName),
		new int(regionArmyCountInt), new string(regionOwnername), new vector<Territory*>()));
}

void MapLoader::createContinent(const vector<string> rawData, Map& map)
{
	string continentName = rawData[1];

	map.addToMap(new Territory(new bool(false), new string(continentName)));
}

//This is not an efficient method of adding them, I will think
//of a more efficient method later
void MapLoader::addMapEdges(Map& map, vector<string> adjs)
{
	vector<Territory*>* territories = map.getVectorOfTerritories();
	vector<string> adjList;
	Territory* t;

	for (int i = 0; i < territories->size(); i++)
	{
		adjList = retriveAdjList(adjs.at(i));
		t = territories->at(i);

		for (vector<string>::iterator k = adjList.begin(); k != adjList.end(); k++)
		{
			for (int j = 0; j < territories->size(); j++)
			{
				Territory* temp = territories->at(j);

				if (temp->getCountry() == *k)
				{
					map.addEdge(t, temp);
				}
			}
		}

	}
}

vector<string> MapLoader::retriveAdjList(string adjStr)
{
	vector<string> adjList;
	int dataSeperator;
	string placeholder;

	adjStr = adjStr.substr(1);

	while (adjStr != "")
	{

		dataSeperator = adjStr.find(',');

		if (dataSeperator == -1)
		{
			dataSeperator = adjStr.find('}');
		}

		placeholder = adjStr.substr(0, dataSeperator);

		adjList.push_back(placeholder);
		adjStr.erase(0, dataSeperator + 1);
	}

	return adjList;
}

