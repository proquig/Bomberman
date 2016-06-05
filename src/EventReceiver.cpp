//
// Created by cloquet on 11/05/16.
//

#include "EventReceiver.hpp"

bool                        EventReceiver::OnEvent(const irr::SEvent &event)
{
  if (event.EventType == irr::EET_KEY_INPUT_EVENT)
    KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
  return false;
}

bool                        EventReceiver::IsKeyDown(irr::EKEY_CODE keyCode) const
{
  return KeyIsDown[keyCode];
}

void                        EventReceiver::MyEventReceiver()
{
  for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
    KeyIsDown[i] = false;
}

std::vector<bool>        EventReceiver::getKeys()
{
  std::vector<bool> vec;

  for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
    vec.push_back(KeyIsDown[i]);
  return vec;
}
