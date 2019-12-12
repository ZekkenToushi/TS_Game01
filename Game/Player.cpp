#include "stdafx.h"
#include "Player.h"
#include "Game.h"

Player::Player()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/unityChan.cmo");
	TEST.Init(L"Assets/modelData/unityChan.cmo");
	//�L�����N�^�[�R���g���[���[���������B
	m_charaCon.Init(
		50.0,			//���a�B 
		50.0f,			//�����B
		m_position	//�����ʒu�B
	);
	//centerrow�����ݒ�B
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

	//���[���h�s��̍X�V�B
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
	//�J�����O�����A�E�������擾�B
	CVector3 CameraForward = Game::GetInstance()->m_tsCamera->GetForward();
	CVector3 CameraRightd = Game::GetInstance()->m_tsCamera->GetRight();
	
	//XZ���ʂł̑O�������A�E�����ɕϊ�����B
	CameraForward.y = 0.0f;
	CameraForward.Normalize();
	CameraRightd.y = 0.0f;
	CameraRightd.Normalize();

	//�A�i���O�X�e�B�b�N�̓��͗ʂ��擾�A�|�W�V�����ւ̓K�p�B
	m_speed = CameraForward * g_pad->GetLStickYF()*1200.0f;
	m_speed += CameraRightd * g_pad->GetLStickXF()*1200.0f;

	//�ꎞ�I�d��
	m_speed.y -= 1000.00f;
	

	//XZ�����̈ړ����x���N���A
	/*if (g_pad->GetLStickXF() == 0.0f) {

		m_speed.x = 0.0f;
	}
	if (g_pad->GetLStickYF() == 0.0f) {
		m_speed.z = 0.0f;
	}*/
	//�W�����v�B
	if (g_pad->IsPress(enButtonB)) {
		m_speed.y += 2000.0f;
	}
	//���C�v�Z�B
	m_speed = m_speed * m_friction;

	m_position = m_charaCon.Execute(1.0f / 60, m_speed);
	
}

void Player::Rotation()
{
	//�������B
	float Rot = atan2(m_playerforward, m_playerside);
	CQuaternion qRot;
	qRot.SetRotation(CVector3::AxisY(), Rot);

	//���͂������
	if (m_speed.x != 0.0f || m_speed.z != 0.0f)
	{
		//��]��K�p�B
		m_rotation = qRot;
		//�i�s�����ۑ��B
		m_playerforward = m_speed.x;
		m_playerside = m_speed.z;
	}
	
}

void Player::TracerowManagement()
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
			m_syakankyori.z = m_basicsyakankyori * (j - m_columnhalf) * -1.0f;
			for (int i = 0;i < m_numberfirstrow + (m_columnhalf*2 - j);//���̗�̍s���� m_columnhalf*2���Ӂi�㔼�B
				i++) {
				Gyouseiretu(j,i);
			}
		}
		else {
			//Z���B
			m_syakankyori.z = m_basicsyakankyori * (m_columnhalf - j);
			//�n�߂�5�C���ׂ邽�߂͂��߂�5�B
			for (int i = 0;i < j + m_numberfirstrow;//���̗�̍s���񂷁i�O��+�^�񒆁B
				i++) {
				Gyouseiretu(j, i);
			}
		}
		m_syakankyori = CVector3::Zero();
	}
	//�J�E���g���Z�b�g�B
	m_rowcount = 0;
	//�����v���C���[��centerrow�̋�����m_centerrowdistance�ȉ��ɂȂ�����ǂ������Ă���悤�ɂ���B
	CVector3 kyori = m_position - m_centerrow;
	//����y�͏�ɓ����ł����B
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
	//��s�B����0����͂��܂���1�񂩂�n�܂邽�߂���Ă钍�ӁB
	if (j % 2 == 0) {
		//���ڂ������S
		if (i == 0) {
			TracerowSet(m_rowcount, m_centerrow + m_syakankyori);
			m_rowcount++;
		}
		//���ڈȍ~�͉E���Ɣz�u���Ă����B
		else if (m_right == true) {//�E
			m_syakankyori.x += m_basicsyakankyori;
			TracerowSet(m_rowcount, m_centerrow + m_syakankyori);
			m_rowcount++;
			m_right = false;
		}
		else {//��
			m_syakankyori.x = m_syakankyori.x*-1.0;
			TracerowSet(m_rowcount, m_centerrow + m_syakankyori);
			m_rowcount++;
			m_right = true;
			//���ɖ߂��B
			m_syakankyori.x = m_syakankyori.x*-1.0;
		}
	}
	//�����s�B
	else {
		if (i == 0) {
			m_syakankyori.x -= m_basicsyakankyori/2;
		}
		//�E���Ɣz�u���Ă����B
		if (m_right == true) {//�E
			m_syakankyori.x += m_basicsyakankyori;
			TracerowSet(m_rowcount, m_centerrow + m_syakankyori);
			m_rowcount++;
			m_right = false;
		}
		else {//��
			m_syakankyori.x = m_syakankyori.x*-1.0;
			TracerowSet(m_rowcount, m_centerrow + m_syakankyori);
			m_rowcount++;
			m_right = true;
			//���ɖ߂��B
			m_syakankyori.x = m_syakankyori.x*-1.0;
		}
	}
}

void Player::TracerowSet(int num,CVector3 position)
{
	
	Tracerow* m_narabe = &tracerow[num];
	//Num��Position�Z�b�g����B
	m_narabe->SetNum(num);
	m_narabe->Setposition(position);
	m_narabe->SetMaxNum(Maxrow);
	m_narabe->Update();
	m_narabe->Render();
	
}
