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
	//Update関数をオーバーライド。
	void Update();
	//Render関数をオーバーライド。
	void Render();
	/// <summary>
	/// レンダリングモード。
	/// </summary>
	enum EnRenderMode {
		enRenderMode_Normal,		//通常レンダリング。
		enRenderMode_Silhouette,	//シルエットをレンダリング。
		enRenderMode_Num,			//レンダリングモードの数。
	};
	//シングルトン。
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
	static Game* m_instance;//シングルトン。
	RenderTarget m_renderTarget;			//レンダリングターゲット。
	int Stage = 0;          //ステージ選択用
	
	Light* m_light = nullptr;
};

