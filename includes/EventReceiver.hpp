//
// Created by cloquet on 11/05/16.
//

#ifndef CPP_INDIE_STUDIO_EVENTRECEIVER_HPP
#define CPP_INDIE_STUDIO_EVENTRECEIVER_HPP

#include <irrlicht.h>
#include <vector>

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

using namespace irr;

class EventReceiver :	public IEventReceiver {
public:
  virtual bool		OnEvent(const SEvent& event);
  virtual bool		IsKeyDown(EKEY_CODE keyCode) const;
  void			MyEventReceiver();
  std::vector<bool>	getKeys();
private:
  bool			KeyIsDown[KEY_KEY_CODES_COUNT];
};


#endif //CPP_INDIE_STUDIO_EVENTRECEIVER_HPP
