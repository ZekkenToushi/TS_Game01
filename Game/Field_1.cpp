#include "stdafx.h"
#include "Field_1.h"

typedef std::vector<CVector3>                   VertexBuffer;        //���_�o�b�t�@�B
typedef std::vector<unsigned int>               IndexBuffer;        //�C���f�b�N�X�o�b�t�@�B
typedef std::unique_ptr<VertexBuffer>           VertexBufferPtr;
typedef std::unique_ptr<IndexBuffer>            IndexBufferPtr;
typedef std::vector<IndexBufferPtr>             in;
typedef std::vector<VertexBufferPtr>            ve;

Field_1::Field_1()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/Field1.cmo");
	//m_model.Init(L"Assets/modelData/simplevalley.cmo");
	//
	
	CreateSTriangle(m_model);


	//�ÓI�����I�u�W�F�N�g������������B
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
	//���[���h�s��̍X�V�B
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
		//���_�o�b�t�@���쐬�B
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
				//�o�C�A�X��������B
				mBias.Mul(pos);
				pos += m_position;//�t�B�[���h�񂷂Ȋ댯�B
				vertexBuffer->push_back(pos);
				//���̒��_�ցB
				pData += mesh->vertexStride;
			}
			//���_�o�b�t�@���A�����b�N
			deviceContext->Unmap(mesh->vertexBuffer.Get(), 0);
			//���_�o�b�t�@�L�^�B
			vertexBufferArray.push_back(std::move(vertexBuffer));
		}
		//�C���f�b�N�X�o�b�t�@���쐬�B
		{
			D3D11_MAPPED_SUBRESOURCE subresource;
			//�C���f�b�N�X�o�b�t�@�����b�N�B
			HRESULT hr = deviceContext->Map(mesh->indexBuffer.Get(), 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &subresource);
			if (FAILED(hr)) {
				return;
			}
			D3D11_BUFFER_DESC bufferDesc;
			mesh->indexBuffer->GetDesc(&bufferDesc);
			//@todo cmo�t�@�C���̓C���f�b�N�X�o�b�t�@�̃T�C�Y��2byte�Œ�B
			IndexBufferPtr indexBuffer = std::make_unique<IndexBuffer>();
			int stride = 2;
			int indexCount = bufferDesc.ByteWidth / stride;
			unsigned short* pIndex = reinterpret_cast<unsigned short*>(subresource.pData);
			for (int i = 0; i < indexCount; i++) {
				indexBuffer->push_back(pIndex[i]);
			}
			//�C���f�b�N�X�o�b�t�@���A�����b�N�B
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
			//�@�����߂�B
			CVector3 tV1 = striangle.pos[0] - striangle.pos[2];
			CVector3 tV2 = striangle.pos[1] - striangle.pos[2];
			striangle.normal.Cross(tV1, tV2);
			striangle.normal.Normalize();

			m_triangles.push_back(striangle);
		}

	}


}
