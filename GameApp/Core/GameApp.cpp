#include "GameApp.h"
#include "pch.h"
#include "Scene/Stages/FirstStage.h"
#include "../Engine/Scene/SceneManager.h"

void GameApp::Initialize()
{
	Scene* scene = new FirstStage("FirstStage");

	m_SceneManager->SetCurrentScene(scene);
	m_SceneManager->AddScene(scene);

}
