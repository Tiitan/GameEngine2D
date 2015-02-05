#include "Game.h"

using namespace Engine;

Game* Game::Singleton = nullptr;

Game::Game(int Width = 640, int Height = 480, char* name = "default name") :
	window(sf::VideoMode(Width, Height), name)
{
	Singleton = this;
}


Game::~Game()
{
	Singleton = nullptr;
}

void Game::Init()
{
	for (std::vector<ASceneBase*>::iterator i = sceneList.begin(); i != sceneList.end(); i++)
		(*i)->Init();

	SetFrameRateLimit(60);
	clockGameLoop.restart();
}

void Game::MainLoop()
{
	while (window.isOpen())
	{
		deltaTime = clockGameLoop.getElapsedTime().asSeconds();
		clockGameLoop.restart();

		Update(deltaTime);
		Draw();
	}
}

void Game::Update(double deltaTime)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}

	for (std::vector<ASceneBase*>::iterator i = sceneList.begin(); i != sceneList.end(); i++)
		(*i)->Update(deltaTime);
}

void Game::Draw()
{
	window.clear();

	for (std::vector<ASceneBase*>::iterator i = sceneList.begin(); i != sceneList.end(); i++)
		(*i)->Draw();

	window.display();
}

sf::RenderWindow& Game::GetWindow()
{
	return window;
}

void Game::AddScene(ASceneBase* scene, bool isPopup)
{
	if (sceneList.size() != 0)
	{
		if (isPopup)
			sceneList.back()->SetSceneState(visible);
		else
			sceneList.back()->SetSceneState(hidden);
	}
	scene->SetSceneState(top);
	sceneList.push_back(scene);
}

double Game::GetFrameRateLimit() const
{
	return frameRateLimit;
}

void Game::SetFrameRateLimit(double value)
{
	frameRateLimit = value;
	window.setFramerateLimit((int)frameRateLimit);
}
