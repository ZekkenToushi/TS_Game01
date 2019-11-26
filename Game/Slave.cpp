#include "stdafx.h"
#include "Slave.h"
#include "Game.h"

Slave::Slave()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/suraimu01.cmo");

	//キャラクターコントローラーを初期化。
	CVector3 pos = m_position;
	
	m_charaCon.Init(
		20.0,			//半径。 
		100.0f,			//高さ。
		pos		//初期位置。
	);
	
}


Slave::~Slave()
{
}

void Slave::Update()
{
	Search();
	Order();
	Move();
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3::One());
}

void Slave::Render()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void Slave::Search()
{
	//命令判定。
	if (g_pad->IsPress(enButtonY)) {
		state = Tuizyuu;
	}
	if (g_pad->IsPress(enButtonX)) {
		state = Taiki;
		m_speed = CVector3::Zero();
	}
	//追従。
	if (Tuizyuu == state) {
		//プレイヤーとのベクトル求めて加算。プレイヤー追従。
		//MasterPosition = Game::GetInstance()->m_player->GetPosition();
		//CVector3 kyori = MasterPosition - m_position;
		//kyori.y = 0.0f;
		//kyori.Normalize();
		//m_speed.x = kyori.x * SpeedMagnification;
		//m_speed.z = kyori.z * SpeedMagnification;

		//Tracerowを参照して並ぶ。3  
		for (int i = 0; i < Game::GetInstance()->m_player->Getrowcount; i++) {
			Tracerow* tracerow = &Game::GetInstance()->m_player->Gettracerow(i);
			if (tracerow->GetReservation == true) {
				m_speed = tracerow->Getposition() 
					* SpeedMagnification;


			}



		}
	}
}

void Slave::Order()
{


}

void Slave::Move()
{
	//一時的重力
	m_speed.y -= 30.00f;

	m_position = m_charaCon.Execute(1.0f / 60, m_speed);

}