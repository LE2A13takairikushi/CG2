#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#include <DirectXMath.h>
using namespace DirectX;
#include <d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")
#include <DirectXTex.h>
#include <iostream>
#include <memory>

//�����ŃN���X���������
#include "WinAPI.h"
#include "Result.h"
#include "Input.h"
#include "DirectXInit.h"
#include "Vertex.h"
#include "Shader.h"
#include "Obj.h"
#include "ViewProjection.h"
#include "Vector3.h"
#include "Model.h"
#include "Texture.h"
#include "GameScene.h"
#include "Pipeline.h"

//��肽�����ƃ���
//�Eobj�̓ǂݍ��݂͎���������

WinAPI winApi_;

struct SpriteS
{
	ID3D12Resource* vertBuff;
	//���_�o�b�t�@�r���[�̍쐬
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	ConstBuffer<ConstBufferDataTransform> constBufferT;

	void Update();
	void Draw(DirectX12 DX12);
};

void SpriteS::Update()
{
}

void SpriteS::Draw(DirectX12 DX12)
{
	DX12.commandList->IASetVertexBuffers(0, 1, &vbView);
	DX12.commandList->SetGraphicsRootConstantBufferView(0, constBufferT.buffer->GetGPUVirtualAddress());
	DX12.commandList->DrawInstanced(4, 1, 0, 0);
}

void SpritePreDraw(DirectX12 DX12,const PipelineSet p, Texture& texture)
{
	DX12.commandList->SetPipelineState(p.pipelineState.Get());
	DX12.commandList->SetGraphicsRootSignature(p.rootSignature.Get());
	DX12.commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//SRV�q�[�v�̐ݒ�R�}���h
	DX12.commandList->SetDescriptorHeaps(1, &texture.srvHeap);
	//SRV�q�[�v�̐擪���珇�Ԃ�SRV�����[�g�p�����[�^1�Ԃɐݒ�
	//���[�g�p�����[�^1�Ԃ̓e�N�X�`���o�b�t�@
	DX12.commandList->SetGraphicsRootDescriptorTable(1, texture.GetHandle());

}

//SpriteS SpriteCreate(DirectX12 DX12)
//{
//	SpriteS sprite{};
//	std::vector<VertexSprite> vertices = {
//		{{   0.0f,100.0f,0.0f} ,{0.0f,1.0f}},	//����
//		{{   0.0f, 0.0f,0.0f} ,{0.0f,0.0f}},	//����
//		{{ 100.0f,100.0f,0.0f} ,{1.0f,1.0f}},	//�E��
//		{{ 100.0f, 0.0f,0.0f} ,{1.0f,0.0f}},	//�E��
//	};
//
//	UINT sizeVB = static_cast<UINT>(sizeof(vertices[0]) * vertices.size());
//
//	//���_�o�b�t�@�̐ݒ�
//	D3D12_HEAP_PROPERTIES heapProp{};		//�q�[�v�ݒ�
//	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;	//GPU�ւ̓]���p
//
//	//���\�[�X�ݒ�
//	D3D12_RESOURCE_DESC resDesc{};
//	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
//	resDesc.Width = sizeVB;	//���_�f�[�^�S�̂̃T�C�Y
//	resDesc.Height = 1;
//	resDesc.DepthOrArraySize = 1;
//	resDesc.MipLevels = 1;
//	resDesc.SampleDesc.Count = 1;
//	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
//
//	result = DX12.device->CreateCommittedResource(
//		&heapProp,	//�q�[�v�ݒ�
//		D3D12_HEAP_FLAG_NONE,
//		&resDesc,	//���\�[�X�ݒ�
//		D3D12_RESOURCE_STATE_GENERIC_READ,
//		nullptr,
//		IID_PPV_ARGS(&sprite.vertBuff));
//	assert(SUCCEEDED(result));
//
//	//GPU��̃o�b�t�@�ɑΉ��������z������(���C����������)���擾
//	VertexSprite* vertMap = nullptr;
//	result = sprite.vertBuff->Map(0, nullptr, (void**)&vertMap);
//	assert(SUCCEEDED(result));
//	//�S���_�ɑ΂���
//	for (int i = 0; i < vertices.size(); i++) {
//		vertMap[i] = vertices[i];	//	���W���R�s�[
//	}
//	//�q���������
//	sprite.vertBuff->Unmap(0, nullptr);
//
//	//GPU���z�A�h���X
//	sprite.vbView.BufferLocation = sprite.vertBuff->GetGPUVirtualAddress();
//	//���_�o�b�t�@�̃T�C�Y
//	sprite.vbView.SizeInBytes = sizeVB;
//	//���_1���̃f�[�^�T�C�Y
//	sprite.vbView.StrideInBytes = sizeof(vertices[0]);
//
//	result = DX12.device->CreateCommittedResource(
//		&heapProp,	//�q�[�v�ݒ�
//		D3D12_HEAP_FLAG_NONE,
//		&resDesc,	//���\�[�X�ݒ�
//		D3D12_RESOURCE_STATE_GENERIC_READ,
//		nullptr,
//		IID_PPV_ARGS(&sprite.constBufferT.buffer));
//
//	//�������ăf�[�^�}�e���A���Ȃ́H
//	ConstBuffer<ConstBufferDataMaterial> constBufferM;
//
//	//������Ӊ�����
//	result = sprite.constBufferT.buffer->Map(0, nullptr, (void**)&constBufferM);
//	constBufferM.constBufferData->color = XMFLOAT4(1, 1, 1, 1); //�F�w�� RGBA
//	sprite.constBufferT.constBufferData->mat = XMMatrixOrthographicOffCenterLH(
//		0.0f, window_width, window_height, 0.0f, 0.0f, 1.0f);
//	sprite.constBufferT.buffer->Unmap(0, nullptr);
//
//	return sprite;
//
//}

//windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	GameScene gameScene_;

	Input* input_ = new Input;

	//WindowsAPI����������
	winApi_.SetWindowClass();

	///---DirectX�����������@��������---///
	
#ifdef  _DEBUG
	//�f�o�b�O���C���[���I����
	ComPtr<ID3D12Debug> debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
		debugController->EnableDebugLayer();
	}
#endif _DEBUG

	DX12.yobidasi(winApi_);

	//DirectInput�̏�����
	input_->DirectInputInit(winApi_);

	//�L�[�{�[�h�f�o�C�X�̐���
	input_->DirectInputCreate(winApi_);

	///---DirectX�����������@�����܂�---///

#pragma region �`�揉��������

	//--depth��������

	D3D12_RESOURCE_DESC depthResourceDesc{};
	depthResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	depthResourceDesc.Width = window_width;	//�����_�[�^�[�Q�b�g�ɍ��킹��
	depthResourceDesc.Height = window_height;	//�����_�[�^�[�Q�b�g�ɍ��킹��
	depthResourceDesc.DepthOrArraySize = 1;
	depthResourceDesc.Format = DXGI_FORMAT_D32_FLOAT;	//�[�x�l�t�H�[�}�b�g
	depthResourceDesc.SampleDesc.Count = 1;
	depthResourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	//�[�x�l�p�q�[�v�v���p�e�B
	D3D12_HEAP_PROPERTIES depthHeapProp{};
	depthHeapProp.Type = D3D12_HEAP_TYPE_DEFAULT;
	//�[�x�l�̃N���A�ݒ�
	D3D12_CLEAR_VALUE depthClearValue{};
	depthClearValue.DepthStencil.Depth = 1.0f;	//�[�x�l1.0f(�ő�l)�ŃN���A
	depthClearValue.Format = DXGI_FORMAT_D32_FLOAT;	//�[�x�l�t�H�[�}�b�g

	//���\�[�X����
	ComPtr<ID3D12Resource> depthBuff;
	result = DX12.device->CreateCommittedResource(
		&depthHeapProp,
		D3D12_HEAP_FLAG_NONE,
		&depthResourceDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,	//�[�x�l�������݂Ɏg�p
		&depthClearValue,
		IID_PPV_ARGS(&depthBuff));

	//�[�x�r���[�p�f�X�N���v�^�q�[�v�쐬
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
	dsvHeapDesc.NumDescriptors = 1;	//�[�x�r���[��1��
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;	//�f�v�X�X�e���V���r���[
	ComPtr<ID3D12DescriptorHeap> dsvHeap;
	result = DX12.device->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&dsvHeap));

	//�[�x�r���[�쐬
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;//�[�x�l�t�H�[�}�b�g
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	DX12.device->CreateDepthStencilView(
		depthBuff.Get(),
		&dsvDesc,
		dsvHeap->GetCPUDescriptorHandleForHeapStart());

	//--depth�����܂�

	Model cube = Cube();
	Model sprite = Sprite();
	Model triangle = Triangle();
	Model line = Line();

	//���_�f�[�^�쐬
	cube.CreateModel(DX12);
	sprite.CreateModel(DX12);
	triangle.CreateModel(DX12);
	line.CreateModel(DX12);

	//SpriteS spriteS;
	//spriteS = SpriteCreate(DX12);

	//WIC�e�N�X�`���̃��[�h
	const wchar_t* msg[3] = { L"Resources/zawa_sironuri.png", L"Resources/slime.png",L"Resources/pizza_sironuri.png" };

	Texture zawa;
	zawa.Load(msg[0], DX12);

	Texture slime;
	slime.Load(msg[1], DX12);

	Texture pizza;
	pizza.Load(msg[2], DX12);

	Texture white;
	white.CreateWhiteTexture(DX12);

	PipelineSet p = ObjectPipelineCreate3D(DX12);
	PipelineSet spriteP = ObjectPipelineCreate2D(DX12);

	//�萔�o�b�t�@�̐���
	ConstBuffer<ConstBufferDataMaterial> constBufferM;

	const int kObjectCount = 2;
	std::unique_ptr<Obj3d[]> object3ds;
	object3ds = std::make_unique<Obj3d[]>(kObjectCount);

	for (int i = 0; i < kObjectCount; i++)
	{
		object3ds[i].Initialize();
		//�e�q�\���@�T���v��
		//�擪�ȊO�Ȃ�
		//if (i > 0)
		//{
		//	//�ЂƂO��e�I�u�W�F�N�g�Ƃ���
		//	object3ds[i].parent = &object3ds[i - 1];
		//	//�q�͐e�I�u�W�F��9���̑傫��
		//	object3ds[i].scale = { 0.9f,0.9f,0.9f };
		//	//�e�I�u�W�F�ɑ΂���Z���܂���30�x��]
		//	object3ds[i].rotation = { 0.0f,0.0f,XMConvertToRadians(30.0f) };

		//	//�e�I�u�W�F�ɑ΂���Z����-8.0���炷
		//	object3ds[i].position = { 0.0f,0.0f,-8.0f };
		//}
	}

	//�ǂ̃��f���̌`���g������ݒ�
	object3ds[0].SetModel(&triangle);
	object3ds[1].SetModel(&cube);

	object3ds[1].position.x = 20;
	object3ds[1].position.y = 10;
	
	//���̃��f�����g���ݒ�
	const int kLineCountX = 15;
	const int kLineCountY = 15;
	std::unique_ptr<Obj3d[]> LineX;
	LineX = std::make_unique<Obj3d[]>(kLineCountX);

	for (int i = 0; i < kLineCountX; i++)
	{
		LineX[i].Initialize();
		LineX[i].SetModel(&line);
		LineX[i].position.x += 10 * i - (10 * kLineCountX / 2);
	}

	std::unique_ptr<Obj3d[]> LineY;
	LineY = std::make_unique<Obj3d[]>(kLineCountY);

	for (int i = 0; i < kLineCountY; i++)
	{
		LineY[i].Initialize();
		LineY[i].SetModel(&line);
		//LineY[i].position.x += 10 * i;
		LineY[i].position.z += 10 * i - (10 * kLineCountY / 2);

		LineY[i].rotation.y += XMConvertToRadians(90.0f);
	}

	//�l���������ނƎ����I�ɓ]�������炵��
	constBufferM.constBufferData->color = XMFLOAT4(1, 1, 1, 1.0f);

	////�P�ʍs��Ŗ��߂�
	//constMapTransform[0]->mat = XMMatrixIdentity();
	////�w��̕���������������
	//constMapTransform[0]->mat.r[0].m128_f32[0] = 2.0f / window_width;
	//constMapTransform[0]->mat.r[1].m128_f32[1] = -2.0f / window_height;

	//constMapTransform[0]->mat.r[3].m128_f32[0] = -1.0f;
	//constMapTransform[0]->mat.r[3].m128_f32[1] = 1.0f;
	//
	//constMapTransform[0]->mat = XMMatrixPerspectiveFovLH(
	//	XMConvertToRadians(45.0f),				//�㉺��p45�x
	//	(float)window_width / window_height,	//�A�X�y�N�g��(��ʉ���/��ʏc��)
	//	0.1f, 1000.0f							//�O�[�A���[
	//);

	//�ˉe�ϊ��s��(�������e)
	XMMATRIX matProjection =
		XMMatrixPerspectiveFovLH(
			XMConvertToRadians(45.0f),
			(float)window_width / window_height,
			0.1f, 1000.0f
		);

	//�r���[�ϊ��s��(�������e)���v�Z
	ViewProjection viewProjection_;
	viewProjection_.Initialize();

	viewProjection_.eye.y = 50.0f;
	viewProjection_.UpdatematView();

#pragma endregion �`�揉��������

	gameScene_.Initialize();

	//�Q�[�����[�v���Ŏg���ϐ��̐錾
	FLOAT clearColor[] = { 0,0,0,0 };

	FLOAT redColor[] = { 0.5f,0.1f,0.25f,0.0f };	//�Ԃ��ۂ��F
	FLOAT blueColor[] = { 0.1f,0.25f,0.5f,0.0f };	//���ۂ��F

	for (int i = 0; i < _countof(clearColor); i++)
	{
		clearColor[i] = blueColor[i];
	}

	//XMFLOAT3 materialColor = { -0.005f,0.005f,0 };

	float angle = 0.0f;	//�J�����̉�]�p
	float angleY = 0.0f;

	float cameraY = 100;

	float count = 0;

	XMFLOAT4 color = { 0,1,0.5f,1.0f };
	XMFLOAT4 colorSpd = { 0.01f,0.01f,0.01f,0.01f };

	//�Q�[�����[�v
	while (true){

#pragma region �E�B���h�E���b�Z�[�W
		if (PeekMessage(&winApi_.msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&winApi_.msg);		//�L�[���̓��b�Z�[�W�̏���
			DispatchMessage(&winApi_.msg);		//�v���V�[�W���Ƀ��b�Z�[�W�𑗂�
		}

		if (winApi_.msg.message == WM_QUIT) {
			break;
		}
#pragma endregion �E�B���h�E���b�Z�[�W

#pragma region DirectX���t���[������
		///---DirectX���t���[������ ��������---///
		
		UINT bbIndex = DX12.swapChain->GetCurrentBackBufferIndex();

		//1.���\�[�X�o���A�ŏ������݉��ɕύX
		D3D12_RESOURCE_BARRIER barrierDesc{};
		barrierDesc.Transition.pResource = DX12.backBuffers[bbIndex].Get();	//�o�b�N�o�b�t�@���w��
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;	//�\����Ԃ���
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;		//�`���Ԃ�
		DX12.commandList->ResourceBarrier(1, &barrierDesc);

		//2.�`���̕ύX
		//�����_�[�^�[�Q�b�g�r���[�̃n���h�����擾
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = DX12.rtvHeap->GetCPUDescriptorHandleForHeapStart();
		rtvHandle.ptr += bbIndex * DX12.device->GetDescriptorHandleIncrementSize(DX12.rtvHeapDesc.Type);
		//DX12.commandList->OMSetRenderTargets(1, &rtvHandle, false, nullptr);
		D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = dsvHeap->GetCPUDescriptorHandleForHeapStart();
		DX12.commandList->OMSetRenderTargets(1, &rtvHandle, false, &dsvHandle);

		//3.��ʃN���A
		DX12.commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
		DX12.commandList->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);


		//�X�V����

		gameScene_.Update();

		input_->Update();

		//�J�������W�𓮂���
		if (input_->PushKey(DIK_RIGHT) || 
			input_->PushKey(DIK_LEFT) || 
			input_->PushKey(DIK_UP) || 
			input_->PushKey(DIK_DOWN))
		{
			if (input_->PushKey(DIK_RIGHT)) { 
				viewProjection_.eye.x += 2;
				//viewProjection_.target.x += 2;
			}
			if (input_->PushKey(DIK_LEFT)) { 
				viewProjection_.eye.x -= 2; 
				//viewProjection_.target.x -= 2;
			}
			if (input_->PushKey(DIK_UP)) {
				viewProjection_.eye.z += 2;
				//viewProjection_.target.z += 2;
			}
			if (input_->PushKey(DIK_DOWN)) {
				viewProjection_.eye.z -= 2;
				//viewProjection_.target.z -= 2;
			}
			viewProjection_.UpdatematView();
		}

		//�I�u�W�F�N�g�̍X�V
		for (size_t i = 0; i < kObjectCount; i++)
		{
			if (input_->PushKey(DIK_D))
			{
				object3ds[i].position.x += 1;
			}
			if (input_->PushKey(DIK_A))
			{
				object3ds[i].position.x -= 1;
			}
			if (input_->PushKey(DIK_W))
			{
				object3ds[i].position.z += 1;
			}
			if (input_->PushKey(DIK_S))
			{
				object3ds[i].position.z -= 1;
			}
			if (input_->PushKey(DIK_Q))
			{
				object3ds[i].rotation.z += 0.1f;
			}
			if (input_->PushKey(DIK_E))
			{
				object3ds[i].rotation.z -= 0.1f;
			}
			object3ds[i].Update(viewProjection_.matView, matProjection);
		}

		for (int i = 0; i < kLineCountX; i++)
		{
			LineX[i].Update(viewProjection_.matView, matProjection);
		}
		for (int i = 0; i < kLineCountY; i++)
		{
			LineY[i].Update(viewProjection_.matView, matProjection);
		}

		//�F��ς��鏈��
		if (color.x < 0 || color.x > 1)
		{
			colorSpd.x *= -1;
		}
		if (color.y < 0 || color.y > 1)
		{
			colorSpd.y *= -1;
		}
		if (color.z < 0 || color.z > 1)
		{
			colorSpd.z *= -1;
		}
		if (color.z < 0 || color.z > 1)
		{
			colorSpd.w *= -1;
		}
		color.x += colorSpd.x;
		color.y += colorSpd.y;
		color.z += colorSpd.z;
		color.w += colorSpd.w;

		constBufferM.constBufferData->color = XMFLOAT4(color.x, color.y, color.z, color.w);

		///---DirectX���t���[������ �����܂�---///
#pragma endregion DirectX���t���[������

#pragma region �O���t�B�b�N�X�R�}���h
		//--4.�`��R�}���h��������--//
		
		D3D12_VIEWPORT viewport{};
		viewport.Width = window_width;
		viewport.Height = window_height;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		//�r���[�|�[�g�ݒ�R�}���h���A�R�}���h���X�g�ɐς�
		DX12.commandList->RSSetViewports(1, &viewport);

		D3D12_RECT scissorRect{};
		scissorRect.left = 0;									//�؂蔲�����W��
		scissorRect.right = scissorRect.left + window_width;	//�؂蔲�����W�E
		scissorRect.top = 0;									//�؂蔲�����W��
		scissorRect.bottom = scissorRect.top + window_height;	//�؂蔲�����W��
		//�V�U�[��`�ݒ�R�}���h���A�R�}���h���X�g�ɐς�
		DX12.commandList->RSSetScissorRects(1, &scissorRect);

		//�p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h
		DX12.commandList->SetPipelineState(p.pipelineState.Get());
		DX12.commandList->SetGraphicsRootSignature(p.rootSignature.Get());

		//�v���~�e�B�u�`��̐ݒ�R�}���h
		DX12.commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//���_�o�b�t�@�r���[�̐ݒ�R�}���h
		//���f���̂ǂꂩ��vertexbuffer�������Ă����ok
		//DX12.commandList->IASetVertexBuffers(0, 1, &cube.vbView);

		//�萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
		//DX12.commandList->SetGraphicsRootConstantBufferView(0, constBufferM.buffer->GetGPUVirtualAddress());

		for (int i = 0; i < kObjectCount; i++)
		{
			object3ds[i].constBufferM = constBufferM;
		}

		//�`�揈��
		gameScene_.Draw();

		object3ds[0].Draw(DX12.commandList.Get(), white);
		object3ds[1].Draw(DX12.commandList.Get(), pizza);

		for (int i = 0; i < kLineCountX; i++)
		{
			//LineX[i].constBufferM = constBufferM;
			LineX[i].Draw(DX12.commandList.Get(), white);
		}
		for (int i = 0; i < kLineCountY; i++)
		{
			//LineY[i].constBufferM = constBufferM;
			LineY[i].Draw(DX12.commandList.Get(), white);
		}

		//SpritePreDraw(DX12, p,white);
		//spriteS.Draw(DX12);

		//--4.�`��R�}���h�����܂�--//

#pragma endregion �O���t�B�b�N�X�R�}���h

#pragma region ��ʓ���ւ�

		//5.���\�[�X�o���A��߂�
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;	//�`���Ԃ���
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;	//�\����Ԃ�
		DX12.commandList->ResourceBarrier(1, &barrierDesc);

		//���߂̃N���[�Y
		result = DX12.commandList->Close();
		assert(SUCCEEDED(result));

		//�R�}���h���X�g�̎��s
		ID3D12CommandList* commandLists[] = { DX12.commandList.Get() };
		DX12.commandQueue->ExecuteCommandLists(1, commandLists);

		//��ʂɕ\������o�b�t�@���t���b�v(���\�̓���ւ�)
		result = DX12.swapChain->Present(1, 0);
		assert(SUCCEEDED(result));

		//�R�}���h�̎��s������҂�
		DX12.commandQueue->Signal(DX12.fence.Get(), ++DX12.fenceVal);
		if (DX12.fence->GetCompletedValue() != DX12.fenceVal) {
			HANDLE event = CreateEvent(nullptr, false, false, nullptr);
			DX12.fence->SetEventOnCompletion(DX12.fenceVal, event);
			WaitForSingleObject(event, INFINITE);
			CloseHandle(event);
		}

		//�L���[���N���A
		result = DX12.commandAllocator->Reset();
		assert(SUCCEEDED(result));

		//�ĂуR�}���h���X�g�𒙂߂鏀��
		result = DX12.commandList->Reset(DX12.commandAllocator.Get(), nullptr);
		assert(SUCCEEDED(result));

#pragma endregion ��ʓ���ւ�

	}

	gameScene_.End();

	//�E�B���h�E�N���X��o�^����
	UnregisterClass(winApi_.w.lpszClassName, winApi_.w.hInstance);

	return 0;
}
