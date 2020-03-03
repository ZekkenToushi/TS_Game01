#pragma once
#include "character/CharacterController.h"
#include "GameObjectManager.h"
#include "Tracerow.h"
class Marker;
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
	//void TracerowManagement();
	/// <summary>
	/// 指定した分の席を用意する。（その行のみ）
	/// </summary>
	/// <param name="j">列番号</param>
	/// <param name="i"></param>
	/// <param name="Tyousei"></param>
	//void Gyouseiretu(int j,int i);
	/// <summary>
	/// Tracerowの回転,プレイヤーの回転に合わせて列も回転する。//回転させた位置ベクトルを返す。
	/// </summary>
	//CVector3 TracerowRotation(CVector3 position);
	/// <summary>
	/// 指定したrowを作る。
	/// 例えば50個のSlaveが並べる行列を作るには 50回 (0～49のnumとpositionを指定して)この関数を呼べば作れる。
	/// </summary>
	/// <param name="num">そのポイントのナンバー</param>
	/// <param name="position">そのポイントのポジション</param>
	//void TracerowSet(int num, CVector3 position);
	/// <summary>
	/// Slaveへの命令系
	/// </summary>
	void Order();
	
	CVector3 GetPosition() const
	{
		return m_position;
	}
	CVector3 GetSpeed() const
	{
		return m_speed;
	}
	CQuaternion Getrotation() 
	{
		return m_rotation;
	}
	//進行方向取得。
	float GetForward() {
		return m_playerforward;
	}
	float GetSide() {
		return m_playerside;
	}
	
private:
	SkinModel m_model;								//スキンモデル。
	CharacterController m_charaCon;		            //キャラクターコントローラー。
	CVector3 m_position = CVector3::Zero();
	CVector3 m_speed = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();//回転。
	float m_playerforward = 0.0f;//プレイヤーの前方向。
	float m_playerside = 0.0f;//プレイヤーの横方向。
	float m_friction = 0.95f;//摩擦。
	float m_jumpCount = 0.0f;
	bool m_isJump = false;

	//Marker
	Marker* marker = nullptr;
	//Slave系。
	
};

