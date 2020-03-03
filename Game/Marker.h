#pragma once
#include "GameObjectManager.h"
#include "character/CharacterController.h"

class Marker : public IGameObject
{
public:
	Marker();
	~Marker();
	void Update()override;
	void Render()override;
	/// <summary>
	/// �}�[�J�[�̓����A�v���C���[����Ɠ���������B
	/// </summary>
	void Move();
	/// <summary>
	/// Y����ł̓����蔻����s�������W�����߂�B
	/// </summary>
	void Ycollision();

	CVector3 GetPosition() const
	{
		return m_position;
	}
private:
	SkinModel m_model;								//�X�L�����f���B
	CVector3 m_position = CVector3::Zero();
	CVector3 m_maxSpeed = { 500.0f,0.0f,500.0f };
	CVector3 m_speed = { 0.0f,0.0f,0.0f };
	//CVector3 m_speedOld;
	CVector3 m_standardSpeed = { 50.0f,0.0f,50.0f };
	CQuaternion m_rotation = CQuaternion::Identity();//��]�B


};
