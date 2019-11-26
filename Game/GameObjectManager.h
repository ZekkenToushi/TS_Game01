#pragma once

#include <vector>
#include <list>
#include "IGameObject.h"

class GameObjectManager
{
public:
	/// <summary>
	/// �X�V�B
	/// </summary>
	void Update();
	/// <summary>
	/// �Q�[���I�u�W�F�N�g��ǉ��B
	/// </summary>
	template <class T>
	T* NewGO()
	{
		T* newObj = new T;
		m_goList.push_back(newObj);
		return newObj;
	}
	/// <summary>
	/// �Q�[���I�u�W�F�N�g�����X�g����폜
	/// </summary>
	/// <param name="go">�폜����Q�[���I�u�W�F�N�g</param>
	void DeleteGameObject(IGameObject* go) {
		//���X�g���猩��������폜����B
		for (auto it = m_goList.begin();
			it != m_goList.end();
			it++
			) {
			if ((*it) == go) {
				////�������B
				////���X�g���猩�������B
				//m_goList.erase(it);
				////�C���X�^���X���̂��폜�B
				//delete go;
				////�폜�ł����̂ŏI���B

				//�폜���N�G�X�g�B
				go->RequestDelete();
				return;
			}
		}


	}
	//�V���O���g���B
	static GameObjectManager& GetInstance();
private:
	GameObjectManager();
	std::list< IGameObject* > m_goList;		//�Q�[���I�u�W�F�N�g�̃��X�g�B
	//�V���O���g���B
	static GameObjectManager m_instance;
};


template <class A>
static inline A* NewGO() {
	return GameObjectManager::GetInstance().NewGO<A>();
};