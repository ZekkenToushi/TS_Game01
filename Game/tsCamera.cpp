#include "stdafx.h"
#include "tsCamera.h"
#include "Game.h"

tsCamera::tsCamera()
{
	
}


tsCamera::~tsCamera()
{
}

void tsCamera::Update()
{
	//�J�����̍X�V�B
	g_camera3D.Update();

	//�J�����^�[�Q�b�g����Ƀv���C���[��
	g_camera3D.SetTarget(Game::GetInstance()->m_player->GetPosition());


	//�J�����̃r���[�s����擾�B
	CMatrix	viewMatrix = g_camera3D.GetViewMatrix();
	//�r���[�s��̋t�s����v�Z�B
	viewMatrix.Inverse(viewMatrix);
	//3�s�ڂ̃J�����̑O��������Set�B
	m_forward.Set(viewMatrix.m[2][0], viewMatrix.m[2][1], viewMatrix.m[2][2]);
	//�s�ڂ̃J�����̉E��������Set�B
	m_right.Set(viewMatrix.m[0][0], viewMatrix.m[0][1], viewMatrix.m[0][2]);

	//Move�̍X�V�B
	Move();

	//���C���J�����ɒ����_�Ǝ��_��ݒ肷��B
	//g_camera3D.SetTarget(m_target);
	//g_camera3D.SetPosition(m_position);
}

void tsCamera::Move()
{
	//�p�b�h�̓��͂��g���ăJ��������
	float x = g_pad->GetRStickXF();
	float y = g_pad->GetRStickYF();

	//Y������̉�]cc1
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY(), 2.0f * x);
	CVector3 POVpos;
	qRot.Multiply(POVpos);

	//X������̉�]
	CVector3 axisX;
	axisX.Cross(CVector3::AxisY(), POVpos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 2.0f * y);
	qRot.Multiply(POVpos);

	//���_���v�Z�B
	m_position = m_target + POVpos;
}
