#include "stdafx.h"
#include "Enemy.h"
#include "Game.h"
Enemy::Enemy()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/medamaaka.cmo");
	//�L�����N�^�[�R���g���[���[���������B
	m_charaCon.Init(
		50.0,			//���a�B 
		50.0f,			//�����B
		m_position	//�����ʒu�B
	);
	//�����ʒu���L�����Ă����B
	m_firstPosition = m_position;
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	//��ԊǗ��B���݂̏�Ԃɍ��킹�ēK�؂Ȋ֐��Ăяo�����s���B
	StateManagement();
	//���S����B
	Death();
	//�ꎞ�I�d��
	m_speed.y += m_gravity / 60.0f;

	//m_position += m_charaCon.Execute(1.0f / 60, m_speed);
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
}

void Enemy::Render()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void Enemy::StateManagement()
{
	Basic();
	if (m_KYOUSEIkitaku == false) {
		switch (state) {
		case stay://���̏�ɑҋ@�B
			Stay();
			break;
		case move://�B
			Move();
			break;
		case attack://�B
			Attack();
			break;
		}
	}
}

void Enemy::Stay()
{

	//�����ʒu����̋����B
	CVector3 Movekyori = m_firstPosition - m_position;
	//��������ʒu�����藣��Ă��܂����ꍇ�@�@�@�B
	if (fabs(Movekyori.x) > m_range.x ||
		fabs(Movekyori.z) > m_range.z) {
		//�A��[�h�ցB
		m_kitaku = true;
	}

	//���ݏ�������Ă��鐔��������������s���B		
	for (int i = 0;i < Game::GetInstance()->m_slaveganerator->GetSlaveCount();i++) {
		//�G�Ƃ̋����𑪂�
		Slave* slave = Game::GetInstance()->m_slaveganerator->GetSlave(i+1);
		CVector3 target = slave->GetPosition();
		CVector3 kyori = target - m_position;
		//���G�͈͂ɓ�������B
		if (fabs(kyori.x) < m_SeeDistance.x &&
			fabs(kyori.z) < m_SeeDistance.z) {
			m_targetNum = i+1;
			//�ړ��ցB
			state = move;
			m_kitaku = false;
		}
	}
	
	//�����̃|�W�V�����ɖ߂�B
	//��������ʒu�����藣��Ă��܂����ꍇ�@�A�@�܂��A��t���O���I���Ȃ�΁B
	//�����ʒu�֋A��i�L�����R���K�p��m_speed�ɂ��悤�j
	if (m_kitaku == true) {
		CVector3 MovekyoriNomalize = Movekyori;
		MovekyoriNomalize.Normalize();
		MovekyoriNomalize.y = 0.0f;
		m_position += MovekyoriNomalize * m_speedMagnification;
		//�����ʒu�ɖ߂ꂽ��B
		if (fabs(Movekyori.x) < m_range.x &&
			fabs(Movekyori.z) < m_range.z) {
			//�A������B
			m_kitaku = false;
			
		}
	}

	//���̏�őҋ@���[�V�����B

}

void Enemy::Move()
{
	//�Ώۂ̈ʒu�܂ňړ�����B
	//�G�Ƃ̋����𑪂�B
	Slave* slave = Game::GetInstance()->m_slaveganerator->GetSlave(m_targetNum);
	CVector3 target = slave->GetPosition();
	CVector3 kyori = target - m_position;
	CVector3 kyoriNormalize = kyori;
	kyoriNormalize.Normalize();
	kyoriNormalize.y = 0.0f;
	m_position += kyoriNormalize * m_speedMagnification;
	//�˒��͈͂ɓ�������B
	if (fabs(kyori.x) < m_range.x &&
		fabs(kyori.z) < m_range.z) {
		//�Ώۂւ̋������߂���΍U�����[�V�����B
		state = attack;
	}
	//�Ώۂ��G�Ȃ�΍U���ֈڍs�B

	//�Ώۂ����Ȃ��Ȃ猳�ƈʒu�ɖ߂�A�ҋ@�ցB

}

void Enemy::Attack()
{
	//�Ώۂւ̋���������Ă�����move��
	//�G�Ƃ̋����𑪂�
	Slave* slave = Game::GetInstance()->m_slaveganerator->GetSlave(m_targetNum);
	CVector3 target = slave->GetPosition();
	CVector3 kyori = target - m_position;
	//�˒��͈͂ɓ�������B
	if (fabs(kyori.x) > m_range.x &&
		fabs(kyori.z) > m_range.z) {
		//�ړ��ցB
		state = move;
	}

	//�U��CT����B
	
	if (m_timer > m_coolTime) 
	{
		//slave�֍U���B
		slave->AddHP(-5);
		//�����Ώۂ��E������B
		if (slave->GetHP() <= 0) {
			state = stay;
		}
		//���Z�b�g�B
		m_timer = 0;
	}
	

}

void Enemy::Death()
{
	//����������HP��0�ȉ��Ȃ��
	//���S����B
	if (enemy.HP <= 0) {
		//���S���[�V�����B


		RequestDelete();
	};
	
}

void Enemy::Basic()
{
	//�����ʒu����̋����B
	CVector3 Movekyori = m_firstPosition - m_position;
	//��������ʒu�����藣��Ă��܂����ꍇ�B
	if (fabs(Movekyori.x) > m_territory.x ||
		fabs(Movekyori.z) > m_territory.z) {
		//�����A��[�h�ցB
		m_KYOUSEIkitaku = true;
	}
	//�����ʒu�֋A��i�L�����R���K�p��m_speed�ɂ��悤�j
	if (m_KYOUSEIkitaku == true) {
		CVector3 MovekyoriNomalize = Movekyori;
		MovekyoriNomalize.Normalize();
		MovekyoriNomalize.y = 0.0f;
		m_position += MovekyoriNomalize * m_speedMagnification;
		//�����ʒu�ɖ߂ꂽ��B
		if (fabs(Movekyori.x) < m_range.x &&
			fabs(Movekyori.z) < m_range.z) {
			//�����A������B
			m_KYOUSEIkitaku = false;
			state =stay;
		}
	}
	//test
	/*if (g_pad->IsTrigger(enButtonLB1)) {
		int a;
		a++;
	}*/
	//�U��CT�񕜁B
	m_timer++;
}
