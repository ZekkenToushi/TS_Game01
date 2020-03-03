#pragma once
#include "character/CharacterController.h"
#include "GameObjectManager.h"
#include "Tracerow.h"
class Marker;
class Player
	: public IGameObject
{
public:
	Player();
	~Player(); 
	void Update()override;
	void Render()override;
	void Move();//�����n�B
	/// <summary>
	/// �i�s�����Ɍ����悤�ɉ�]������B
	/// </summary>
	void Rotation();
	/// <summary>
	/// Tracerow���Ǘ�����B��̍쐬��m_centerrow�̒Ǐ]�����B
	/// </summary>
	//void TracerowManagement();
	/// <summary>
	/// �w�肵�����̐Ȃ�p�ӂ���B�i���̍s�̂݁j
	/// </summary>
	/// <param name="j">��ԍ�</param>
	/// <param name="i"></param>
	/// <param name="Tyousei"></param>
	//void Gyouseiretu(int j,int i);
	/// <summary>
	/// Tracerow�̉�],�v���C���[�̉�]�ɍ��킹�ė����]����B//��]�������ʒu�x�N�g����Ԃ��B
	/// </summary>
	//CVector3 TracerowRotation(CVector3 position);
	/// <summary>
	/// �w�肵��row�����B
	/// �Ⴆ��50��Slave�����ׂ�s������ɂ� 50�� (0�`49��num��position���w�肵��)���̊֐����Ăׂ΍���B
	/// </summary>
	/// <param name="num">���̃|�C���g�̃i���o�[</param>
	/// <param name="position">���̃|�C���g�̃|�W�V����</param>
	//void TracerowSet(int num, CVector3 position);
	/// <summary>
	/// Slave�ւ̖��ߌn
	/// </summary>
	void Order();
	
	CVector3 GetPosition() const
	{
		return m_position;
	}
	CVector3 GetSpeed() const
	{
		return m_speed;
	}
	CQuaternion Getrotation() 
	{
		return m_rotation;
	}
	//�i�s�����擾�B
	float GetForward() {
		return m_playerforward;
	}
	float GetSide() {
		return m_playerside;
	}
	
private:
	SkinModel m_model;								//�X�L�����f���B
	CharacterController m_charaCon;		            //�L�����N�^�[�R���g���[���[�B
	CVector3 m_position = CVector3::Zero();
	CVector3 m_speed = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();//��]�B
	float m_playerforward = 0.0f;//�v���C���[�̑O�����B
	float m_playerside = 0.0f;//�v���C���[�̉������B
	float m_friction = 0.95f;//���C�B
	float m_jumpCount = 0.0f;
	bool m_isJump = false;

	//Marker
	Marker* marker = nullptr;
	//Slave�n�B
	
};

