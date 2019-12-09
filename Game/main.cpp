#include "stdafx.h"
#include "system/system.h"
#include "Game.h"
#include "Player.h"
#include "level/Level.h"
#include"GameObjectManager.h"
#include "physics/Physics.h"
///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	
	
		//
		NewGO<Game>();
	
	//�Q�[�����[�v�B
	while (DispatchWindowMessage() == true)
	{
		//�`��J�n�B
		g_graphicsEngine->BegineRender();
		//�Q�[���p�b�h�̍X�V�B	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//GameObjectManager�̍X�V�B
		GameObjectManager::GetInstance().Update();

		//�����G���W���n�X�V�B
		g_physics.Update();
		//Debug�p�����蔻������B
		g_physics.DebugWireDraw();

		//�`��I���B
		g_graphicsEngine->EndRender();
	}
}