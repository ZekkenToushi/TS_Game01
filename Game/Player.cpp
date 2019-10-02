#include "stdafx.h"
#include "Player.h"
#include "Game.h"

Player::Player()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/unityChan.cmo");

	//キャラクターコントローラーを初期化。
	//m_charaCon.Init(
	//	20.0,			//半径。 
	//	50.0f,			//高さ。
	//	m_position	//初期位置。
	//);

}


Player::~Player()
{
	//g_goMgr.DeleteGameObject(this);
}

void Player::Update()
{
	Move();
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
	Game::GetInstance()->m_tsCamera->GetForward();

	//XZ平面での前方方向、右方向に変換する。
	CameraForward.y = 0.0f;
	CameraForward.Normalize();
	CameraRightd.y = 0.0f;
	CameraRightd.Normalize();

	//アナログスティックの入力量を取得、ポジションへの適用。
	//m_position.z -= g_pad->GetLStickYF()*5.0f;
	//m_position.x -= g_pad->GetLStickXF()*5.0f;
	m_position -= CameraForward * g_pad->GetLStickYF()*5.0f;
	m_position -= CameraRightd * g_pad->GetLStickXF()*5.0f;



	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3::One());
}
