#pragma once
#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <DirectXMath.h>
using namespace DirectX;

//���_�f�[�^
XMFLOAT3 vertices[] = {
   { -0.5f,-0.5f,0.0f},//����
   { -0.5f,+0.5f,0.0f},//����
   { +0.5f,-0.5f,0.0f},//�E��
};

class DrawInit
{
public:

	//���_�f�[�^�S�̂̃T�C�Y = ���_�f�[�^����̃T�C�Y * ���_�f�[�^�̗v�f��
	UINT sizeVB = static_cast<UINT>(sizeof(XMFLOAT3) * _countof(vertices));

	//���_�o�b�t�@�̐ݒ�
	D3D12_HEAP_PROPERTIES heapProp{};		//�q�[�v�ݒ�

	//���\�[�X�ݒ�
	D3D12_RESOURCE_DESC resDesc{};

	DrawInit();
	~DrawInit();

	void SetResDesc();
};

