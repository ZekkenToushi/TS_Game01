#include "stdafx.h"
#include "Field_1.h"


Field_1::Field_1()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/Field1.cmo");
}


Field_1::~Field_1()
{
}

void Field_1::Update()
{
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
}

void Field_1::Render()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
