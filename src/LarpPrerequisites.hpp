#pragma once

#include <memory>       // shared_ptr, weak_ptr
#include <iostream>
#include <string>
#include <sstream>

#include <SOIL.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <GL/glew.h>    // All da OpenGL schtuff

#include "Error.hpp"    // Custom error handling macro
#include "GLMTypedefs.hpp"

namespace Larp
{
    class ConfigurationLoader;
    class DirectionalLight;
    class Entity;
    class Mesh;
    class Model;
    class Node;
    class PointLight;
    class SceneGraph;
    class Shader;
    class SkyBox;
    class SpotLight;
    class Texture;
    class Vertex;

    typedef std::unique_ptr<DirectionalLight> UniqueDirectional;
    typedef std::unique_ptr<Entity>           UniqueEntity;
    typedef std::unique_ptr<Model>            UniqueModel;
    typedef std::unique_ptr<Node>             UniqueNode;
    typedef std::unique_ptr<PointLight>       UniquePoint;
    typedef std::unique_ptr<SceneGraph>       UniqueSceneGraph;
    typedef std::unique_ptr<SkyBox>           UniqueSkyBox;
    typedef std::unique_ptr<SpotLight>        UniqueSpot;

    typedef Entity*                const EntityPtr;
    typedef DirectionalLight*      const DirectionalLightPtr;
    typedef Model*                 const ModelPtr;
    typedef Node*                  const NodePtr;
    typedef PointLight*            const PointLightPtr;
    typedef SceneGraph*            const SceneGraphPtr;
    typedef SkyBox*                const SkyBoxPtr;
    typedef SpotLight*             const SpotLightPtr;
}
