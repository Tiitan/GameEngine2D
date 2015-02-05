#pragma once

#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include "ASceneBase.h"

namespace Engine
{
	class Game
	{
	public:
		static Game*		Singleton;

	private:
		sf::RenderWindow	window;
		sf::Clock			clockGameLoop;
		double				deltaTime;
		double				frameRateLimit;

		std::vector<ASceneBase*> sceneList;

	public:
		Game(int Height, int Width, char* name);
		~Game();

		void Init();
		void MainLoop();
		void Draw();
		void Update(double deltaTime);
		void Wait();

		void AddScene(ASceneBase* scene, bool isPopup = false);

		sf::RenderWindow& GetWindow();
		double GetFrameRateLimit() const;
		void SetFrameRateLimit(double value);
		
	};
}