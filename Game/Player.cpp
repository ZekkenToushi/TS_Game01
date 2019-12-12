#include "stdafx.h"
#include "Player.h"
#include "Game.h"

Player::Player()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/unityChan.cmo");
	TEST.Init(L"Assets/modelData/unityChan.cmo");
	//キャラクターコントローラーを初期化。
	m_charaCon.Init(
		50.0,			//半径。 
		50.0f,			//高さ。
		m_position	//初期位置。
	);
	//centerrow初期設定。
	m_centerrow.z = m_position.z - m_centerrowdistance;
}


Player::~Player()
{
	//g_goMgr.DeleteGameObject(this);
}

void Player::Update()
{
	Move();
	Rotation();
	/*TracerowSet();*/
	TracerowManagement();

	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
	TEST.UpdateWorldMatrix(m_centerrow, m_rotation, CVector3::One());
}
void Player::Render()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
	TEST.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void Player::Move()
{
	//カメラ前方向、右方向を取得。
	CVector3 CameraForward = Game::GetInstance()->m_tsCamera->GetForward();
	CVector3 CameraRightd = Game::GetInstance()->m_tsCamera->GetRight();
	
	//XZ平面での前方方向、右方向に変換する。
	CameraForward.y = 0.0f;
	CameraForward.Normalize();
	CameraRightd.y = 0.0f;
	CameraRightd.Normalize();

	//アナログスティックの入力量を取得、ポジションへの適用。
	m_speed = CameraForward * g_pad->GetLStickYF()*1200.0f;
	m_speed += CameraRightd * g_pad->GetLStickXF()*1200.0f;

	//一時的重力
	m_speed.y -= 1000.00f;
	

	//XZ成分の移動速度をクリア
	/*if (g_pad->GetLStickXF() == 0.0f) {

		m_speed.x = 0.0f;
	}
	if (g_pad->GetLStickYF() == 0.0f) {
		m_speed.z = 0.0f;
	}*/
	//ジャンプ。
	if (g_pad->IsPress(enButtonB)) {
		m_speed.y += 2000.0f;
	}
	//摩擦計算。
	m_speed = m_speed * m_friction;

	m_position = m_charaCon.Execute(1.0f / 60, m_speed);
	
}

void Player::Rotation()
{
	//下準備。
	float Rot = atan2(m_playerforward, m_playerside);
	CQuaternion qRot;
	qRot.SetRotation(CVector3::AxisY(), Rot);

	//入力があれば
	if (m_speed.x != 0.0f || m_speed.z != 0.0f)
	{
		//回転を適用。
		m_rotation = qRot;
		//進行方向保存。
		m_playerforward = m_speed.x;
		m_playerside = m_speed.z;
	}
	
}

void Player::TracerowManagement()
{
	//centerrowを中心とした円状に整列するように。
	//もし61匹並ぶなら9列。
		//イメージ↓

	//        P
	//    〇〇〇〇〇
	//   〇〇〇〇〇〇
	//  〇〇〇〇〇〇〇
	// 〇〇〇〇〇〇〇〇
	//〇〇〇〇●〇〇〇〇
	// 〇〇〇〇〇〇〇〇
	//  〇〇〇〇〇〇〇
	//   〇〇〇〇〇〇
	//    〇〇〇〇〇

	for (int j = 0; j < m_column;//列の数分回す。
		j++) {
		//半分より下の列。
		if (j > (m_column / 2)) {
			//Z軸。kokodake
			m_syakankyori.z = m_basicsyakankyori * (j - m_columnhalf) * -1.0f;
			for (int i = 0;i < m_numberfirstrow + (m_columnhalf*2 - j);//その列の行分回す m_columnhalf*2注意（後半。
				i++) {
				Gyouseiretu(j,i);
			}
		}
		else {
			//Z軸。
			m_syakankyori.z = m_basicsyakankyori * (m_columnhalf - j);
			//始めは5匹並べるためはじめは5。
			for (int i = 0;i < j + m_numberfirstrow;//その列の行分回す（前半+真ん中。
				i++) {
				Gyouseiretu(j, i);
			}
		}
		m_syakankyori = CVector3::Zero();
	}
	//カウントリセット。
	m_rowcount = 0;
	//もしプレイヤーとcenterrowの距離がm_centerrowdistance以下になったら追いかけてくるようにする。
	CVector3 kyori = m_position - m_centerrow;
	//高さyは常に同じでいい。
	m_centerrow.y = m_position.y;
	kyori.y = 0.0f;
	if (fabs(kyori.x) > m_centerrowdistance ||
		/*fabs(kyori.y) > m_centerrowdistance ||*/
		fabs(kyori.z) > m_centerrowdistance) {
		
		kyori.Normalize();
		m_centerrow += kyori * m_centerrowdistance / 20;
	}
}

void Player::Gyouseiretu(int j, int i)
{
	//奇数行。ｊは0からはじまり列は1列から始まるためずれてる注意。
	if (j % 2 == 0) {
		//一回目だけ中心
		if (i == 0) {
			TracerowSet(m_rowcount, m_centerrow + m_syakankyori);
			m_rowcount++;
		}
		//二回目以降は右左と配置していく。
		else if (m_right == true) {//右
			m_syakankyori.x += m_basicsyakankyori;
			TracerowSet(m_rowcount, m_centerrow + m_syakankyori);
			m_rowcount++;
			m_right = false;
		}
		else {//左
			m_syakankyori.x = m_syakankyori.x*-1.0;
			TracerowSet(m_rowcount, m_centerrow + m_syakankyori);
			m_rowcount++;
			m_right = true;
			//元に戻す。
			m_syakankyori.x = m_syakankyori.x*-1.0;
		}
	}
	//偶数行。
	else {
		if (i == 0) {
			m_syakankyori.x -= m_basicsyakankyori/2;
		}
		//右左と配置していく。
		if (m_right == true) {//右
			m_syakankyori.x += m_basicsyakankyori;
			TracerowSet(m_rowcount, m_centerrow + m_syakankyori);
			m_rowcount++;
			m_right = false;
		}
		else {//左
			m_syakankyori.x = m_syakankyori.x*-1.0;
			TracerowSet(m_rowcount, m_centerrow + m_syakankyori);
			m_rowcount++;
			m_right = true;
			//元に戻す。
			m_syakankyori.x = m_syakankyori.x*-1.0;
		}
	}
}

void Player::TracerowSet(int num,CVector3 position)
{
	
	Tracerow* m_narabe = &tracerow[num];
	//NumとPositionセットする。
	m_narabe->SetNum(num);
	m_narabe->Setposition(position);
	m_narabe->SetMaxNum(Maxrow);
	m_narabe->Update();
	m_narabe->Render();
	
}
