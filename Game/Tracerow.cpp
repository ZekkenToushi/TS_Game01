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

