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
	
	m_slaveCon.Init(
		30.0,			//���a�B 
		20.0f,			//�����B
		pos		//�����ʒu�B
	);
	
}


Slave::~Slave()
{
	RequestDelete();
}

void Slave::Update()
{
	Search();
	StateManagement();
	Move();
	
	//�L�����R���B
	m_position = m_slaveCon.Execute(1.0f / 60, m_speed + m_force);
	m_force *= 0.5f;
	
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
	//���ߔ���B��
	if (g_pad->IsPress(enButtonX)&&
		state != Tuizyuu) {
		state = Mukau;
	}
	if (g_pad->IsPress(enButtonA)) {
		state = Taiki;
		m_speed = CVector3::Zero();
	}

	
}


void Slave::Move()
{
	//�d�͂����ȏォ����Ə���˂�������ׁB
	if (m_speed.y > -1000.0f) {
		//�d�́B
		m_speed.y += m_gravity / 60.0f;
	}
	//���C�v�Z�B
	//m_speed = m_speed * m_friction;

	////�����ɓ�������I�I�i�v���C���[�ƂԂ������̂ŃX�s�[�h�x�N�g���ɉe�������悤�Ɂj�B
	////�v���C���[�Ƃ̃x�N�g�����߂āB
	//m_masterposition = Game::GetInstance()->m_player->GetPosition();
	//CVector3 kyori = m_masterposition - m_position;
	////�����v���C���[�Ƃ̋��������ȉ��Ȃ�i�Ԃ����Ă���j�B
	//if (fabs(kyori.x) < m_distancejudgment.
	//	fabs(kyori.z) < m_distancejudgment.z) {
	//	//�v���C���[�̈ړ��x�N�g���������ɉ��Z���ĉ����o�����悤�ɂ���B
	//	m_speed += Game::GetInstance()->m_player->Getspeed()/3;
	//}

	//���̃X���C���Əd�Ȃ��Ă�ꍇ�悯��B
	//���ݏ������Ă��鐔��for�����񂷁B
	for (int i = 1;i < Game::GetInstance()->m_slaveganerator->GetSlaveCount();i++) {
		//�����ȊO�B
		if (i != m_mynumber) {
			Slave* slave = Game::GetInstance()->m_slaveganerator->GetSlave(i);
			CVector3 kyori = slave->GetPosition() - m_position;
			if (kyori.Length() < m_personalSpace) {
				float Leave = m_personalSpace - kyori.Length();
				kyori.Normalize();
				m_speed += kyori * fabs(Leave) *-1.0f;
			}

		}
	}
	//�v���C���[��������i�������悤�ɁB
	CVector3 kyori = Game::GetInstance()->m_player->GetPosition() - m_position;
	if (kyori.Length() < m_personalSpace) {
		float Leave = kyori.Length() - m_personalSpace;
		kyori.Normalize();
		m_speed += kyori * Leave;
	}

	//���S����B
	if (slave.HP <= 0) {
		RequestDelete();
	};

}

void Slave::Buttobu(CVector3 point)
{
	//�������鏀���B
	m_markpoint = point;
	m_buttobi = m_markpoint - m_position;
	//m_buttobi.y = m_markpoint.Length()/2;

	//�������ԁB
	float time = 1.50f;
	//�}�[�J�[�ƌ��݈ʒu��y�����B
	float y = m_markpoint.y - m_position.y;
	//y(����) =v(�����x)t(����) - 1/2gt^2�@����
	float init_vy = (y + 0.5f * -m_gravity*(time*time)) / time;
	//XY���ړ��B
	m_speed.y = init_vy;
	//XZ���ړ��B
	float vxz = m_buttobi.Length() / time;
	auto v = m_buttobi;
	v.y = 0.0f;
	v.Normalize();
	v *= vxz;
	m_speed.x = v.x;
	m_speed.z = v.z;
	//�X�e�[�g�ύX�B
	state = Nagerare;
	//�����������Ă����Ȃ��󂯂�
	Tracerow* tracerow = Game::GetInstance()->m_tracerowmanager->Gettracerow(m_TracerowNum);
	
	tracerow->SetStay(false, m_mynumber);
	tracerow->SetReservation(false);
}

void Slave::StateManagement()
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
	case Nagerare://���l�͓������Ă��܂��B
		Nagerare_processing();
		break;
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

	//�����ҏ����^����B
	/*
	for (int i = 0; i < Game::GetInstance()->m_player->Getrowcount(); i++) {
		//�w��ii�j���ꂽ��̃A�h���X�擾�B
		Tracerow* tracerow = Game::GetInstance()->m_player->Gettracerow(i);

		//���̔z��|�C���g�Ɏ�������邩���ׂ�B
		if (tracerow->GetStay() == false//��񂪂��Ȃ��B
			) {
			//�v���C���[�Ƃ̃x�N�g�����߂ĉ��Z�B
			CVector3 kyori = tracerow->Getposition() - m_position;
			CVector3 kyoriNormalize = kyori;
			kyoriNormalize.y = 0.0f;
			kyoriNormalize.Normalize();
			m_speed.x = kyoriNormalize.x * m_SpeedMagnification;
			m_speed.z = kyoriNormalize.z * m_SpeedMagnification;

			//�قڂ��̃|�C���g�ɍs�����̂�
			if (fabs(kyori.x) < m_alignmentcompletiondistance.x &&
				fabs(kyori.z) < m_alignmentcompletiondistance.z) {
				//Stay��錾�B
				tracerow->SetStay(true);
				//���񊮗����܂��������I�I�i���񊮗������̂Ŏ����̏�Ԃ�Ǐ]�ɕς���B
				state = Tuizyuu;
				//���������񊮗������ꏊ�o���Ă����B
				m_TracerowNum = i;
				//�ǐՃX�s�[�h���Z�b�g�B
				m_speed = { 0.0f,0.0f,0.0f };
			}
			//�I�������B
			i = Game::GetInstance()->m_player->GetMaxrow();
		}
	}
	*/
	//�\��^����B
	for (int i = 0; i < Game::GetInstance()->m_tracerowmanager->GetMaxrow(); i++) {
		//�w��ii�j���ꂽ��̃A�h���X�擾�B
		Tracerow* tracerow = Game::GetInstance()->m_tracerowmanager->Gettracerow(i);

		//���̔z��|�C���g�Ɏ�������邩���ׂ�B
		if (tracerow->GetStay() == false//��񂪂��Ȃ��B
			&& tracerow->GetReservation() == false//���\�񂪂Ȃ��B
			//&& m_TracerowNum > Game::GetInstance()->m_player->GetMaxrow()
			) {
			//�������������Ă���|�C���g��ۑ����Ă����B
			m_TracerowNum = i;
			//�������������Ă���̂Ŕ��Ȃ��悤�ɗ\�񂵂Ă����B
			tracerow->SetReservation(true);
		}
		//�����̗\��ȂȂ�Β��s�B
		if (m_TracerowNum == i) {
			//�v���C���[�Ƃ̃x�N�g�����߂ĉ��Z�B�v���C���[�Ǐ]�B
			CVector3 kyori = tracerow->Getposition() - m_position;
			CVector3 kyoriNormalize = kyori;
			kyoriNormalize.y = 0.0f;
			kyoriNormalize.Normalize();
			m_speed.x = kyoriNormalize.x * m_SpeedMagnification;
			m_speed.z = kyoriNormalize.z * m_SpeedMagnification;

			//�قڂ��̃|�C���g�ɍs�����̂�
			if (fabs(kyori.x) < m_alignmentcompletiondistance.x &&
				fabs(kyori.z) < m_alignmentcompletiondistance.z) {
				//Stay��錾�B
				tracerow->SetStay(true,m_mynumber);
				//���񊮗����܂��������I�I�i���񊮗������̂Ŏ����̏�Ԃ�Ǐ]�ɕς���B
				state = Tuizyuu;
				//���������񊮗������ꏊ�o���Ă����B
				m_TracerowNum = i;
				//���ȃX�s�[�h���Z�b�g�B
				m_speed = { 0.0f,0.0f,0.0f };
			}
			//�I�������B
			i = Game::GetInstance()->m_tracerowmanager->GetMaxrow();
		}
	}
}

void Slave::Tuizyuu_processing()
{
	//�w�肳�ꂽ��̃A�h���X�擾�B
	Tracerow* tracerow = Game::GetInstance()->m_tracerowmanager->Gettracerow(m_TracerowNum);
	//��Ƃ̃x�N�g�����߂āB
	CVector3 kyori = tracerow->Getposition() - m_position;
	CVector3 kyoriNormalize = kyori;
	kyoriNormalize.y = 0.0f;
	kyoriNormalize.Normalize();
	//���Z�v���C���[�Ǐ]�B
	m_speed.x = kyoriNormalize.x * m_SpeedMagnification;
	m_speed.z = kyoriNormalize.z * m_SpeedMagnification;

	//�قڂ��̃|�C���g�ɍs�����̂ŁB
	if (fabs(kyori.x) < m_alignmentcompletiondistance.x &&
		fabs(kyori.z) < m_alignmentcompletiondistance.z) {
		//�~�܂�B
		m_speed = { 0.0f,0.0f,0.0f };
	}
}

void Slave::Nagerare_processing()
{
	CVector3 kyori = m_markpoint - m_position;
	//��������i�����n�_�ɂ��邩�ǂ����j
	if (fabs(kyori.x) < m_alignmentcompletiondistance.x &&
		fabs(kyori.z) < m_alignmentcompletiondistance.z){
		//���x���Z�b�g�B
		m_speed = CVector3::Zero();
		//���������ł����̂őҋ@��Ԃ�
		state = Taiki;
	}
}
