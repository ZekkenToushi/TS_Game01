#pragma once
#include"IGameObject.h"
#include "Player.h"
#include"Field_1.h"
#include "tsCamera.h"
class Game: public IGameObject
{
public:
	Game();
	~Game();
	//Update関数をオーバーライド。
	void Update();
	//Render関数をオーバーライド。
	void Render();
	//シングルトン。
	static Game* GetInstance();
	Player* m_player = nullptr;
	tsCamera* m_tsCamera = nullptr;
private:
	//シングルトン。
	static Game* m_instance;
	
	Field_1* m_field1 = nullptr;
	
};

