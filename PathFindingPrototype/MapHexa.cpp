#include "MapHexa.h"


MapHexa::MapHexa(Engine::ASceneBase& scene)
	: scene(scene),
	  hexaStart(NULL),
	  hexaEnd(NULL),
	  mapLengh(10),
	  mapHeight(10)
{
	hexas = new Hexa[mapHeight * mapLengh];
}


MapHexa::~MapHexa()
{
	delete[] hexas;
}

void MapHexa::Init()
{
	debugFont.loadFromFile("arial.ttf");

	Engine::Vector2i coord;
	for (coord.y = 0; coord.y < mapHeight; coord.y++)
		for (coord.x = 0; coord.x < mapLengh; coord.x++)
			hexas[coord.y * mapLengh + coord.x].init(*this, coord);

	selectedType = blocking;
}

void MapHexa::Update(double deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
		selectedType = normal;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
		selectedType = blocking;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
		selectedType = start;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
		selectedType = end;

	hexaHeigth = scene.GetMainCamera()->GetZoom() * 2;
	hexaWidth = SQRT3_2 * hexaHeigth;

	Engine::Vector2i mouseGridCoordinate = GetMouseGridCoordinate();
	if (DoesHexaExist(mouseGridCoordinate.x, mouseGridCoordinate.y) &&
		&(hexas[mouseGridCoordinate.y * mapLengh + mouseGridCoordinate.x]) != lastOverHexa)
	{
		if (lastOverHexa != NULL)
			lastOverHexa->OnMouseLeaveOver();
		hexas[mouseGridCoordinate.y * mapLengh + mouseGridCoordinate.x].OnMouseEnterOver();
		lastOverHexa = &(hexas[mouseGridCoordinate.y * mapLengh + mouseGridCoordinate.x]);
	}

	if (lastOverHexa != NULL && sf::Mouse::isButtonPressed(sf::Mouse::Left) && lastOverHexa->GetType() != selectedType)
	{
		if (selectedType == HexaType::start)
		{
			if (hexaStart != NULL)
				hexaStart->SetType(HexaType::normal);
			hexaStart = lastOverHexa;
		}
		if (selectedType == HexaType::end)
		{
			if (hexaEnd != NULL)
				hexaEnd->SetType(HexaType::normal);
			hexaEnd = lastOverHexa;
		}
		lastOverHexa->SetType(selectedType);
		if (hexaStart && hexaEnd)
			CalculatePath();
	}
}

void MapHexa::Draw()
{
	for (int i = 0; i < mapHeight * mapLengh; i++)
		hexas[i].Draw(Engine::Game::Singleton->GetWindow(), *scene.GetMainCamera(), *this);
}

bool MapHexa::DoesHexaExist(int x, int y) const
{
	return x >= 0 && x < 10 && 
		   y >= 0 && y < 10;
}

Engine::Vector2i MapHexa::GetMouseGridCoordinate() const
{

	Engine::Vector2d worldMousePos = Engine::Vector2d((float)sf::Mouse::getPosition(Engine::Game::Singleton->GetWindow()).x + scene.GetMainCamera()->GetPosition().x, 
													  (float)sf::Mouse::getPosition(Engine::Game::Singleton->GetWindow()).y + scene.GetMainCamera()->GetPosition().y);
	
	Engine::Vector2i AproxGridCoord = Engine::Vector2i((int)((worldMousePos.x / hexaWidth - worldMousePos.y * 2 / 3 / hexaHeigth) + 0.5),
														(int)((worldMousePos.y * 4 / 3 / hexaHeigth) + 0.5));
	Engine::Vector2i	nerbyHex[5];
	nerbyHex[0].x = AproxGridCoord.x;		nerbyHex[0].y = AproxGridCoord.y;
	nerbyHex[1].x = AproxGridCoord.x - 1;	nerbyHex[1].y = AproxGridCoord.y;
	nerbyHex[2].x = AproxGridCoord.x + 1;	nerbyHex[2].y = AproxGridCoord.y;
	nerbyHex[3].x = AproxGridCoord.x;		nerbyHex[3].y = AproxGridCoord.y - 1;
	nerbyHex[4].x = AproxGridCoord.x;		nerbyHex[4].y = AproxGridCoord.y + 1;

	Engine::Vector2d orthoCoordHexPos = Engine::Vector2d(nerbyHex[0].x * GetHexaWidth() + nerbyHex[0].y * 0.5 * GetHexaWidth(),
														 nerbyHex[0].y * 0.75 * GetHexaHeight());

	double shortestDist = orthoCoordHexPos.Distance(worldMousePos);
	int idxShortestDist = 0;
	for (int i = 1; i < 5; i++)
	{
		orthoCoordHexPos = Engine::Vector2d(nerbyHex[i].x * GetHexaWidth() + nerbyHex[i].y * 0.5 * GetHexaWidth(),
											nerbyHex[i].y * 0.75 * GetHexaHeight());

		double currentDist = orthoCoordHexPos.Distance(worldMousePos);
		if (currentDist < shortestDist)
		{
			shortestDist = currentDist;
			idxShortestDist = i;
		}
	}

	return Engine::Vector2i(nerbyHex[idxShortestDist].x, nerbyHex[idxShortestDist].y);
}

double MapHexa::GetHexaHeight() const
{
	return hexaHeigth;
}

double MapHexa::GetHexaWidth() const
{
	return hexaWidth;
}

std::list<Hexa*> MapHexa::CalculatePath()
{
	std::list<Hexa*> closedlist;
	std::list<Hexa*> openlist;
	Hexa*			 currentHex;
	Hexa**			 neighbors;

	/////////// Debug //////////////////
	for (int i = 0; i < mapLengh * mapHeight; i++)
	{
		hexas[i].gScore = -1;
		hexas[i].hScore = -1;
	}
	////////////////////////////////////

	for (std::list<Hexa*>::iterator i = lastPath.begin(); i != lastPath.end(); i++)
		(*i)->isPath = false;
	lastPath.clear();

	openlist.push_front(hexaStart);
	hexaStart->gScore = 0;
	hexaStart->hScore = HeuristicCostEstimate(hexaStart);
	hexaStart->cameFrom = NULL;
	while (openlist.size() != 0)
	{
		currentHex = PopLowestFScore(openlist);
		if (currentHex == hexaEnd)
			return ReconstructPath();
		closedlist.push_back(currentHex);
		neighbors = GetNeighbor(currentHex);
		for (int i = 0; i < 6; i++)
		{
			if (neighbors[i] == NULL || std::find(closedlist.begin(), closedlist.end(), neighbors[i]) != closedlist.end())
				continue;
			double tmpGScore = currentHex->gScore + 1;
			bool notInOpenList = std::find(openlist.begin(), openlist.end(), neighbors[i]) == openlist.end();
			if (neighbors[i]->GetType() != HexaType::blocking && (notInOpenList || tmpGScore < neighbors[i]->gScore))
			{
				neighbors[i]->cameFrom = currentHex;
				neighbors[i]->gScore = tmpGScore;
				neighbors[i]->hScore = HeuristicCostEstimate(neighbors[i]);
				if (notInOpenList)
					openlist.push_front(neighbors[i]);
			}
		}
		delete neighbors;
	}
	return std::list<Hexa*>();
}

Hexa* MapHexa::PopLowestFScore(std::list<Hexa*>& openlist)
{
	Hexa* lowestHexa = openlist.front();
	double lowestValue = lowestHexa->GetFScore();
	std::list<Hexa*>::iterator i = ++openlist.begin();
	for (; i != openlist.end(); i++)
	{
		double fscore = (*i)->GetFScore();
		if (fscore < lowestValue)
		{
			lowestValue = fscore;
			lowestHexa = *i;
		}
	}
	openlist.remove(lowestHexa);
	return lowestHexa;
}

Hexa** MapHexa::GetNeighbor(Hexa* currentHex) const
{
	Hexa** neighbors = new Hexa*[6];

	neighbors[0] = NULL;
	neighbors[1] = NULL;
	neighbors[2] = NULL;
	neighbors[3] = NULL;
	neighbors[4] = NULL;
	neighbors[5] = NULL;

	if (currentHex->GetCoordinate().y > 0)
		neighbors[0] = &(hexas[(currentHex->GetCoordinate().y - 1) * mapLengh + currentHex->GetCoordinate().x]);
	if (currentHex->GetCoordinate().y < mapHeight - 1)
		neighbors[1] = &(hexas[(currentHex->GetCoordinate().y + 1) * mapLengh + currentHex->GetCoordinate().x]);
	if (currentHex->GetCoordinate().x > 0)
		neighbors[2] = &(hexas[currentHex->GetCoordinate().y * mapLengh + currentHex->GetCoordinate().x - 1]);
	if (currentHex->GetCoordinate().x < mapLengh - 1)
		neighbors[3] = &(hexas[currentHex->GetCoordinate().y * mapLengh + currentHex->GetCoordinate().x + 1]);
	if (currentHex->GetCoordinate().y > 0 && currentHex->GetCoordinate().x < mapLengh - 1)
		neighbors[4] = &(hexas[(currentHex->GetCoordinate().y - 1) * mapLengh + currentHex->GetCoordinate().x + 1]);
	if (currentHex->GetCoordinate().y < mapHeight - 1 && currentHex->GetCoordinate().x > 0)
		neighbors[5] = &(hexas[(currentHex->GetCoordinate().y + 1) * mapLengh + currentHex->GetCoordinate().x - 1]);

	return neighbors;
}

std::list<Hexa*> MapHexa::ReconstructPath()
{
	std::list<Hexa*> out;
	out.push_front(hexaEnd);
	Hexa* currentHexa = hexaEnd->cameFrom;
	while (currentHexa != hexaStart && currentHexa != NULL)
	{
		out.push_front(currentHexa);
		lastPath.push_front(currentHexa);
		currentHexa->isPath = true;
		currentHexa = currentHexa->cameFrom;
	}
	out.push_front(hexaStart);
	return out;
}

double MapHexa::HeuristicCostEstimate(Hexa* hexa) const
{
	int x1 = hexa->GetCoordinate().x;
	int y1 = hexa->GetCoordinate().y;
	int z1 = x1 + y1;

	int x2 = hexaEnd->GetCoordinate().x;
	int y2 = hexaEnd->GetCoordinate().y;
	int z2 = x2 + y2;

	return (abs(x1 - x2) + abs(y1 - y2) + abs(z1 - z2)) / 2;
}
