#include "stdafx.h"
#include "tsCamera.h"
#include "Game.h"

tsCamera::tsCamera()
{
	m_position.Set(m_toCameraPos);
}


tsCamera::~tsCamera()
{
}

void tsCamera::Update()
{
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
	//�J�����^�[�Q�b�g����Ƀv���C���[��
	//g_camera3D.SetTarget(Game::GetInstance()->m_player->GetPosition());
	g_camera3D.SetTarget(m_target);
	g_camera3D.SetPosition(m_position);
	//�J�����̍X�V�B
	g_camera3D.Update();
}

void tsCamera::Move()
{
	//�p�b�h�̓��͂��g���ăJ�������񂷁B
	{
		//�p�b�h�̓��́B
		float x = g_pad->GetRStickXF()*3.0f;
		float y = g_pad->GetRStickYF()*3.0f;

		//Y������̉�]cc1�B
		CQuaternion qRot;
		qRot.SetRotationDeg(CVector3::AxisY(), x);
		qRot.Multiply(m_toCameraPos);
		//�O�ς̗��p�B
		CVector3 axisX;
		axisX.Cross(CVector3::AxisY(), m_toCameraPos);
		axisX.Normalize();
		//X������̉�]�B
		qRot.SetRotationDeg(axisX, y);
		qRot.Multiply(m_toCameraPos);
	}

	//L�{�^���Ńv���C���[�Ƃ̋������ߒ����ɂ���B
	if (g_pad->IsTrigger(enButtonLB1)) {
		//�J�����O�x�N�g���擾�B
		m_ZoomVector = m_forward;
		m_ZoomVector.Normalize();
		m_ZoomVector *= kyorikannkaku;
		if (Zoom == Zoom00) {
			//���ցB
			m_toCameraPos -= m_ZoomVector;
			Zoom = Zoom01;
		}
		else if (Zoom == Zoom01) {
			//���ցB
			m_toCameraPos -= m_ZoomVector;
			Zoom = Zoom02;
		}
		else {
			//�߂ցB
			m_toCameraPos += m_ZoomVector * 2;
			Zoom = Zoom00;
		}
		
	}

	//�^�[�Q�b�g���W�̎擾�B
	m_target = Game::GetInstance()->m_player->Getposition();

	//�Ǐ]�B
	m_position = m_target + m_toCameraPos;

}
