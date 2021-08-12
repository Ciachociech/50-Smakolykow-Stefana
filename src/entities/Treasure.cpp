#include "..\..\include\entities\Treasure.h"

Treasure::Treasure(treasureType type) : Graph(), type(type) {}

Treasure::Treasure(int x, int y, treasureType type) : Graph(x, y), type(type) {}

Treasure::~Treasure() {}

//load a texture at the certain scale and file
bool Treasure::loadFromFile(float scaleX, float scaleY, std::string filepath, SDL_Renderer* renderer)
{
	return Graph::loadFromFile(scaleX, scaleY, filepath, renderer);			//returns a status of generating (true - if object is valid, false - if not)
}

//return type of treasure
treasureType Treasure::getType() { return this->type; }

//return the path to certain treasure type
std::string Treasure::getAssetPath()
{
	switch (type)
	{
	case treasureType::carrot:			{ baseScore = 40;	return std::string("marchewka.png");	break; }
	case treasureType::mniszek:			{ baseScore = 40;	return std::string("mniszek.png");		break; }
	case treasureType::salad:			{ baseScore = 40;	return std::string("salata.png");		break; }
	case treasureType::banana:			{ baseScore = 40;	return std::string("banan.png");		break; }
	case treasureType::strawBerry:		{ baseScore = 40;	return std::string("truskawka.png");	break; }
	case treasureType::dill:			{ baseScore = 120;	return std::string("koperek.png");		break; }
	case treasureType::wildRose:		{ baseScore = 40;	return std::string("dzikaroza.png");	break; }
	case treasureType::bamboo:			{ baseScore = 80;	return std::string("bamboo.png");		break; }
	case treasureType::daisy:			{ baseScore = 80;	return std::string("stokrotka.png");	break; }
	case treasureType::eggplant:		{ baseScore = 40;	return std::string("baklazan.png");		break; }
	case treasureType::alcea:			{ baseScore = 120;	return std::string("malwa.png");		break; }
	case treasureType::humulus:			{ baseScore = 120;	return std::string("chmiel.png");		break; }
	case treasureType::quince:			{ baseScore = 40;	return std::string("pigwa.png");		break; }
	case treasureType::asparagus:		{ baseScore = 80;	return std::string("szparagi.png");		break; }
	case treasureType::kiwi:			{ baseScore = 40;	return std::string("kiwi.png");			break; }
	case treasureType::parsnip:			{ baseScore = 80;	return std::string("pasternak.png");	break; }
	case treasureType::cornflower:		{ baseScore = 40;	return std::string("chaber.png");		break; }
	case treasureType::timothy:			{ baseScore = 120;	return std::string("tymotka.png");		break; }
	case treasureType::clover3:			{ baseScore = 30;	return std::string("koniczyna3.png");	break; }
	case treasureType::clover4:			{ baseScore = 40;	return std::string("koniczyna4.png");	break; }
	case treasureType::rutabaga:		{ baseScore = 40;	return std::string("brukiew.png");		break; }
	case treasureType::cauliflower:		{ baseScore = 40;	return std::string("kalafior.png");		break; }
	case treasureType::broccoli:		{ baseScore = 40;	return std::string("brokul.png");		break; }
	case treasureType::hibiscus:		{ baseScore = 80;	return std::string("hibiskus.png");		break; }
	case treasureType::apple:			{ baseScore = 40;	return std::string("jablko.png");		break; }
	case treasureType::kohlrabi:		{ baseScore = 80;	return std::string("kalarepa.png");		break; }
	case treasureType::forsythia:		{ baseScore = 80;	return std::string("forsycja.png");		break; }
	case treasureType::rose:			{ baseScore = 40;	return std::string("roza.png");			break; }
	case treasureType::silverweed:		{ baseScore = 40;	return std::string("pieciornik.png");	break; }

	case treasureType::dignine:			{ baseScore = 50;	return std::string("kopanina.png");		break; }
	case treasureType::nosescan:		{ baseScore = 50;	return std::string("nososkan.png");		break; }
	case treasureType::stubborntunism:	{ baseScore = 50;	return std::string("uportunizm.png");	break; }

	case treasureType::none: default:	{ baseScore = 0;	return std::string();					break; }
	}
}

//Return the values of visibilty oraz treasure score
bool Treasure::getIsHidden() { return isHidden; }

int Treasure::getBaseScore() { return this->baseScore; }

//Set a value of visibility flag
void Treasure::setIsShown() { isHidden = false; }
