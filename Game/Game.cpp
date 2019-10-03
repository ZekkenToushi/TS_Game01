#include "stdafx.h"
#include "Game.h"

Game* Game::m_instance = nullptr;

Game::Game()
{	
	if (m_instance != nullptr) {
		abort();
	}
	m_instance = this;

	//物理エンジンの更新。
	g_physics.Update();
	//カメラを初期化。
	g_camera3D.SetFar(50000.0f);
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetPosition({ 0.0f, 100.0f, 300.0f });
	
	
	//フィールドの生成。
	m_field1 = NewGO<Field_1>();
	//プレイヤーの更新。
	m_player = NewGO<Player>();
	//プレイ用のカメラ更新。
	m_tsCamera = NewGO<tsCamera>();
	//ライトの更新。
	m_light = NewGO<Light>();
}


Game::~Game()
{
	m_instance = nullptr;
}

void Game::Update()
{
	//constant buffer
}

void Game::Render()
{
}

Game * Game::GetInstance()
{
	return m_instance;
}
