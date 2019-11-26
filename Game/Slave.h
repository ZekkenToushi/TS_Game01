#pragma once
#include "GameObjectManager.h"
#include "character/CharacterController.h"

enum SuraimuState {
	Taiki,
	Tuizyuu

};
class Slave : public IGameObject
{
public:
	Slave();
	~Slave();
	void Update()override;
	void Render()override;
	
	void Search();
	void Order();
	void Move();

private:
	
	SkinModel m_model;								//�X�L�����f���B
	CharacterController m_charaCon;		            //�L�����N�^�[�R���g���[���[�B
	CVector3 m_position = { 0.0f,  0.0f,  -700.0f };
	CVector3 m_speed = CVector3::Zero();
	CVector3 MasterPosition = CVector3::Zero();
	//�X���C����ԊǗ��B
	SuraimuState state = Taiki;
	int SpeedMagnification = 500; //�X�s�[�h�{���B
};

