#include "stdafx.h"
#include "Enemy.h"
#include "Game.h"
Enemy::Enemy()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/medamaaka.cmo");
	//キャラクターコントローラーを初期化。
	m_charaCon.Init(
		50.0,			//半径。 
		50.0f,			//高さ。
		m_position	//初期位置。
	);
	//初期位置を記憶しておく。
	m_firstPosition = m_position;
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	//状態管理。現在の状態に合わせて適切な関数呼び出しを行う。
	StateManagement();
	//死亡判定。
	Death();
	//一時的重力
	m_speed.y += m_gravity / 60.0f;

	//m_position += m_charaCon.Execute(1.0f / 60, m_speed);
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
}

void Enemy::Render()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void Enemy::StateManagement()
{
	Basic();
	if (m_KYOUSEIkitaku == false) {
		switch (state) {
		case stay://その場に待機。
			Stay();
			break;
		case move://。
			Move();
			break;
		case attack://。
			Attack();
			break;
		}
	}
}

void Enemy::Stay()
{

	//初期位置からの距離。
	CVector3 Movekyori = m_firstPosition - m_position;
	//もし守備位置から一定離れてしまった場合　①　。
	if (fabs(Movekyori.x) > m_range.x ||
		fabs(Movekyori.z) > m_range.z) {
		//帰宅モードへ。
		m_kitaku = true;
	}

	//現在召喚されている数だけ距離判定を行う。		
	for (int i = 0;i < Game::GetInstance()->m_slaveganerator->GetSlaveCount();i++) {
		//敵との距離を測る
		Slave* slave = Game::GetInstance()->m_slaveganerator->GetSlave(i+1);
		CVector3 target = slave->GetPosition();
		CVector3 kyori = target - m_position;
		//索敵範囲に入ったら。
		if (fabs(kyori.x) < m_SeeDistance.x &&
			fabs(kyori.z) < m_SeeDistance.z) {
			m_targetNum = i+1;
			//移動へ。
			state = move;
			m_kitaku = false;
		}
	}
	
	//自分のポジションに戻る。
	//もし守備位置から一定離れてしまった場合　②　まだ帰宅フラグがオンならば。
	//初期位置へ帰る（キャラコン適用後m_speedにしよう）
	if (m_kitaku == true) {
		CVector3 MovekyoriNomalize = Movekyori;
		MovekyoriNomalize.Normalize();
		MovekyoriNomalize.y = 0.0f;
		m_position += MovekyoriNomalize * m_speedMagnification;
		//初期位置に戻れたら。
		if (fabs(Movekyori.x) < m_range.x &&
			fabs(Movekyori.z) < m_range.z) {
			//帰宅解除。
			m_kitaku = false;
			
		}
	}

	//その場で待機モーション。

}

void Enemy::Move()
{
	//対象の位置まで移動する。
	//敵との距離を測る。
	Slave* slave = Game::GetInstance()->m_slaveganerator->GetSlave(m_targetNum);
	CVector3 target = slave->GetPosition();
	CVector3 kyori = target - m_position;
	CVector3 kyoriNormalize = kyori;
	kyoriNormalize.Normalize();
	kyoriNormalize.y = 0.0f;
	m_position += kyoriNormalize * m_speedMagnification;
	//射程範囲に入ったら。
	if (fabs(kyori.x) < m_range.x &&
		fabs(kyori.z) < m_range.z) {
		//対象への距離が近ければ攻撃モーション。
		state = attack;
	}
	//対象が敵ならば攻撃へ移行。

	//対象がいないなら元と位置に戻り、待機へ。

}

void Enemy::Attack()
{
	//対象への距離が離れていたらmoveへ
	//敵との距離を測る
	Slave* slave = Game::GetInstance()->m_slaveganerator->GetSlave(m_targetNum);
	CVector3 target = slave->GetPosition();
	CVector3 kyori = target - m_position;
	//射程範囲に入ったら。
	if (fabs(kyori.x) > m_range.x &&
		fabs(kyori.z) > m_range.z) {
		//移動へ。
		state = move;
	}

	//攻撃CT判定。
	
	if (m_timer > m_coolTime) 
	{
		//slaveへ攻撃。
		slave->AddHP(-5);
		//もし対象を殺したら。
		if (slave->GetHP() <= 0) {
			state = stay;
		}
		//リセット。
		m_timer = 0;
	}
	

}

void Enemy::Death()
{
	//もし自分のHPが0以下ならば
	//死亡判定。
	if (enemy.HP <= 0) {
		//死亡モーション。


		RequestDelete();
	};
	
}

void Enemy::Basic()
{
	//初期位置からの距離。
	CVector3 Movekyori = m_firstPosition - m_position;
	//もし守備位置から一定離れてしまった場合。
	if (fabs(Movekyori.x) > m_territory.x ||
		fabs(Movekyori.z) > m_territory.z) {
		//強制帰宅モードへ。
		m_KYOUSEIkitaku = true;
	}
	//初期位置へ帰る（キャラコン適用後m_speedにしよう）
	if (m_KYOUSEIkitaku == true) {
		CVector3 MovekyoriNomalize = Movekyori;
		MovekyoriNomalize.Normalize();
		MovekyoriNomalize.y = 0.0f;
		m_position += MovekyoriNomalize * m_speedMagnification;
		//初期位置に戻れたら。
		if (fabs(Movekyori.x) < m_range.x &&
			fabs(Movekyori.z) < m_range.z) {
			//強制帰宅解除。
			m_KYOUSEIkitaku = false;
			state =stay;
		}
	}
	//test
	/*if (g_pad->IsTrigger(enButtonLB1)) {
		int a;
		a++;
	}*/
	//攻撃CT回復。
	m_timer++;
}
