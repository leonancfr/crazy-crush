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
#include "TextureCache.hpp"
#include "Irrlicht/IGUIEnvironment.h"
#include "Random.hpp"

namespace CrazyCrush{
namespace TextureCache{

SharedPointer<irr::video::ITexture> gem0;
SharedPointer<irr::video::ITexture> gem1;
SharedPointer<irr::video::ITexture> gem2;
SharedPointer<irr::video::ITexture> gem3;
SharedPointer<irr::video::ITexture> gem4;
SharedPointer<irr::video::ITexture> gem5;
SharedPointer<irr::video::ITexture> gem6;
SharedPointer<irr::video::ITexture> rock;
SharedPointer<irr::video::ITexture> seta_v;
SharedPointer<irr::video::ITexture> seta_h;
SharedPointer<irr::video::ITexture> selector;
SharedPointer<irr::video::ITexture> stageBackground;
SharedPointer<irr::video::ITexture> gameBackground;
SharedPointer<irr::video::ITexture> sprites;
SharedPointer<irr::video::ITexture> buttons;
SharedPointer<irr::video::ITexture> buttons_circle;
SharedPointer<irr::gui::IGUIFont> font1;
SharedPointer<irr::gui::IGUIFont> fontSFComic;
ScreenObject ObjectModel(NULL);
SpriteAnimator DefaultAnimator;
  
void setDefault(){
  DefaultAnimator.setResourcePosition(1.0/15,0.0);
  DefaultAnimator.setResourceLoop(20,84);
  ObjectModel.setScreenSize(gemWidth,gemHeight);
  ObjectModel.setResourceSize(84,84);
  ObjectModel.setResourcePosition(0,0);
  ObjectModel.setDisplay(false);
  ObjectModel.setSpriteAnimator(&DefaultAnimator);
}
    
bool loadTextures(ScreenProgress& progress){
  progress.drawScene();
  bool useDark = true;//rand()%2==0;
  if(useDark)
    gem0.set(progress.getDriver()->getTexture("gem0_dark.png"));
  else
    gem0.set(progress.getDriver()->getTexture("gem0.png"));
  progress.incLoaded().drawScene();
  if(useDark)
    gem1.set(progress.getDriver()->getTexture("gem1_dark.png"));
  else
    gem1.set(progress.getDriver()->getTexture("gem1.png"));
  progress.incLoaded().drawScene();
  if(useDark)
    gem2.set(progress.getDriver()->getTexture("gem2_dark.png"));
  else
    gem2.set(progress.getDriver()->getTexture("gem2.png"));
  progress.incLoaded().drawScene();
  if(useDark)
    gem3.set(progress.getDriver()->getTexture("gem3_dark.png"));
  else
    gem3.set(progress.getDriver()->getTexture("gem3.png"));
  progress.incLoaded().drawScene();
  if(useDark)
    gem4.set(progress.getDriver()->getTexture("gem4_dark.png"));
  else
    gem4.set(progress.getDriver()->getTexture("gem4.png"));
  progress.incLoaded().drawScene();
  if(useDark)
    gem5.set(progress.getDriver()->getTexture("gem5_dark.png"));
  else
    gem5.set(progress.getDriver()->getTexture("gem5.png"));
  progress.incLoaded().drawScene();
  if(useDark)
    gem6.set(progress.getDriver()->getTexture("gem6_dark.png"));
  else
    gem6.set(progress.getDriver()->getTexture("gem6.png"));
  progress.incLoaded().drawScene();
  
  rock.set(progress.getDriver()->getTexture("rock.png"));
  progress.incLoaded().drawScene();
  selector.set(progress.getDriver()->getTexture("mySelector.png"));
  progress.incLoaded().drawScene();
  stageBackground.set(progress.getDriver()->getTexture("stageBackground.png"));
  progress.incLoaded().drawScene();
  switch(CrazyCrush::Random::get()%4){
    case 1:
      gameBackground.set(progress.getDriver()->getTexture("background_1.png"));
      break;
    case 2:
      gameBackground.set(progress.getDriver()->getTexture("background_2.png"));
      break;
    case 3:
      gameBackground.set(progress.getDriver()->getTexture("background_3.png"));
      break;
    default:
      gameBackground.set(progress.getDriver()->getTexture("background_4.png"));
      break;
  }
  progress.incLoaded().drawScene();
  seta_v.set(progress.getDriver()->getTexture("seta_v.png"));
  progress.incLoaded().drawScene();
  seta_h.set(progress.getDriver()->getTexture("seta_h.png"));
  progress.incLoaded().drawScene();
  sprites.set(progress.getDriver()->getTexture("sprites.png"));
  progress.incLoaded().drawScene();
  buttons.set(progress.getDriver()->getTexture("buttons.png"));
  progress.incLoaded().drawScene();
  buttons_circle.set(progress.getDriver()->getTexture("sprite_button_circle.png"));
  progress.incLoaded().drawScene();
  font1.set(progress.getDevice()->getGUIEnvironment()->getFont("itc_14.xml"));
  progress.incLoaded().drawScene();
  fontSFComic.set(progress.getDevice()->getGUIEnvironment()->getFont("SF_Comic_26.xml"));
  progress.incLoaded().drawScene();
  setDefault();
  return true;
}

unsigned char getTotalTexturesLoadNumber(){
  return 18;
}
}} // Close CrazyCrush::TextureCache
