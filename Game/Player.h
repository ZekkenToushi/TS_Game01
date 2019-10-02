#pragma once
#include "character/CharacterController.h"
#include "GameObjectManager.h"
class Player
	: public IGameObject
{
public:
	Player();
	~Player();
	void Update()override;
	void Render()override;
	void Move();
	CVector3 GetPosition()
	{
		return m_position;
	}
private:
	SkinModel m_model;									//スキンモデル。
	//CharacterController m_charaCon;		            //キャラクターコントローラー。
	CVector3 m_position = CVector3::Zero();
	CVector3 m_speed = CVector3::Zero();
};

