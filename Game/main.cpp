#include "stdafx.h"
#include "system/system.h"
#include "Game.h"
#include "Player.h"
#include "level/Level.h"
#include"GameObjectManager.h"
#include "physics/Physics.h"
///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	
	
		//
		NewGO<Game>();
	
	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		//描画開始。
		g_graphicsEngine->BegineRender();
		//ゲームパッドの更新。	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//GameObjectManagerの更新。
		GameObjectManager::GetInstance().Update();

		//物理エンジン系更新。
		g_physics.Update();
		//Debug用当たり判定可視化。
		g_physics.DebugWireDraw();

		//描画終了。
		g_graphicsEngine->EndRender();
	}
}