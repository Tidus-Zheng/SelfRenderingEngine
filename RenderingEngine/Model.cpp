#include "Model.h"

void Model::LoadModel(string path)
{
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs|aiProcess_CalcTangentSpace );

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
		return;
	}
	directory = path.substr(0, path.find_last_of('/'));

	processNode(scene->mRootNode, scene);
}

void Model::SetPosition(double x, double y, double z)
{
	position = glm::vec3(x, y, z);
} 

void Model::SetPosition(glm::vec3 position)
{
	this->position = position;
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	for (GLuint i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}

	for (GLuint i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;
	for (GLuint i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;
		glm::vec3 vector;
		glm::vec2 uv(0);
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.position = vector;

		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.normal = vector;

		if (mesh->mTextureCoords[0]) {
			uv.x = mesh->mTextureCoords[0][i].x;
			uv.y = mesh->mTextureCoords[0][i].y;
		}

		if (mesh->mTangents) {
			vector.x = mesh->mTangents[i].x;
			vector.y = mesh->mTangents[i].y;
			vector.z = mesh->mTangents[i].z;
			vertex.tangent = vector;
		}

		if (mesh->mBitangents) {
			vector.x = mesh->mBitangents[i].x;
			vector.y = mesh->mBitangents[i].y;
			vector.z = mesh->mBitangents[i].z;
			vertex.bitangent = vector;
		}

		vertex.uv = uv;

		vertices.push_back(vertex);
	}

	for (GLuint i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (GLuint j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}

	//Material mat;
	Mesh outputMesh(vertices, indices);
	if (mesh->mMaterialIndex >= 0) {
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		cout << "diffuse" << endl;
		vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, diffuse);
		//textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		cout << "normal" << endl;
		vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, normal);
		//textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
		cout << "specular" << endl;
		vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, specular);
		//textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

		outputMesh.material->diffuse = diffuseMaps[0];
		if (normalMaps.size() > 0)
			outputMesh.material->normal = normalMaps[0];
		if (specularMaps.size() > 0)
			outputMesh.material->specular = specularMaps[0];
	}

	return outputMesh;
}

vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, TextureType typeName)
{
	vector<Texture> textures;
	for (GLuint i = 0; i < mat->GetTextureCount(type); i++) {
		aiString str;
		mat->GetTexture(type, i, &str);
		cout << str.C_Str() << endl;
		Texture texture;
		texture.TextureFromFile(str.C_Str(), directory);
		texture.type = typeName;
		texture.path = str;
		textures.push_back(texture);
	}

	return textures;
}

void Model::Draw()
{
	for (int i = 0; i < meshes.size(); i++) {
		mat4x4 model, rModel;
		mat4x4_identity(model);
		mat4x4_translate(model, position.x, position.y, position.z);
		mat4x4_rotate_Y(model, model, (float)glfwGetTime());

		meshes[i].Draw(model);
	}
}
