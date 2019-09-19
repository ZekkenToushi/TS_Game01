#pragma once
#include"IGameObject.h"
#include "Player.h"
//#include "Camera.h"
class Game: public IGameObject
{
public:
	Game();
	~Game();
	//Update�֐����I�[�o�[���C�h�B
	void Update();
	//Render�֐����I�[�o�[���C�h�B
	void Render();
	//�V���O���g���B
	static Game* GetInstance();
private:
	//�V���O���g���B
	static Game* m_instance;
	Player* m_player = nullptr;

};

