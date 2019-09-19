#pragma once
#include"IGameObject.h"
#include "Player.h"
//#include "Camera.h"
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
private:
	//シングルトン。
	static Game* m_instance;
	Player* m_player = nullptr;

};

