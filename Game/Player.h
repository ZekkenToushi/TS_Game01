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
	SkinModel m_model;									//�X�L�����f���B
	//CharacterController m_charaCon;		            //�L�����N�^�[�R���g���[���[�B
	CVector3 m_position = CVector3::Zero();
	CVector3 m_speed = CVector3::Zero();
};

