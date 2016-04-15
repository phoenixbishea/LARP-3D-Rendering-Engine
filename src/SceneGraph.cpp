#include "SceneGraph.hpp"

pSceneGraph SceneGraph::_singleton(nullptr);

SceneGraph::SceneGraph()
    : _root(new Node())
{
}

pSceneGraph SceneGraph::singleton()
{
    if (!_singleton)
    {
        _singleton = pSceneGraph(new SceneGraph());
    }
    return _singleton;
}


pNode SceneGraph::create_child_node()
{
    return _root->create_child();
}

void SceneGraph::draw(glm::mat4& view, glm::mat4& projection)
{
    glm::mat4 identity;
    this->_root->draw(identity, view, projection);
}

void SceneGraph::set_ambient_light(glm::vec3 color)
{
}
