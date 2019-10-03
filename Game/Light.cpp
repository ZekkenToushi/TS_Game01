#include "stdafx.h"
#include "Light.h"


Light::Light()
{
	m_light.directionLight.direction = { 0.0f, -1.0f,0.0f, 0.0f };
	m_light.directionLight.color = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_light.specPow = 10.0f;
	m_light.Kankyoukou = { 0.4f, 0.4f, 0.4f };
}


Light::~Light()
{
}

void Light::Update()
{
	//
	Lcb.m_light = m_light;

	Lcb.Update();
}
