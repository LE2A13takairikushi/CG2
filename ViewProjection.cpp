#include "ViewProjection.h"

void ViewProjection::Initialize()
{
	eye = { 0, 0, -100 };	//���_���W
	target = {0, 0, 0};	//�����_���W
	up = { 0, 1, 0 };		//������x�N�g��
	UpdatematView();
}

void ViewProjection::UpdatematView()
{
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));
}