#pragma once
#include "character/CharacterController.h"
#include "GameObjectManager.h"
#include "Tracerow.h"
class Player
	: public IGameObject
{
public:
	Player();
	~Player();
	void Update()override;
	void Render()override;
	void Move();//動き系。
	/// <summary>
	/// 進行方向に向くように回転させる。
	/// </summary>
	void Rotation();
	void Tracerowset();//Numとプレイヤーポジションを与える。
	CVector3 GetPosition() const
	{
		return m_position;
	}
	CVector3 Getspeed() const
	{
		return m_speed;
	}
	int Getrowcount() {
		return rowcount;
	}
	Tracerow* Gettracerow(int num) {
		return &tracerow[num];
	}
private:
	SkinModel m_model;								//スキンモデル。
	CharacterController m_charaCon;		            //キャラクターコントローラー。
	CVector3 m_position = CVector3::Zero();
	CVector3 m_speed = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();//回転。
	float m_playerforward = 0.0f;//プレイヤーの前方向。
	float m_playerside = 0.0f;//プレイヤーの横方向。
	static constexpr int rowcount = 6;//この数だけ↓配列作る。
	Tracerow tracerow[rowcount];//Slaveが並ぶ列配列。
};

