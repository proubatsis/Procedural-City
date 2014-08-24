#include "CustomNode.h"

CustomNode::CustomNode(std::vector<irr::video::S3DVertex> vertices, std::vector<irr::u16> indices, irr::core::aabbox3df box, irr::scene::ISceneManager* sceneManager, ISceneNode* parent, int id)
	: ISceneNode(parent, sceneManager, id), _vertices(vertices), _indices(indices), _box(box), _polyCount(indices.size() / 3)
{
	_material.Wireframe = false;
	_material.Lighting = true;
}

CustomNode::CustomNode(CustomNode* node, irr::scene::ISceneManager* sceneManager, ISceneNode* parent, int id)
	: ISceneNode(parent, sceneManager, id)
{
	_vertices = node->_vertices;
	_indices = node->_indices;
	_box = node->_box;
	_material = node->_material;
	_polyCount = node->_polyCount;
}

void CustomNode::setMaterial(irr::video::SMaterial material)
{
	_material = material;
}

void CustomNode::OnRegisterSceneNode()
{
	if(this->IsVisible)
		this->SceneManager->registerNodeForRendering(this);

	irr::scene::ISceneNode::OnRegisterSceneNode();
}

void CustomNode::render()
{
	irr::video::IVideoDriver* driver = this->SceneManager->getVideoDriver();

	driver->setMaterial(_material);
	driver->setTransform(irr::video::ETS_WORLD, this->AbsoluteTransformation);
	driver->drawVertexPrimitiveList(&_vertices[0], _vertices.size(), &_indices[0], _polyCount, irr::video::EVT_STANDARD, irr::scene::EPT_TRIANGLES, irr::video::EIT_16BIT);
}