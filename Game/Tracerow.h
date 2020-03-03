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
	/// 並ぶ列の番号をセットする。
	/// </summary>
	/// <param name="set">自分のNum</param>
	void SetNum(int set) {
		m_num = set;
	}
	/// <summary>
	/// 並ぶ列の最大番号をセットする。
	/// </summary>
	/// <param name="set">最大数</param>
	void SetMaxNum(int set) {
		m_maxnum = set;
	}
	/// <summary>
	/// 追従している（プレイヤー）のポジション
	/// </summary>
	/// <param name="position"></param>
	void SetTargetPosition(CVector3 position) {
		m_targetposition = position;
	}
	/// <summary>
	/// positionセット、成功すれば↑いらない
	/// </summary>
	/// <param name="position"></param>
	void Setposition(CVector3 position) {
		m_position = position;
	}
	/// <summary>
	/// このポイントに向かって進んでる奴がいるかどうかの結果を返す。
	/// </summary>
	/// <returns></returns>
	bool GetReservation(){
		return Reservation;
	}
	/// <summary>
	/// ポイントに予約する。現在向かっています。
	/// </summary>
	/// <param name="yoyaku"></param>
	void SetReservation(bool yoyaku) {
		Reservation = yoyaku;
	}
	/// <summary>
	/// すでに先約があるかどうか確認。
	/// </summary>
	/// <returns></returns>
	bool GetStay() {
		return Stay;
	}
	/// <summary>
	/// 着席しました。すでにいると主張するため。
	/// </summary>
	/// <param name="posiGetdaze"></param>
	void SetStay(bool posiGetdaze,int num) {
		m_slavenum = num;
		Stay = posiGetdaze;
	}
	/// <summary>
	/// m_slavenumを返す。
	/// </summary>
	/// <returns></returns>
	int GetSlaveNum() {
		return m_slavenum;
	}

	/// <summary>
	/// このポイントのポジションを返す。
	/// </summary>
	/// <returns></returns>
	CVector3 Getposition() {
		return m_position;
	}
private:
	
	int m_num;//ポイントナンバー。
	int m_maxnum = 50;//最大ナンバー。
	int m_slavenum = 0;//現在この席についているSlaveナンバーを保存。
	CVector3 m_position;//自分のポジション。
	CVector3 m_targetposition;//追従するターゲット（プレイヤー）ポジション。
	CVector3 center = CVector3::Zero();//中心を取得して保持しておく。
	CQuaternion m_rotation = CQuaternion::Identity();//回転。
	bool Reservation = false;//このポイントにSlaveが向かっている予約。
	bool Stay = false;//このポイントにいる。
	//テストよう表示スライム。
	SkinModel m_model;								//スキンモデル。
};

