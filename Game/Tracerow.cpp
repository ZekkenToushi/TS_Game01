#include "stdafx.h"
#include "Tracerow.h"
#include"Game.h"

Tracerow::Tracerow()
{
	//�����p�X���C���\��
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/suraimu01.cmo");
	

}


Tracerow::~Tracerow()
{
}

void Tracerow::Update()
{
	//������Num�ɂ���Ď����̃|�W�V���������肷��B
	//�����p�x�N�g���Ƃ肠����
	CVector3 zure = CVector3::Zero();
	if (m_Num == 0) {
		zure.z = -100.0f;
		m_position = m_targetposition + zure;
	}
	if (m_Num == 1) {
		zure.z = -100.0f;
		zure.x = -100.0f;
		m_position = m_targetposition + zure;
	}
	if (m_Num == 2) {
		zure.z = -100.0f;
		zure.x = 100.0f;
		m_position = m_targetposition + zure;
	}
	if (m_Num == 3) {
		zure.z = -200.0f;
		zure.x = -150.0f;
		m_position = m_targetposition + zure;
	}
	if (m_Num == 4) {
		zure.z = -200.0f;
		
		m_position = m_targetposition + zure;
	}
	if (m_Num == 5) {
		zure.z = -200.0f;
		zure.x = 150.0f;
		m_position = m_targetposition + zure;
	}
	//�����p�X���C���\��
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3::One());

}

void Tracerow::Render()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
