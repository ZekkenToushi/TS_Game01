#pragma once
#include "GameObjectManager.h"
class LightConstantBuffer
{
public:
	LightConstantBuffer();
	~LightConstantBuffer();
	void Update();
	/// <summary>
	///定数バッファの初期化。
	/// </summary>
	void InitConstantBuffer();
	/// <summary>
	

	


	/*!
	*@brief	ディレクションライト。
	*/
	struct SDirectionLight {
		CVector4 color;			//ライトのカラー。
		CVector4 direction;		//ライトの方向。
	};
	/*!ライト構造体を用意した。
	*@brief	ライト構造体。
	*/
	struct SLight {
		SDirectionLight		directionLight;		//ディレクションライト
		CVector3			eyePos;				//視点の座標。
		float				specPow;			//鏡面反射の絞り。
		CVector3            Kankyoukou;         //環境光。
	};

	ID3D11Buffer*		m_lightCb = nullptr;				//!<ライト用の定数バッファ。
	SLight				m_light;							//!<ライト構造体 ライト用の構造体を使うように変更。



};

