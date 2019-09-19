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
	
	//プレイヤーの更新。
	m_player = NewGO<Player>();
	//m_player->Update();
	//m_player->Draw();
	
	//カメラの更新。
	g_camera3D.Update();
}


Game::~Game()
{
	m_instance = nullptr;
}

void Game::Update()
{
}

void Game::Render()
{
}

Game * Game::GetInstance()
{
	return m_instance;
}
