#include "stdafx.h"
#include "LightConstantBuffer.h"

/*!16の倍数に切り上げる処理を関数化。
*@brief	引数で渡された整数値を16の倍数に切り上げます。
*@param[in]		n		整数の値。
*@return		nを16の倍数に切り上げた値。
*/
int Raundup16(int n)
{
	return (((n - 1) / 16) + 1) * 16;
}
LightConstantBuffer::LightConstantBuffer()
{
	//定数バッファを初期化。
	InitConstantBuffer();

	
}


LightConstantBuffer::~LightConstantBuffer()
{

	//ライト用の定数バッファの解放。
	if (m_lightCb != nullptr) {
		m_lightCb->Release();
	}
	

}

void LightConstantBuffer::Update()
{
	//定数バッファの更新。
	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
	DirectX::CommonStates state(g_graphicsEngine->GetD3DDevice());

	//ライト用の定数バッファを更新。
	deviceContext->UpdateSubresource(m_lightCb, 0, nullptr, &m_light, 0, 0);

	//定数バッファをシェーダースロットに設定。
	deviceContext->PSSetConstantBuffers(1, 1, &m_lightCb);
	
}

//定数バッファの初期化。
void LightConstantBuffer::InitConstantBuffer()
{
	//bufferDescに設定する。
	D3D11_BUFFER_DESC bufferDesc{};
	//ライト用の定数バッファを作成。
	//作成するバッファのサイズを変更するだけ。
	bufferDesc.ByteWidth = Raundup16(sizeof(SLight));
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_lightCb);
}



