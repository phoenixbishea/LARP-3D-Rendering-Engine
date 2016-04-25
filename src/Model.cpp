#include "Model.hpp"
#include "Error.hpp"

namespace Larp
{
    std::unordered_map<std::string, UniqueModel> Model::_loaded_models;

    // ----------------
    // Public functions
    // ----------------

    ModelPtr Model::create(std::string path)
    {
        if (_loaded_models.find(path) == _loaded_models.end())
        {
            _loaded_models.emplace(path, UniqueModel(new Model(path)));
        }
        return _loaded_models.at(path).get();
    }

    void Model::draw(Shader& shader)
    {
        for (GLuint i = 0; i < this->_meshes.size(); ++i)
            this->_meshes.at(i).draw(shader);
    }

    // -----------------
    // Private functions
    // -----------------

    Model::Model(std::string path)
    {
        this->load_model(path);
    }

    void Model::load_model(std::string path)
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            PRINT_ERROR("ERROR::ASSIMP::" << importer.GetErrorString());
            return;
        }

        this->_directory = path.substr(0, path.find_last_of('/'));
        this->process_node(scene->mRootNode, scene);
    }

    void Model::process_node(aiNode* node, const aiScene* scene)
    {
        // Process all the node's meshes (if any)
        for(GLuint i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            this->_meshes.push_back(this->process_mesh(mesh, scene));
        }

        // Then do the same for each of its children
        for(GLuint i = 0; i < node->mNumChildren; i++)
        {
            this->process_node(node->mChildren[i], scene);
        }
    }

    Mesh Model::process_mesh(aiMesh* mesh, const aiScene* scene)
    {
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        std::vector<Texture> textures;

        // Process vertices
        for(GLuint i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            // Process vertex positions, normals and texture coordinates
            glm::vec3 vector;
            if (mesh->mNormals == NULL)
            {
                THROW_RUNTIME_ERROR("mesh->mVertices is NULL");
            }
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex._position = vector;

            if (mesh->mNormals == NULL)
            {
                THROW_RUNTIME_ERROR("mesh->mNormals is NULL");
            }
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex._normal = vector;

            if (mesh->mTextureCoords[0])
            {
                glm::vec2 vec;
                vec.x = mesh->mTextureCoords[0][i].x;
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex._tex_coords = vec;
            }
            else
                vertex._tex_coords = glm::vec2(0.0f, 0.0f);

            vertices.push_back(vertex);
        }

        // Process indices
        for (GLuint i = 0; i < mesh->mNumFaces; ++i)
        {
            aiFace face = mesh->mFaces[i];
            for (GLuint j = 0; j < face.mNumIndices; ++j)
                indices.push_back(face.mIndices[j]);
        }

        // Process material
        if (mesh->mMaterialIndex >= 0)
        {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
            std::vector<Texture> diffuseMaps = this->load_material_textures(material,
                                                                            aiTextureType_DIFFUSE, Texture::DIFFUSE);
            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
            std::vector<Texture> specularMaps = this->load_material_textures(material,
                                                                             aiTextureType_SPECULAR, Texture::SPECULAR);
            textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        }

        return Mesh(vertices, indices, textures);
    }

    std::vector<Texture> Model::load_material_textures(aiMaterial* mat, aiTextureType type, Texture::Type textureType)
    {
        std::vector<Texture> textures;
        for (GLuint i = 0; i < mat->GetTextureCount(type); ++i)
        {
            aiString str;
            mat->GetTexture(type, i, &str);
            GLboolean skip = false;
            for (GLuint j = 0; j < this->_loaded_textures.size(); ++j)
            {
                if (this->_loaded_textures.at(i)._path == str)
                {
                    textures.push_back(this->_loaded_textures.at(i));
                    skip = true;
                    break;
                }
            }

            if (!skip)
            {
                // If the texture isn't already loaded, load it
                Texture texture;
                texture._id = Mesh::texture_from_file(str.C_Str(), this->_directory);
                texture._type = textureType;
                texture._path = str;
                textures.push_back(texture);
                this->_loaded_textures.push_back(texture); // Add to loaded textures
            }
        }

        return textures;
    }

    std::vector<Mesh>& Model::get_meshes()
    {
        return this->_meshes;
    }
}
