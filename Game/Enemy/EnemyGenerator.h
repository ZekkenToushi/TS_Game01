#pragma once
#include"IGameObject.h"
#include "Enemy.h"

class EnemyGenerator
	: public IGameObject
{
public:
	EnemyGenerator();
	~EnemyGenerator();
	void Update()override;
	void Render()override;

private:
	static constexpr int Max = 50;//敵の最大数制限。
	Enemy* m_enemy[Max];
	int m_enemycount = 0;//現在召喚したenemyの数。
	//初期ポジションとして渡す
	CVector3 m_position0 = { 0.0f,  -500.0f,  -1000.0f };
};

