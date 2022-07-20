#pragma once
#include "DirectXInit.h"

struct PipelineSet
{
	//�p�C�v���C���X�e�[�g�̐���
	ComPtr<ID3D12PipelineState> pipelineState;
	//���[�g�V�O�l�`��
	ComPtr<ID3D12RootSignature> rootSignature;
};

PipelineSet ObjectPipelineCreate3D(DirectX12 DX12);

PipelineSet ObjectPipelineCreate2D(DirectX12 DX12);