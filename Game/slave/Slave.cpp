#include "stdafx.h"
#include "Slave.h"
#include "Game.h"
#include "math.h"//��Βl�������Ŏg�p�B
Slave::Slave()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/suraimu01.cmo");

	//�L�����N�^�[�R���g���[���[���������B
	CVector3 pos = m_position;
	
	m_charaCon.Init(
		30.0,			//���a�B 
		20.0f,			//�����B
		pos		//�����ʒu�B
	);
	
}


Slave::~Slave()
{
}

void Slave::Update()
{
	Search();
	Move();
	Statemanagement();
	//�L�����R���B
	m_position = m_charaCon.Execute(1.0f / 60, m_speed);
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
	if (g_pad->IsPress(enButtonY)&&
		state != Tuizyuu) {
		state = Mukau;
	}
	if (g_pad->IsPress(enButtonX)) {
		state = Taiki;
		m_speed = CVector3::Zero();
	}
}


void Slave::Move()
{
	//�ꎞ�I�d��
	m_speed.y -= 30.00f;

	//�����ɓ�������I�I�i�v���C���[�ƂԂ������̂ŃX�s�[�h�x�N�g���ɉe�������悤�Ɂj�B
	//�v���C���[�Ƃ̃x�N�g�����߂āB
	m_masterposition = Game::GetInstance()->m_player->Getposition();
	m_kyori = m_masterposition - m_position;
	//�����v���C���[�Ƃ̋��������ȉ��Ȃ�i�Ԃ����Ă���j�B
	if (fabs(m_kyori.x) < m_distancejudgment.x&&
		fabs(m_kyori.z) < m_distancejudgment.z) {
		//�v���C���[�̈ړ��x�N�g���������ɉ��Z���ĉ����o�����悤�ɂ���B
		m_speed += Game::GetInstance()->m_player->Getspeed()/3;
	
	}

	//���C�v�Z�B
	m_speed = m_speed * m_friction;

}

void Slave::Statemanagement()
{
	switch (state) {
	case Taiki://���̏�ɑҋ@�B
		Taiki_processing();
		break;
	case Mukau://�v���C���[�ɌĂ΂ꂽ�̂ŗ�ɕ��ԁB
		Mukau_processing();
		break;
	case Tuizyuu://��ɕ��񂾂̂Ńv���C���[�ɂ��Ă����B
		Tuizyuu_processing();
		break;
	//case 3:

	}

}

void Slave::Taiki_processing()
{
	//�����U�����ꂽ�甽������B

}

void Slave::Mukau_processing()
{
	//Tracerow���Q�Ƃ��ĕ��ԁB
	//�z�񕪉�
	for (int i = 0; i < Game::GetInstance()->m_player->Getrowcount(); i++) {
		//�w��ii�j���ꂽ��̃A�h���X�擾�B
		Tracerow* tracerow = Game::GetInstance()->m_player->Gettracerow(i);

		//���̔z��|�C���g�Ɏ�������邩���ׂ�B
		if (tracerow->GetStay() == false//��񂪂��Ȃ��B
			) {
			//�v���C���[�Ƃ̃x�N�g�����߂ĉ��Z�B
			m_kyori = tracerow->Getposition() - m_position;
			CVector3 kyoriNormalize = m_kyori;
			kyoriNormalize.y = 0.0f;
			kyoriNormalize.Normalize();
			m_speed.x = kyoriNormalize.x * m_SpeedMagnification;
			m_speed.z = kyoriNormalize.z * m_SpeedMagnification;

			//�قڂ��̃|�C���g�ɍs�����̂�
			if (fabs(m_kyori.x) < m_alignmentcompletiondistance.x &&
				fabs(m_kyori.z) < m_alignmentcompletiondistance.z) {
				//Stay��錾�B
				tracerow->SetStay(true);
				//���񊮗����܂��������I�I�i���񊮗������̂Ŏ����̏�Ԃ�Ǐ]�ɕς���B
				state = Tuizyuu;
				//���������񊮗������ꏊ�o���Ă����B
				m_TracerowNum = i;
				//tomeru
				m_speed = { 0.0f,0.0f,0.0f };
			}
			//�I�������B
			i = Game::GetInstance()->m_player->Getrowcount();
		}


	}
}

void Slave::Tuizyuu_processing()
{
	//�w�肳�ꂽ��̃A�h���X�擾�B
	Tracerow* tracerow = Game::GetInstance()->m_player->Gettracerow(m_TracerowNum);
	//��Ƃ̃x�N�g�����߂āB
	m_kyori = tracerow->Getposition() - m_position;
	CVector3 kyoriNormalize = m_kyori;
	kyoriNormalize.y = 0.0f;
	kyoriNormalize.Normalize();
	//���Z�v���C���[�Ǐ]�B
	m_speed.x = kyoriNormalize.x * m_SpeedMagnification;
	m_speed.z = kyoriNormalize.z * m_SpeedMagnification;

	//�قڂ��̃|�C���g�ɍs�����̂ŁB
	if (fabs(m_kyori.x) < m_alignmentcompletiondistance.x &&
		fabs(m_kyori.z) < m_alignmentcompletiondistance.z) {
		//�~�܂�B
		m_speed = { 0.0f,0.0f,0.0f };
	}
}
