#pragma once
#include "character/CharacterController.h"
enum  EnemyState {
	stay,
	move,
	attack
};
class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();
	void Update()override;
	void Render()override;

	void StateManagement();
	void Stay();
	void Move();
	void Attack();
	void Death();
	/// <summary>
	/// ��{�s���B�ǂ̏�Ԃł����������B
	/// </summary>
	void Basic();

	/// <summary>
	/// �����̃i���o�[�L�^�p�B
	/// </summary>
	/// <param name="num"></param>
	/// <returns></returns>
	void SetNumber(int num) {
		m_mynumber = num;
	}
	void SetPosition(CVector3 posi) {
		m_position = posi;
	}
	void SetFirstPosition(CVector3 posi) {
		m_firstPosition = posi;
	}
	/// <summary>
	/// �U�����Ă܂���I�����͉��Ԃł�.�Ƃ����ŋ����Ă�����
	/// </summary>
	/// <param name="judge">true�ŉ����Ă���F�����ł���</param>
	/// <param name="hp">�^�����_���[�W</param>
	/// <param name="num">������slave�ԍ�</param>
	//void SetAtackJudgement(bool judge,int addhp,int num) {
	//	m_atackJudgement = judge;
	//	enemy.HP += addhp;
	//	if(m_targetNum < 0)
	//	m_targetNum = num;
	//}


private:
	//�p�����[�^�B
	struct Parameters{
		int Max_HP = 100;
		int HP = Max_HP;
		int Lv = 1;
	};
	struct 
		Parameters enemy;

	CharacterController m_charaCon;		            //�L�����N�^�[�R���g���[���[�B

	//�G��ԊǗ��B
	EnemyState state = stay;

	SkinModel m_model;								//�X�L�����f���B

	float m_gravity = -980.0f; //cm/sec^2
	
	CVector3 m_position = CVector3::Zero();
	CVector3 m_firstPosition = CVector3::Zero();
	CVector3 m_maxSpeed = { 500.0f,0.0f,500.0f };
	CVector3 m_speed = CVector3::Zero();
	CVector3 m_SeeDistance = { 600.0f,0.0f,600.0f };//�ڎ��͈�(���G�͈�)�B
	CVector3 m_territory = { 600.0f,0.0f,600.0f };//����͈�(��������鋗���A�ݒ�n�_����ǂ̂��炢���ꂽ����߂邩���߂鋗��)�B
	CVector3 m_range = { 100.0f,0.0f,100.0f };//�˒��͈́B
	CQuaternion m_rotation = CQuaternion::Identity();//��]�B
	int m_mynumber = 0;//�����̃i���o�[�B
	bool m_atackJudgement = false;//�������U������Ă��邩�̔���B
	bool m_KYOUSEIkitaku = false;//�����A��[�h�̃t���O�B
	bool m_kitaku = false;//�A��[�h�̃t���O�B
	int m_targetNum;//�U���Ώۂ̃i���o�[�ۊǗp�B�i���������Ă����畡���K�v�H
	int m_timer = 100;//CT����p�^�C�}�[�B
	int m_coolTime = 200;//�U��CT�B
	int m_speedMagnification = 10; //�X�s�[�h�{���B

};

