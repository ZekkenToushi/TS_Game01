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
	/// ���̃|�C���g�Ɍ������Đi��ł�z�����邩�ǂ����̌��ʂ�Ԃ��B
	/// </summary>
	/// <returns></returns>
	bool GetReservation(){
		return Reservation;
	}
	/// <summary>
	/// �|�C���g�ɗ\�񂷂�B���݌������Ă��܂��B
	/// </summary>
	/// <param name="yoyaku"></param>
	void SetReservation(bool yoyaku) {
		Reservation = yoyaku;
	}
	/// <summary>
	/// ���łɐ�񂪂��邩�ǂ����m�F�B
	/// </summary>
	/// <returns></returns>
	bool GetStay() {
		return Stay;
	}
	/// <summary>
	/// ���Ȃ��܂����B���łɂ���Ǝ咣���邽�߁B
	/// </summary>
	/// <param name="posiGetdaze"></param>
	void SetStay(bool posiGetdaze) {
		Stay = posiGetdaze;
	}
	/// <summary>
	/// ���̃|�C���g�̃|�W�V������Ԃ��B
	/// </summary>
	/// <returns></returns>
	CVector3 Getposition() {
		return m_position;
	}
private:
	
	int m_Num;//�|�C���g�i���o�[�B
	CVector3 m_position;//�����̃|�W�V�����B
	CVector3 m_targetposition;//�Ǐ]����^�[�Q�b�g�i�v���C���[�j�|�W�V�����B
	bool Reservation = false;//���̃|�C���g��Slave���������Ă���\��B
	bool Stay = false;//���̃|�C���g�ɂ���B
	//�e�X�g�悤�\���X���C���B
	SkinModel m_model;								//�X�L�����f���B
};

