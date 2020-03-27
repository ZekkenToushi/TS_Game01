#pragma once
class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();
	void Update()override;
	void Render()override;



};

