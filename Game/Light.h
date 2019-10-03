#pragma once
#include "GameObjectManager.h"
#include "LightConstantBuffer.h"

class Light 
	: public IGameObject
{
public:
	Light();
	~Light();
	void Update()override;

	LightConstantBuffer::SLight		m_light;				//!<ライト構造体 ライト用の構造体を使うように変更。
	LightConstantBuffer Lcb;								//光用定数バッファ。毎回更新。

};

