﻿#include "GameApp.h"
#include "pch.h"
#include "Scene/Stages/FirstStage.h"
#include "../Engine/Scene/SceneManager.h"
#include "../Engine/Renderer/FontRenderer.h"

void GameApp::Initialize()
{
	Scene* scene = new FirstStage("FirstStage", m_FontRenderer);

	m_SceneManager->SetCurrentScene(scene);
	m_SceneManager->AddScene(scene);

	m_FontRenderer->LoadFont("../Resources/Fonts/NotoSansKR-Regular.ttf", 32.0f);
}
