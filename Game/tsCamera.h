#pragma once

class tsCamera
	: public IGameObject
{
public:
	tsCamera();
	~tsCamera();
	/// <summary>
	/// カメラ処理の更新。
	/// </summary>
	void Update()override;
	/// <summary>
	/// プレイヤーを中心に移動するカメラ。
	/// </summary>
	void Move();
	/*!
	* @brief	カメラの座標を設定。
	*@param[in]	pos		カメラの座標。
	*/
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	/*!
	* @brief	カメラの座標を取得
	*@return	カメラの座標。
	*/
	const CVector3& GetPosition() const
	{
		return m_position;
	}
	/*!
	* @brief	注視点を設定。
	*@param[in]	target		注視点。
	*/
	void SetTarget(const CVector3& target)
	{
		m_target = target;
	}
	/*!
	* @brief	注視点を取得。
	*@return	注視点。
	*/
	const CVector3& GetTarget() const
	{
		return m_target;
	}
	/*!
	* @brief	カメラの前方方向を取得。
	*/
	const CVector3& GetForward() const
	{
		return m_forward;
	}
	/*!
		* @brief	カメラの右方向を取得。
		*/
	const CVector3& GetRight() const
	{
		return m_right;
	}
protected:

	CVector3	m_position;							//!<カメラ位置。
	CVector3	m_target;							//!<カメラの中止点。
	CVector3	m_forward = CVector3::Front();		//!<カメラの前方。
	CVector3    m_right = CVector3::Right();		//!<カメラの右。
	CMatrix		m_viewMatrix;						//!<ビュー行列。
	CMatrix		m_projectionMatrix;					//!<プロジェクション行列。
	CMatrix		m_viewProjectionMatrix;				//!<ビュープロジェクション行列。
	CMatrix		m_viewMatrixInv;					//!<ビュー行列の逆行列。
	CMatrix		m_cameraRotation;					//!<カメラの回転行列。

};

