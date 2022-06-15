#include "Obj.h"
#include "Result.h"

void Obj3d::SetModel(Model* model)
{
	this->model = model;
}

void Obj3d::Initialize(ID3D12Device* device)
{
	D3D12_HEAP_PROPERTIES heapProp{};
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;

	D3D12_RESOURCE_DESC resdesc{};
	resdesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resdesc.Width = (sizeof(ConstBufferDataTransform) + 0xff) & ~0xff;
	resdesc.Height = 1;
	resdesc.DepthOrArraySize = 1;
	resdesc.MipLevels = 1;
	resdesc.SampleDesc.Count = 1;
	resdesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	result = device->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&resdesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffTransform));
	assert(SUCCEEDED(result));

	result = constBuffTransform->Map(0, nullptr, (void**)&constMapTransform);
	assert(SUCCEEDED(result));
}

void Obj3d::Update(XMMATRIX& matView, XMMATRIX& matProjection)
{
	XMMATRIX matScale;	//�X�P�[�����O�s��
	XMMATRIX matRot;	//��]�s��
	XMMATRIX matTrans;	//���s�ړ��s��

	matScale = XMMatrixScaling(scale.x, scale.y, scale.z);
	matRot = XMMatrixIdentity();
	matRot *= XMMatrixRotationZ(rotation.z);
	matRot *= XMMatrixRotationX(rotation.x);
	matRot *= XMMatrixRotationY(rotation.y);
	matTrans = XMMatrixTranslation(
		position.x, position.y, position.z);

	matWorld = XMMatrixIdentity();
	matWorld *= matScale;
	matWorld *= matRot;
	matWorld *= matTrans;

	if (parent != nullptr)
	{
		matWorld *= parent->matWorld;
	}

	constMapTransform->mat = matWorld * matView * matProjection;
	////	 �� �s��͂Ȃ�Ɗ|���Z�ɂ����1�ɂ܂Ƃ߂邱�Ƃ��ł����ł��I�I�I�I
	////		�s��͊|���鏇�Ԃɂ���Č��ʂ��ς��̂Œ��ӁI�I�I���ӁI�I�I���ӁI�I�I
}

void Obj3d::Draw(ID3D12GraphicsCommandList* commandList) {
	//���_�o�b�t�@�̐ݒ�
	commandList->IASetVertexBuffers(0, 1, &model->vbView);
	//�C���f�b�N�X�o�b�t�@�̐ݒ�
	commandList->IASetIndexBuffer(&model->ibView);
	//�萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	commandList->SetGraphicsRootConstantBufferView(2, constBuffTransform->GetGPUVirtualAddress());

	//�`��R�}���h
	commandList->DrawIndexedInstanced(model->indices.size() , 1, 0, 0, 0);
}

//XMMATRIX Obj3d::GetMatWorld()
//{
//	return matWorld;
//}
//
//void Obj3d::ScaleUpdate(float matSx, float matSy, float matSz)
//{
//	matScale = XMMatrixScaling(matSx, matSy, matSz);
//}
//
//void Obj3d::ScaleUpdate(XMFLOAT3 scale)
//{
//	matScale = XMMatrixScaling(scale.x, scale.y, scale.z);
//}
//
//void Obj3d::TransUpdate(float posx, float posy, float posz)
//{
//	matTrans = XMMatrixTranslation(posx, posy, posz);
//}
//
//void Obj3d::TransUpdate(XMFLOAT3 pos)
//{
//	matTrans = XMMatrixTranslation(pos.x, pos.y, pos.z);
//}
//
//void Obj3d::MatWorldUpdate()
//{
//	matWorld = XMMatrixIdentity();	//�ό`�����Z�b�g
//	matWorld *= matScale;			//���[���h�s��ɃX�P�[�����O�𔽉f
//	matWorld *= matRot;				//���[���h�s��ɉ�]�𔽉f
//	matWorld *= matTrans;			//���[���h�s��ɕ��s�ړ��𔽉f
//}
//
//void Obj3d::RotUpdateZXY(float matRx, float matRy, float matRz)
//{
//	matRot *= XMMatrixRotationZ(matRz);
//	matRot *= XMMatrixRotationX(matRx);
//	matRot *= XMMatrixRotationY(matRy);
//}
//
//void Obj3d::RotUpdateZXY(XMFLOAT3 rot)
//{
//	matRot *= XMMatrixRotationZ(rot.z);
//	matRot *= XMMatrixRotationX(rot.x);
//	matRot *= XMMatrixRotationY(rot.y);
//}
//
//void Obj3d::MatWorldIdentity()
//{
//	matWorld = XMMatrixIdentity();
//}
//
//void Obj3d::MatScaleIdentity()
//{
//	matScale = XMMatrixIdentity();
//}
//
//void Obj3d::MatRotIdentity()
//{
//	matRot = XMMatrixIdentity();
//}
//
//void Obj3d::MatTransIdentity()
//{
//	matTrans = XMMatrixIdentity();
//}