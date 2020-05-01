#pragma once
#include"IGameObject.h"
#include"RenderTarget.h"
#include"Player.h"
#include"Field_1.h"
#include "slave/SlaveGenerator.h"
#include"tsCamera.h"
#include"Light/Light.h"
#include"TracerowManager.h"
#include"Enemy/EnemyGenerator.h"
class Game: public IGameObject
{
public:
	Game();
	~Game();
	//Update�֐����I�[�o�[���C�h�B
	void Update();
	//Render�֐����I�[�o�[���C�h�B
	void Render();
	/// <summary>
	/// �����_�����O���[�h�B
	/// </summary>
	enum EnRenderMode {
		enRenderMode_Normal,		//�ʏ탌���_�����O�B
		enRenderMode_Silhouette,	//�V���G�b�g�������_�����O�B
		enRenderMode_Num,			//�����_�����O���[�h�̐��B
	};
	//�V���O���g���B
	static Game* GetInstance();
	Player* m_player = nullptr;
	tsCamera* m_tsCamera = nullptr;
	Field_1* m_field1 = nullptr;
	//Slave* m_slave = nullptr;
	SlaveGenerator* m_slaveganerator = nullptr;
	TracerowManager* m_tracerowmanager = nullptr;
	EnemyGenerator* m_enemygenerator = nullptr;
private:
	void CreateStage0();
	static Game* m_instance;//�V���O���g���B
	RenderTarget m_renderTarget;			//�����_�����O�^�[�Q�b�g�B
	int Stage = 0;          //�X�e�[�W�I��p
	
	Light* m_light = nullptr;
};

