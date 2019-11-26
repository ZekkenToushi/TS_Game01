#pragma once

#include <vector>
#include <list>
#include "IGameObject.h"

class GameObjectManager
{
public:
	/// <summary>
	/// 更新。
	/// </summary>
	void Update();
	/// <summary>
	/// ゲームオブジェクトを追加。
	/// </summary>
	template <class T>
	T* NewGO()
	{
		T* newObj = new T;
		m_goList.push_back(newObj);
		return newObj;
	}
	/// <summary>
	/// ゲームオブジェクトをリストから削除
	/// </summary>
	/// <param name="go">削除するゲームオブジェクト</param>
	void DeleteGameObject(IGameObject* go) {
		//リストから見つかったら削除する。
		for (auto it = m_goList.begin();
			it != m_goList.end();
			it++
			) {
			if ((*it) == go) {
				////見つけた。
				////リストから見つかった。
				//m_goList.erase(it);
				////インスタンス自体を削除。
				//delete go;
				////削除できたので終わり。

				//削除リクエスト。
				go->RequestDelete();
				return;
			}
		}


	}
	//シングルトン。
	static GameObjectManager& GetInstance();
private:
	GameObjectManager();
	std::list< IGameObject* > m_goList;		//ゲームオブジェクトのリスト。
	//シングルトン。
	static GameObjectManager m_instance;
};


template <class A>
static inline A* NewGO() {
	return GameObjectManager::GetInstance().NewGO<A>();
};