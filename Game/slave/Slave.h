#pragma once
#include "GameObjectManager.h"
#include "character/CharacterController.h"

enum SuraimuState {
	Taiki,//���̏�ɑҋ@�B0
	Mukau,//�v���C���[(��)�Ɍ������B1
	Tuizyuu//�v���C���[�ɒǏ]�B2

};
class Slave : public IGameObject
{
public:
	Slave();
	~Slave();
	void Update()override;
	void Render()override;
	
	void Search();
	void Move();
	/// <summary>
	/// State�ɉ����ď������Ăт����B
	/// </summary>
	void Statemanagement();
	void Taiki_processing();//�T�{�邺�x�C�x�[�B
	void Mukau_processing();//�������������܂��I�I�����I�I�B
	void Tuizyuu_processing();//�ꐶ���Ă����܂������I�I�i�Ǐ]��ԁB

	/// <summary>
	/// position�擾�B
	/// </summary>
	/// <returns></returns>
	CVector3 GetPosition() const
	{
		return m_position;
	}
	/// <summary>
	/// Slace�֗^���鑬�x�x�N�g���B
	/// </summary>
	/// <param name="speed"></param>
	/// <returns></returns>
	CVector3 Setspeed(CVector3 speed) {
		m_speed = speed;
	}
private:
	
	SkinModel m_model;								//�X�L�����f���B
	CharacterController m_charaCon;		            //�L�����N�^�[�R���g���[���[�B
	CVector3 m_position = { 0.0f,  0.0f,  -700.0f };
	CVector3 m_speed = CVector3::Zero();
	CVector3 m_kyori = CVector3::Zero();
	CVector3 m_distancejudgment = { 65.0f,  0.0f,  65.0f };//��������A�Ԃ��������ǂ����̔���Ɏg���B
	CVector3 m_alignmentcompletiondistance = { 3.0f,0.0f,3.0f };//���񊮗������B���������̏ꏊ�ɓ���������Ɏg���B
	CVector3 m_masterposition = CVector3::Zero();

	float m_friction = 0.95f;//���C�B
	//�X���C����ԊǗ��B
	SuraimuState state = Taiki;
	int m_SpeedMagnification = 500; //�X�s�[�h�{���B
	int m_TracerowNum = 0;//�������Ō�ɃA�N�Z�X������ԍ��ۑ��p�B0�`99�B
};

