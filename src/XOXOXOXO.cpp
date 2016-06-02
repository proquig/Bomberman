//
// Created by cloquet on 02/06/16.
//

if (type == STAR)
{
this->_mesh_name = "./assets/BONUS/estrellica.obj";
this->_node = this->_irr.getSmgr()->addMeshSceneNode(this->_irr.getSmgr()->getMesh(this->_mesh_name.c_str()),
						     0, -1, irr::core::vector3df(x, 0, y),
						     irr::core::vector3df(0, 0, 0),
						     irr::core::vector3df(0.15, 0.15, 0.15));
this->_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
