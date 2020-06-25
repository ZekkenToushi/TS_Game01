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
	RequestDelete();
}

void Slave::Update()
{
	Search();
	StateManagement();
	Move();
	
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
	//命令判定。仮
	if (g_pad->IsPress(enButtonX)&&
		state != Tuizyuu) {
		state = Mukau;
	}
	if (g_pad->IsPress(enButtonA)) {
		state = Taiki;
		m_speed = CVector3::Zero();
	}

	
}


void Slave::Move()
{
	//重力が一定以上かかると床を突き抜ける為。
	if (m_speed.y > -1000.0f) {
		//重力。
		m_speed.y += m_gravity / 60.0f;
	}
	//摩擦計算。
	//m_speed = m_speed * m_friction;

	////隊長に道を譲れ！！（プレイヤーとぶつかったのでスピードベクトルに影響されるように）。
	////プレイヤーとのベクトル求めて。
	//m_masterposition = Game::GetInstance()->m_player->GetPosition();
	//CVector3 kyori = m_masterposition - m_position;
	////もしプレイヤーとの距離が一定以下なら（ぶつかっている）。
	//if (fabs(kyori.x) < m_distancejudgment.
	//	fabs(kyori.z) < m_distancejudgment.z) {
	//	//プレイヤーの移動ベクトルを自分に加算して押し出されるようにする。
	//	m_speed += Game::GetInstance()->m_player->Getspeed()/3;
	//}

	//他のスライムと重なってる場合よける。
	//現在召喚している数分for文を回す。
	for (int i = 1;i < Game::GetInstance()->m_slaveganerator->GetSlaveCount();i++) {
		//自分以外。
		if (i != m_mynumber) {
			Slave* slave = Game::GetInstance()->m_slaveganerator->GetSlave(i);
			CVector3 kyori = slave->GetPosition() - m_position;
			if (kyori.Length() < m_personalSpace) {
				float Leave = m_personalSpace - kyori.Length();
				kyori.Normalize();
				m_speed += kyori * fabs(Leave) *-1.0f;
			}

		}
	}
	//プレイヤーも避ける（↑同じように。
	CVector3 kyori = Game::GetInstance()->m_player->GetPosition() - m_position;
	if (kyori.Length() < m_personalSpace) {
		float Leave = kyori.Length() - m_personalSpace;
		kyori.Normalize();
		m_speed += kyori * Leave;
	}

	//死亡判定。
	if (slave.HP <= 0) {
		RequestDelete();
	};

}

void Slave::Buttobu(CVector3 point)
{
	//投げられる準備。
	m_markpoint = point;
	m_buttobi = m_markpoint - m_position;
	//m_buttobi.y = m_markpoint.Length()/2;

	//落下時間。
	float time = 1.50f;
	//マーカーと現在位置のy軸差。
	float y = m_markpoint.y - m_position.y;
	//y(高さ) =v(初速度)t(時間) - 1/2gt^2　から
	float init_vy = (y + 0.5f * -m_gravity*(time*time)) / time;
	//XY軸移動。
	m_speed.y = init_vy;
	//XZ軸移動。
	float vxz = m_buttobi.Length() / time;
	auto v = m_buttobi;
	v.y = 0.0f;
	v.Normalize();
	v *= vxz;
	m_speed.x = v.x;
	m_speed.z = v.z;
	//ステート変更。
	state = Nagerare;
	//自分が座っていた席を空ける
	Tracerow* tracerow = Game::GetInstance()->m_tracerowmanager->Gettracerow(m_TracerowNum);
	
	tracerow->SetStay(false, m_mynumber);
	tracerow->SetReservation(false);
}

void Slave::StateManagement()
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
	case Nagerare://今僕は投げられています。
		Nagerare_processing();
		break;
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
	/*
	for (int i = 0; i < Game::GetInstance()->m_player->Getrowcount(); i++) {
		//指定（i）された列のアドレス取得。
		Tracerow* tracerow = Game::GetInstance()->m_player->Gettracerow(i);

		//その配列ポイントに自分入れるか調べる。
		if (tracerow->GetStay() == false//先約がいない。
			) {
			//プレイヤーとのベクトル求めて加算。
			CVector3 kyori = tracerow->Getposition() - m_position;
			CVector3 kyoriNormalize = kyori;
			kyoriNormalize.y = 0.0f;
			kyoriNormalize.Normalize();
			m_speed.x = kyoriNormalize.x * m_SpeedMagnification;
			m_speed.z = kyoriNormalize.z * m_SpeedMagnification;

			//ほぼそのポイントに行けたので
			if (fabs(kyori.x) < m_alignmentcompletiondistance.x &&
				fabs(kyori.z) < m_alignmentcompletiondistance.z) {
				//Stayを宣言。
				tracerow->SetStay(true);
				//整列完了しました隊長！！（整列完了したので自分の状態を追従に変える。
				state = Tuizyuu;
				//自分が整列完了した場所覚えておく。
				m_TracerowNum = i;
				//追跡スピードリセット。
				m_speed = { 0.0f,0.0f,0.0f };
			}
			//終了条件。
			i = Game::GetInstance()->m_player->GetMaxrow();
		}
	}
	*/
	//予約型整列。
	for (int i = 0; i < Game::GetInstance()->m_tracerowmanager->GetMaxrow(); i++) {
		//指定（i）された列のアドレス取得。
		Tracerow* tracerow = Game::GetInstance()->m_tracerowmanager->Gettracerow(i);

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
			CVector3 kyori = tracerow->Getposition() - m_position;
			CVector3 kyoriNormalize = kyori;
			kyoriNormalize.y = 0.0f;
			kyoriNormalize.Normalize();
			m_speed.x = kyoriNormalize.x * m_SpeedMagnification;
			m_speed.z = kyoriNormalize.z * m_SpeedMagnification;

			//ほぼそのポイントに行けたので
			if (fabs(kyori.x) < m_alignmentcompletiondistance.x &&
				fabs(kyori.z) < m_alignmentcompletiondistance.z) {
				//Stayを宣言。
				tracerow->SetStay(true,m_mynumber);
				//整列完了しました隊長！！（整列完了したので自分の状態を追従に変える。
				state = Tuizyuu;
				//自分が整列完了した場所覚えておく。
				m_TracerowNum = i;
				//着席スピードリセット。
				m_speed = { 0.0f,0.0f,0.0f };
			}
			//終了条件。
			i = Game::GetInstance()->m_tracerowmanager->GetMaxrow();
		}
	}
}

void Slave::Tuizyuu_processing()
{
	//指定された列のアドレス取得。
	Tracerow* tracerow = Game::GetInstance()->m_tracerowmanager->Gettracerow(m_TracerowNum);
	//列とのベクトル求めて。
	CVector3 kyori = tracerow->Getposition() - m_position;
	CVector3 kyoriNormalize = kyori;
	kyoriNormalize.y = 0.0f;
	kyoriNormalize.Normalize();
	//加算プレイヤー追従。
	m_speed.x = kyoriNormalize.x * m_SpeedMagnification;
	m_speed.z = kyoriNormalize.z * m_SpeedMagnification;

	//ほぼそのポイントに行けたので。
	if (fabs(kyori.x) < m_alignmentcompletiondistance.x &&
		fabs(kyori.z) < m_alignmentcompletiondistance.z) {
		//止まれ。
		m_speed = { 0.0f,0.0f,0.0f };
	}
}

void Slave::Nagerare_processing()
{
	CVector3 kyori = m_markpoint - m_position;
	//距離判定（落下地点にいるかどうか）
	if (fabs(kyori.x) < m_alignmentcompletiondistance.x &&
		fabs(kyori.z) < m_alignmentcompletiondistance.z){
		//速度リセット。
		m_speed = CVector3::Zero();
		//無事落下できたので待機状態へ
		state = Taiki;
	}
}
