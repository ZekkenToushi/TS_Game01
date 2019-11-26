#include "stdafx.h"
#include "Field_1.h"


Field_1::Field_1()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/Field1.cmo");
	//�ÓI�����I�u�W�F�N�g������������B
	CQuaternion rot = {0.0f,0.0f,0.0f,1.0f};
	m_phyStaticObject.CreateMeshObject(
		m_model,
		m_position,
		rot
	);
}


Field_1::~Field_1()
{
}

void Field_1::Update()
{
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3::One());
}

void Field_1::Render()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
