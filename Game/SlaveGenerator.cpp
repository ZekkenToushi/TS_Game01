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
	//判定。
	Decision();

	//生成フラグ判定。
	if (m_decision == true) {
		
		//<Slave>生成。
		m_slave = NewGO<Slave>();
		m_decision = false;
		
	}
}

void SlaveGenerator::Render()
{
}

void SlaveGenerator::Decision()
{
	//仮の生成判定。
	if (g_pad->IsTrigger(enButtonRB1)) {
		m_decision = true;
	}
}
