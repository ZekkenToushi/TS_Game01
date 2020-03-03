#include "stdafx.h"
#include "Player.h"
#include "Game.h"
#include "Marker.h"

Player::Player()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/unityChan.cmo");
	//キャラクターコントローラーを初期化。
	m_charaCon.Init(
		50.0,			//半径。 
		50.0f,			//高さ。
		m_position	//初期位置。
	);
	//centerrow初期設定。
	//m_centerrow.z = m_position.z - m_centerrowdistance;

	//markerの作成。
	marker = NewGO<Marker>();
}


Player::~Player()
{
	//g_goMgr.DeleteGameObject(this);
}

void Player::Update()
{
	Move();
	Rotation();
	Order();

	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());

}
void Player::Render()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);

}

void Player::Move(){

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

	//一時的重力
	m_speed.y -= 1000.00f;
	

	//XZ成分の移動速度をクリア
	/*if (g_pad->GetLStickXF() == 0.0f) {

		m_speed.x = 0.0f;
	}
	if (g_pad->GetLStickYF() == 0.0f) {
		m_speed.z = 0.0f;
	}*/

	//ジャンプ判定。
	if (g_pad->IsTrigger(enButtonY)&&
		m_isJump == false) {
		m_isJump = true;
	}
	//ジャンプ加速中。
	if (m_isJump == true) {
		m_speed.y += 2000.0f;
		m_jumpCount++;
		//ジャンプ加速中2。
		if (m_jumpCount > 5.0f) {
			m_speed.y -= 500.0f;
			//ジャンプ加速終了または地面についたならばリセット。
			if (m_jumpCount > 10.0f
				//||m_charaCon.IsOnGround()
				) {
				m_jumpCount = 0.0f;
				m_isJump = false;
			}
		}
	}
	//摩擦計算。
	m_speed = m_speed * m_friction;

	m_position = m_charaCon.Execute(1.0f / 60, m_speed);
	
}

void Player::Rotation()
{
	//下準備。
	float Rot = atan2(m_playerforward, m_playerside);
	CQuaternion qRot;
	qRot.SetRotation(CVector3::AxisY(), Rot);

	//入力があれば
	if (m_speed.x != 0.0f || m_speed.z != 0.0f)
	{
		//回転を適用。
		m_rotation = qRot;
		//進行方向保存。
		m_playerforward = m_speed.x;
		m_playerside = m_speed.z;
	}
	
}

void Player::Order()
{
	//Bが押されたら。
	if (g_pad->IsTrigger(enButtonB)) {
		//手持ちにSlaveがいれば。つまりステイがあるか調べる。
		int slavenum = Game::GetInstance()->m_tracerowmanager->SearchReadyNum();
		//0以上であればその番号のslaveがいる。
		if (slavenum >= 0) {
			//マーカーの位置を取得。
			CVector3 position_marker =
				marker->GetPosition();
			//一番席にいるSlaveへ飛ばす。
			Slave* slave = Game::GetInstance()->m_slaveganerator->GetSlave(slavenum);
			slave->Buttobu(position_marker);
			
		}

	}

}
