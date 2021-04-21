#pragma once

#include "..\external_dependencies.h"

typedef std::vector<std::string> VecString;
typedef std::vector<std::vector<std::string>> Vec2String;

class DatInterpreter
{
public:
	DatInterpreter(std::string filename, std::string version);
	virtual ~DatInterpreter();

	void load(int& hiscore);
	//void load(ScoreManager sm);

	void save(int level, int hiscore, int foundSnacks);

	VecString extractData();
	Vec2String extractData(char controlChar);
	void dumpData(char controlChar, VecString oldData, Vec2String data);
private:
	std::string filename;											//name and path of .dat file
	std::string version;											//version of game
};

