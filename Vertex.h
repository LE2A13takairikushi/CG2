#pragma once

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

#include "DirectXInit.h"

//���_�f�[�^�\����
struct Vertex
{
	XMFLOAT3 pos;	//xyz���W
	XMFLOAT2 uv;	//uv���W
};

class VertexData
{
public:
	UINT sizeVB;
	D3D12_RESOURCE_DESC resDesc{};
	D3D12_INDEX_BUFFER_VIEW ibView{};
	//���_�o�b�t�@�r���[�̍쐬
	D3D12_VERTEX_BUFFER_VIEW vbView{};

	void CreateVertex(DirectXInit dx12_);
};

//���_�f�[�^
static Vertex vertices[] = {
	// x	y	  z		 u	   v
	{{-0.4f,-0.7f,0.0f},{0.0f,1.0f}},	//����
	{{-0.4f,+0.7f,0.0f},{0.0f,0.0f}},	//����
	{{+0.4f,-0.7f,0.0f},{1.0f,1.0f}},	//�E��
	{{+0.4f,+0.7f,0.0f},{1.0f,0.0f}},	//�E��
};

//�C���f�b�N�X�f�[�^
static uint16_t indices[] =
{
	0,1,2,//�O�p�`1��
	1,2,3,//�O�p�`2��
};
