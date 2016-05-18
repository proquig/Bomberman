//
// Created by cloquet on 11/05/16.
//

#ifndef CPP_INDIE_STUDIO_EVENTRECEIVER_HPP
#define CPP_INDIE_STUDIO_EVENTRECEIVER_HPP

#include <irrlicht.h>

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

class EventReceiver : public IEventReceiver
{
   public:
  	virtual bool OnEvent(const SEvent& event);
  	virtual bool IsKeyDown(EKEY_CODE keyCode) const;
  	MyEventReceiver();
   private:
    bool KeyIsDown[KEY_KEY_CODES_COUNT];
};


#endif //CPP_INDIE_STUDIO_EVENTRECEIVER_HPP
