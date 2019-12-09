#pragma once
#include"IGameObject.h"
#include"RenderTarget.h"
#include"Player.h"
#include"Field_1.h"
//#include"Slave.h"
#include "slave/SlaveGenerator.h"
#include"tsCamera.h"
#include"Light/Light.h"
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
	//Slave* m_slave = nullptr;
	SlaveGenerator* m_slaveganerator = nullptr;
private:
	//シングルトン。
	static Game* m_instance;
	
	RenderTarget m_renderTarget;			//レンダリングターゲット。

	Field_1* m_field1 = nullptr;
	Light* m_light = nullptr;
};

