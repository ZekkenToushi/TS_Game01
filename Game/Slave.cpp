#include "stdafx.h"
#include "Slave.h"
#include "Game.h"

Slave::Slave()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/suraimu01.cmo");

	//�L�����N�^�[�R���g���[���[���������B
	CVector3 pos = m_position;
	
	m_charaCon.Init(
		20.0,			//���a�B 
		100.0f,			//�����B
		pos		//�����ʒu�B
	);
	
}


Slave::~Slave()
{
}

void Slave::Update()
{
	Search();
	Order();
	Move();
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3::One());
}

void Slave::Render()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void Slave::Search()
{
	//���ߔ���B
	if (g_pad->IsPress(enButtonY)) {
		state = Tuizyuu;
	}
	if (g_pad->IsPress(enButtonX)) {
		state = Taiki;
		m_speed = CVector3::Zero();
	}
	//�Ǐ]�B
	if (Tuizyuu == state) {
		//�v���C���[�Ƃ̃x�N�g�����߂ĉ��Z�B�v���C���[�Ǐ]�B
		//MasterPosition = Game::GetInstance()->m_player->GetPosition();
		//CVector3 kyori = MasterPosition - m_position;
		//kyori.y = 0.0f;
		//kyori.Normalize();
		//m_speed.x = kyori.x * SpeedMagnification;
		//m_speed.z = kyori.z * SpeedMagnification;

		//Tracerow���Q�Ƃ��ĕ��ԁB3  
		for (int i = 0; i < Game::GetInstance()->m_player->Getrowcount; i++) {
			Tracerow* tracerow = &Game::GetInstance()->m_player->Gettracerow(i);
			if (tracerow->GetReservation == true) {
				m_speed = tracerow->Getposition() 
					* SpeedMagnification;


			}



		}
	}
}

void Slave::Order()
{


}

void Slave::Move()
{
	//�ꎞ�I�d��
	m_speed.y -= 30.00f;

	m_position = m_charaCon.Execute(1.0f / 60, m_speed);

}