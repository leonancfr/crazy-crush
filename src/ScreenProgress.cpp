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
#include "ScreenProgress.hpp"

void ScreenProgress::instaceObjects(){
  bar.set(driver->getTexture("progress_bar.png"));
  barRight = new ScreenObject(bar);
  barLeft = new ScreenObject(bar);
  barMiddle = new ScreenObject(bar);
  loadText.set(driver->getTexture("loading_text.png"));
  loadingText = new ScreenObject(loadText);
  barRight->setScreenSize(5,11);
  barLeft->setScreenSize(5,11);
  barMiddle->setScreenSize(1,11);
  barRight->setResourceSize(5,11);
  barLeft->setResourceSize(5,11);
  barMiddle->setResourceSize(1,11);
  barRight->setResourcePosition(13,0);
  barLeft->setResourcePosition(0,0);
  barMiddle->setResourcePosition(6,0);
  loadingText->setResourceSize(329,69);
  loadingText->setScreenSize(329,69);
  loadingText->setScreenPosition(155,205);
  loadingText->setImageAlpha(0);
}

ScreenProgress::ScreenProgress(irr::IrrlichtDevice* dev){
  device = dev;
  driver = dev->getVideoDriver();
  bar_size = 340;
  total_load = 0;
  total_loaded = 0;
  instaceObjects();
}

ScreenProgress::ScreenProgress(irr::IrrlichtDevice* dev,unsigned total){
  device = dev;
  driver = dev->getVideoDriver();
  bar_size = 340;
  total_load = total;
  total_loaded = 0;
  instaceObjects();
}

ScreenProgress::ScreenProgress(irr::IrrlichtDevice* dev,unsigned total,unsigned bar){
  device = dev;
  driver = dev->getVideoDriver();
  bar_size = bar;
  total_load = total;
  total_loaded = 0;
  instaceObjects();
}

ScreenProgress::~ScreenProgress(){
  delete barRight;
  delete barLeft;
  delete barMiddle;
  delete loadingText;
}

void ScreenProgress::setTotalToLoad(unsigned total){
  total_load = total;
}

ScreenProgress& ScreenProgress::incLoaded(){
  total_loaded++;
  if(total_loaded > total_load)
    total_loaded = total_load;
  return *this;
}

ScreenProgress& ScreenProgress::incLoaded(unsigned val){
  total_loaded += val;
  if(total_loaded > total_load)
    total_loaded = total_load;
  return *this;
}

bool ScreenProgress::drawScene(){
  if(total_loaded == 0){
    barMiddle->setScreenSize(0,11);
    barLeft->setScreenPosition(315,300);
    barRight->setScreenPosition(320,300);
  }else{
    unsigned use_size = bar_size*((float)total_loaded/total_load);
    loadingText->setImageAlpha(255*((float)total_loaded/total_load));
    barMiddle->setScreenSize(use_size,11);
    barMiddle->setScreenPosition(320-use_size/2,300);
    barLeft->setScreenPosition(315-use_size/2,300);
    if(use_size%2 == 1)
      barRight->setScreenPosition(321+use_size/2,300);
    else
      barRight->setScreenPosition(320+use_size/2,300);
  }
  if((!device->run())||(!driver))
    return false;
  driver->beginScene();
  driver->enableMaterial2D();
    driver->draw2DImage(
      barLeft->getTexture(),
      barLeft->getScreenRect(),
      barLeft->getResourceRect(),
      0,
      barLeft->getImageColor(),
      true
    );
    driver->draw2DImage(
      barRight->getTexture(),
      barRight->getScreenRect(),
      barRight->getResourceRect(),
      0,
      barRight->getImageColor(),
      true
    );
    driver->draw2DImage(
      barMiddle->getTexture(),
      barMiddle->getScreenRect(),
      barMiddle->getResourceRect(),
      0,
      barMiddle->getImageColor(),
      true
    );
    driver->draw2DImage(
      loadingText->getTexture(),
      loadingText->getScreenRect(),
      loadingText->getResourceRect(),
      0,
      loadingText->getImageColor(),
      true
    );
  driver->enableMaterial2D(false);
  driver->endScene();
  return true;
}

unsigned ScreenProgress::getTotalToLoad(){
  return total_load;
}

unsigned ScreenProgress::getTotalLoaded(){
  return total_loaded;
}

irr::IrrlichtDevice* ScreenProgress::getDevice(){
  return device;
}
irr::video::IVideoDriver* ScreenProgress::getDriver(){
  return driver;
}