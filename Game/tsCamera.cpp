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
	//カメラの更新。
	g_camera3D.Update();

	//カメラターゲットを常にプレイヤーに
	g_camera3D.SetTarget(Game::GetInstance()->m_player->GetPosition());


	//カメラのビュー行列を取得。
	CMatrix	viewMatrix = g_camera3D.GetViewMatrix();
	//ビュー行列の逆行列を計算。
	viewMatrix.Inverse(viewMatrix);
	//3行目のカメラの前方方向をSet。
	m_forward.Set(viewMatrix.m[2][0], viewMatrix.m[2][1], viewMatrix.m[2][2]);
	//行目のカメラの右方方向をSet。
	m_right.Set(viewMatrix.m[0][0], viewMatrix.m[0][1], viewMatrix.m[0][2]);

	//Moveの更新。
	Move();

	//メインカメラに注視点と視点を設定する。
	//g_camera3D.SetTarget(m_target);
	//g_camera3D.SetPosition(m_position);
}

void tsCamera::Move()
{
	//パッドの入力を使ってカメラを回す
	float x = g_pad->GetRStickXF();
	float y = g_pad->GetRStickYF();

	//Y軸周りの回転cc1
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY(), 2.0f * x);
	CVector3 POVpos;
	qRot.Multiply(POVpos);

	//X軸周りの回転
	CVector3 axisX;
	axisX.Cross(CVector3::AxisY(), POVpos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 2.0f * y);
	qRot.Multiply(POVpos);

	//視点を計算。
	m_position = m_target + POVpos;
}
