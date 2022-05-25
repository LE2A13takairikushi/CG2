#include "Obj.h"

XMMATRIX Obj::GetMatWorld()
{
	return matWorld;
}

void Obj::ScaleUpdate(float matSx, float matSy, float matSz)
{
	matScale = XMMatrixScaling(matSx, matSy, matSz);
}

void Obj::ScaleUpdate(XMFLOAT3 scale)
{
	matScale = XMMatrixScaling(scale.x, scale.y, scale.z);
}

void Obj::TransUpdate(float posx, float posy, float posz)
{
	matTrans = XMMatrixTranslation(posx, posy, posz);
}

void Obj::TransUpdate(XMFLOAT3 pos)
{
	matTrans = XMMatrixTranslation(pos.x, pos.y, pos.z);
}

void Obj::MatWorldUpdate()
{
	matWorld = XMMatrixIdentity();	//�ό`�����Z�b�g
	matWorld *= matScale;			//���[���h�s��ɃX�P�[�����O�𔽉f
	matWorld *= matRot;				//���[���h�s��ɉ�]�𔽉f
	matWorld *= matTrans;			//���[���h�s��ɕ��s�ړ��𔽉f
}

void Obj::RotUpdateZXY(float matRx, float matRy, float matRz)
{
	matRot *= XMMatrixRotationZ(matRz);
	matRot *= XMMatrixRotationX(matRx);
	matRot *= XMMatrixRotationY(matRy);
}

void Obj::RotUpdateZXY(XMFLOAT3 rot)
{
	matRot *= XMMatrixRotationZ(rot.z);
	matRot *= XMMatrixRotationX(rot.x);
	matRot *= XMMatrixRotationY(rot.y);
}

void Obj::MatWorldIdentity()
{
	matWorld = XMMatrixIdentity();
}

void Obj::MatScaleIdentity()
{
	matScale = XMMatrixIdentity();
}

void Obj::MatRotIdentity()
{
	matRot = XMMatrixIdentity();
}

void Obj::MatTransIdentity()
{
	matTrans = XMMatrixIdentity();
}