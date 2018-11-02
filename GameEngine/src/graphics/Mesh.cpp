#include "Mesh.h"

#include "glad/glad.h"
#include <memory>
#include <map>

std::map<std::string, std::shared_ptr<Mesh>> Mesh::meshes_;

void Mesh::CreateMesh(std::vector<int> _indices, std::vector<float> _verts, std::vector<float> _norms, std::vector<float> _texCoords) {
	indices_ = _indices;
	vertices_ = _verts;
	normals_ = _norms;
	texCoords_ = _texCoords;

	glGenVertexArrays(1, &vaoId_);
	glBindVertexArray(vaoId_);

	//std::cout << "Mesh::SetupAttribBuffer::Vertex Array Created: " << vaoId_ << std::endl;

	glGenBuffers(1, &indicesVboId_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesVboId_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(int), indices_.data(), GL_STATIC_DRAW);

	//std::cout << "Mesh::SetupAttribBuffer::Indices Buffer Created: " << indicesVboId_ << std::endl;

	verticesVboId_ = SetupAttribBuffer(0, 3, vertices_.data());
	normalsVboId_ = SetupAttribBuffer(1, 3, normals_.data());
	texCoordsVboId_ = SetupAttribBuffer(2, 2, texCoords_.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

int Mesh::SetupAttribBuffer(int _location, int _components, float _data[]) {
	unsigned int bufferId;
	glGenBuffers(1, &bufferId);
	glBindBuffer(GL_ARRAY_BUFFER, bufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_data) * sizeof(float), _data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(_location);
	glVertexAttribPointer(_location, _components, GL_FLOAT, GL_FALSE, 0, 0);

	//std::cout << "Mesh::SetupAttribBuffer::Attribute Buffer Created: " << bufferId << std::endl;

	return bufferId;
}

void Mesh::prepareRender() {
	glBindVertexArray(vaoId_);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesVboId_);
}

std::shared_ptr<Mesh> Mesh::CreateMesh(std::string _meshIdentifier, std::vector<int> _indices, std::vector<float> _verts, std::vector<float> _norms, std::vector<float> _texCoords) {
	if(meshes_.find(_meshIdentifier) != meshes_.end())
		return meshes_[_meshIdentifier];

	std::shared_ptr<Mesh> mesh(new Mesh);
	mesh->_identifier = _meshIdentifier;
	mesh->CreateMesh(_indices, _verts, _norms, _texCoords);

	meshes_[_meshIdentifier] = std::move(mesh);

	return meshes_[_meshIdentifier];
}

