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
	//�J�������������B
	g_camera3D.SetFar(50000.0f);
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetPosition({ 0.0f, 100.0f, 300.0f });
	
	
	//�t�B�[���h�̐����B
	m_field1 = NewGO<Field_1>();
	//�v���C���[�̍X�V�B
	m_player = NewGO<Player>();
	//�v���C�p�̃J�����X�V�B
	m_tsCamera = NewGO<tsCamera>();
	//���C�g�̍X�V�B
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
