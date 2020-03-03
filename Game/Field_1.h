#pragma once
#include "GameObjectManager.h"
#include "physics/PhysicsStaticObject.h"
class Field_1
	: public IGameObject
{
private:
	struct STriangle {
		CVector3 pos[3];
		CVector3 normal;
	};
public:
	Field_1();
	~Field_1();
	void Update()override;
	void Render()override;
	void CreateSTriangle(const SkinModel& model);

	int GetTriangleMaxCount() {
		return m_triangles.size();
	}
	STriangle GetTriangle(int i) {
		return m_triangles[i];
	}
private:
	CVector3 m_scale = {100.0f,100.0f, 100.0f};
	std::vector<STriangle> m_triangles;
	SkinModel m_model;									//スキンモデル。
	CVector3 m_position = { 0.0f,  2500.0f,  0.0f };
	PhysicsStaticObject m_phyStaticObject;//静的物理オブジェクト。
};

