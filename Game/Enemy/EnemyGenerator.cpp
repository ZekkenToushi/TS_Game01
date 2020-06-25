#include "stdafx.h"
#include "EnemyGenerator.h"

EnemyGenerator::EnemyGenerator()
{
	//‰Šú¶¬B1
	m_enemy[m_enemycount] = NewGO<Enemy>();
	m_enemy[m_enemycount]->SetNumber(m_enemycount);
	m_enemy[m_enemycount]->SetPosition(m_position0); 
	m_enemy[m_enemycount]->SetFirstPosition(m_position0);
	m_enemycount++;

	//2
	m_enemy[m_enemycount] = NewGO<Enemy>();
	m_enemy[m_enemycount]->SetNumber(m_enemycount);
	m_enemy[m_enemycount]->SetPosition({ 400.0f,  -600.0f,  -3500.0f });
	m_enemy[m_enemycount]->SetFirstPosition({ 400.0f,  -600.0f,  -3500.0f });
	m_enemycount++;
	//3
	m_enemy[m_enemycount] = NewGO<Enemy>();
	m_enemy[m_enemycount]->SetNumber(m_enemycount);
	m_enemy[m_enemycount]->SetPosition({ -400.0f,  -600.0f,  -4000.0f });
	m_enemy[m_enemycount]->SetFirstPosition({ -400.0f,  -600.0f,  -4000.0f });
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
