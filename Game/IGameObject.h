#pragma once
class IGameObject
{
public:
	/// <summary>
	/// �X�V�֐��B
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// �`��B
	/// </summary>
	virtual void Render();
	/// <summary>
	/// �폜���N�G�X�g���s���B
	/// </summary>
	void RequestDelete() {
		isRequestDelete = true;
	}
	/// <summary>
	/// 
	/// </summary>
	/// <returns>
	/// true���Ԃ��Ă�����,���N�G�X�g���󂯂Ă���B
	/// </returns>
	bool IsRequestDelete() {
		return isRequestDelete;
	}
private:
	bool  isRequestDelete = false;//�폜���N�G�X�g�B���������ƃA�b�v�f�[�g�̒��ŃA�N�Z�X���Ă��܂��̂ŁB

};
