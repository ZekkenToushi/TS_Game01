#pragma once
#include"IGameObject.h"
#include"Slave.h"

class SlaveGenerator 
	: public IGameObject
{
public:
	SlaveGenerator();
	~SlaveGenerator();
	void Update()override;
	void Render()override;
	void Decision(); //�����̔���B
	/// <summary>
	/// ���ݏ������Ă���Slave���B
	/// </summary>
	/// <returns></returns>
	int GetSlaveCount() {
		return m_slavecount;
	}
	/// <summary>
	/// �n���ꂽ�i���o�[��Slave�|�C���^��Ԃ��B
	/// </summary>
	/// <param name="num">�w�肷��i���o�[</param>
	/// <returns></returns>
	Slave* GetSlave(int num) {
		return m_slave[num];
	}
private:
	static constexpr int Maxrow = 61;//���̐��������z����B�ꎞ�IGet����
	Slave* m_slave[Maxrow];
	bool m_decision = false;
	int timer = 0;
	int m_slavecount = 0;//���ݏ�������Slave�̐��B
};

