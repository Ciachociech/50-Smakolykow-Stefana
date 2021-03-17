#include "DatInterpreter.h"

DatInterpreter::DatInterpreter(std::string filename) : filename(filename) {}

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

//save a best score to .dat file
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
	tempLine.push_back("0.7");

	data.push_back(tempLine);													//push back new line to data segment
	dumpData('A', extractData(), data);											//save file with new data
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
					VecString splitLine;											//vector with string of proper values
					std::string tempString;											//buffer line with separated values
					std::stringstream baseLine(stringLine);							//stringstream containing read line

					//for all text line split it to smaller values
					while (std::getline(baseLine, tempString, inLineSeparationChar)) { splitLine.push_back(tempString); }

					splitTable.push_back(splitLine);								//add splitted line to whole table

				} while (stringLine[stringLine.size() - 1] != sectionEndChar);
			}
		} while (stringLine[stringLine.size() - 1] != sectionEndChar || stringLine[stringLine.size() - 2] != sectionEndChar);
	}

	file.close();

	//delete ';' separated at the end of last line (if exists)
	int lastIndex = splitTable.size() - 1;
	if (splitTable[lastIndex][splitTable[lastIndex].size() - 1] == ";") { splitTable[lastIndex].pop_back(); }
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
					//savedLine.substr(0, savedLine.size());
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
