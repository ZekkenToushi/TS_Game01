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
	//�����t���O����B
	if (m_decision == true) {

		//<Slave>�����B
		m_slavecount++;
		m_slave[m_slavecount] = NewGO<Slave>();
		m_slave[m_slavecount]->SetNumber(m_slavecount);
		m_decision = false;

	}
}
