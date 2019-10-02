#pragma once

class tsCamera
	: public IGameObject
{
public:
	tsCamera();
	~tsCamera();
	/// <summary>
	/// �J���������̍X�V�B
	/// </summary>
	void Update()override;
	/// <summary>
	/// �v���C���[�𒆐S�Ɉړ�����J�����B
	/// </summary>
	void Move();
	/*!
	* @brief	�J�����̍��W��ݒ�B
	*@param[in]	pos		�J�����̍��W�B
	*/
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	/*!
	* @brief	�J�����̍��W���擾
	*@return	�J�����̍��W�B
	*/
	const CVector3& GetPosition() const
	{
		return m_position;
	}
	/*!
	* @brief	�����_��ݒ�B
	*@param[in]	target		�����_�B
	*/
	void SetTarget(const CVector3& target)
	{
		m_target = target;
	}
	/*!
	* @brief	�����_���擾�B
	*@return	�����_�B
	*/
	const CVector3& GetTarget() const
	{
		return m_target;
	}
	/*!
	* @brief	�J�����̑O���������擾�B
	*/
	const CVector3& GetForward() const
	{
		return m_forward;
	}
	/*!
		* @brief	�J�����̉E�������擾�B
		*/
	const CVector3& GetRight() const
	{
		return m_right;
	}
protected:

	CVector3	m_position;							//!<�J�����ʒu�B
	CVector3	m_target;							//!<�J�����̒��~�_�B
	CVector3	m_forward = CVector3::Front();		//!<�J�����̑O���B
	CVector3    m_right = CVector3::Right();		//!<�J�����̉E�B
	CMatrix		m_viewMatrix;						//!<�r���[�s��B
	CMatrix		m_projectionMatrix;					//!<�v���W�F�N�V�����s��B
	CMatrix		m_viewProjectionMatrix;				//!<�r���[�v���W�F�N�V�����s��B
	CMatrix		m_viewMatrixInv;					//!<�r���[�s��̋t�s��B
	CMatrix		m_cameraRotation;					//!<�J�����̉�]�s��B

};

