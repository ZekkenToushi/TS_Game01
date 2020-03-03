#include "stdafx.h"
#include "Game.h"
#include "TracerowManager.h"

TracerowManager::TracerowManager()
{
	//centerrow�����ݒ�B
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
	//centerrow�𒆐S�Ƃ����~��ɐ��񂷂�悤�ɁB
	//����61�C���ԂȂ�9��B
		//�C���[�W��
	//        P
	//    �Z�Z�Z�Z�Z
	//   �Z�Z�Z�Z�Z�Z
	//  �Z�Z�Z�Z�Z�Z�Z
	// �Z�Z�Z�Z�Z�Z�Z�Z
	//�Z�Z�Z�Z���Z�Z�Z�Z
	// �Z�Z�Z�Z�Z�Z�Z�Z
	//  �Z�Z�Z�Z�Z�Z�Z
	//   �Z�Z�Z�Z�Z�Z
	//    �Z�Z�Z�Z�Z

	for (int j = 0; j < m_column;//��̐����񂷁B
		j++) {
		//������艺�̗�B
		if (j > (m_column / 2)) {
			//Z���Bkokodake
			m_seatPos.z = m_syakankyori * (j - m_columnhalf) * -1.0f;
			for (int i = 0;i < m_numberfirstrow + (m_columnhalf * 2 - j);//���̗�̍s���� m_columnhalf*2���Ӂi�㔼�B
				i++) {
				Gyouseiretu(j, i);
			}
		}
		else {
			//Z���B
			m_seatPos.z = m_syakankyori * (m_columnhalf - j);
			//�n�߂�5�C���ׂ邽�߂͂��߂�5�B
			for (int i = 0;i < j + m_numberfirstrow;//���̗�̍s���񂷁i�O��+�^�񒆁B
				i++) {
				Gyouseiretu(j, i);
			}
		}
		m_seatPos = CVector3::Zero();
	}

	//�R���i���S�j����v���C���[�ւ̃x�N�g�������߂Ă����i�R����]�Ŏg���j�B
	CVector3 position_player = Game::GetInstance()->m_player->GetPosition();
	m_rowForward = position_player - m_centerrow;

	//�J�E���g���Z�b�g�B
	m_rowcount = 0;
	//�����v���C���[��centerrow�̋�����m_centerrowdistance�ȉ��ɂȂ�����ǂ������Ă���悤�ɂ���B
	CVector3 kyori = position_player - m_centerrow;
	//����y�͏�ɓ����ł����B
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
	//��s�B����0����͂��܂���1�񂩂�n�܂邽�߂���Ă钍�ӁB
	if (j % 2 == 0) {
		//���ڂ������S
		if (i == 0) {
			TracerowSet(m_rowcount, m_centerrow + m_seatPos);
			m_rowcount++;
		}
		//���ڈȍ~�͉E���Ɣz�u���Ă����B
		else if (m_right == true) {//�E
			m_seatPos.x += m_syakankyori;
			TracerowSet(m_rowcount, m_centerrow + m_seatPos);
			m_rowcount++;
			m_right = false;
		}
		else {//��
			m_seatPos.x = m_seatPos.x*-1.0;
			TracerowSet(m_rowcount, m_centerrow + m_seatPos);
			m_rowcount++;
			m_right = true;
			//���ɖ߂��B
			m_seatPos.x = m_seatPos.x*-1.0;
		}
	}
	//�����s�B
	else {
		if (i == 0) {
			m_seatPos.x -= m_syakankyori / 2;
		}
		//�E���Ɣz�u���Ă����B
		if (m_right == true) {//�E
			m_seatPos.x += m_syakankyori;
			TracerowSet(m_rowcount, m_centerrow + m_seatPos);
			m_rowcount++;
			m_right = false;
		}
		else {//��
			m_seatPos.x = m_seatPos.x*-1.0;
			TracerowSet(m_rowcount, m_centerrow + m_seatPos);
			m_rowcount++;
			m_right = true;
			//���ɖ߂��B
			m_seatPos.x = m_seatPos.x*-1.0;
		}
	}
}

CVector3 TracerowManager::TracerowRotation(CVector3 position)
{
	//��̑O�����������B
	float Rot = atan2(m_rowForward.x, m_rowForward.z);
	//m_seatPos���̑O�����Ɍ����悤�ɉ�]������B
	CVector3 toCenter = position - m_centerrow;
	CQuaternion qRot;
	qRot.SetRotation(CVector3::AxisY(), Rot);
	qRot.Multiply(toCenter);
	toCenter = toCenter + m_centerrow;
	//��]�������ʒu�x�N�g����Ԃ��B
	return toCenter;
}

void TracerowManager::TracerowSet(int num, CVector3 position)
{
	Tracerow* m_narabe = &tracerow[num];
	//��]����
	CVector3 pos = TracerowRotation(position);
	//Num��Position�Z�b�g����B
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
			//���̐Ȃ�Slave������̂ł���Number��Ԃ��B
			int slavenum = m_narabe->GetSlaveNum();
			return slavenum;
		}
		
	}
	//�N�����Ȃ������B�B�B�B
	return -1;
}
