#include "ViewProjection.h"

void ViewProjection::Initialize()
{
	eye = { 0, 0, -100 };	//視点座標
	target = {0, 0, 0};	//注視点座標
	up = { 0, 1, 0 };		//上方向ベクトル
	UpdatematView();
}

void ViewProjection::UpdatematView()
{
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));
}