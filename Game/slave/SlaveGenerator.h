#pragma once
#include"IGameObject.h"
#include"Slave.h"

class SlaveGenerator 
	: public IGameObject
{
public:
	SlaveGenerator();
	~SlaveGenerator();
	void Update()override;
	void Render()override;
	void Decision(); //ê∂ê¨ÇÃîªíËÅB
private:
	Slave* m_slave = nullptr;
	bool m_decision = false;
	int timer = 0;
};

