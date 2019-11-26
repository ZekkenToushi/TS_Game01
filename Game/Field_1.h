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
	SkinModel m_model;									//スキンモデル。
	CVector3 m_position = { 0.0f,  2500.0f,  0.0f };
	//静的物理オブジェクト。
	PhysicsStaticObject m_phyStaticObject;
};

