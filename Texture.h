#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#include <DirectXMath.h>
using namespace DirectX;
#include <d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")
#include <DirectXTex.h>
#include "Model.h"

//�����I�Ƀe�N�X�`�����Ɠǂݍ��݂��SRV�ɏ������ނ��͕�������
class Texture
{
public:
	//�Ȃ����֐����ɓ������r�[DX12���S�ď��������ꂽ�̂ň����ł�����Ă���
	void Load(const wchar_t* t,DirectX12 DX12);
	void CreateSRV(DirectX12 DX12);
	void SetSRV(Model cube, DirectX12 DX12);
	D3D12_GPU_DESCRIPTOR_HANDLE GetHandle();
	//�ݒ������SRV�p�f�X�N���v�^�q�[�v�𐶐�
	ID3D12DescriptorHeap* srvHeap = nullptr;

	//�e�N�X�`���������ǂݍ��񂾂�
	int loadTexCount = 0;

private:
	TexMetadata metadata{};
	ScratchImage scratchImg{};
	ScratchImage mipChain{};

	ID3D12Resource* texBuff = nullptr;

	//SRV�̍ő��
	const size_t kMaxSRVCount = 2056;
	//�f�X�N���v�^�q�[�v�̐ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
	
	//SRV�q�[�v�̐擪�n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE srvHandle = { 0 };
	//�V�F�[�_���\�[�X�r���[�ݒ�
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};//�ݒ�\����
		//SRV�q�[�v�̑傫�����擾
	UINT SRVHandleSize = 0;

};

