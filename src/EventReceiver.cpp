//
// Created by cloquet on 11/05/16.
//

#include "EventReceiver.hpp"

bool EventReceiver::OnEvent(const SEvent& event)
{
  if (event.EventType == irr::EET_KEY_INPUT_EVENT)
    KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
  return false;
}

bool EventReceiver::IsKeyDown(EKEY_CODE keyCode) const
{
  return KeyIsDown[keyCode];
}

void EventReceiver::MyEventReceiver() {
  for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
    KeyIsDown[i] = false;
}
