#include "stdafx.h"
#include "Player.h"
#include "Game.h"

Player::Player()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/unityChan.cmo");

	//キャラクターコントローラーを初期化。
	m_charaCon.Init(
		20.0,			//半径。 
		50.0f,			//高さ。
		m_position	//初期位置。
	);

}


Player::~Player()
{
	//g_goMgr.DeleteGameObject(this);
}

void Player::Update()
{
	Move();
	Tracerowset();
}
void Player::Render()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
}

void Player::Move()
{
	//カメラ前方向、右方向を取得。
	CVector3 CameraForward = Game::GetInstance()->m_tsCamera->GetForward();
	CVector3 CameraRightd = Game::GetInstance()->m_tsCamera->GetRight();
	
	//XZ平面での前方方向、右方向に変換する。
	CameraForward.y = 0.0f;
	CameraForward.Normalize();
	CameraRightd.y = 0.0f;
	CameraRightd.Normalize();

	//アナログスティックの入力量を取得、ポジションへの適用。
	m_speed = CameraForward * g_pad->GetLStickYF()*1200.0f;
	m_speed += CameraRightd * g_pad->GetLStickXF()*1200.0f;
	////プレイヤー移動。
	//m_speed.z = g_pad->GetLStickYF()*1200.0f;
	//m_speed.x = g_pad->GetLStickXF()*1200.0f;

	//一時的重力
	m_speed.y -= 1000.00f;
	

	//XZ成分の移動速度をクリア
	if (g_pad->GetLStickXF() == 0.0f) {

		m_speed.x = 0.0f;
		m_speed.z = 0.0f;
	}
	
	//ジャンプ。
	if (g_pad->IsPress(enButtonB)) {
		m_speed.y += 2000.0f;
	}

	m_position = m_charaCon.Execute(1.0f / 60, m_speed);
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3::One());
}

void Player::Tracerowset()
{
	for (int i = 0; i < rowcount; i++) {
		//配列分ポインタを作り。
		Tracerow* m_narabe = &tracerow[i];
		//NumとPositionセットする。
		m_narabe->SetNum(i);
		m_narabe->SetTargetPosition(m_position);
		m_narabe->Update();
		m_narabe->Render();
	}
	
}
