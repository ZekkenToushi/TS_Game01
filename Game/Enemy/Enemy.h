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
	/// <summary>
	/// �^�[�Q�b�g���F�p�A�g���̂�slave��.....�v���C���[�ǂ����悤��
	/// �U�����Ă܂���I�Ƃ����Œm�点�Ă����Ď����͉��Ԃł��Ƌ����Ă�����i���ꂪ�Ȃ���Enemy�͈ĎR�q�j
	/// </summary>
	/// <param name="judge">true�ŉ����Ă���F�����ł���</param>
	/// <param name="num"></param>
	void SetAtackJudgement(bool judge,int num) {
		m_atackJudgement = judge;
		m_targetNum = num;
	}


private:
	int Parameters {
		
	};


	//�G��ԊǗ��B
	EnemyState state = stay;

	SkinModel m_model;								//�X�L�����f���B

	float m_gravity = -980.0f; //cm/sec^2
	
	CVector3 m_position = CVector3::Zero();
	CVector3 m_maxSpeed = { 500.0f,0.0f,500.0f };
	CVector3 m_speed = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();//��]�B
	int m_mynumber = 0;//�����̃i���o�[�B
	bool m_atackJudgement = false;//�������U������Ă��邩�̔���B
	int m_targetNum;//�U���Ώۂ̃i���o�[�ۊǗp�B�i���������Ă����畡���K�v�H

};

