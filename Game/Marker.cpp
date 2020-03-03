#include "stdafx.h"
#include "Marker.h"
#include "Game.h"


Marker::Marker()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/aikonn.cmo");
}

Marker::~Marker()
{
}

void Marker::Update()
{
	Move();
	//Y座標を求め、y座標を確定させる。
	Ycollision();
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
}

void Marker::Render()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void Marker::Move()
{
	m_position = Game::GetInstance()->m_player->GetPosition();
	//マーカーの操作＝＝プレイヤースピードとする。
	CVector3 playerSpeed = Game::GetInstance()->m_player->GetSpeed();
	playerSpeed.Normalize();
	m_speed.x += m_standardSpeed.x * playerSpeed.x;
	m_speed.z += m_standardSpeed.z* playerSpeed.z;
	//プレイヤーと一定距離離れた時その距離を縮める。	
	if (m_speed.Length() > m_maxSpeed.Length()) {

		for (int i = 0;m_speed.Length() > m_maxSpeed.Length();i++) {
			m_speed *= 0.99;
		}
	}
	//ポジションをプレイヤー+ずれにする。
	m_position += m_speed;
}

void Marker::Ycollision()
{
	//検査するY座標の高さの初めと終わり。
	CVector3 startpos = { m_position.x,10000.0f,m_position.z };
	CVector3 endpos = { m_position.x,-10000.0f,m_position.z };
	for (int i = 0; i < Game::GetInstance()->m_field1->GetTriangleMaxCount(); i++) {
		auto triangle = Game::GetInstance()->m_field1->GetTriangle(i);
		CVector3 triangleFirstPos = triangle.pos[0];
		//ステップ1.triangleがstartposとendposの中に位置するか確認する。
		CVector3 startvector = startpos - triangleFirstPos;
		CVector3 normalize_s = startvector;
		normalize_s.Normalize();
		CVector3 endvector = endpos - triangleFirstPos;
		CVector3 normalize_e = endvector;
		normalize_e.Normalize();
		if (normalize_s.Dot(normalize_e) < 0.0f) {//ステップ1 OK 。
			//ステップ2.三角形とぶつかっている点を求める。
			float ratio_S = fabs(startvector.Dot(triangle.normal));
			float ratio_E = fabs(endvector.Dot(triangle.normal));
			float t = ratio_S / (ratio_S + ratio_E);
			CVector3 V = endpos - startpos;
			float t0 = V.Length()*t;
			V.Normalize();
			CVector3 crossPoint = startpos + (V * t0);
			//ステップ3.三角形内外判定。
			CVector3 triangleSide[3];//三辺。
			triangleSide[0] = triangle.pos[1] - triangle.pos[0];
			triangleSide[1] = triangle.pos[2] - triangle.pos[1];
			triangleSide[2] = triangle.pos[0] - triangle.pos[2];
			CVector3 triangleCross[3];//頂点から点へのベクトル。
			triangleCross[0] = crossPoint - triangle.pos[0];
			triangleCross[1] = crossPoint - triangle.pos[1];
			triangleCross[2] = crossPoint - triangle.pos[2];
			CVector3 crossVector[3];//上二つの外積。
			crossVector[0].Cross(triangleSide[0], triangleCross[0]);
			crossVector[1].Cross(triangleSide[1], triangleCross[1]);
			crossVector[2].Cross(triangleSide[2], triangleCross[2]);
			//上記の結果3つのベクトル全て同じ方向なら三角形の中に点がある。
			if (crossVector[0].Dot(crossVector[1]) > 0.0f&&
				crossVector[1].Dot(crossVector[2]) > 0.0f) {
				//これだ！。
				m_position.y = crossPoint.y;
				//面倒な計算は終了や！(終了条件。
				i = Game::GetInstance()->m_field1->GetTriangleMaxCount();
			}

		}

	}

}
