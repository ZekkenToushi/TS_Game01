#pragma once
#include "GameObjectManager.h"
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

};

