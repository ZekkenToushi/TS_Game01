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
	//Update�֐����I�[�o�[���C�h�B
	void Update();
	//Render�֐����I�[�o�[���C�h�B
	void Render();
	//�V���O���g���B
	static Game* GetInstance();
	Player* m_player = nullptr;
	tsCamera* m_tsCamera = nullptr;
private:
	//�V���O���g���B
	static Game* m_instance;
	
	Field_1* m_field1 = nullptr;
	
};

