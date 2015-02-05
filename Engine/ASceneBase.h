#pragma once

#include <Vector>
#include "AObject.h"
#include "ACameraBase.h"

namespace Engine
{
	enum e_SceneState
	{
		top,
		visible,
		hidden,
		removed
	};

	class ASceneBase
	{
	protected:
		std::vector<AObject*>	objectList;
		e_SceneState			sceneState;
		ACameraBase*			mainCamera;

	public:
		ASceneBase();
		virtual ~ASceneBase();

		virtual void Init() = 0;
		virtual void Update(double deltaTime);
		virtual void Draw();

		e_SceneState	GetSceneState() const;
		void			SetSceneState(e_SceneState val);
		ACameraBase*	GetMainCamera() const;
	};
}