#pragma once

#include <string>
#include <vector>

struct aiMesh;
struct aiNode;
struct aiScene;

namespace GLI
{
	class Mesh;

	class Model
	{
	private:

		std::vector<Mesh> meshes;

	public:

		Model(std::string const& path);
		virtual ~Model();

	private:

		void LoadModel(std::string const& path);

		void ProcessNode(aiNode* node, const aiScene* scene);

		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	};
}

