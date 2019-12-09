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

	LightConstantBuffer::SLight		m_light;				//!<���C�g�\���� ���C�g�p�̍\���̂��g���悤�ɕύX�B
	LightConstantBuffer Lcb;								//���p�萔�o�b�t�@�B����X�V�B

};

