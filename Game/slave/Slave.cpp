#include "stdafx.h"
#include "Slave.h"
#include "Game.h"
#include "math.h"//絶対値条件文で使用。
Slave::Slave()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/suraimu01.cmo");

	//キャラクターコントローラーを初期化。
	CVector3 pos = m_position;
	
	m_charaCon.Init(
		50.0,			//半径。 
		50.0f,			//高さ。
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
	//キャラコン。
	m_position = m_charaCon.Execute(1.0f / 60, m_speed);
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
	if (g_pad->IsPress(enButtonY)&&
		state != Tuizyuu) {
		state = Mukau;
	}
	if (g_pad->IsPress(enButtonX)) {
		state = Taiki;
		m_speed = CVector3::Zero();
	}
	//今すぐ向かいます！！隊長！！。
	if (state == Mukau) {
		
		//Tracerowを参照して並ぶ。
		//配列分回す
		for (int i = 0; i < Game::GetInstance()->m_player->Getrowcount(); i++) {
			//指定（i）された列のアドレス取得。
			Tracerow* tracerow = Game::GetInstance()->m_player->Gettracerow(i);
			
			//その配列ポイントに自分入れるか調べる。
			if (tracerow->GetStay() == false//先約がいない。
				){
				//プレイヤーとのベクトル求めて加算。
				m_MasterPosition = tracerow->Getposition();
				m_kyori = m_MasterPosition - m_position;
				CVector3 kyoriNormalize = m_kyori;
				kyoriNormalize.y = 0.0f;
				kyoriNormalize.Normalize();
				m_speed.x = kyoriNormalize.x * m_SpeedMagnification;
				m_speed.z = kyoriNormalize.z * m_SpeedMagnification;

				//ほぼそのポイントに行けたので
				if (fabs(m_kyori.x) < m_AlignmentCompletionDistance.x &&
					fabs(m_kyori.z) < m_AlignmentCompletionDistance.z) {
					//Stayを宣言。
					tracerow->SetStay(true);
					//整列完了しました隊長！！（整列完了したので自分の状態を追従に変える。
					state = Tuizyuu;
					//自分が整列完了した場所覚えておく。
					m_TracerowNum = i;
					//tomeru
					m_speed = { 0.0f,0.0f,0.0f };
				}
				//終了条件。
				i = Game::GetInstance()->m_player->Getrowcount();
			}
			

		}
		
	}
	//一生ついていきます隊長！！（追従状態。
	if (state == Tuizyuu) {
		//指定された列のアドレス取得。
		Tracerow* tracerow = Game::GetInstance()->m_player->Gettracerow(m_TracerowNum);
		//プレイヤーとのベクトル求めて加算。プレイヤー追従。
		m_MasterPosition = tracerow->Getposition();
		m_kyori = m_MasterPosition - m_position;
		CVector3 kyoriNormalize = m_kyori;
		kyoriNormalize.y = 0.0f;
		kyoriNormalize.Normalize();
		m_speed.x = kyoriNormalize.x * m_SpeedMagnification;
		m_speed.z = kyoriNormalize.z * m_SpeedMagnification;

		//ほぼそのポイントに行けたので。
		if (fabs(m_kyori.x) < m_AlignmentCompletionDistance.x &&
			fabs(m_kyori.z) < m_AlignmentCompletionDistance.z) {
			//止まれ。
			m_speed = { 0.0f,0.0f,0.0f };
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

	

}