#pragma once
#include "GameObjectManager.h"
#include "character/CharacterController.h"
#include "SlaveController.h"
enum SuraimuState {
	Taiki,//その場に待機。0
	Mukau,//プレイヤー(列)に向かう。1
	Tuizyuu//プレイヤーに追従。2

};
class Slave : public IGameObject
{
public:
	Slave();
	~Slave();
	void Update()override;
	void Render()override;
	
	void Search();
	void Move();//どの状態でも処理する関数。
	/// <summary>
	/// Stateに応じて処理を呼びだす。
	/// </summary>
	void Statemanagement();
	void Taiki_processing();//サボるぜベイベー。
	void Mukau_processing();//今すぐ向かいます！！隊長！！。
	void Tuizyuu_processing();//一生ついていきます隊長！！（追従状態。

	/// <summary>
	/// position取得。
	/// </summary>
	/// <returns></returns>
	CVector3 GetPosition() const
	{
		return m_position;
	}
	/// <summary>
	/// 自分のナンバー記録用。
	/// </summary>
	/// <param name="num"></param>
	/// <returns></returns>
	void SetNumber(int num) {
		m_mynumber = num;
	}
	/// <summary>
	/// Slaceへ与える速度ベクトル。
	/// </summary>
	/// <param name="speed"></param>
	/// <returns></returns>
	CVector3 Setspeed(CVector3 speed) {
		m_speed = speed;
	}
	/// <summary>
	/// 重なってしまった時の離れる力。複数重なってる場合も想定してAdd。
	/// </summary>
	/// <param name="force">加算される力</param>
	/// <returns></returns>
	CVector3 Addforce(CVector3 force) {
		m_force += force;
	}
private:
	
	SkinModel m_model;								//スキンモデル。
	SlaveController m_slaveCon;					    //Slaveコントローラー。
	CVector3 m_position = { 0.0f,  0.0f,  -700.0f };
	CVector3 m_speed = CVector3::Zero();
	CVector3 m_kyori = CVector3::Zero();
	CVector3 m_distancejudgment = { 65.0f,  0.0f,  65.0f };//距離判定、ぶつかったかどうかの判定に使う。
	CVector3 m_alignmentcompletiondistance = { 10.0f,0.0f,10.0f };//整列完了距離。自分がその場所に入った判定に使う。
	CVector3 m_masterposition = CVector3::Zero();
	CVector3 m_force = CVector3::Zero();//重なってしまった時の離れる力。
	float m_friction = 0.95f;//摩擦。
	float m_personalSpace = 50.0f;//重なってしまった時の離れ始める距離。
	int m_mynumber = 0;//自分のナンバー。
	//スライム状態管理。
	SuraimuState state = Taiki;
	int m_SpeedMagnification = 500; //スピード倍率。
	int m_TracerowNum = 61;//自分が最後にアクセスした列番号保存用。0～99。
};

