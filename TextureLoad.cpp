#include "TextureLoad.h"
#include "Result.h"


void TextureLoad::WIC(const wchar_t* file_pass)
{
	//WIC�e�N�X�`���̃��[�h
	result = LoadFromWICFile(
		file_pass,	//�����ɓǂݍ��݂����t�@�C���̃p�X������
		WIC_FLAGS_NONE,
		&metadata, scratchImg
	);

	ScratchImage mipChain{};
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
}