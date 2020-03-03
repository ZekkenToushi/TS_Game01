#include "stdafx.h"
#include "Marker.h"
#include "Game.h"


Marker::Marker()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/aikonn.cmo");
}

Marker::~Marker()
{
}

void Marker::Update()
{
	Move();
	//Y���W�����߁Ay���W���m�肳����B
	Ycollision();
	//���[���h�s��̍X�V�B
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
	//�}�[�J�[�̑��쁁���v���C���[�X�s�[�h�Ƃ���B
	CVector3 playerSpeed = Game::GetInstance()->m_player->GetSpeed();
	playerSpeed.Normalize();
	m_speed.x += m_standardSpeed.x * playerSpeed.x;
	m_speed.z += m_standardSpeed.z* playerSpeed.z;
	//�v���C���[�ƈ�苗�����ꂽ�����̋������k�߂�B	
	if (m_speed.Length() > m_maxSpeed.Length()) {

		for (int i = 0;m_speed.Length() > m_maxSpeed.Length();i++) {
			m_speed *= 0.99;
		}
	}
	//�|�W�V�������v���C���[+����ɂ���B
	m_position += m_speed;
}

void Marker::Ycollision()
{
	//��������Y���W�̍����̏��߂ƏI���B
	CVector3 startpos = { m_position.x,10000.0f,m_position.z };
	CVector3 endpos = { m_position.x,-10000.0f,m_position.z };
	for (int i = 0; i < Game::GetInstance()->m_field1->GetTriangleMaxCount(); i++) {
		auto triangle = Game::GetInstance()->m_field1->GetTriangle(i);
		CVector3 triangleFirstPos = triangle.pos[0];
		//�X�e�b�v1.triangle��startpos��endpos�̒��Ɉʒu���邩�m�F����B
		CVector3 startvector = startpos - triangleFirstPos;
		CVector3 normalize_s = startvector;
		normalize_s.Normalize();
		CVector3 endvector = endpos - triangleFirstPos;
		CVector3 normalize_e = endvector;
		normalize_e.Normalize();
		if (normalize_s.Dot(normalize_e) < 0.0f) {//�X�e�b�v1 OK �B
			//�X�e�b�v2.�O�p�`�ƂԂ����Ă���_�����߂�B
			float ratio_S = fabs(startvector.Dot(triangle.normal));
			float ratio_E = fabs(endvector.Dot(triangle.normal));
			float t = ratio_S / (ratio_S + ratio_E);
			CVector3 V = endpos - startpos;
			float t0 = V.Length()*t;
			V.Normalize();
			CVector3 crossPoint = startpos + (V * t0);
			//�X�e�b�v3.�O�p�`���O����B
			CVector3 triangleSide[3];//�O�ӁB
			triangleSide[0] = triangle.pos[1] - triangle.pos[0];
			triangleSide[1] = triangle.pos[2] - triangle.pos[1];
			triangleSide[2] = triangle.pos[0] - triangle.pos[2];
			CVector3 triangleCross[3];//���_����_�ւ̃x�N�g���B
			triangleCross[0] = crossPoint - triangle.pos[0];
			triangleCross[1] = crossPoint - triangle.pos[1];
			triangleCross[2] = crossPoint - triangle.pos[2];
			CVector3 crossVector[3];//���̊O�ρB
			crossVector[0].Cross(triangleSide[0], triangleCross[0]);
			crossVector[1].Cross(triangleSide[1], triangleCross[1]);
			crossVector[2].Cross(triangleSide[2], triangleCross[2]);
			//��L�̌���3�̃x�N�g���S�ē��������Ȃ�O�p�`�̒��ɓ_������B
			if (crossVector[0].Dot(crossVector[1]) > 0.0f&&
				crossVector[1].Dot(crossVector[2]) > 0.0f) {
				//���ꂾ�I�B
				m_position.y = crossPoint.y;
				//�ʓ|�Ȍv�Z�͏I����I(�I�������B
				i = Game::GetInstance()->m_field1->GetTriangleMaxCount();
			}

		}

	}

}
