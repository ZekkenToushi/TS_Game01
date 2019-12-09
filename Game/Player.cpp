#include "stdafx.h"
#include "Player.h"
#include "Game.h"

Player::Player()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/unityChan.cmo");

	//�L�����N�^�[�R���g���[���[���������B
	m_charaCon.Init(
		50.0,			//���a�B 
		50.0f,			//�����B
		m_position	//�����ʒu�B
	);

}


Player::~Player()
{
	//g_goMgr.DeleteGameObject(this);
}

void Player::Update()
{
	Move();
	Rotation();
	Tracerowset();
	

	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
	
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
	
	//XZ���ʂł̑O�������A�E�����ɕϊ�����B
	CameraForward.y = 0.0f;
	CameraForward.Normalize();
	CameraRightd.y = 0.0f;
	CameraRightd.Normalize();

	//�A�i���O�X�e�B�b�N�̓��͗ʂ��擾�A�|�W�V�����ւ̓K�p�B
	m_speed = CameraForward * g_pad->GetLStickYF()*1200.0f;
	m_speed += CameraRightd * g_pad->GetLStickXF()*1200.0f;

	//�ꎞ�I�d��
	m_speed.y -= 1000.00f;
	

	//XZ�����̈ړ����x���N���A
	if (g_pad->GetLStickXF() == 0.0f) {

		m_speed.x = 0.0f;
	}
	if (g_pad->GetLStickYF() == 0.0f) {
		m_speed.z = 0.0f;
	}
	//�W�����v�B
	if (g_pad->IsPress(enButtonB)) {
		m_speed.y += 2000.0f;
	}

	m_position = m_charaCon.Execute(1.0f / 60, m_speed);
	
}

void Player::Rotation()
{
	//�������B
	float Rot = atan2(m_playerforward, m_playerside);
	CQuaternion qRot;
	qRot.SetRotation(CVector3::AxisY(), Rot);

	//���͂������
	if (m_speed.x != 0.0f || m_speed.z != 0.0f)
	{
		//��]��K�p�B
		m_rotation = qRot;
		//�i�s�����ۑ��B
		m_playerforward = m_speed.x;
		m_playerside = m_speed.z;
	}
	
}

void Player::Tracerowset()
{
	for (int i = 0; i < rowcount; i++) {
		//�z�񕪃|�C���^�����B
		Tracerow* m_narabe = &tracerow[i];
		//Num��Position�Z�b�g����B
		m_narabe->SetNum(i);
		m_narabe->SetTargetPosition(m_position);
		m_narabe->Update();
		m_narabe->Render();
	}
	
}
