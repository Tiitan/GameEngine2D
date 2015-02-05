#include "SceneTestMap.h"


SceneTestMap::SceneTestMap()
	: map(*this)
{
}


SceneTestMap::~SceneTestMap()
{
}

void SceneTestMap::Init()
{
	camera.Init();
	mainCamera = &camera;
	objectList.push_back(&camera);

	map.Init();
	objectList.push_back(&map);

	debugFont.loadFromFile("arial.ttf");
	debugText.setFont(debugFont);
	debugText.setCharacterSize(14);
	debugText.setColor(sf::Color::Color(255, 128, 0, 255));
}

void SceneTestMap::Update(double deltaTime)
{
	Engine::ASceneBase::Update(deltaTime);

	std::stringstream ss;
	ss << "FPS: " << std::setprecision(3) << 1 / deltaTime;
	debugText.setString(ss.str());
}

void SceneTestMap::Draw()
{
	Engine::ASceneBase::Draw();
	Engine::Game::Singleton->GetWindow().draw(debugText);
}
