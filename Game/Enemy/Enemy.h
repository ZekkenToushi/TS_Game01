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
	/// <summary>
	/// ターゲット視認用、使うのはslaveか.....プレイヤーどうしようｗ
	/// 攻撃してますよ！とここで知らせてあげて自分は何番ですと教えてあげる（これがないとEnemyは案山子）
	/// </summary>
	/// <param name="judge">trueで殴られている認識ができる</param>
	/// <param name="num"></param>
	void SetAtackJudgement(bool judge,int num) {
		m_atackJudgement = judge;
		m_targetNum = num;
	}


private:
	int Parameters {
		
	};


	//敵状態管理。
	EnemyState state = stay;

	SkinModel m_model;								//スキンモデル。

	float m_gravity = -980.0f; //cm/sec^2
	
	CVector3 m_position = CVector3::Zero();
	CVector3 m_maxSpeed = { 500.0f,0.0f,500.0f };
	CVector3 m_speed = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();//回転。
	int m_mynumber = 0;//自分のナンバー。
	bool m_atackJudgement = false;//自分が攻撃されているかの判定。
	int m_targetNum;//攻撃対象のナンバー保管用。（複数殴られていたら複数必要？

};

