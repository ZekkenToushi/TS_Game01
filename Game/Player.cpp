#include "stdafx.h"
#include "Player.h"
#include "Game.h"

Player::Player()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/unityChan.cmo");

	//�L�����N�^�[�R���g���[���[���������B
	//m_charaCon.Init(
	//	20.0,			//���a�B 
	//	50.0f,			//�����B
	//	m_position	//�����ʒu�B
	//);

}


Player::~Player()
{
	//g_goMgr.DeleteGameObject(this);
}

void Player::Update()
{
	Move();
}
void Player::Render()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
}

void Player::Move()
{
	//�J�����O�����A�E�������擾�B
	CVector3 CameraForward = Game::GetInstance()->m_tsCamera->GetForward();
	CVector3 CameraRightd = Game::GetInstance()->m_tsCamera->GetRight();
	Game::GetInstance()->m_tsCamera->GetForward();

	//XZ���ʂł̑O�������A�E�����ɕϊ�����B
	CameraForward.y = 0.0f;
	CameraForward.Normalize();
	CameraRightd.y = 0.0f;
	CameraRightd.Normalize();

	//�A�i���O�X�e�B�b�N�̓��͗ʂ��擾�A�|�W�V�����ւ̓K�p�B
	//m_position.z -= g_pad->GetLStickYF()*5.0f;
	//m_position.x -= g_pad->GetLStickXF()*5.0f;
	m_position -= CameraForward * g_pad->GetLStickYF()*5.0f;
	m_position -= CameraRightd * g_pad->GetLStickXF()*5.0f;



	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3::One());
}
