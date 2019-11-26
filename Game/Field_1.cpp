#include "stdafx.h"
#include "Field_1.h"


Field_1::Field_1()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/Field1.cmo");
	//静的物理オブジェクトを初期化する。
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
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3::One());
}

void Field_1::Render()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
