#include "stdafx.h"
#include "LightConstantBuffer.h"

/*!16�̔{���ɐ؂�グ�鏈�����֐����B
*@brief	�����œn���ꂽ�����l��16�̔{���ɐ؂�グ�܂��B
*@param[in]		n		�����̒l�B
*@return		n��16�̔{���ɐ؂�グ���l�B
*/
int Raundup16(int n)
{
	return (((n - 1) / 16) + 1) * 16;
}
LightConstantBuffer::LightConstantBuffer()
{
	//�萔�o�b�t�@���������B
	InitConstantBuffer();

	
}


LightConstantBuffer::~LightConstantBuffer()
{

	//���C�g�p�̒萔�o�b�t�@�̉���B
	if (m_lightCb != nullptr) {
		m_lightCb->Release();
	}
	

}

void LightConstantBuffer::Update()
{
	//�萔�o�b�t�@�̍X�V�B
	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
	DirectX::CommonStates state(g_graphicsEngine->GetD3DDevice());

	//���C�g�p�̒萔�o�b�t�@���X�V�B
	deviceContext->UpdateSubresource(m_lightCb, 0, nullptr, &m_light, 0, 0);

	//�萔�o�b�t�@���V�F�[�_�[�X���b�g�ɐݒ�B
	deviceContext->PSSetConstantBuffers(1, 1, &m_lightCb);
	
}

//�萔�o�b�t�@�̏������B
void LightConstantBuffer::InitConstantBuffer()
{
	//bufferDesc�ɐݒ肷��B
	D3D11_BUFFER_DESC bufferDesc{};
	//���C�g�p�̒萔�o�b�t�@���쐬�B
	//�쐬����o�b�t�@�̃T�C�Y��ύX���邾���B
	bufferDesc.ByteWidth = Raundup16(sizeof(SLight));
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_lightCb);
}



