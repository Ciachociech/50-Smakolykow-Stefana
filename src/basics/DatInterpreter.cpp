#include "..\..\include\basics\DatInterpreter.h"

DatInterpreter::DatInterpreter(std::string filename, std::string version) : filename(filename), gameVersion(version) { forceUpdate(); }

DatInterpreter::~DatInterpreter() {}

//load a best score from .dat file
void DatInterpreter::load(int& hiscore)
{
	Vec2String data = extractData('A');											//extract data from 'A' (highscores) section

	//for each line in data file
	for (auto line : data)
	{
		//if current highscore is lower than highscore in certain line
		if (hiscore < std::stoi(line[2])) { hiscore = std::stoi(line[2]); }
	}
}

//load all scores from .dat file
void DatInterpreter::load(ScoreManager& sm)
{
	sm.exterminate();															//clear all previously loaded scores for not-doubling them
	Vec2String data = extractData('A');											//extract data from 'A' (highscores) section

	//for each line in data file
	for (auto line : data)
	{
		//build each of HistoryScore object and fill with values
		HistoryScore hiscore(std::stoi(line[2]));
		hiscore.setNickname(line[0]);
		hiscore.setGainedLevel(std::stoi(line[1]));
		hiscore.setCollectedTidbits(std::stoi(line[3]));
		hiscore.setDate(line[4]);
		hiscore.setVersion(line[5]);
		sm.addHistoryScore(hiscore);
	}
}

//load all options from .dat file
void DatInterpreter::load(OptionsManager& om)
{
	Vec2String data = extractData('B');

	//safely delete all saved options
	om.exterminate();
	//create some options
	om.addOption(0, 16, std::stoi(data[0][1]));
	om.addOption(0, 16, std::stoi(data[1][1]));
}

//deprecated method - save a best score to .dat file
void DatInterpreter::save(int level, int hiscore, int foundSnacks)
{
	Vec2String data = extractData('A');											//extract data from 'A' (highscores) section
	VecString tempLine;															//buffer for line to save

	//getting actual time
	time_t actualTime;
	tm fTime;
	time(&actualTime);
	localtime_s(&fTime, &actualTime);

	//gathering and saving data from previous game as a line of data
	tempLine.push_back("/NONAME/");
	tempLine.push_back(std::to_string(level));
	tempLine.push_back(std::to_string(hiscore));
	tempLine.push_back(std::to_string(foundSnacks));
	tempLine.push_back(std::to_string(fTime.tm_year + 1900) + "/" + std::to_string(fTime.tm_mon + 1) + "/" + std::to_string(fTime.tm_mday));
	tempLine.push_back(gameVersion);

	data.push_back(tempLine);													//push back new line to data segment
	dumpData('A', extractData(), data);											//save file with new data
}

//save a new score to .dat file
void DatInterpreter::save(HistoryScore hiscore)
{
	Vec2String data = extractData('A');											//extract data from 'A' (highscores) section
	VecString tempLine;															//buffer for line to save

	//getting actual time
	time_t actualTime;
	tm fTime;
	time(&actualTime);
	localtime_s(&fTime, &actualTime);

	//gathering and saving data from previous game as a line of data
	if (hiscore.getNickname().empty() || hiscore.getNickname() == "Stefan") { tempLine.push_back("/NONAME/"); }
	else { tempLine.push_back(hiscore.getNickname()); }
	tempLine.push_back(std::to_string(hiscore.getGainedLevel()));
	tempLine.push_back(std::to_string(hiscore.getScore()));
	tempLine.push_back(std::to_string(hiscore.getCollectedTidbits()));
	tempLine.push_back(std::to_string(fTime.tm_year + 1900) + "/" + std::to_string(fTime.tm_mon + 1) + "/" + std::to_string(fTime.tm_mday));
	tempLine.push_back(gameVersion);

	data.push_back(tempLine);													//push back new line to data segment
	dumpData('A', extractData(), data);											//save file with new data
}

//save current options value to .dat file
void DatInterpreter::save(OptionsManager& om)
{
	Vec2String data = extractData('B');											//extract data from 'B' (options) section

	for (int i = 0; i < data.size(); i++)
	{
		data[i][1] = (om.getOptionValue(i) != -1 ? std::to_string(om.getOptionValue(i)) : data[i][1]);
	}

	dumpData('B', extractData(), data);
}

//extract content from .dat file to vector of strings
VecString DatInterpreter::extractData()
{
	char inLineSeparationChar = '=', sectionEndChar = ';', sectionBeginChar = ':';	//buffer for read char
	VecString fileTable;															//table (vector of vectors of strings) of data from whole segment
	std::fstream file(filename);													//open .dat file

	//If file is good, manage it
	if (!file.fail())
	{
		std::string stringLine;														//string with line of .dat text
		//save whole file to vector until EOF (";;")
		do
		{
			file >> stringLine;														//load whole line from file
			fileTable.push_back(stringLine);										//append a line to table
		} while (stringLine[stringLine.size() - 1] != sectionEndChar || stringLine[stringLine.size() - 2] != sectionEndChar);
	}

	file.close();
	return fileTable;																//return file content as a vector of strings
}

//extract content from certain segment as a vector of vectors of strings (two-dimensional table of strings)
Vec2String DatInterpreter::extractData(char controlChar)
{
	char inLineSeparationChar = '=', sectionEndChar = ';', sectionBeginChar = ':';	//buffer for read char
	Vec2String splitTable;															//table (vector of vectors of strings) of data from whole segment
	std::fstream file(filename);													//open .dat file

	//If file is good, manage it
	if (!file.fail())
	{
		std::string stringLine;														//string with line of .dat text
		do
		{
			file >> stringLine;														//load whole line from file
			//if is proper control line (A - for best scores)
			if (stringLine[0] == sectionBeginChar && stringLine[1] == controlChar)
			{
				//for all lines which are in proper category
				do
				{
					file >> stringLine;

					if (stringLine[0] != ':')
					{
						VecString splitLine;											//vector with string of proper values
						std::string tempString;											//buffer line with separated values
						std::stringstream baseLine(stringLine);							//stringstream containing read line

						//for all text line split it to smaller values
						while (std::getline(baseLine, tempString, inLineSeparationChar)) { splitLine.push_back(tempString); }

						splitTable.push_back(splitLine);								//add splitted line to whole table
					}

				} while (stringLine[stringLine.size() - 1] != sectionEndChar);
			}
		} while (stringLine[stringLine.size() - 1] != sectionEndChar || stringLine[stringLine.size() - 2] != sectionEndChar);
	}

	file.close();

	//delete ';' separated at the end of last line (if exists)
	if (splitTable.size() != 0)
	{
		int lastIndex = splitTable.size() - 1;
		if (splitTable[lastIndex][splitTable[lastIndex].size() - 1] == ";") { splitTable[lastIndex].pop_back(); }
	}
	return splitTable;
}

//save file with new content at the certain segment and old at the rest of file
void DatInterpreter::dumpData(char controlChar, VecString oldData, Vec2String data)
{
	char inLineSeparationChar = '=', sectionEndChar = ';', sectionBeginChar = ':';	//buffer for read char
	Vec2String splitTable;															//table (vector of vectors of strings) of data from whole segment
	std::fstream file(filename);													//open .dat file

	//If file is good, manage it
	if (!file.fail())
	{
		//for each line on old file, line variable contains information about number of line to save from old line
		for (int line = 0; line < oldData.size(); line++)
		{
			file << oldData[line];													//save as before

			//if this line is a title of changed segment (containing "X:" - when 'X' is a letter of segment), rewrite it with new content
			if (oldData[line][0] == sectionBeginChar && oldData[line][1] == controlChar)
			{
				line++;
				//for each line of changed segment to save
				for (int dataLine = 0; dataLine < data.size(); dataLine++)
				{
					file << std::endl;
					std::stringstream savedStream;									//stringstream to prepare structure saveable to data

					//for each data from line
					for (int it = 0; it < data[dataLine].size(); it++)
					{
						savedStream << data[dataLine][it] << inLineSeparationChar;	//mixed data with inline separator sign
					}

					std::string savedLine = savedStream.str();						//extract string from stringstream
					file << savedLine;

				}

				file << sectionEndChar;												//at the end of segment add end sign

				while (oldData[line][oldData[line].size() - 1] != ';') { line++; }	//count the number of changed segment lines in old file
			}

			file << std::endl;
		}
	}
	file.close();
}

//check the latest version of .dat file and compare to newest standard, if existing file is obsolete, it will be updated
void DatInterpreter::forceUpdate()
{
	//get whole content of file
	VecString fileData = extractData();

	for (int i = 0; i < fileData.size(); i++)
	{
		//check a data type head
		if (fileData[i][0] == ':')
		{
			//check a version for specified data type
			switch (fileData[i][1])
			{
			case 'A':
			{
				//for version 0 just increase a version (only for separating implemented and not-implemented data types)
				if (fileData[i][2] == '0') { fileData[i] = ":A1-HISCORES-:"; }
				break;
			}
			case 'B':
			{
				//for version 0 add sound volume properties
				if (fileData[i][2] == '0')
				{
					fileData[i] = ":B1-OPTIONS-:";
					fileData.insert(fileData.begin() + i + 1, "BGM_VOLUME=8=");
					fileData.insert(fileData.begin() + i + 2, "SE_VOLUME=8=;");
				}
				break;
			}
			case 'C':
			{
				if (fileData[i][2] != menuVersion + '0') {}
				break;
			}
			case 'D':
			{
				if (fileData[i][2] != achievesVersion + '0') {}
				break;
			}
			default: { break; }
			}
		}
	}

	std::fstream file(filename);													//open .dat file
	//If file is good, manage it
	if (!file.fail())
	{
		for (int i = 0; i < fileData.size(); i++)
		{
			file << fileData[i] << std::endl;
		}
	}
	file.close();
}
