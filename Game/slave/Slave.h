#pragma once
#include "GameObjectManager.h"
#include "character/CharacterController.h"

enum SuraimuState {
	Taiki,//その場に待機。
	Mukau,//プレイヤーに向かう。
	Tuizyuu//プレイヤーに追従。

};
class Slave : public IGameObject
{
public:
	Slave();
	~Slave();
	void Update()override;
	void Render()override;
	
	void Search();
	void Order();
	void Move();

private:
	
	SkinModel m_model;								//スキンモデル。
	CharacterController m_charaCon;		            //キャラクターコントローラー。
	CVector3 m_position = { 0.0f,  0.0f,  -700.0f };
	CVector3 m_speed = CVector3::Zero();
	CVector3 m_kyori = CVector3::Zero();
	CVector3 m_AlignmentCompletionDistance = { 3.0f,0.0f,3.0f };//整列完了距離。自分がその場所に入った判定に使う。
	CVector3 m_MasterPosition = CVector3::Zero();
	//スライム状態管理。
	SuraimuState state = Taiki;
	int m_SpeedMagnification = 500; //スピード倍率。
	int m_TracerowNum = 0;//自分が最後にアクセスした列番号保存用。0～99。
};

