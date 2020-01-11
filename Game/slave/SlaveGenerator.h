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
	void Decision(); //生成の判定。
	/// <summary>
	/// 現在召喚しているSlave数。
	/// </summary>
	/// <returns></returns>
	int GetSlaveCount() {
		return m_slavecount;
	}
	/// <summary>
	/// 渡されたナンバーのSlaveポインタを返す。
	/// </summary>
	/// <param name="num">指定するナンバー</param>
	/// <returns></returns>
	Slave* GetSlave(int num) {
		return m_slave[num];
	}
private:
	static constexpr int Maxrow = 61;//この数だけ↓配列作る。一時的Getつくれ
	Slave* m_slave[Maxrow];
	bool m_decision = false;
	int timer = 0;
	int m_slavecount = 0;//現在召喚したSlaveの数。
};

