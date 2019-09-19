#include"stdafx.h"
#include "GameObjectManager.h"

//GameObjectManager�N���X�̃C���X�^���X�B
GameObjectManager GameObjectManager::m_instance;

GameObjectManager::GameObjectManager() {

	
}

void GameObjectManager::Update()
{
	//�o�^����Ă���Q�[���I�u�W�F�N�g�̍X�V�������ĂԁB
	for (auto go : m_goList) {
		go->Update();
	}
	//�v�������_�[�|�X�����_�[�Ȃ�
	//�ʁX��for���ɂ���̂̓����_�[�ȂǑS�ďI����Ă���e���ȂǕ\�������_�[���������肷�邽�߁B
	for (auto go : m_goList) {
		go->Render();
	}
	//�S�ẴQ�[���I�u�W�F�N�g��1�t���[�����̏������I����Ă���폜����B
	for (auto it = m_goList.begin();
		it != m_goList.end();) {
		if ((*it)->IsRequestDelete()) {
			//�폜���N�G�X�g���󂯂Ă���̂ō폜�B
			delete* it;
			it = m_goList.erase(it);
		}
		else {
			//���N�G�X�g���󂯂Ă��Ȃ��B
			it++;
		}
	}


}

GameObjectManager & GameObjectManager::GetInstance()
{
	return m_instance;
}


