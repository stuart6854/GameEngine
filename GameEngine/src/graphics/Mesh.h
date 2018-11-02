#pragma once

#include <vector>
#include <memory>
#include <map>

class Mesh {

private:
	static std::map<std::string, std::shared_ptr<Mesh>> meshes_;

	std::string _identifier;

	std::vector<int> indices_;
	std::vector<float> vertices_;
	std::vector<float> normals_;
	std::vector<float> texCoords_;

	unsigned int vaoId_ = -1;
	unsigned int indicesVboId_ = -1;
	unsigned int verticesVboId_ = -1;
	unsigned int normalsVboId_ = -1;
	unsigned int texCoordsVboId_ = -1;

	void CreateMesh(std::vector<int> _indices, std::vector<float> _verts, std::vector<float> _norms, std::vector<float> _texCoords);

	static int SetupAttribBuffer(int _location, int _components, float _data[]);

public:
	std::string identifier() { return _identifier; }
	unsigned int vaoId() { return vaoId_; }
	int indicesCount() { return indices_.size(); }

	void prepareRender();

	static std::shared_ptr<Mesh> CreateMesh(std::string _meshIdentifier, std::vector<int> _indices, std::vector<float> _verts, std::vector<float> _norms, std::vector<float> _texCoords);

};

