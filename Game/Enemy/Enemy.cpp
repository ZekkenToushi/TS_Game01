#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/aikonn.cmo");
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

void Enemy::Stay()
{
	//その場で待機モーション。

	//もし攻撃されたら→敵へ移動→攻撃。


}

void Enemy::Move()
{
	//対象の位置まで移動する。

	//対象が敵ならば攻撃へ移行。

	//対象がいないなら元と位置に戻り、待機へ。

}

void Enemy::Attack()
{
	//対象への距離が離れていたらmoveへ

	//対象への距離が近ければ攻撃モーション

	//HPへ攻撃。

	//攻撃CT判定。

}

void Enemy::Death()
{
	//もし自分のHPが0以下ならば

	//死亡モーション。Delete this
}
