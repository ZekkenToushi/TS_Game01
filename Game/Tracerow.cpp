#include "stdafx.h"
#include "Tracerow.h"
#include"Game.h"

Tracerow::Tracerow()
{
	//実験用スライム表示
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/suraimu01.cmo");
	
}


Tracerow::~Tracerow()
{
}

void Tracerow::Update()
{
	
	//実験用スライム表示
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3::One());
	
}

void Tracerow::Render()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

