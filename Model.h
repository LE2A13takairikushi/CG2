#pragma once
#include <vector>
#include "Vertex.h"


class Model : public VertexData
{
public:

	std::vector<Vertex> vertices;	//こいつらが頑張ればmodel読み込みもいけるっピ
	std::vector<uint16_t> indices;
	void CreateModel(DirectXInit dx12_);

};


class Cube : public Model
{
public:
	Cube();
	~Cube(){};

	//void CreateModel(DirectXInit dx12_);
};

class Triangle : public Model
{
public:

};