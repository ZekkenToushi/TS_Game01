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
	
	//�X�e�[�W�U�蕪���B
	switch (Stage) {
	case 0:
		CreateStage0();
		break;
	default:
		CreateStage0();
	}
	
}


Game::~Game()
{
	m_instance = nullptr;
	
	//DeleteGO(m_field1);

}

void Game::CreateStage0() {
	//�t�B�[���h�̐����B
	m_field1 = NewGO<Field_1>();
	//�v���C���[�̍X�V�B
	m_player = NewGO<Player>();
	//�v���C�p�̃J�����X�V�B
	m_tsCamera = NewGO<tsCamera>();
	//���C�g�̍X�V�B
	m_light = NewGO<Light>();
	//�X���C���W�F�l���[�^�[�̍X�V�B
	m_slaveganerator = NewGO<SlaveGenerator>();
	//�s��}�l�[�W���[�̍X�V�B
	m_tracerowmanager = NewGO<TracerowManager>();
	//�G�W�F�l���[�^�[�̍X�V�B
	m_enemygenerator = NewGO<EnemyGenerator>();
}

void Game::Update()
{
	//constant buffer
}

void Game::Render()
{
	/*
	//�����_�����O���[�h�B
	EnRenderMode renderMode = enRenderMode_Normal;
	//�`��J�n�B
	g_graphicsEngine->BegineRender();

	///////////////////////////////////////////////
	//�܂��̓I�t�X�N���[�������_�����O
	///////////////////////////////////////////////
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	//���݂̃����_�����O�^�[�Q�b�g���o�b�N�A�b�v���Ă����B
	ID3D11RenderTargetView* oldRenderTargetView;
	ID3D11DepthStencilView* oldDepthStencilView;
	d3dDeviceContext->OMGetRenderTargets(1, &oldRenderTargetView, &oldDepthStencilView);
	//�����_�����O�^�[�Q�b�g��؂�ւ���B
	ID3D11RenderTargetView* rts[] = {
		//m_renderTargetView
		m_renderTarget.GetRenderTargetView()
	};
	d3dDeviceContext->OMSetRenderTargets(1, rts, m_renderTarget.GetDepthStensilView());
	//�����_�����O�^�[�Q�b�g���N���A�B
	float clearColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f }; //red,green,blue,alpha
	//d3dDeviceContext->ClearRenderTargetView(m_renderTargetView, clearColor);
	//d3dDeviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	m_renderTarget.ClearRenderTarget(clearColor);
	


	///////////////////////////////////////////////
	//��������I���X�N���[�������_�����O�B
	///////////////////////////////////////////////
	
	
	//�����_�����O�^�[�Q�b�g�����ɖ߂��B
	d3dDeviceContext->OMSetRenderTargets(1, &oldRenderTargetView, oldDepthStencilView);
	//�����_�����O�^�[�Q�b�g�ƃf�v�X�X�e���V���̎Q�ƃJ�E���^�������B
	oldRenderTargetView->Release();
	oldDepthStencilView->Release();


	//�`��I���B
	g_graphicsEngine->EndRender();
	*/
}

Game * Game::GetInstance()
{
	return m_instance;
}
