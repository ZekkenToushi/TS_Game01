#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/aikonn.cmo");
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

void Enemy::Stay()
{
	//���̏�őҋ@���[�V�����B

	//�����U�����ꂽ�灨�G�ֈړ����U���B


}

void Enemy::Move()
{
	//�Ώۂ̈ʒu�܂ňړ�����B

	//�Ώۂ��G�Ȃ�΍U���ֈڍs�B

	//�Ώۂ����Ȃ��Ȃ猳�ƈʒu�ɖ߂�A�ҋ@�ցB

}

void Enemy::Attack()
{
	//�Ώۂւ̋���������Ă�����move��

	//�Ώۂւ̋������߂���΍U�����[�V����

	//HP�֍U���B

	//�U��CT����B

}

void Enemy::Death()
{
	//����������HP��0�ȉ��Ȃ��

	//���S���[�V�����BDelete this
}
