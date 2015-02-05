#include "ASceneBase.h"

using namespace Engine;

ASceneBase::ASceneBase()
{
}

ASceneBase::~ASceneBase()
{
}

void ASceneBase::Update(double deltaTime)
{
	for (std::vector<Engine::AObject*>::iterator i = objectList.begin(); i != objectList.end(); i++)
		(*i)->Update(deltaTime);
}

void ASceneBase::Draw()
{
	for (std::vector<Engine::AObject*>::iterator i = objectList.begin(); i != objectList.end(); i++)
		(*i)->Draw();
}

e_SceneState ASceneBase::GetSceneState() const
{
	return sceneState;
}

void ASceneBase::SetSceneState(e_SceneState val)
{
	sceneState = val;
}

ACameraBase* ASceneBase::GetMainCamera() const
{
	return mainCamera;
}
