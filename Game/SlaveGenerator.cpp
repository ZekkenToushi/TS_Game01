#include "stdafx.h"
#include "SlaveGenerator.h"


SlaveGenerator::SlaveGenerator()
{
	
}


SlaveGenerator::~SlaveGenerator()
{
}

void SlaveGenerator::Update()
{
	//����B
	Decision();

	//�����t���O����B
	if (m_decision == true) {
		
		//<Slave>�����B
		m_slave = NewGO<Slave>();
		m_decision = false;
		
	}
}

void SlaveGenerator::Render()
{
}

void SlaveGenerator::Decision()
{
	//���̐�������B
	if (g_pad->IsTrigger(enButtonRB1)) {
		m_decision = true;
	}
}
