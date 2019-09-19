#include"stdafx.h"
#include "GameObjectManager.h"

//GameObjectManagerクラスのインスタンス。
GameObjectManager GameObjectManager::m_instance;

GameObjectManager::GameObjectManager() {

	
}

void GameObjectManager::Update()
{
	//登録されているゲームオブジェクトの更新処理を呼ぶ。
	for (auto go : m_goList) {
		go->Update();
	}
	//プリレンダーポスレンダーなど
	//別々のfor分にするのはレンダーなど全て終わってから影光など表現レンダーを書いたりするため。
	for (auto go : m_goList) {
		go->Render();
	}
	//全てのゲームオブジェクトの1フレーム分の処理が終わってから削除する。
	for (auto it = m_goList.begin();
		it != m_goList.end();) {
		if ((*it)->IsRequestDelete()) {
			//削除リクエストを受けているので削除。
			delete* it;
			it = m_goList.erase(it);
		}
		else {
			//リクエストを受けていない。
			it++;
		}
	}


}

GameObjectManager & GameObjectManager::GetInstance()
{
	return m_instance;
}


