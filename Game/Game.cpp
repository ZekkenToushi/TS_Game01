#include "stdafx.h"
#include "Game.h"

Game* Game::m_instance = nullptr;

Game::Game()
{	
	if (m_instance != nullptr) {
		abort();
	}
	m_instance = this;

	//�����G���W���̍X�V�B
	g_physics.Update();
	
	//�v���C���[�̍X�V�B
	m_player = NewGO<Player>();
	//m_player->Update();
	//m_player->Draw();
	
	//�J�����̍X�V�B
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
