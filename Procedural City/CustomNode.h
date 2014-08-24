#ifndef CUSTOM_NODE
#define CUSTOM_NODE

#include <irrlicht.h>
#include <vector>

class CustomNode : public irr::scene::ISceneNode
{
private:
	std::vector<irr::video::S3DVertex> _vertices;
	std::vector<irr::u16> _indices;
	irr::core::aabbox3df _box;
	irr::video::SMaterial _material;
	int _polyCount;

public:
	CustomNode(std::vector<irr::video::S3DVertex> vertices, std::vector<irr::u16> indices, irr::core::aabbox3df box, irr::scene::ISceneManager* sceneManager, ISceneNode* parent, int id);
	CustomNode(CustomNode* node, irr::scene::ISceneManager* sceneManager, ISceneNode* parent, int id);

	void setMaterial(irr::video::SMaterial material);

	virtual void OnRegisterSceneNode();
	virtual void render();

	virtual const irr::core::aabbox3df& getBoundingBox() const { return _box; }
	virtual irr::u32 getMaterialCount() const { return 1; }
	virtual irr::video::SMaterial& getMaterial(irr::u32 i) { return _material; }
};

#endif