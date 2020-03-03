#include "stdafx.h"
#include "Field_1.h"

typedef std::vector<CVector3>                   VertexBuffer;        //頂点バッファ。
typedef std::vector<unsigned int>               IndexBuffer;        //インデックスバッファ。
typedef std::unique_ptr<VertexBuffer>           VertexBufferPtr;
typedef std::unique_ptr<IndexBuffer>            IndexBufferPtr;
typedef std::vector<IndexBufferPtr>             in;
typedef std::vector<VertexBufferPtr>            ve;

Field_1::Field_1()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/Field1.cmo");
	//m_model.Init(L"Assets/modelData/simplevalley.cmo");
	//
	
	CreateSTriangle(m_model);


	//静的物理オブジェクトを初期化する。
	CQuaternion rot = {0.0f,0.0f,0.0f,1.0f};
	m_phyStaticObject.CreateMeshObject(
		m_model,
		m_position,
		rot
	);
}


Field_1::~Field_1()
{
}

void Field_1::Update()
{
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3::One());
}

void Field_1::Render()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void Field_1::CreateSTriangle(const SkinModel & model)
{
	
	CMatrix mBias;
	mBias.MakeRotationX(CMath::PI * -0.5f);
	in indexBufferArray;
	ve vertexBufferArray;

	model.FindMesh([&](const auto& mesh) {

		ID3D11DeviceContext* deviceContext = g_graphicsEngine->GetD3DDeviceContext();
		//頂点バッファを作成。
		{
			D3D11_MAPPED_SUBRESOURCE subresource;
			HRESULT hr = deviceContext->Map(mesh->vertexBuffer.Get(), 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &subresource);
			if (FAILED(hr)) {
				return;
			}
			D3D11_BUFFER_DESC bufferDesc;
			mesh->vertexBuffer->GetDesc(&bufferDesc);
			int vertexCount = bufferDesc.ByteWidth / mesh->vertexStride;
			char* pData = reinterpret_cast<char*>(subresource.pData);
			VertexBufferPtr vertexBuffer = std::make_unique<VertexBuffer>();
			CVector3 pos;
			for (int i = 0; i < vertexCount; i++) {
				pos = *reinterpret_cast<CVector3*>(pData);
				//バイアスをかける。
				mBias.Mul(pos);
				pos += m_position;//フィールド回すな危険。
				vertexBuffer->push_back(pos);
				//次の頂点へ。
				pData += mesh->vertexStride;
			}
			//頂点バッファをアンロック
			deviceContext->Unmap(mesh->vertexBuffer.Get(), 0);
			//頂点バッファ記録。
			vertexBufferArray.push_back(std::move(vertexBuffer));
		}
		//インデックスバッファを作成。
		{
			D3D11_MAPPED_SUBRESOURCE subresource;
			//インデックスバッファをロック。
			HRESULT hr = deviceContext->Map(mesh->indexBuffer.Get(), 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &subresource);
			if (FAILED(hr)) {
				return;
			}
			D3D11_BUFFER_DESC bufferDesc;
			mesh->indexBuffer->GetDesc(&bufferDesc);
			//@todo cmoファイルはインデックスバッファのサイズは2byte固定。
			IndexBufferPtr indexBuffer = std::make_unique<IndexBuffer>();
			int stride = 2;
			int indexCount = bufferDesc.ByteWidth / stride;
			unsigned short* pIndex = reinterpret_cast<unsigned short*>(subresource.pData);
			for (int i = 0; i < indexCount; i++) {
				indexBuffer->push_back(pIndex[i]);
			}
			//インデックスバッファをアンロック。
			deviceContext->Unmap(mesh->indexBuffer.Get(), 0);
			indexBufferArray.push_back(std::move(indexBuffer));
		}
	});


	for (int i=0;i < indexBufferArray.size();i++) {
		for (int j = 0;j < indexBufferArray[i]->size();) {
			STriangle striangle;
			striangle.pos[0] = vertexBufferArray[i]->at(indexBufferArray[i]->at(j++));
			striangle.pos[1] = vertexBufferArray[i]->at(indexBufferArray[i]->at(j++));
			striangle.pos[2] = vertexBufferArray[i]->at(indexBufferArray[i]->at(j++));
			//法線求める。
			CVector3 tV1 = striangle.pos[0] - striangle.pos[2];
			CVector3 tV2 = striangle.pos[1] - striangle.pos[2];
			striangle.normal.Cross(tV1, tV2);
			striangle.normal.Normalize();

			m_triangles.push_back(striangle);
		}

	}


}
