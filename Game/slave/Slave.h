#pragma once
#include "GameObjectManager.h"
#include "character/CharacterController.h"
#include "SlaveController.h"
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
	void Move();//�ǂ̏�Ԃł���������֐��B
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
	/// �����̃i���o�[�L�^�p�B
	/// </summary>
	/// <param name="num"></param>
	/// <returns></returns>
	void SetNumber(int num) {
		m_mynumber = num;
	}
	/// <summary>
	/// Slace�֗^���鑬�x�x�N�g���B
	/// </summary>
	/// <param name="speed"></param>
	/// <returns></returns>
	CVector3 Setspeed(CVector3 speed) {
		m_speed = speed;
	}
	/// <summary>
	/// �d�Ȃ��Ă��܂������̗����́B�����d�Ȃ��Ă�ꍇ���z�肵��Add�B
	/// </summary>
	/// <param name="force">���Z������</param>
	/// <returns></returns>
	CVector3 Addforce(CVector3 force) {
		m_force += force;
	}
private:
	
	SkinModel m_model;								//�X�L�����f���B
	SlaveController m_slaveCon;					    //Slave�R���g���[���[�B
	CVector3 m_position = { 0.0f,  0.0f,  -700.0f };
	CVector3 m_speed = CVector3::Zero();
	CVector3 m_kyori = CVector3::Zero();
	CVector3 m_distancejudgment = { 65.0f,  0.0f,  65.0f };//��������A�Ԃ��������ǂ����̔���Ɏg���B
	CVector3 m_alignmentcompletiondistance = { 10.0f,0.0f,10.0f };//���񊮗������B���������̏ꏊ�ɓ���������Ɏg���B
	CVector3 m_masterposition = CVector3::Zero();
	CVector3 m_force = CVector3::Zero();//�d�Ȃ��Ă��܂������̗����́B
	float m_friction = 0.95f;//���C�B
	float m_personalSpace = 50.0f;//�d�Ȃ��Ă��܂������̗���n�߂鋗���B
	int m_mynumber = 0;//�����̃i���o�[�B
	//�X���C����ԊǗ��B
	SuraimuState state = Taiki;
	int m_SpeedMagnification = 500; //�X�s�[�h�{���B
	int m_TracerowNum = 61;//�������Ō�ɃA�N�Z�X������ԍ��ۑ��p�B0�`99�B
};

