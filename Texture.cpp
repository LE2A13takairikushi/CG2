#include "Texture.h"
#include "Result.h"
#include "DirectXInit.h"

void Texture::Load(const wchar_t* t, Model cube, DirectX12 DX12)
{

	result = LoadFromWICFile(
		t,	//�����ɓǂݍ��݂����t�@�C���̃p�X������
		WIC_FLAGS_NONE,
		&metadata, scratchImg
	);

	//�~�b�v�}�b�v����
	result = GenerateMipMaps(
		scratchImg.GetImages(), scratchImg.GetImageCount(), scratchImg.GetMetadata(),
		TEX_FILTER_DEFAULT, 0, mipChain);
	if (SUCCEEDED(result)) {
		scratchImg = std::move(mipChain);
		metadata = scratchImg.GetMetadata();
	}

	//�ǂݍ��񂾃f�B�t���[�Y�e�N�X�`����SRGB�Ƃ��Ĉ���
	metadata.format = MakeSRGB(metadata.format);

	//�q�[�v�ݒ�
	D3D12_HEAP_PROPERTIES textureHeapProp{};
	textureHeapProp.Type = D3D12_HEAP_TYPE_CUSTOM;
	textureHeapProp.CPUPageProperty =
		D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	textureHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
	//���\�[�X�ݒ�
	D3D12_RESOURCE_DESC textureResourceDesc{};
	textureResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	textureResourceDesc.Format = metadata.format;
	textureResourceDesc.Width = metadata.width;
	textureResourceDesc.Height = (UINT)metadata.height;
	textureResourceDesc.DepthOrArraySize = (UINT)metadata.arraySize;
	textureResourceDesc.MipLevels = (UINT16)metadata.mipLevels;
	textureResourceDesc.SampleDesc.Count = 1;

	//�e�N�X�`���o�b�t�@�̐���
	result = DX12.device->CreateCommittedResource(
		&textureHeapProp,
		D3D12_HEAP_FLAG_NONE,
		&textureResourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&texBuff));

	for (SIZE_T j = 0; j < metadata.mipLevels; j++)
	{
		//�~�b�v�}�b�v���x�����w�肵�ăC���[�W���擾
		const Image* img = scratchImg.GetImage(j, 0, 0);
		//�e�N�X�`���o�b�t�@�Ƀf�[�^�]��
		result = texBuff->WriteToSubresource(
			(UINT)j,
			nullptr,	//�S�̈�փR�s�[
			img->pixels,	//���f�[�^�A�h���X
			(UINT)img->rowPitch,	//1���C���T�C�Y
			(UINT)img->slicePitch	//�S�T�C�Y
		);
		assert(SUCCEEDED(result));
	}

	//�f�X�N���v�^�q�[�v�̐ݒ�
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//�V�F�[�_�[���猩����悤��
	srvHeapDesc.NumDescriptors = kMaxSRVCount;

	//�ݒ������SRV�p�f�X�N���v�^�q�[�v�𐶐�
	result = DX12.device->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&srvHeap));
	assert(SUCCEEDED(result));

	//SRV�q�[�v�̐擪�n���h�����擾
	srvHandle = srvHeap->GetCPUDescriptorHandleForHeapStart();

	//�V�F�[�_���\�[�X�r���[�ݒ�
	srvDesc.Format = cube.resDesc.Format;//RGBA float
	srvDesc.Shader4ComponentMapping =
		D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2D�e�N�X�`��
	srvDesc.Texture2D.MipLevels = cube.resDesc.MipLevels;

	//SRV�q�[�v��ookisawosyutoku
	//SRVHandleSize = DX12.device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	//�n���h���̎w���ʒu�ɃV�F�[�_�[���\�[�X�r���[�쐬
	DX12.device->CreateShaderResourceView(texBuff.Get(), &srvDesc, srvHandle);

	//�n���h�����擾���镔��
	//SRV�q�[�v�̐擪�n���h�����擾(SRV���w���Ă���͂�)
	srvGpuHandle = srvHeap->GetGPUDescriptorHandleForHeapStart();
}

D3D12_GPU_DESCRIPTOR_HANDLE Texture::GetHandle()
{
	return srvGpuHandle;
}