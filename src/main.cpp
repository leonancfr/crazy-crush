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
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

#if defined(_MSC_VER) || defined(_WIN32) || defined (_WIN64)
#include <windows.h>
#endif

#include "Irrlicht/irrlicht.h"
#include "SpriteAnimator.hpp"
#include "ScreenProgress.hpp"
#include "Screen.hpp"
#include "ScreenHoverList.hpp"
#include "TextureCache.hpp"
#include "AudioManager.hpp"
#include "Timer.hpp"
#include "ThreadProcessTime.hpp"
#include "CoreOpenGLVersion.hpp"
#include "Score.hpp"
#include "CoreProcess.hpp"
#include "ThreadProcessMouse.hpp"
#include "GameDefines.hpp"
#include "MainDraw.hpp"
#include "GameMainScreen.hpp"
#include "GameLevelFile.hpp"
#include "GameControl.hpp"
#include "ZOrder.hpp"
#include "Logger.hpp"
#include "Percentage.hpp"

int main(int argc,char** argv){
  std::fstream *fileCheck;
  fileCheck = new std::fstream();
  fileCheck->open("resource.zip");
  if(!fileCheck->is_open()){
    std::cerr<<"CrazyError: File resource.zip not found!"<<std::endl;
    abort();
  }
  fileCheck->close();
  
  bool fullscreen = false;
  bool vsyncFail = false;
  bool debug = false;
  bool convertFile = false;
  bool openBin = false;
  unsigned char timeWait = 15;
  for(unsigned i=1;i<(unsigned)argc;i++){
    if(strcmp(argv[i],"--fullscreen") == 0)
      fullscreen = true;
    else if(strcmp(argv[i],"--debug") == 0)
      debug = true;
    else if(strcmp(argv[i],"--convert") == 0){
      convertFile = true;
      openBin = false;
    }else if(strcmp(argv[i],"--openbin") == 0){
      convertFile = false;
      openBin = true;
    }
  }
  
  // Initialize and Pre-set IrrLicht Device and Driver
  CrazyCrush::device = irr::createDevice(
    irr::video::EDT_OPENGL,
    irr::core::dimension2d<irr::u32>(CrazyCrush::Screen::screenWidth, CrazyCrush::Screen::screenHeight),
    16,fullscreen,false,true,&CrazyCrush::event
  );
  
  if(CrazyCrush::device == NULL){
    LOG_ERROR("Unable to initialize Irrlicht device!");
    std::cerr<<"CrazyError: Unable to initialize IrrLicht device!"<<std::endl;
    abort();
  }
  CrazyCrush::device->setWindowCaption(L"CrazyCrush");
  CrazyCrush::device->getFileSystem()->addFileArchive("resource.zip",true,true,irr::io::EFAT_ZIP,"iUJOv0PbuPhyu9b2wRKO67DbJlE4hE8Mw8yL8ePk");
  CrazyCrush::driver = CrazyCrush::device->getVideoDriver();
  CrazyCrush::OpenGL::getOpenGLVersion(CrazyCrush::driver);
  CrazyCrush::driver->getMaterial2D().TextureLayer[0].BilinearFilter = true;
  CrazyCrush::driver->getMaterial2D().AntiAliasing = irr::video::EAAM_FULL_BASIC;
  
  // Initialize Progress class and load textures
  ScreenProgress progress(CrazyCrush::device,CrazyCrush::TextureCache::getTotalTexturesLoadNumber()+CrazyCrush::AudioManager::getTotalProgress()+1);
  progress.drawScene();
  if(CrazyCrush::AudioManager::initialize() == false){
    LOG_ERROR("Unable to initialize audio!");
    std::cerr<<"CrazyError: Unable to initialize audio!"<<std::endl;
    abort();
  }
  if(CrazyCrush::TextureCache::loadTextures(progress) == false){
    LOG_ERROR("Unable to load textures!");
    std::cerr<<"CrazyError: Unable to load textures!"<<std::endl;
    abort();
  }
  if(CrazyCrush::AudioManager::preLoadAudio(progress) == false){
    LOG_ERROR("Unable to load audio!");
    std::cerr<<"CrazyError: Unable to pre load audio!"<<std::endl;
    abort();
  }
  
  // Initialize Screen system
  CrazyCrush::Game::initialize();
  if(CrazyCrush::Screen::initializeScreen() == false){
    LOG_ERROR("Unable to set up Screen objects.");
    std::cerr<<"CrazyError: Unable to set up Screen objects."<<std::endl;
    abort();
  }
  CrazyCrush::Score::initialize();
  if(!CrazyCrush::Thread::startProcessTime()){
    LOG_ERROR("Unable to initialize time thread.");
    std::cerr<<"CrazyError: Unable to initialize time thread."<<std::endl;
    abort();
  }
  if(!CrazyCrush::Thread::startProcessMouse()){
    LOG_ERROR("Unable to initialize mouse thread.");
    std::cerr<<"CrazyError: Unable to initialize mouse thread."<<std::endl;
    abort();
  }
  pauseGameTimer();
  CrazyCrush::Game::MainScreen::screen.show();
  
  progress.incLoaded().drawScene();
  
  if(convertFile){
    if(CrazyCrush::Game::LevelFile::openLevelText("in.txt",false)){
      if(CrazyCrush::Game::LevelFile::saveLevel("out.bin")){
      
      }else{
        LOG_ERROR("Unable to save the output level");
        std::cerr<<"CrazyError: Unable to save the output level."<<std::endl;
      }
    }else{
       LOG_WARN("Unable to read input level as text");
      std::cerr<<"CrazyError: Unable to read input level as text."<<std::endl;
    }
  }else if(openBin){
    if(CrazyCrush::Game::LevelFile::openLevel("in.bin",false)){
    
    }else{
      LOG_WARN("Unable to read input level as binary");
      std::cerr<<"CrazyError: Unable to read input level as binary."<<std::endl;
    }
  }

  int lastFPS = -1;
  int fps = -1;
  bool lastButtonState = false;
  while(CrazyCrush::device->run() && CrazyCrush::driver){
    CrazyCrush::irrlicht_thread_read_file();
    if(CrazyCrush::device->isWindowActive()){
      CrazyCrush::core::resumeGame();
      irr::u32 time = CrazyCrush::device->getTimer()->getTime();
      if(time != getUnprotectedTime())
        setTime(time);
      fps = CrazyCrush::driver->getFPS();
      if(fps!=lastFPS){
        if(fps > 65){
          vsyncFail = true;
          if(lastFPS > 65)
            timeWait++;
        }else if((fps < 55)&&(lastFPS < 55)){
          if(timeWait == 0)
            vsyncFail = false;
          else
            timeWait--;
        }
        if(debug){
          irr::core::stringw str = "Crazy Crush - FPS: ";
          str += fps;
          CrazyCrush::device->setWindowCaption(str.c_str());
        }
        lastFPS = fps;
      }
      CrazyCrush::ThreadProcessMouse::setCursor(CrazyCrush::event.getMouseX(),CrazyCrush::event.getMouseY());
      if(CrazyCrush::event.mouseLeftButtonPressed() != lastButtonState){
        lastButtonState = CrazyCrush::event.mouseLeftButtonPressed();
        if(lastButtonState)
          CrazyCrush::ThreadProcessMouse::setClick();
      }

      CrazyCrush::draw();
      
      if(CrazyCrush::event.IsKeyDown(irr::KEY_ESCAPE))
        CrazyCrush::Game::Control::pauseGame();
      if(CrazyCrush::event.IsKeyDown(irr::KEY_KEY_A)){
        #ifdef DEBUG
        CrazyCrush::ScreenHoverList::debug();
        #endif
      }
      if(CrazyCrush::event.IsKeyDown(irr::KEY_KEY_S)){
        #ifdef DEBUG
        CrazyCrush::z_order.debug();
        #endif
      }

      if(vsyncFail){
        irr::u32 now = CrazyCrush::device->getTimer()->getTime();
        if(now-time < timeWait)
          CrazyCrush::device->sleep(timeWait-(now-time));
      }
    }else{
      CrazyCrush::core::pauseGame();
      CrazyCrush::device->yield();
    }
    if(CrazyCrush::shutdownGame.get()){
      CrazyCrush::device->closeDevice();
    }
  }
  CrazyCrush::Thread::stopProcessTime();
  CrazyCrush::Thread::stopProcessMouse();
  CrazyCrush::AudioManager::destroy();
  LOG_INFO("Audio destroyed");
  CrazyCrush::device->drop();
  LOG_INFO("Engine destroyed");
  return 0;
}