#pragma once
#include "GameObjectManager.h"
class Tracerow
{
public:
	Tracerow();
	~Tracerow();
	void Update();
	void Render();
	/// <summary>
	/// ���ԗ�̔ԍ����Z�b�g����
	/// </summary>
	/// <param name="set">������Num</param>
	void SetNum(int set) {
		m_Num = set;
	}
	/// <summary>
	/// �Ǐ]���Ă���i�v���C���[�j�̃|�W�V����
	/// </summary>
	/// <param name="position"></param>
	void SetTargetPosition(CVector3 position) {
		m_targetposition = position;
	}
	/// <summary>
	/// ���̃|�C���g�ɓ���邩�ǂ����̗\�񌋉ʂ�Ԃ�
	/// </summary>
	/// <returns></returns>
	bool GetReservation(){
		return Reservation;
	}
	/// <summary>
	/// ���̃|�C���g�̃|�W�V������Ԃ�
	/// </summary>
	/// <returns></returns>
	CVector3 Getposition() {
		return m_position;
	}
private:
	
	int m_Num;//�|�C���g�i���o�[�B
	CVector3 m_position;//�����̃|�W�V�����B
	CVector3 m_targetposition;//�Ǐ]����^�[�Q�b�g�i�v���C���[�j�|�W�V�����B
	bool Reservation;//���̃|�C���g��Slave���������Ă���\��B
	//�e�X�g�悤
	SkinModel m_model;								//�X�L�����f���B
};

