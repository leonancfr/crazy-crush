/* Universidade Federal do Rio de Janeiro
 * Escola Politécnica
 * Departamento de Eletrônica e Computação
 * Prof. Fernando Silva
 * EEL 670 - Linguagem de Programação
 *
 * Authors: Daniel Dahis     (dahisdaniel@poli.ufrj.br)
 *          Leonan França    (leonancfr@poli.ufrj.br)
 *          Gustavo Silva    (diguser@gmail.com)
 *          Michael Douglas  (michaeldouglas@poli.ufrj.br)
 */
#include "EventReceiver.hpp"

MyEventReceiver::MyEventReceiver(){
  mouseX = 0;
  mouseY = 0;
  mouseLeftButtonDown = false;
  KeyIsDown.resize(irr::KEY_KEY_CODES_COUNT);
  mouse = PTHREAD_MUTEX_INITIALIZER;
  keyboard = PTHREAD_MUTEX_INITIALIZER;
  for(irr::u32 i=0; i<irr::KEY_KEY_CODES_COUNT; ++i)
    KeyIsDown[i] = false;
}

bool MyEventReceiver::mouseLeftButtonPressed(){
  bool r;
  pthread_mutex_lock(&mouse);
  r = mouseLeftButtonDown;
  pthread_mutex_unlock(&mouse);
  return r;
}

unsigned MyEventReceiver::getMouseY(){
  unsigned r;
  pthread_mutex_lock(&mouse);
  r = mouseY;
  pthread_mutex_unlock(&mouse);
  return r;
}

unsigned MyEventReceiver::getMouseX(){
  unsigned r;
  pthread_mutex_lock(&mouse);
  r = mouseX;
  pthread_mutex_unlock(&mouse);
  return r;
}

bool MyEventReceiver::IsKeyDown(irr::EKEY_CODE keyCode) {
  bool r;
  pthread_mutex_lock(&keyboard);
  r = KeyIsDown[keyCode];
  pthread_mutex_unlock(&keyboard);
  return r;
}

bool MyEventReceiver::OnEvent(const irr::SEvent& event){
  if(event.EventType == irr::EET_KEY_INPUT_EVENT){
    pthread_mutex_lock(&keyboard);
    KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    pthread_mutex_unlock(&keyboard);
  }else if(event.EventType == irr::EET_MOUSE_INPUT_EVENT){
    pthread_mutex_lock(&mouse);
    switch(event.MouseInput.Event){
      case irr::EMIE_LMOUSE_PRESSED_DOWN:
        mouseLeftButtonDown = true;
        break;
      case irr::EMIE_LMOUSE_LEFT_UP:
        mouseLeftButtonDown = false;
        break;
      case irr::EMIE_MOUSE_MOVED:
        mouseX = event.MouseInput.X;
        mouseY = event.MouseInput.Y;
        break;
      default:
        break;
    }
    pthread_mutex_unlock(&mouse);
  }
  return false;
}