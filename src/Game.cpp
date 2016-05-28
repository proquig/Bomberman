//
// Created by cloquet on 24/05/16.
//

#include "Game.hpp"
#include "Character.hpp"

# define X 90
# define Y 70

Bomberman::Game::Game() : irr(Bomberman::Irrlicht::instance())
{
  x = 0;
  y = 0;
  _material.Lighting = true;

  _scene = irr.getSmgr()->getRootSceneNode();

  scene::IMesh *plan = irr.getSmgr()->getGeometryCreator()
			  ->createPlaneMesh(core::dimension2df(X, Y), core::dimension2d<u32>(1, 1), 0,
					    core::dimension2df(1.f, 1.f));
  _m_scene = irr.getSmgr()->addMeshSceneNode(plan);
  _m_scene->setMaterialFlag(video::E_MATERIAL_FLAG::EMF_LIGHTING, false);
  irr.getSmgr()->getMeshManipulator()->makePlanarTextureMapping(plan, 0.5f);
  _m_scene->setMaterialTexture(0, irr.getDriver()->getTexture("./assets/Te/Wall_Normal.JPG"));

  for (int wallnbr = 0; wallnbr <= X; wallnbr += 5)
    {
      scene::IMesh *cube = irr.getSmgr()->getGeometryCreator()->createCubeMesh(core::vector3df(5.f, 5.f, 5.f));
      _wall = irr.getSmgr()->addMeshSceneNode(cube, _m_scene);
      _wall->setMaterialFlag(video::E_MATERIAL_FLAG::EMF_LIGHTING, false);
      irr.getSmgr()->getMeshManipulator()->makePlanarTextureMapping(plan, 0.5f);
      _wall->setMaterialTexture(0, irr.getDriver()->getTexture("./assets/Te/rock-wall-6-1.jpg"));
      _wall->setPosition(irr::core::vector3df(X / 2 - wallnbr, 2.5, Y / 2));

      scene::IMesh *cube2 = irr.getSmgr()->getGeometryCreator()->createCubeMesh(core::vector3df(5.f, 5.f, 5.f));
      _wall = irr.getSmgr()->addMeshSceneNode(cube2, _m_scene);
      _wall->setMaterialFlag(video::E_MATERIAL_FLAG::EMF_LIGHTING, false);
      irr.getSmgr()->getMeshManipulator()->makePlanarTextureMapping(plan, 0.5f);
      _wall->setMaterialTexture(0, irr.getDriver()->getTexture("./assets/Te/rock-wall-6-1.jpg"));
      _wall->setPosition(irr::core::vector3df(X / 2 - wallnbr, 2.5, -Y / 2));
    }

  for (int wallnbr = 0; wallnbr <= Y; wallnbr += 5)
    {
      scene::IMesh *cube = irr.getSmgr()->getGeometryCreator()->createCubeMesh(core::vector3df(5.f, 5.f, 5.f));
      _wall = irr.getSmgr()->addMeshSceneNode(cube, _m_scene);
      _wall->setMaterialFlag(video::E_MATERIAL_FLAG::EMF_LIGHTING, false);
      irr.getSmgr()->getMeshManipulator()->makePlanarTextureMapping(plan, 0.5f);
      _wall->setMaterialTexture(0, irr.getDriver()->getTexture("./assets/Te/rock-wall-6-1.jpg"));
      _wall->setPosition(irr::core::vector3df(X / 2, 2.5, Y / 2 - wallnbr));

      scene::IMesh *cube2 = irr.getSmgr()->getGeometryCreator()->createCubeMesh(core::vector3df(5.f, 5.f, 5.f));
      _wall = irr.getSmgr()->addMeshSceneNode(cube2, _m_scene);
      _wall->setMaterialFlag(video::E_MATERIAL_FLAG::EMF_LIGHTING, false);
      irr.getSmgr()->getMeshManipulator()->makePlanarTextureMapping(plan, 0.5f);
      _wall->setMaterialTexture(0, irr.getDriver()->getTexture("./assets/Te/rock-wall-6-1.jpg"));
      _wall->setPosition(irr::core::vector3df(-X/ 2, 2.5, Y / 2 - wallnbr));
    }


  scene::ITriangleSelector* selector = 0;
  selector = irr.getSmgr()->createOctreeTriangleSelector(
	  _m_scene->getMesh(), _m_scene, 128);
  _m_scene->setTriangleSelector(selector);



 /* scene::ISceneNodeAnimator* anim = irr.getSmgr()->createCollisionResponseAnimator(
	  selector, camera, core::vector3df(0,0,0),
	  core::vector3df(0,0,0), core::vector3df(0,0,0));
  selector->drop(); // As soon as we're done with the selector, drop it.
  camera->addAnimator(anim);
  anim->drop();*/
  //http://irrlicht-fr.org/viewtopic.php?id=1670

}

Bomberman::Game::~Game()
{
}

void Bomberman::Game::run()
{
  Character lol;
  scene::ICameraSceneNode *camera = irr.getSmgr()->addCameraSceneNode(_m_scene, core::vector3df(0, 60, -20), core::vector3df(0, 0, 0));
  irr::video::ITexture *background = irr.getDriver()->getTexture("./assets/Te/sky-clouds.jpg"),

  u32 now = 0;
  while (irr.getDevice()->run())
    {
      u32 then = irr.getDevice()->getTimer()->getTime();
      if (irr.event.IsKeyDown(irr::KEY_KEY_Z))
	lol.set_pos(UP);
    if (irr.event.IsKeyDown(irr::KEY_KEY_S))
      lol.set_pos(DOWN);
    if (irr.event.IsKeyDown(irr::KEY_KEY_Q))
      lol.set_pos(LEFT);
    if (irr.event.IsKeyDown(irr::KEY_KEY_D))
      lol.set_pos(RIGHT);
      if (irr.event.IsKeyDown(irr::KEY_KEY_U))
	{
	  now = irr.getDevice()->getTimer()->getTime();
	  lol.u();
	}
      if (now && then > (now + 1800))
	{
	  lol.base();
	  now = 0;
	}

      irr.getDriver()->beginScene(true, true, video::SColor(255,100,101,140));
      irr.getDriver()->draw2DImage(background, core::rect<s32>(0, 0, 1920, 1080),
				   core::rect<s32>(0, 0, 1920, 1080));
      irr.getSmgr()->drawAll();
      irr.getGui()->drawAll();
      irr.getDriver()->endScene();
    }
}
