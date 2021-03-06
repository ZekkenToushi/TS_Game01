#include "stdafx.h"
#include "Game.h"
#include "TracerowManager.h"

TracerowManager::TracerowManager()
{
	//centerrow初期設定。
	CVector3 position_player = Game::GetInstance()->m_player->GetPosition();
	m_centerrow.z = position_player.z - m_centerrowdistance;
}
TracerowManager::~TracerowManager()
{
}

void TracerowManager::Update()
{
	TRManagement();
}

void TracerowManager::Render()
{

}
void TracerowManager::TRManagement()
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
			m_seatPos.z = m_syakankyori * (j - m_columnhalf) * -1.0f;
			for (int i = 0;i < m_numberfirstrow + (m_columnhalf * 2 - j);//その列の行分回す m_columnhalf*2注意（後半。
				i++) {
				Gyouseiretu(j, i);
			}
		}
		else {
			//Z軸。
			m_seatPos.z = m_syakankyori * (m_columnhalf - j);
			//始めは5匹並べるためはじめは5。
			for (int i = 0;i < j + m_numberfirstrow;//その列の行分回す（前半+真ん中。
				i++) {
				Gyouseiretu(j, i);
			}
		}
		m_seatPos = CVector3::Zero();
	}

	//軍隊（中心）からプレイヤーへのベクトルを求めておく（軍隊回転で使う）。
	CVector3 position_player = Game::GetInstance()->m_player->GetPosition();
	m_rowForward = position_player - m_centerrow;

	//カウントリセット。
	m_rowcount = 0;
	//もしプレイヤーとcenterrowの距離がm_centerrowdistance以下になったら追いかけてくるようにする。
	CVector3 kyori = position_player - m_centerrow;
	//高さyは常に同じでいい。
	m_centerrow.y = position_player.y;
	kyori.y = 0.0f;
	if (fabs(kyori.x) > m_centerrowdistance ||
		/*fabs(kyori.y) > m_centerrowdistance ||*/
		fabs(kyori.z) > m_centerrowdistance) {

		kyori.Normalize();
		m_centerrow += kyori * m_centerrowdistance / 20;
	}

}

void TracerowManager::Gyouseiretu(int j, int i)
{
	//奇数行。ｊは0からはじまり列は1列から始まるためずれてる注意。
	if (j % 2 == 0) {
		//一回目だけ中心
		if (i == 0) {
			TracerowSet(m_rowcount, m_centerrow + m_seatPos);
			m_rowcount++;
		}
		//二回目以降は右左と配置していく。
		else if (m_right == true) {//右
			m_seatPos.x += m_syakankyori;
			TracerowSet(m_rowcount, m_centerrow + m_seatPos);
			m_rowcount++;
			m_right = false;
		}
		else {//左
			m_seatPos.x = m_seatPos.x*-1.0;
			TracerowSet(m_rowcount, m_centerrow + m_seatPos);
			m_rowcount++;
			m_right = true;
			//元に戻す。
			m_seatPos.x = m_seatPos.x*-1.0;
		}
	}
	//偶数行。
	else {
		if (i == 0) {
			m_seatPos.x -= m_syakankyori / 2;
		}
		//右左と配置していく。
		if (m_right == true) {//右
			m_seatPos.x += m_syakankyori;
			TracerowSet(m_rowcount, m_centerrow + m_seatPos);
			m_rowcount++;
			m_right = false;
		}
		else {//左
			m_seatPos.x = m_seatPos.x*-1.0;
			TracerowSet(m_rowcount, m_centerrow + m_seatPos);
			m_rowcount++;
			m_right = true;
			//元に戻す。
			m_seatPos.x = m_seatPos.x*-1.0;
		}
	}
}

CVector3 TracerowManager::TracerowRotation(CVector3 position)
{
	//列の前方向を合成。
	float Rot = atan2(m_rowForward.x, m_rowForward.z);
	//m_seatPosを列の前方向に向くように回転させる。
	CVector3 toCenter = position - m_centerrow;
	CQuaternion qRot;
	qRot.SetRotation(CVector3::AxisY(), Rot);
	qRot.Multiply(toCenter);
	toCenter = toCenter + m_centerrow;
	//回転させた位置ベクトルを返す。
	return toCenter;
}

void TracerowManager::TracerowSet(int num, CVector3 position)
{
	Tracerow* m_narabe = &tracerow[num];
	//回転処理
	CVector3 pos = TracerowRotation(position);
	//NumとPositionセットする。
	m_narabe->SetNum(num);
	m_narabe->Setposition(pos);
	m_narabe->SetMaxNum(Maxrow);
	m_narabe->Update();
	m_narabe->Render();
}

int TracerowManager::SearchReadyNum()
{
	for (int i = 0;i < Maxrow;i++) {
		Tracerow* m_narabe = &tracerow[i];
		if (true == m_narabe->GetStay()){
			//この席にSlaveがいるのでそのNumberを返す。
			int slavenum = m_narabe->GetSlaveNum();
			return slavenum;
		}
		
	}
	//誰もいなかった。。。。
	return -1;
}
