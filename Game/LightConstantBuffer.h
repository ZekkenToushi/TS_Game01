#pragma once
#include "GameObjectManager.h"
class LightConstantBuffer
{
public:
	LightConstantBuffer();
	~LightConstantBuffer();
	void Update();
	/// <summary>
	///�萔�o�b�t�@�̏������B
	/// </summary>
	void InitConstantBuffer();
	/// <summary>
	

	


	/*!
	*@brief	�f�B���N�V�������C�g�B
	*/
	struct SDirectionLight {
		CVector4 color;			//���C�g�̃J���[�B
		CVector4 direction;		//���C�g�̕����B
	};
	/*!���C�g�\���̂�p�ӂ����B
	*@brief	���C�g�\���́B
	*/
	struct SLight {
		SDirectionLight		directionLight;		//�f�B���N�V�������C�g
		CVector3			eyePos;				//���_�̍��W�B
		float				specPow;			//���ʔ��˂̍i��B
		CVector3            Kankyoukou;         //�����B
	};

	ID3D11Buffer*		m_lightCb = nullptr;				//!<���C�g�p�̒萔�o�b�t�@�B
	SLight				m_light;							//!<���C�g�\���� ���C�g�p�̍\���̂��g���悤�ɕύX�B



};

