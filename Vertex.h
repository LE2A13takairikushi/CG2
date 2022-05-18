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
//static Vertex vertices[] = {
//	// x	y	  z		 u	   v
//	{{-0.4f,-0.7f,0.0f},{0.0f,1.0f}},	//����
//	{{-0.4f,+0.7f,0.0f},{0.0f,0.0f}},	//����
//	{{+0.4f,-0.7f,0.0f},{1.0f,1.0f}},	//�E��
//	{{+0.4f,+0.7f,0.0f},{1.0f,0.0f}},	//�E��
//};

static Vertex vertices[] = {
	// x	 y	   z	  u	   v
	//�O
	{{-5.0f,-5.0f,-5.0f},{0.0f,1.0f}},	//����
	{{-5.0f, 5.0f,-5.0f},{0.0f,0.0f}},	//����
	{{ 5.0f,-5.0f,-5.0f},{1.0f,1.0f}},	//�E��
	{{ 5.0f, 5.0f,-5.0f},{1.0f,0.0f}},	//�E��
	//���
	{{-5.0f,-5.0f, 5.0f},{0.0f,1.0f}},	//����
	{{-5.0f, 5.0f, 5.0f},{0.0f,0.0f}},	//����
	{{ 5.0f,-5.0f, 5.0f},{1.0f,1.0f}},	//�E��
	{{ 5.0f, 5.0f, 5.0f},{1.0f,0.0f}},	//�E��
	//��
	{{-5.0f,-5.0f,-5.0f},{0.0f,1.0f}},	//����
	{{-5.0f,-5.0f, 5.0f},{0.0f,0.0f}},	//����
	{{-5.0f, 5.0f,-5.0f},{1.0f,1.0f}},	//�E��
	{{-5.0f, 5.0f, 5.0f},{1.0f,0.0f}},	//�E��
	//�E
	{{ 5.0f,-5.0f,-5.0f},{0.0f,1.0f}},	//����
	{{ 5.0f,-5.0f, 5.0f},{0.0f,0.0f}},	//����
	{{ 5.0f, 5.0f,-5.0f},{1.0f,1.0f}},	//�E��
	{{ 5.0f, 5.0f, 5.0f},{1.0f,0.0f}},	//�E��
	//��
	{{-5.0f,-5.0f,-5.0f},{0.0f,1.0f}},	//����
	{{-5.0f,-5.0f, 5.0f},{0.0f,0.0f}},	//����
	{{ 5.0f,-5.0f,-5.0f},{1.0f,1.0f}},	//�E��
	{{ 5.0f,-5.0f, 5.0f},{1.0f,0.0f}},	//�E��
	//��
	{{-5.0f, 5.0f,-5.0f},{0.0f,1.0f}},	//����
	{{-5.0f, 5.0f, 5.0f},{0.0f,0.0f}},	//����
	{{ 5.0f, 5.0f,-5.0f},{1.0f,1.0f}},	//�E��
	{{ 5.0f, 5.0f, 5.0f},{1.0f,0.0f}},	//�E��
};

//�C���f�b�N�X�f�[�^
static uint16_t indices[] =
{
	//�O
	0,1,2,		//�O�p�`1��
	1,2,3,		//�O�p�`2��
	//���(�O�̖ʂ�4���Z)
	4,5,6,		//�O�p�`3��
	5,6,7,		//�O�p�`4��
	//��
	8,9,10,		//�O�p�`5��
	9,10,11,	//�O�p�`6��
	//�E
	12,13,14,	//�O�p�`7��
	13,14,15,	//�O�p�`8��
	//��
	16,17,18,	//�O�p�`9��
	17,18,19,	//�O�p�`10��
	//��
	20,21,22,	//�O�p�`11��
	21,22,23,	//�O�p�`12��

	//�O�p�`��2���킹�Ďl�p�ɂ��Ă�̂�
	//6�ʂɂ���Ȃ�12�K�v...���ĺ�!? ܡ��
};
