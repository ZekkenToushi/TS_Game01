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
	
	m_slaveCon.Init(
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
	m_position = m_slaveCon.Execute(1.0f / 60, m_speed + m_force);
	m_force *= 0.5f;
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
	//摩擦計算。
	m_speed = m_speed * m_friction;
	////隊長に道を譲れ！！（プレイヤーとぶつかったのでスピードベクトルに影響されるように）。
	////プレイヤーとのベクトル求めて。
	//m_masterposition = Game::GetInstance()->m_player->Getposition();
	//m_kyori = m_masterposition - m_position;
	////もしプレイヤーとの距離が一定以下なら（ぶつかっている）。
	//if (fabs(m_kyori.x) < m_distancejudgment.x&&
	//	fabs(m_kyori.z) < m_distancejudgment.z) {
	//	//プレイヤーの移動ベクトルを自分に加算して押し出されるようにする。
	//	m_speed += Game::GetInstance()->m_player->Getspeed()/3;
	//
	//}

	//他のスライムと重なってる場合よける。
	//現在召喚している数分for文を回す。
	for (int i = 0;i < Game::GetInstance()->m_slaveganerator->GetSlaveCount();i++) {
		//自分以外。
		if (i != m_mynumber) {
			//Slave* slave = Game::GetInstance()->m_slaveganerator->GetSlave[i];
			//CVector3 kyori = slave->GetPosition() - m_position;



		}
	}

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

	//早い者勝ち型整列。
	//for (int i = 0; i < Game::GetInstance()->m_player->Getrowcount(); i++) {
	//	//指定（i）された列のアドレス取得。
	//	Tracerow* tracerow = Game::GetInstance()->m_player->Gettracerow(i);

	//	//その配列ポイントに自分入れるか調べる。
	//	if (tracerow->GetStay() == false//先約がいない。
	//		) {
	//		//プレイヤーとのベクトル求めて加算。
	//		m_kyori = tracerow->Getposition() - m_position;
	//		CVector3 kyoriNormalize = m_kyori;
	//		kyoriNormalize.y = 0.0f;
	//		kyoriNormalize.Normalize();
	//		m_speed.x = kyoriNormalize.x * m_SpeedMagnification;
	//		m_speed.z = kyoriNormalize.z * m_SpeedMagnification;

	//		//ほぼそのポイントに行けたので
	//		if (fabs(m_kyori.x) < m_alignmentcompletiondistance.x &&
	//			fabs(m_kyori.z) < m_alignmentcompletiondistance.z) {
	//			//Stayを宣言。
	//			tracerow->SetStay(true);
	//			//整列完了しました隊長！！（整列完了したので自分の状態を追従に変える。
	//			state = Tuizyuu;
	//			//自分が整列完了した場所覚えておく。
	//			m_TracerowNum = i;
	//			//追跡スピードリセット。
	//			m_speed = { 0.0f,0.0f,0.0f };
	//		}
	//		//終了条件。
	//		i = Game::GetInstance()->m_player->GetMaxrow();
	//	}
	//}
	//予約型整列。
	for (int i = 0; i < Game::GetInstance()->m_player->GetMaxrow(); i++) {
		//指定（i）された列のアドレス取得。
		Tracerow* tracerow = Game::GetInstance()->m_player->Gettracerow(i);

		//その配列ポイントに自分入れるか調べる。
		if (tracerow->GetStay() == false//先約がいない。
			&& tracerow->GetReservation() == false//かつ予約がない。
			//&& m_TracerowNum > Game::GetInstance()->m_player->GetMaxrow()
			) {
			//自分が向かっているポイントを保存しておく。
			m_TracerowNum = i;
			//自分が向かっているので被らないように予約しておく。
			tracerow->SetReservation(true);
		}
		//自分の予約席ならば直行。
		if (m_TracerowNum == i) {
			//プレイヤーとのベクトル求めて加算。プレイヤー追従。
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
				//着席スピードリセット。
				m_speed = { 0.0f,0.0f,0.0f };
			}
			//終了条件。
			i = Game::GetInstance()->m_player->GetMaxrow();
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
