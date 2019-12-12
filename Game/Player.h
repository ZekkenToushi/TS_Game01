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
	void Move();//動き系。
	/// <summary>
	/// 進行方向に向くように回転させる。
	/// </summary>
	void Rotation();
	/// <summary>
	/// Tracerowを管理する。列の作成とm_centerrowの追従処理。
	/// </summary>
	void TracerowManagement();
	/// <summary>
	/// Tracerowの行を作る
	/// </summary>
	/// <param name="j"></param>
	/// <param name="i"></param>
	/// <param name="Tyousei"></param>
	void Gyouseiretu(int j,int i);
	/// <summary>
	/// 指定したrowを作る。
	/// 例えば50個のSlaveが並べる行列を作るには 50回 (0～49のnumとpositionを指定して)この関数を呼べば作れる。
	/// </summary>
	/// <param name="num">そのポイントのナンバー</param>
	/// <param name="position">そのポイントのポジション</param>
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
	SkinModel m_model;								//スキンモデル。
	SkinModel TEST;
	CharacterController m_charaCon;		            //キャラクターコントローラー。
	CVector3 m_position = CVector3::Zero();
	CVector3 m_speed = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();//回転。
	float m_playerforward = 0.0f;//プレイヤーの前方向。
	float m_playerside = 0.0f;//プレイヤーの横方向。
	float m_friction = 0.95f;//摩擦。
	//tracerow系。
	CVector3 m_centerrow = CVector3::Zero();//行列の中心。ここを中心にSlave達は整列する。
	CVector3 m_syakankyori = CVector3::Zero();//行列を作る際席同士の距離調整に使用。
	int m_numberfirstrow = 5;//一行目の人数。
	int m_column = 9;//列の数。
	int m_columnhalf = 4;//列の数の半分。
	float m_basicsyakankyori = 70.0f;//基本的な車間距離。
	float m_centerrowdistance = 350.0f;//隊列の中心とプレイヤーとの距離。
	static constexpr int Maxrow = 61;//この数だけ↓配列作る。
	Tracerow tracerow[Maxrow];//Slaveが並ぶ列配列。
	int m_rowcount = 0;//tracerowを作る時に使う。現在作っているrowナンバー。
	bool m_right = true;//tracerowを作る時に使う。右から交互に並べる、trueなら右　falseなら左
};

