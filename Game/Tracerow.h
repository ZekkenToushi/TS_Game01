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
	/// ���ԗ�̔ԍ����Z�b�g����B
	/// </summary>
	/// <param name="set">������Num</param>
	void SetNum(int set) {
		m_num = set;
	}
	/// <summary>
	/// ���ԗ�̍ő�ԍ����Z�b�g����B
	/// </summary>
	/// <param name="set">�ő吔</param>
	void SetMaxNum(int set) {
		m_maxnum = set;
	}
	/// <summary>
	/// �Ǐ]���Ă���i�v���C���[�j�̃|�W�V����
	/// </summary>
	/// <param name="position"></param>
	void SetTargetPosition(CVector3 position) {
		m_targetposition = position;
	}
	/// <summary>
	/// position�Z�b�g�A��������΁�����Ȃ�
	/// </summary>
	/// <param name="position"></param>
	void Setposition(CVector3 position) {
		m_position = position;
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
	void SetStay(bool posiGetdaze,int num) {
		m_slavenum = num;
		Stay = posiGetdaze;
	}
	/// <summary>
	/// m_slavenum��Ԃ��B
	/// </summary>
	/// <returns></returns>
	int GetSlaveNum() {
		return m_slavenum;
	}

	/// <summary>
	/// ���̃|�C���g�̃|�W�V������Ԃ��B
	/// </summary>
	/// <returns></returns>
	CVector3 Getposition() {
		return m_position;
	}
private:
	
	int m_num;//�|�C���g�i���o�[�B
	int m_maxnum = 50;//�ő�i���o�[�B
	int m_slavenum = 0;//���݂��̐Ȃɂ��Ă���Slave�i���o�[��ۑ��B
	CVector3 m_position;//�����̃|�W�V�����B
	CVector3 m_targetposition;//�Ǐ]����^�[�Q�b�g�i�v���C���[�j�|�W�V�����B
	CVector3 center = CVector3::Zero();//���S���擾���ĕێ����Ă����B
	CQuaternion m_rotation = CQuaternion::Identity();//��]�B
	bool Reservation = false;//���̃|�C���g��Slave���������Ă���\��B
	bool Stay = false;//���̃|�C���g�ɂ���B
	//�e�X�g�悤�\���X���C���B
	SkinModel m_model;								//�X�L�����f���B
};

