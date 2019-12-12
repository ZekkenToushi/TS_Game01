#pragma once
#include "character/CharacterController.h"
#include "GameObjectManager.h"
#include "Tracerow.h"
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
	void TracerowManagement();
	/// <summary>
	/// Tracerow�̍s�����
	/// </summary>
	/// <param name="j"></param>
	/// <param name="i"></param>
	/// <param name="Tyousei"></param>
	void Gyouseiretu(int j,int i);
	/// <summary>
	/// �w�肵��row�����B
	/// �Ⴆ��50��Slave�����ׂ�s������ɂ� 50�� (0�`49��num��position���w�肵��)���̊֐����Ăׂ΍���B
	/// </summary>
	/// <param name="num">���̃|�C���g�̃i���o�[</param>
	/// <param name="position">���̃|�C���g�̃|�W�V����</param>
	void TracerowSet(int num, CVector3 position);

	
	CVector3 Getposition() const
	{
		return m_position;
	}
	CVector3 Getspeed() const
	{
		return m_speed;
	}
	CQuaternion Getrotation() 
	{
		return m_rotation;
	}
	int Getrowcount() {
		return Maxrow;
	}
	Tracerow* Gettracerow(int num) {
		return &tracerow[num];
	}
private:
	SkinModel m_model;								//�X�L�����f���B
	SkinModel TEST;
	CharacterController m_charaCon;		            //�L�����N�^�[�R���g���[���[�B
	CVector3 m_position = CVector3::Zero();
	CVector3 m_speed = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();//��]�B
	float m_playerforward = 0.0f;//�v���C���[�̑O�����B
	float m_playerside = 0.0f;//�v���C���[�̉������B
	float m_friction = 0.95f;//���C�B
	//tracerow�n�B
	CVector3 m_centerrow = CVector3::Zero();//�s��̒��S�B�����𒆐S��Slave�B�͐��񂷂�B
	CVector3 m_syakankyori = CVector3::Zero();//�s������ېȓ��m�̋��������Ɏg�p�B
	int m_numberfirstrow = 5;//��s�ڂ̐l���B
	int m_column = 9;//��̐��B
	int m_columnhalf = 4;//��̐��̔����B
	float m_basicsyakankyori = 70.0f;//��{�I�ȎԊԋ����B
	float m_centerrowdistance = 350.0f;//����̒��S�ƃv���C���[�Ƃ̋����B
	static constexpr int Maxrow = 61;//���̐��������z����B
	Tracerow tracerow[Maxrow];//Slave�����ԗ�z��B
	int m_rowcount = 0;//tracerow����鎞�Ɏg���B���ݍ���Ă���row�i���o�[�B
	bool m_right = true;//tracerow����鎞�Ɏg���B�E������݂ɕ��ׂ�Atrue�Ȃ�E�@false�Ȃ獶
};

