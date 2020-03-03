#include "stdafx.h"
#include "Game.h"
#include "TracerowManager.h"

TracerowManager::TracerowManager()
{
	//centerrow‰Šúİ’èB
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
	//centerrow‚ğ’†S‚Æ‚µ‚½‰~ó‚É®—ñ‚·‚é‚æ‚¤‚ÉB
	//‚à‚µ61•C•À‚Ô‚È‚ç9—ñB
		//ƒCƒ[ƒW«
	//        P
	//    ZZZZZ
	//   ZZZZZZ
	//  ZZZZZZZ
	// ZZZZZZZZ
	//ZZZZœZZZZ
	// ZZZZZZZZ
	//  ZZZZZZZ
	//   ZZZZZZ
	//    ZZZZZ

	for (int j = 0; j < m_column;//—ñ‚Ì”•ª‰ñ‚·B
		j++) {
		//”¼•ª‚æ‚è‰º‚Ì—ñB
		if (j > (m_column / 2)) {
			//Z²Bkokodake
			m_seatPos.z = m_syakankyori * (j - m_columnhalf) * -1.0f;
			for (int i = 0;i < m_numberfirstrow + (m_columnhalf * 2 - j);//‚»‚Ì—ñ‚Ìs•ª‰ñ‚· m_columnhalf*2’ˆÓiŒã”¼B
				i++) {
				Gyouseiretu(j, i);
			}
		}
		else {
			//Z²B
			m_seatPos.z = m_syakankyori * (m_columnhalf - j);
			//n‚ß‚Í5•C•À‚×‚é‚½‚ß‚Í‚¶‚ß‚Í5B
			for (int i = 0;i < j + m_numberfirstrow;//‚»‚Ì—ñ‚Ìs•ª‰ñ‚·i‘O”¼+^‚ñ’†B
				i++) {
				Gyouseiretu(j, i);
			}
		}
		m_seatPos = CVector3::Zero();
	}

	//ŒR‘ài’†Sj‚©‚çƒvƒŒƒCƒ„[‚Ö‚ÌƒxƒNƒgƒ‹‚ğ‹‚ß‚Ä‚¨‚­iŒR‘à‰ñ“]‚Åg‚¤jB
	CVector3 position_player = Game::GetInstance()->m_player->GetPosition();
	m_rowForward = position_player - m_centerrow;

	//ƒJƒEƒ“ƒgƒŠƒZƒbƒgB
	m_rowcount = 0;
	//‚à‚µƒvƒŒƒCƒ„[‚Æcenterrow‚Ì‹——£‚ªm_centerrowdistanceˆÈ‰º‚É‚È‚Á‚½‚ç’Ç‚¢‚©‚¯‚Ä‚­‚é‚æ‚¤‚É‚·‚éB
	CVector3 kyori = position_player - m_centerrow;
	//‚‚³y‚Íí‚É“¯‚¶‚Å‚¢‚¢B
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
	//Šï”sB‚Š‚Í0‚©‚ç‚Í‚¶‚Ü‚è—ñ‚Í1—ñ‚©‚çn‚Ü‚é‚½‚ß‚¸‚ê‚Ä‚é’ˆÓB
	if (j % 2 == 0) {
		//ˆê‰ñ–Ú‚¾‚¯’†S
		if (i == 0) {
			TracerowSet(m_rowcount, m_centerrow + m_seatPos);
			m_rowcount++;
		}
		//“ñ‰ñ–ÚˆÈ~‚Í‰E¶‚Æ”z’u‚µ‚Ä‚¢‚­B
		else if (m_right == true) {//‰E
			m_seatPos.x += m_syakankyori;
			TracerowSet(m_rowcount, m_centerrow + m_seatPos);
			m_rowcount++;
			m_right = false;
		}
		else {//¶
			m_seatPos.x = m_seatPos.x*-1.0;
			TracerowSet(m_rowcount, m_centerrow + m_seatPos);
			m_rowcount++;
			m_right = true;
			//Œ³‚É–ß‚·B
			m_seatPos.x = m_seatPos.x*-1.0;
		}
	}
	//‹ô”sB
	else {
		if (i == 0) {
			m_seatPos.x -= m_syakankyori / 2;
		}
		//‰E¶‚Æ”z’u‚µ‚Ä‚¢‚­B
		if (m_right == true) {//‰E
			m_seatPos.x += m_syakankyori;
			TracerowSet(m_rowcount, m_centerrow + m_seatPos);
			m_rowcount++;
			m_right = false;
		}
		else {//¶
			m_seatPos.x = m_seatPos.x*-1.0;
			TracerowSet(m_rowcount, m_centerrow + m_seatPos);
			m_rowcount++;
			m_right = true;
			//Œ³‚É–ß‚·B
			m_seatPos.x = m_seatPos.x*-1.0;
		}
	}
}

CVector3 TracerowManager::TracerowRotation(CVector3 position)
{
	//—ñ‚Ì‘O•ûŒü‚ğ‡¬B
	float Rot = atan2(m_rowForward.x, m_rowForward.z);
	//m_seatPos‚ğ—ñ‚Ì‘O•ûŒü‚ÉŒü‚­‚æ‚¤‚É‰ñ“]‚³‚¹‚éB
	CVector3 toCenter = position - m_centerrow;
	CQuaternion qRot;
	qRot.SetRotation(CVector3::AxisY(), Rot);
	qRot.Multiply(toCenter);
	toCenter = toCenter + m_centerrow;
	//‰ñ“]‚³‚¹‚½ˆÊ’uƒxƒNƒgƒ‹‚ğ•Ô‚·B
	return toCenter;
}

void TracerowManager::TracerowSet(int num, CVector3 position)
{
	Tracerow* m_narabe = &tracerow[num];
	//‰ñ“]ˆ—
	CVector3 pos = TracerowRotation(position);
	//Num‚ÆPositionƒZƒbƒg‚·‚éB
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
			//‚±‚ÌÈ‚ÉSlave‚ª‚¢‚é‚Ì‚Å‚»‚ÌNumber‚ğ•Ô‚·B
			int slavenum = m_narabe->GetSlaveNum();
			return slavenum;
		}
		
	}
	//’N‚à‚¢‚È‚©‚Á‚½BBBB
	return -1;
}
