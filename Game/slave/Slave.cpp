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
		30.0,			//半径。 
		20.0f,			//高さ。
		pos		//初期位置。
	);
	
}


Slave::~Slave()
{
}

void Slave::Update()
{
	Search();
	Move();
	Statemanagement();
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
}


void Slave::Move()
{
	//一時的重力
	m_speed.y -= 30.00f;

	//隊長に道を譲れ！！（プレイヤーとぶつかったのでスピードベクトルに影響されるように）。
	//プレイヤーとのベクトル求めて。
	m_masterposition = Game::GetInstance()->m_player->Getposition();
	m_kyori = m_masterposition - m_position;
	//もしプレイヤーとの距離が一定以下なら（ぶつかっている）。
	if (fabs(m_kyori.x) < m_distancejudgment.x&&
		fabs(m_kyori.z) < m_distancejudgment.z) {
		//プレイヤーの移動ベクトルを自分に加算して押し出されるようにする。
		m_speed += Game::GetInstance()->m_player->Getspeed()/3;
	
	}

	//摩擦計算。
	m_speed = m_speed * m_friction;

}

void Slave::Statemanagement()
{
	switch (state) {
	case Taiki://その場に待機。
		Taiki_processing();
		break;
	case Mukau://プレイヤーに呼ばれたので列に並ぶ。
		Mukau_processing();
		break;
	case Tuizyuu://列に並んだのでプレイヤーについていく。
		Tuizyuu_processing();
		break;
	//case 3:

	}

}

void Slave::Taiki_processing()
{
	//もし攻撃されたら反撃する。

}

void Slave::Mukau_processing()
{
	//Tracerowを参照して並ぶ。
	//配列分回す
	for (int i = 0; i < Game::GetInstance()->m_player->Getrowcount(); i++) {
		//指定（i）された列のアドレス取得。
		Tracerow* tracerow = Game::GetInstance()->m_player->Gettracerow(i);

		//その配列ポイントに自分入れるか調べる。
		if (tracerow->GetStay() == false//先約がいない。
			) {
			//プレイヤーとのベクトル求めて加算。
			m_kyori = tracerow->Getposition() - m_position;
			CVector3 kyoriNormalize = m_kyori;
			kyoriNormalize.y = 0.0f;
			kyoriNormalize.Normalize();
			m_speed.x = kyoriNormalize.x * m_SpeedMagnification;
			m_speed.z = kyoriNormalize.z * m_SpeedMagnification;

			//ほぼそのポイントに行けたので
			if (fabs(m_kyori.x) < m_alignmentcompletiondistance.x &&
				fabs(m_kyori.z) < m_alignmentcompletiondistance.z) {
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

void Slave::Tuizyuu_processing()
{
	//指定された列のアドレス取得。
	Tracerow* tracerow = Game::GetInstance()->m_player->Gettracerow(m_TracerowNum);
	//列とのベクトル求めて。
	m_kyori = tracerow->Getposition() - m_position;
	CVector3 kyoriNormalize = m_kyori;
	kyoriNormalize.y = 0.0f;
	kyoriNormalize.Normalize();
	//加算プレイヤー追従。
	m_speed.x = kyoriNormalize.x * m_SpeedMagnification;
	m_speed.z = kyoriNormalize.z * m_SpeedMagnification;

	//ほぼそのポイントに行けたので。
	if (fabs(m_kyori.x) < m_alignmentcompletiondistance.x &&
		fabs(m_kyori.z) < m_alignmentcompletiondistance.z) {
		//止まれ。
		m_speed = { 0.0f,0.0f,0.0f };
	}
}
