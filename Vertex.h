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
#include <vector>

std::vector<int>;

//���_�f�[�^�\����
struct Vertex
{
	XMFLOAT3 pos;	//xyz���W
	XMFLOAT3 normal;	//�@���x�N�g��
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

	void CreateVertex(DirectXInit dx12_, std::vector<Vertex> vertices, std::vector<uint16_t> indices);
};

//���_�f�[�^
//static Vertex vertices[] = {
//	// x	y	  z		 u	   v
//	{{-0.4f,-0.7f,0.0f},{0.0f,1.0f}},	//����
//	{{-0.4f,+0.7f,0.0f},{0.0f,0.0f}},	//����
//	{{+0.4f,-0.7f,0.0f},{1.0f,1.0f}},	//�E��
//	{{+0.4f,+0.7f,0.0f},{1.0f,0.0f}},	//�E��
//};

static std::vector<Vertex> vertices = {
	// x	 y	   z	 n	 u	   v
	//�O
	{{-5.0f,-5.0f,-5.0f},{} ,{0.0f,1.0f}},	//����
	{{-5.0f, 5.0f,-5.0f},{} ,{0.0f,0.0f}},	//����
	{{ 5.0f,-5.0f,-5.0f},{} ,{1.0f,1.0f}},	//�E��
	{{ 5.0f, 5.0f,-5.0f},{} ,{1.0f,0.0f}},	//�E��
	//���			 
	{{-5.0f,-5.0f, 5.0f},{} ,{0.0f,1.0f}},	//����
	{{-5.0f, 5.0f, 5.0f},{} ,{0.0f,0.0f}},	//����
	{{ 5.0f,-5.0f, 5.0f},{} ,{1.0f,1.0f}},	//�E��
	{{ 5.0f, 5.0f, 5.0f},{} ,{1.0f,0.0f}},	//�E��
	//��				
	{{-5.0f,-5.0f,-5.0f},{} ,{0.0f,1.0f}},	//����
	{{-5.0f,-5.0f, 5.0f},{} ,{0.0f,0.0f}},	//����
	{{-5.0f, 5.0f,-5.0f},{} ,{1.0f,1.0f}},	//�E��
	{{-5.0f, 5.0f, 5.0f},{} ,{1.0f,0.0f}},	//�E��
	//�E				
	{{ 5.0f,-5.0f,-5.0f},{} ,{0.0f,1.0f}},	//����
	{{ 5.0f,-5.0f, 5.0f},{} ,{0.0f,0.0f}},	//����
	{{ 5.0f, 5.0f,-5.0f},{} ,{1.0f,1.0f}},	//�E��
	{{ 5.0f, 5.0f, 5.0f},{} ,{1.0f,0.0f}},	//�E��
	//��					
	{{-5.0f,-5.0f,-5.0f},{} ,{0.0f,1.0f}},	//����
	{{-5.0f,-5.0f, 5.0f},{} ,{0.0f,0.0f}},	//����
	{{ 5.0f,-5.0f,-5.0f},{} ,{1.0f,1.0f}},	//�E��
	{{ 5.0f,-5.0f, 5.0f},{} ,{1.0f,0.0f}},	//�E��
	//��				
	{{-5.0f, 5.0f,-5.0f},{} ,{0.0f,1.0f}},	//����
	{{-5.0f, 5.0f, 5.0f},{} ,{0.0f,0.0f}},	//����
	{{ 5.0f, 5.0f,-5.0f},{} ,{1.0f,1.0f}},	//�E��
	{{ 5.0f, 5.0f, 5.0f},{} ,{1.0f,0.0f}},	//�E��
};

//�C���f�b�N�X�f�[�^
static std::vector<uint16_t> indices =
{
	//�O
	0,1,2,		//�O�p�`1��
	2,1,3,		//�O�p�`2��
	//���(�O�̖ʂ�4���Z)
	6,5,4,		//�O�p�`4��
	7,5,6,		//�O�p�`3��
				//��
	8,9,10,		//�O�p�`5��
	10,9,11,	//�O�p�`6��
	//�E
	14,13,12,	//�O�p�`7��
	15,13,14,	//�O�p�`8��
	//��
	19,17,18,	//�O�p�`10��
	18,17,16,	//�O�p�`9��
	//��
	20,21,22,	//�O�p�`11��
	22,21,23,	//�O�p�`12��

	//�O�p�`��2���킹�Ďl�p�ɂ��Ă�̂�
	//6�ʂɂ���Ȃ�12�K�v...���ĺ�!? ܡ��
};
