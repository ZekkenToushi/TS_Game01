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
	/// 並ぶ列の番号をセットする
	/// </summary>
	/// <param name="set">自分のNum</param>
	void SetNum(int set) {
		m_Num = set;
	}
	/// <summary>
	/// 追従している（プレイヤー）のポジション
	/// </summary>
	/// <param name="position"></param>
	void SetTargetPosition(CVector3 position) {
		m_targetposition = position;
	}
	/// <summary>
	/// このポイントに入れるかどうかの予約結果を返す
	/// </summary>
	/// <returns></returns>
	bool GetReservation(){
		return Reservation;
	}
	/// <summary>
	/// このポイントのポジションを返す
	/// </summary>
	/// <returns></returns>
	CVector3 Getposition() {
		return m_position;
	}
private:
	
	int m_Num;//ポイントナンバー。
	CVector3 m_position;//自分のポジション。
	CVector3 m_targetposition;//追従するターゲット（プレイヤー）ポジション。
	bool Reservation;//このポイントにSlaveが向かっている予約。
	//テストよう
	SkinModel m_model;								//スキンモデル。
};

