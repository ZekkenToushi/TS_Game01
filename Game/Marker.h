#pragma once
#include "GameObjectManager.h"
#include "character/CharacterController.h"

class Marker : public IGameObject
{
public:
	Marker();
	~Marker();
	void Update()override;
	void Render()override;
	/// <summary>
	/// マーカーの動き、プレイヤー操作と同期させる。
	/// </summary>
	void Move();
	/// <summary>
	/// Y軸上での当たり判定を行いｙ座標を決める。
	/// </summary>
	void Ycollision();

	CVector3 GetPosition() const
	{
		return m_position;
	}
private:
	SkinModel m_model;								//スキンモデル。
	CVector3 m_position = CVector3::Zero();
	CVector3 m_maxSpeed = { 500.0f,0.0f,500.0f };
	CVector3 m_speed = { 0.0f,0.0f,0.0f };
	//CVector3 m_speedOld;
	CVector3 m_standardSpeed = { 50.0f,0.0f,50.0f };
	CQuaternion m_rotation = CQuaternion::Identity();//回転。


};
