#pragma once
#include "GameObjectManager.h"
#include "physics/PhysicsStaticObject.h"
class Field_1
	: public IGameObject
{
public:
	Field_1();
	~Field_1();
	void Update()override;
	void Render()override;
private:
	SkinModel m_model;									//�X�L�����f���B
	CVector3 m_position = { 0.0f,  2500.0f,  0.0f };
	//�ÓI�����I�u�W�F�N�g�B
	PhysicsStaticObject m_phyStaticObject;
};

