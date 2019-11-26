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
	void Move();
	void Tracerowset();//Num�ƃv���C���[�|�W�V������^����B
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
	Tracerow Gettracerow(int num) {
		return tracerow[num];
	}
private:
	SkinModel m_model;								//�X�L�����f���B
	CharacterController m_charaCon;		            //�L�����N�^�[�R���g���[���[�B
	CVector3 m_position = CVector3::Zero();
	CVector3 m_speed = CVector3::Zero();
	static constexpr int rowcount = 6;//���̐��������z����B
	Tracerow tracerow[rowcount];//Slave�����ԗ�z��B
};

