#pragma once
#include "character/CharacterController.h"
enum  EnemyState {
	stay,
	move,
	attack
};
class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();
	void Update()override;
	void Render()override;

	void StateManagement();
	void Stay();
	void Move();
	void Attack();
	void Death();
	/// <summary>
	/// 基本行動。どの状態でも処理される。
	/// </summary>
	void Basic();

	/// <summary>
	/// 自分のナンバー記録用。
	/// </summary>
	/// <param name="num"></param>
	/// <returns></returns>
	void SetNumber(int num) {
		m_mynumber = num;
	}
	void SetPosition(CVector3 posi) {
		m_position = posi;
	}
	void SetFirstPosition(CVector3 posi) {
		m_firstPosition = posi;
	}
	/// <summary>
	/// 攻撃してますよ！自分は何番です.とここで教えてあげる
	/// </summary>
	/// <param name="judge">trueで殴られている認識ができる</param>
	/// <param name="hp">与えたダメージ</param>
	/// <param name="num">殴ったslave番号</param>
	//void SetAtackJudgement(bool judge,int addhp,int num) {
	//	m_atackJudgement = judge;
	//	enemy.HP += addhp;
	//	if(m_targetNum < 0)
	//	m_targetNum = num;
	//}


private:
	//パラメータ。
	struct Parameters{
		int Max_HP = 100;
		int HP = Max_HP;
		int Lv = 1;
	};
	struct 
		Parameters enemy;

	CharacterController m_charaCon;		            //キャラクターコントローラー。

	//敵状態管理。
	EnemyState state = stay;

	SkinModel m_model;								//スキンモデル。

	float m_gravity = -980.0f; //cm/sec^2
	
	CVector3 m_position = CVector3::Zero();
	CVector3 m_firstPosition = CVector3::Zero();
	CVector3 m_maxSpeed = { 500.0f,0.0f,500.0f };
	CVector3 m_speed = CVector3::Zero();
	CVector3 m_SeeDistance = { 600.0f,0.0f,600.0f };//目視範囲(索敵範囲)。
	CVector3 m_territory = { 600.0f,0.0f,600.0f };//守備範囲(自分が守る距離、設定地点からどのくらい離れたら諦めるか決める距離)。
	CVector3 m_range = { 100.0f,0.0f,100.0f };//射程範囲。
	CQuaternion m_rotation = CQuaternion::Identity();//回転。
	int m_mynumber = 0;//自分のナンバー。
	bool m_atackJudgement = false;//自分が攻撃されているかの判定。
	bool m_KYOUSEIkitaku = false;//強制帰宅モードのフラグ。
	bool m_kitaku = false;//帰宅モードのフラグ。
	int m_targetNum;//攻撃対象のナンバー保管用。（複数殴られていたら複数必要？
	int m_timer = 100;//CT判定用タイマー。
	int m_coolTime = 200;//攻撃CT。
	int m_speedMagnification = 10; //スピード倍率。

};

