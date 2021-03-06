#pragma once
#include <vector>
#include "Vertex.h"


class Model : public VertexData
{
public:

	std::vector<Vertex> vertices;	//こいつらが頑張ればmodel読み込みもいけるっピ
	std::vector<uint16_t> indices;
	void CreateModel(DirectX12 dx12_);

};


class Cube : public Model
{
public:
	Cube();
	~Cube(){};

	//void CreateModel(DirectXInit dx12_);
};

class Sprite : public Model
{
public:
	Sprite();
	~Sprite() {};
};

class Triangle : public Model
{
public:
	Triangle();
	~Triangle() {};
};

class Line : public Model
{
public:
	Line();
	~Line() {};
};