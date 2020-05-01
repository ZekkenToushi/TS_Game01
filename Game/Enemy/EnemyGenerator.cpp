#include "stdafx.h"
#include "EnemyGenerator.h"

EnemyGenerator::EnemyGenerator()
{
	//‰Šú¶¬B
	m_enemy[m_enemycount] = NewGO<Enemy>();
	m_enemy[m_enemycount]->SetNumber(m_enemycount);
	m_enemy[m_enemycount]->SetPosition(m_position0);  
	m_enemycount++;


}


EnemyGenerator::~EnemyGenerator()
{
}

void EnemyGenerator::Update()
{
}

void EnemyGenerator::Render()
{
}
