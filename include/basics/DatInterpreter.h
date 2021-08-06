#pragma once

#include "..\external_dependencies.h"
#include "..\managers\OptionsManager.h"
#include "..\managers\ScoreManager.h"

typedef std::vector<std::string> VecString;
typedef std::vector<std::vector<std::string>> Vec2String;

class DatInterpreter
{
public:
	DatInterpreter(std::string filename, std::string version);
	virtual ~DatInterpreter();

	void load(int& hiscore);
	void load(ScoreManager& sm);
	void load(OptionsManager& om);

	void save(int level, int hiscore, int foundSnacks);
	void save(HistoryScore hiscore);
	void save(OptionsManager& om);

	VecString extractData();
	Vec2String extractData(char controlChar);
	void dumpData(char controlChar, VecString oldData, Vec2String data);
private:
	std::string filename;											//name and path of .dat file
	std::string gameVersion;										//version of game

	int hiscoresVersion = 1, optionsVersion = 1, menuVersion = 0, achievesVersion = 0;

	void forceUpdate();
};

