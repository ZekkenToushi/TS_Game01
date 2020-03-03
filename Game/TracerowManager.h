#pragma once
#include "GameObjectManager.h"
#include "Tracerow.h"

class TracerowManager
	: public IGameObject
{
public:
	TracerowManager();
	~TracerowManager();
	//Update�֐����I�[�o�[���C�h�B
	void Update();
	//Render�֐����I�[�o�[���C�h�B
	void Render();

	/// <summary>
	/// Tracerow���Ǘ�����B��̍쐬��m_centerrow(���S�A���S�̓v���C���[�֒Ǐ]�j�̒Ǐ]�����B
	/// </summary>
	void TRManagement();

	/// <summary>
	/// �w�肵�����̐Ȃ�p�ӂ���B�i���̍s�̂݁j
	/// </summary>
	/// <param name="j">��ԍ�</param>
	/// <param name="i"></param>
	/// <param name="Tyousei"></param>
	void Gyouseiretu(int j, int i);

	/// <summary>
	/// Tracerow�̉�],�v���C���[�̉�]�ɍ��킹�ė����]����B//��]�������ʒu�x�N�g����Ԃ��B
	/// </summary>
	CVector3 TracerowRotation(CVector3 position);

	/// <summary>
	/// �w�肵��row�����B
	/// �Ⴆ��50��Slave�����ׂ�s������ɂ� 50�� (0�`49��num��position���w�肵��)���̊֐����Ăׂ΍���B
	/// </summary>
	/// <param name="num">���̃|�C���g�̃i���o�[</param>
	/// <param name="position">���̃|�C���g�̃|�W�V����</param>
	void TracerowSet(int num, CVector3 position);

	/// <summary>
	/// �o���\��slave��T���A��ԎႢ�Ȃɂ���slave�ԍ���Ԃ��B-1��Ԃ������͒N�����Ȃ��B
	/// </summary>
	int SearchReadyNum();

	int GetMaxrow() {
		return Maxrow;
	}
	Tracerow* Gettracerow(int num) {
		return &tracerow[num];
	}
private:
	SkinModel TEST;
	CQuaternion m_rotation = CQuaternion::Identity();//��]�B
	//tracerow�n�B
	CVector3 m_centerrow = CVector3::Zero();//�s��̒��S�B�����𒆐S��Slave�B�͐��񂷂�B
	CVector3 m_rowForward = CVector3::Zero();//�s��̑O�����B�i�v���C���[�ւ̃x�N�g���j�B
	CVector3 m_seatPos = CVector3::Zero();//�s��̒��S���炻�ꂼ��̃|�C���g�ւ̃x�N�g���B�s������ۋ��������Ɏg�p�B
	int m_numberfirstrow = 5;//��s�ڂ̐l���B
	int m_column = 9;//��̐��B
	int m_columnhalf = 4;//��̐��̔����B
	float m_syakankyori = 70.0f;//��{�I�ȎԊԋ����B
	float m_centerrowdistance = 350.0f;//����̒��S�ƃv���C���[�Ƃ̋����B
	static constexpr int Maxrow = 61;//���̐��������z����B
	Tracerow tracerow[Maxrow];//Slave�����ԗ�z��B
	int m_rowcount = 0;//tracerow����鎞�Ɏg���B���ݍ���Ă���row�i���o�[�B
	bool m_right = true;//tracerow����鎞�Ɏg���B�E������݂ɕ��ׂ�Atrue�Ȃ�E�@false�Ȃ獶
};


