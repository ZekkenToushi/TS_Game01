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
	//カメラターゲットを常にプレイヤーに
	//g_camera3D.SetTarget(Game::GetInstance()->m_player->GetPosition());
	g_camera3D.SetTarget(m_target);
	g_camera3D.SetPosition(m_position);
	//カメラの更新。
	g_camera3D.Update();
}

void tsCamera::Move()
{
	//パッドの入力を使ってカメラを回す。
	{
		//パッドの入力。
		float x = g_pad->GetRStickXF()*3.0f;
		float y = g_pad->GetRStickYF()*3.0f;

		//Y軸周りの回転cc1。
		CQuaternion qRot;
		qRot.SetRotationDeg(CVector3::AxisY(), x);
		qRot.Multiply(m_toCameraPos);
		//外積の利用。
		CVector3 axisX;
		axisX.Cross(CVector3::AxisY(), m_toCameraPos);
		axisX.Normalize();
		//X軸周りの回転。
		qRot.SetRotationDeg(axisX, y);
		qRot.Multiply(m_toCameraPos);
	}

	//Lボタンでプレイヤーとの距離を近中遠にする。
	if (g_pad->IsTrigger(enButtonLB1)) {
		//カメラ前ベクトル取得。
		m_ZoomVector = m_forward;
		m_ZoomVector.Normalize();
		m_ZoomVector *= kyorikannkaku;
		if (Zoom == Zoom00) {
			//中へ。
			m_toCameraPos -= m_ZoomVector;
			Zoom = Zoom01;
		}
		else if (Zoom == Zoom01) {
			//遠へ。
			m_toCameraPos -= m_ZoomVector;
			Zoom = Zoom02;
		}
		else {
			//近へ。
			m_toCameraPos += m_ZoomVector * 2;
			Zoom = Zoom00;
		}
		
	}

	//ターゲット座標の取得。
	m_target = Game::GetInstance()->m_player->Getposition();

	//追従。
	m_position = m_target + m_toCameraPos;

}
