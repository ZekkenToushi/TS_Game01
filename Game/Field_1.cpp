#include "stdafx.h"
#include "Field_1.h"


Field_1::Field_1()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/Field1.cmo");
}


Field_1::~Field_1()
{
}

void Field_1::Update()
{
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
}

void Field_1::Render()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
