#pragma once

#include <d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")

class Shader
{
public:
	ID3DBlob* vsBlob = nullptr;		//���_�V�F�[�_�I�u�W�F�N�g
	ID3DBlob* psBlob = nullptr;		//�s�N�Z���V�F�[�_�[�I�u�W�F�N�g
	ID3DBlob* errorBlob = nullptr;	//�G���[�I�u�W�F�N�g

	ID3DBlob* Compile(const wchar_t* shaderFilename, LPCSTR shadermodelname, ID3DBlob* blob, LPCSTR entrypointname);
};

