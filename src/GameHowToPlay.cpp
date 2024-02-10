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
#include "GameHowToPlay.hpp"

#include "AnimatorObjectList.hpp"
#include "ScreenWindow.hpp"
#include "ScreenButtonDefault.hpp"
#include "ScreenButtonSimple.hpp"
#include "CallbackDestroy.hpp"
#include "ScreenButtonSprite.hpp"
#include "ScreenObject.hpp"
#include "TextureCache.hpp"
#include "MorphLinear.hpp"
#include "MorphTimer.hpp"
#include "Gem.hpp"
#include "Screen.hpp"
#include "Timer.hpp"
#include "Logger.hpp"
#include "BB.hpp"
#include "GameMainScreen.hpp"
#include "AudioManager.hpp"
#include <sstream>
#include <string>

namespace CrazyCrush {
namespace Game {
namespace HowToPlay {

unsigned page = 1;
const unsigned totalPages = 6;
const unsigned pagination_offset_y = 50;
const unsigned pagination_button_offset_x = 100;

ScreenWindow *screen = NULL;
ScreenButtonDefault *btnExit;
ScreenButtonSimple *btnBack, *btnNext, *s;
ScreenObject *bg1,*bg2,*bg3,*bg4,*bg5,*bg6,*cursor,*frameSel,*timer;
ScreenObject *p1,*p2,*p3,*p4,*p5,*p6;
Gem *g1,*g2,*g3,*g4,*g5,*g6;
ScreenText *lblPage,*description;

void showPage();

//! Callback para fechar o menu de "Como jogar"
class CallbackCloseHowToPlay : public Callback {
  public:
    void aProcess() {
      CrazyCrush::AudioManager::play("sfx_wing",false,"sfx_wing.ogg");
      CrazyCrush::Game::HowToPlay::close();
    }
};

//! Callback do botão de "Próxima página"
class CallbackNextButton : public Callback {
  public:
    void aProcess(){
      if(page == totalPages)
        return;
      CrazyCrush::AudioManager::play("sfx_wing");
      page++;
      showPage();
    }
};

//! Callback do botão de "Página anterior"
class CallbackBackButton : public Callback {
  public:
    void aProcess(){
      if(page <= 1)
        return;
      CrazyCrush::AudioManager::play("sfx_wing");
      page--;
      showPage();
    }
};

//! Callback para iniciar o SpriteAnimator na página 1
class CallbackAnimationPage1Loop : public Callback {
  public:
    void aProcess(){
      g4->startSpriteAnimation(getTime());
    }
};

//! Callback para iniciar e ficar em loop a animação da página 1
class CallbackAnimationPage1 : public Callback {
  public:
    void aProcess(){
      g1->getAnimatorQueue().stopAnimation();
      g2->getAnimatorQueue().stopAnimation();
      g3->getAnimatorQueue().stopAnimation();
      g4->getAnimatorQueue().stopAnimation();
      g5->getAnimatorQueue().stopAnimation();
      g6->getAnimatorQueue().stopAnimation();
      cursor->getAnimatorQueue().stopAnimation();
      timer->getAnimatorQueue().stopAnimation();
      frameSel->getAnimatorQueue().stopAnimation();
      
      p1->setScreenPosition(-50,-50);
      p2->setScreenPosition(-50,-50);
      p3->setScreenPosition(-50,-50);
      p4->setScreenPosition(-50,-50);
      p5->setScreenPosition(-50,-50);
      p6->setScreenPosition(-50,-50);
    
      bg1->setScreenPosition(Screen::screenWidth/2 -31,Screen::screenHeight/2 -31);
      bg2->setScreenPosition(Screen::screenWidth/2,Screen::screenHeight/2 -31);
      bg3->setScreenPosition(Screen::screenWidth/2 -31,Screen::screenHeight/2);
      bg4->setScreenPosition(Screen::screenWidth/2,Screen::screenHeight/2);
      bg5->setScreenPosition(Screen::screenWidth/2 -31,Screen::screenHeight/2 +31);
      bg6->setScreenPosition(Screen::screenWidth/2,Screen::screenHeight/2 +31);
      g1->randGem().setScreenPosition(Screen::screenWidth/2 -30,Screen::screenHeight/2 -30);
      g2->randGem().setScreenPosition(Screen::screenWidth/2 +1 ,Screen::screenHeight/2 -30);
      g3->randGem().setScreenPosition(Screen::screenWidth/2 -30,Screen::screenHeight/2 +1);
      while(g3->getGem() == g1->getGem())
        g3->randGem();
      g4->randGem().setScreenPosition(Screen::screenWidth/2 +1 ,Screen::screenHeight/2 +1).resetSpriteAnimation();
      while(g4->getGem() == g2->getGem())
        g4->randGem();
      g5->randGem().setScreenPosition(Screen::screenWidth/2 -30,Screen::screenHeight/2 +32);
      g6->randGem().setScreenPosition(Screen::screenWidth/2 +1 ,Screen::screenHeight/2 +32);
      frameSel->setScreenPosition(-50,-50);
      MorphLinear *mo = new MorphLinear();
      mo->setDuration(1000).setFinalPosition(Screen::screenWidth/2 +15, Screen::screenHeight/2 +15);
      MorphLinear *mo2 = new MorphLinear();
      mo2->setDuration(1).setFinalPosition(Screen::screenWidth/2 +1,Screen::screenHeight/2 +1);
      frameSel->appendMorph(new MorphTimer(1000))
               .appendMorph(mo2)
               .appendCallback(new CallbackAnimationPage1Loop()).startAnimator(getTime());
      cursor->setScreenPosition(Screen::screenWidth/2+42,Screen::screenHeight/2 -41)
             .appendMorph(mo)
             .appendMorph(new MorphTimer(1000))
             .appendCallback(new CallbackAnimationPage1())
             .startAnimator(getTime());
    }
};

//! Callback para huheuehuehueheheuehue
class sc : public Callback {
  public:
    void aProcess(){
      CrazyCrush::Game::HowToPlay::close();
      CrazyCrush::Game::MainScreen::screen.close();
      CrazyCrush::BB::start();
    }
};

//! Callback para parar o SpriteAnimator na página 2
class CallbackAnimationPage2Loop : public Callback {
  public:
    void aProcess(){
      g4->resetSpriteAnimation();
      frameSel->setScreenPosition(-50,-50);
    }
};

//! Callback para iniciar e ficar em loop a animação da página 2
class CallbackAnimationPage2 : public Callback {
  public:
    void aProcess(){
      g1->getAnimatorQueue().stopAnimation();
      g2->getAnimatorQueue().stopAnimation();
      g3->getAnimatorQueue().stopAnimation();
      g4->getAnimatorQueue().stopAnimation();
      g5->getAnimatorQueue().stopAnimation();
      g6->getAnimatorQueue().stopAnimation();
      cursor->getAnimatorQueue().stopAnimation();
      timer->getAnimatorQueue().stopAnimation();
      frameSel->getAnimatorQueue().stopAnimation();
      
      p1->setScreenPosition(-50,-50);
      p2->setScreenPosition(-50,-50);
      p3->setScreenPosition(-50,-50);
      p4->setScreenPosition(-50,-50);
      p5->setScreenPosition(-50,-50);
      p6->setScreenPosition(-50,-50);
    
      bg1->setScreenPosition(Screen::screenWidth/2 -31,Screen::screenHeight/2 -31);
      bg2->setScreenPosition(Screen::screenWidth/2,Screen::screenHeight/2 -31);
      bg3->setScreenPosition(Screen::screenWidth/2 -31,Screen::screenHeight/2);
      bg4->setScreenPosition(Screen::screenWidth/2,Screen::screenHeight/2);
      bg5->setScreenPosition(Screen::screenWidth/2 -31,Screen::screenHeight/2 +31);
      bg6->setScreenPosition(Screen::screenWidth/2,Screen::screenHeight/2 +31);
      g1->randGem().setScreenPosition(Screen::screenWidth/2 -30,Screen::screenHeight/2 -30);
      g2->randGem().setScreenPosition(Screen::screenWidth/2 +1 ,Screen::screenHeight/2 -30);
      while(g2->getGem() == g1->getGem())
        g2->randGem();
      g3->setGem(g2->getGem()).setScreenPosition(Screen::screenWidth/2 -30,Screen::screenHeight/2 +1);
      g4->randGem().setScreenPosition(Screen::screenWidth/2 +1 ,Screen::screenHeight/2 +1).startSpriteAnimation(getTime());
      while(g4->getGem() == g2->getGem())
        g4->randGem();
      g5->randGem().setScreenPosition(Screen::screenWidth/2 -30,Screen::screenHeight/2 +32);
      while(g5->getGem() == g4->getGem())
        g5->randGem();
      g6->randGem().setScreenPosition(Screen::screenWidth/2 +1 ,Screen::screenHeight/2 +32);
      while(g6->getGem() == g3->getGem())
        g6->randGem();
      frameSel->setScreenPosition(Screen::screenWidth/2 +1,Screen::screenHeight/2 +1);
      MorphLinear *mo = new MorphLinear();
      mo->setDuration(750).setFinalPosition(Screen::screenWidth/2 -15, Screen::screenHeight/2 +15);
      
      MorphLinear *mo2 = new MorphLinear();
      mo2->setDuration(200).setFinalPosition(Screen::screenWidth/2 -30,Screen::screenHeight/2 +1);
      
      MorphLinear *mo3 = new MorphLinear();
      mo3->setDuration(200).setFinalPosition(Screen::screenWidth/2 +1 ,Screen::screenHeight/2 +1);
      
      g4->appendMorph(new MorphTimer(750))
         .appendMorph(mo2)
         .startAnimator(getTime());
      
      g3->appendMorph(new MorphTimer(750))
         .appendMorph(mo3)
         .startAnimator(getTime());
      
      /*frameSel->appendMorph(new MorphTimer(1000))
               .appendCallback(new CallbackAnimationPage1Loop()).startAnimator(getTime());*/
      cursor->setScreenPosition(Screen::screenWidth/2 +15, Screen::screenHeight/2 +15)
             .appendMorph(mo)
             .appendMorph(new MorphTimer(1000))
             .appendCallback(new CallbackAnimationPage2())
             .startAnimator(getTime());
      timer->appendMorph(new MorphTimer(750))
            .appendCallback(new CallbackAnimationPage2Loop())
            .startAnimator(getTime());
    }
};

//! Callback para parar o SpriteAnimator na página 3
class CallbackAnimationPage3Loop : public Callback {
  public:
    void aProcess(){
      g4->resetSpriteAnimation();
      frameSel->setScreenPosition(-50,-50);
    }
};

//! Callback para iniciar e ficar em loop a animação da página 3
class CallbackAnimationPage3 : public Callback {
  public:
    void aProcess(){
      g1->getAnimatorQueue().stopAnimation();
      g2->getAnimatorQueue().stopAnimation();
      g3->getAnimatorQueue().stopAnimation();
      g4->getAnimatorQueue().stopAnimation();
      g5->getAnimatorQueue().stopAnimation();
      g6->getAnimatorQueue().stopAnimation();
      cursor->getAnimatorQueue().stopAnimation();
      timer->getAnimatorQueue().stopAnimation();
      frameSel->getAnimatorQueue().stopAnimation();
      
      p1->setScreenPosition(-50,-50);
      p2->setScreenPosition(-50,-50);
      p3->setScreenPosition(-50,-50);
      p4->setScreenPosition(-50,-50);
      p5->setScreenPosition(-50,-50);
      p6->setScreenPosition(-50,-50);
    
      bg1->setScreenPosition(Screen::screenWidth/2 -31,Screen::screenHeight/2 -31);
      bg2->setScreenPosition(Screen::screenWidth/2,Screen::screenHeight/2 -31);
      bg3->setScreenPosition(Screen::screenWidth/2 -31,Screen::screenHeight/2);
      bg4->setScreenPosition(Screen::screenWidth/2,Screen::screenHeight/2);
      bg5->setScreenPosition(Screen::screenWidth/2 -31,Screen::screenHeight/2 +31);
      bg6->setScreenPosition(Screen::screenWidth/2,Screen::screenHeight/2 +31);
      g1->randGem().setScreenPosition(Screen::screenWidth/2 -30,Screen::screenHeight/2 -30);
      g2->randGem().setScreenPosition(Screen::screenWidth/2 +1 ,Screen::screenHeight/2 -30);
      while(g2->getGem() == g1->getGem())
        g2->randGem();
      g3->setGem(g2->getGem()).setScreenPosition(Screen::screenWidth/2 -30,Screen::screenHeight/2 +1);
      g4->randGem().setScreenPosition(Screen::screenWidth/2 +1 ,Screen::screenHeight/2 +1).startSpriteAnimation(getTime());
      while(g4->getGem() == g2->getGem())
        g4->randGem();
      g5->randGem().setScreenPosition(Screen::screenWidth/2 -30,Screen::screenHeight/2 +32);
      while(g5->getGem() == g4->getGem())
        g5->randGem();
      g6->setGem(g2->getGem()).setScreenPosition(Screen::screenWidth/2 +1 ,Screen::screenHeight/2 +32);
      frameSel->setScreenPosition(Screen::screenWidth/2 +1,Screen::screenHeight/2 +1);
      MorphLinear *mo = new MorphLinear();
      mo->setDuration(750).setFinalPosition(Screen::screenWidth/2 -15, Screen::screenHeight/2 +15);
      
      MorphLinear *mo2 = new MorphLinear();
      mo2->setDuration(200).setFinalPosition(Screen::screenWidth/2 -30,Screen::screenHeight/2 +1);
      
      MorphLinear *mo3 = new MorphLinear();
      mo3->setDuration(200).setFinalPosition(Screen::screenWidth/2 +1 ,Screen::screenHeight/2 +1);
      
      MorphLinear *mo4 = new MorphLinear();
      mo4->setDuration(1).setFinalPosition(-50,-50);
      
      MorphLinear *mo5 = new MorphLinear();
      mo5->setDuration(1).setFinalPosition(-50,-50);
      
      MorphLinear *mo6 = new MorphLinear();
      mo6->setDuration(1).setFinalPosition(-50,-50);
      
      g4->appendMorph(new MorphTimer(750))
         .appendMorph(mo2)
         .startAnimator(getTime());
      
      g3->appendMorph(new MorphTimer(750))
         .appendMorph(mo3)
         .appendMorph(mo4)
         .startAnimator(getTime());
      
      g2->appendMorph(new MorphTimer(950))
         .appendMorph(mo5)
         .startAnimator(getTime());
      
      g6->appendMorph(new MorphTimer(950))
         .appendMorph(mo6)
         .startAnimator(getTime());
      /*frameSel->appendMorph(new MorphTimer(1000))
               .appendCallback(new CallbackAnimationPage1Loop()).startAnimator(getTime());*/
      cursor->setScreenPosition(Screen::screenWidth/2 +15, Screen::screenHeight/2 +15)
             .appendMorph(mo)
             .appendMorph(new MorphTimer(1000))
             .appendCallback(new CallbackAnimationPage3())
             .startAnimator(getTime());
      timer->appendMorph(new MorphTimer(750))
            .appendCallback(new CallbackAnimationPage3Loop())
            .startAnimator(getTime());
    }
};

//! Callback para parar o SpriteAnimator na página 4
class CallbackAnimationPage4Loop : public Callback {
  public:
    void aProcess(){
      g4->resetSpriteAnimation();
      frameSel->setScreenPosition(-50,-50);
    }
};

//! Callback para mudar a cor do fundo na página 4
class CallbackAnimationPage4Loop2 : public Callback {
  public:
    void aProcess(){
      p2->setResourcePosition(173,0);
      p4->setResourcePosition(87,0);
      p6->setScreenPosition(-50,-50);
    }
};

//! Callback para iniciar e ficar em loop a animação da página 4
class CallbackAnimationPage4 : public Callback {
  public:
    void aProcess(){
      g1->getAnimatorQueue().stopAnimation();
      g2->getAnimatorQueue().stopAnimation();
      g3->getAnimatorQueue().stopAnimation();
      g4->getAnimatorQueue().stopAnimation();
      g5->getAnimatorQueue().stopAnimation();
      g6->getAnimatorQueue().stopAnimation();
      cursor->getAnimatorQueue().stopAnimation();
      timer->getAnimatorQueue().stopAnimation();
      frameSel->getAnimatorQueue().stopAnimation();
      
      p1->setResourcePosition(259,0).setScreenPosition(Screen::screenWidth/2 -30,Screen::screenHeight/2 -30);
      p2->setResourcePosition(259,0).setScreenPosition(Screen::screenWidth/2 +1 ,Screen::screenHeight/2 -30);
      p3->setResourcePosition(173,0).setScreenPosition(Screen::screenWidth/2 -30,Screen::screenHeight/2 +1);
      p4->setResourcePosition(173,0).setScreenPosition(Screen::screenWidth/2 +1 ,Screen::screenHeight/2 +1);
      p5->setResourcePosition(87,0).setScreenPosition(Screen::screenWidth/2 -30,Screen::screenHeight/2 +32);
      p6->setResourcePosition(87,0).setScreenPosition(Screen::screenWidth/2 +1 ,Screen::screenHeight/2 +32);
    
      bg1->setScreenPosition(Screen::screenWidth/2 -31,Screen::screenHeight/2 -31);
      bg2->setScreenPosition(Screen::screenWidth/2,Screen::screenHeight/2 -31);
      bg3->setScreenPosition(Screen::screenWidth/2 -31,Screen::screenHeight/2);
      bg4->setScreenPosition(Screen::screenWidth/2,Screen::screenHeight/2);
      bg5->setScreenPosition(Screen::screenWidth/2 -31,Screen::screenHeight/2 +31);
      bg6->setScreenPosition(Screen::screenWidth/2,Screen::screenHeight/2 +31);
      g1->randGem().setScreenPosition(Screen::screenWidth/2 -30,Screen::screenHeight/2 -30);
      g2->randGem().setScreenPosition(Screen::screenWidth/2 +1 ,Screen::screenHeight/2 -30);
      while(g2->getGem() == g1->getGem())
        g2->randGem();
      g3->setGem(g2->getGem()).setScreenPosition(Screen::screenWidth/2 -30,Screen::screenHeight/2 +1);
      g4->randGem().setScreenPosition(Screen::screenWidth/2 +1 ,Screen::screenHeight/2 +1).startSpriteAnimation(getTime());
      while(g4->getGem() == g2->getGem())
        g4->randGem();
      g5->randGem().setScreenPosition(Screen::screenWidth/2 -30,Screen::screenHeight/2 +32);
      while(g5->getGem() == g4->getGem())
        g5->randGem();
      g6->setGem(g2->getGem()).setScreenPosition(Screen::screenWidth/2 +1 ,Screen::screenHeight/2 +32);
      frameSel->setScreenPosition(Screen::screenWidth/2 +1,Screen::screenHeight/2 +1);
      MorphLinear *mo = new MorphLinear();
      mo->setDuration(750).setFinalPosition(Screen::screenWidth/2 -15, Screen::screenHeight/2 +15);
      
      MorphLinear *mo2 = new MorphLinear();
      mo2->setDuration(200).setFinalPosition(Screen::screenWidth/2 -30,Screen::screenHeight/2 +1);
      
      MorphLinear *mo3 = new MorphLinear();
      mo3->setDuration(200).setFinalPosition(Screen::screenWidth/2 +1 ,Screen::screenHeight/2 +1);
      
      MorphLinear *mo4 = new MorphLinear();
      mo4->setDuration(1).setFinalPosition(-50,-50);
      
      MorphLinear *mo5 = new MorphLinear();
      mo5->setDuration(1).setFinalPosition(-50,-50);
      
      MorphLinear *mo6 = new MorphLinear();
      mo6->setDuration(1).setFinalPosition(-50,-50);
      
      g4->appendMorph(new MorphTimer(750))
         .appendMorph(mo2)
         .startAnimator(getTime());
      
      g3->appendMorph(new MorphTimer(750))
         .appendMorph(mo3)
         .appendMorph(mo4)
         .startAnimator(getTime());
      
      g2->appendMorph(new MorphTimer(950))
         .appendMorph(mo5)
         .startAnimator(getTime());
      
      g6->appendMorph(new MorphTimer(950))
         .appendMorph(mo6)
         .appendCallback(new CallbackAnimationPage4Loop2())
         .startAnimator(getTime());
      /*frameSel->appendMorph(new MorphTimer(1000))
               .appendCallback(new CallbackAnimationPage1Loop()).startAnimator(getTime());*/
      cursor->setScreenPosition(Screen::screenWidth/2 +15, Screen::screenHeight/2 +15)
             .appendMorph(mo)
             .appendMorph(new MorphTimer(1000))
             .appendCallback(new CallbackAnimationPage4())
             .startAnimator(getTime());
      timer->appendMorph(new MorphTimer(750))
            .appendCallback(new CallbackAnimationPage4Loop())
            .startAnimator(getTime());
    }
};

//! Callback para iniciar e ficar em loop a animação da página 5
class CallbackAnimationPage5 : public Callback {
  public:
    void aProcess(){
      g1->getAnimatorQueue().stopAnimation();
      g2->getAnimatorQueue().stopAnimation();
      g3->getAnimatorQueue().stopAnimation();
      g4->getAnimatorQueue().stopAnimation();
      g5->getAnimatorQueue().stopAnimation();
      g6->getAnimatorQueue().stopAnimation();
      cursor->getAnimatorQueue().stopAnimation();
      timer->getAnimatorQueue().stopAnimation();
      frameSel->getAnimatorQueue().stopAnimation();
      
      p1->setResourcePosition(0,0).setScreenPosition(-50,-50);
      p2->setResourcePosition(0,0).setScreenPosition(Screen::screenWidth/2 +1 ,Screen::screenHeight/2 -30);
      p3->setResourcePosition(0,0).setScreenPosition(-50,-50);
      p4->setResourcePosition(0,0).setScreenPosition(-50,-50);
      p5->setResourcePosition(0,0).setScreenPosition(Screen::screenWidth/2 -30,Screen::screenHeight/2 +32);
      p6->setResourcePosition(0,0).setScreenPosition(-50,-50);
    
      bg1->setScreenPosition(Screen::screenWidth/2 -31,Screen::screenHeight/2 -31);
      bg2->setScreenPosition(Screen::screenWidth/2,Screen::screenHeight/2 -31);
      bg3->setScreenPosition(Screen::screenWidth/2 -31,Screen::screenHeight/2);
      bg4->setScreenPosition(Screen::screenWidth/2,Screen::screenHeight/2);
      bg5->setScreenPosition(Screen::screenWidth/2 -31,Screen::screenHeight/2 +31);
      bg6->setScreenPosition(Screen::screenWidth/2,Screen::screenHeight/2 +31);
      g1->randGem().setScreenPosition(Screen::screenWidth/2 -30,Screen::screenHeight/2 -30);
      g2->randGem().setScreenPosition(-50,-50);
      g3->randGem().setScreenPosition(Screen::screenWidth/2 -30,Screen::screenHeight/2 +1);
      while(g3->getGem() == g1->getGem())
        g3->randGem();
      g4->randGem().setScreenPosition(Screen::screenWidth/2 +1 ,Screen::screenHeight/2 +1).resetSpriteAnimation();
      while(g4->getGem() == g2->getGem())
        g4->randGem();
      g5->randGem().setScreenPosition(-50,-50);
      g6->randGem().setScreenPosition(Screen::screenWidth/2 +1 ,Screen::screenHeight/2 +32);
      frameSel->setScreenPosition(-50,-50);
      cursor->setScreenPosition(-50,-50);
      
    }
};

void showPage(){
  std::stringstream SS;
  std::string S;
  Callback *x = NULL;
  switch(page){
    default:
    case 1:
      description->setString("Click over one gem to select it.");
      x = new CallbackAnimationPage1();
      x->process();
      break;
    case 2:
      description->setString("Click on gem next to selected gem to swap then.\nDiagonal isn't possible.");
      x = new CallbackAnimationPage2();
      x->process();
      break;
    case 3:
      description->setString("Swap gems to make 3-in-row or 3-in-column identical gems\nand destroy them.\nNote: 3 or more. Maximum possible is 7 gems simultaneous.");
      x = new CallbackAnimationPage3();
      x->process();
      break;
    case 4:
      description->setString("In Level mode, change the background color destroying a gem \nabove it. Change all colors to transparency to win the level.\nColor sequence:  Red -> Blue -> Green -> transparency");
      x = new CallbackAnimationPage4();
      x->process();
      break;
    case 5:
      description->setString("Blocks are fixed. You can't move them and can't move the gems \nthrough them.");
      x = new CallbackAnimationPage5();
      x->process();
      break;
    case 6:
      description->setString("Enjoy");
      break;
  }
  if(page != 6)
    screen->setVisibility(s,false);
  else
    screen->setVisibility(s,true);
  if(x != NULL)
    deleteCallback(x);
  
  S="";
  SS.str(S);
  SS << "Page " << page << " of " << totalPages;
  lblPage->setString(SS.str().c_str());
  if(page == 1){
    screen->setVisibility(btnBack,false);
  }else{
    screen->setVisibility(btnBack,true);
  }
  if(page == totalPages){
    screen->setVisibility(btnNext,false);
  }else{
    screen->setVisibility(btnNext,true);
  }
}

void show(){
  if(screen != NULL){
    page = 1;
    showPage();
    screen->show();
    return;
  }
  screen = new ScreenWindow();
  screen->setSize(0,400);
  screen->setPosition((Screen::screenWidth-screen->getWidth())/2,(Screen::screenHeight-screen->getHeight())/2);
  
  timer = new ScreenObject(TextureCache::sprites);
  screen->inject(timer,1);
  
  btnExit = new ScreenButtonDefault();
  btnExit->setLabel("Close").setOnClick(new CallbackCloseHowToPlay()).setScreenPosition((screen->getWidth()-btnExit->getScreenWidth())/2,screen->getHeight()-27);
  screen->inject(btnExit,1);
  
  lblPage = new ScreenText(TextureCache::font1);
  lblPage->setScreenAlign(ScreenText::center).setScreenPosition(screen->getWidth()/2,screen->getHeight()-pagination_offset_y).setColor(255,255,255,255);
  screen->inject(lblPage,1);
  
  description = new ScreenText(TextureCache::font1);
  description->setScreenPosition(40,80).setColor(255,255,255,255);
  screen->inject(description,1);
  
  btnBack = new ScreenButtonSimple();
  btnBack->setIconResourceSize(16,16).setIconSize(16,16)
          .setIconResourceSizeHover(16,16).setIconSizeHover(16,16)
          .setIconResourceOffset(ScreenButtonSprite::getOffsetX(ScreenButtonSprite::button_left_white),ScreenButtonSprite::getOffsetY(ScreenButtonSprite::button_left_white))
          .setIconResourceOffsetHover(ScreenButtonSprite::getOffsetX(ScreenButtonSprite::button_left_white),ScreenButtonSprite::getOffsetY(ScreenButtonSprite::button_left_white))
          .setIconOffset(4,4).setIconOffsetHover(4,4)
          .setButtonColor(ScreenButtonSimple::blue).setButtonColorHover(ScreenButtonSimple::blue_light)
          .setButtonSize(24,24).setButtonSizeHover(24,24)
          .setOnClick(new CallbackBackButton())
          .setScreenPosition(screen->getWidth()/2-(pagination_button_offset_x+24),screen->getHeight()-pagination_offset_y);
  screen->inject(btnBack,1);
  
  s = new ScreenButtonSimple();
  s->setButtonColor(255).setButtonColorHover(255)
    .setButtonSize(16,26).setButtonSizeHover(16,26)
    .setOnClick(new sc())
    .setScreenPosition(screen->getWidth()/2-8,30);
  screen->inject(s,1);
  
  btnNext = new ScreenButtonSimple();
  btnNext->setIconResourceSize(16,16).setIconSize(16,16)
          .setIconResourceSizeHover(16,16).setIconSizeHover(16,16)
          .setIconResourceOffset(ScreenButtonSprite::getOffsetX(ScreenButtonSprite::button_right_white),ScreenButtonSprite::getOffsetY(ScreenButtonSprite::button_right_white))
          .setIconResourceOffsetHover(ScreenButtonSprite::getOffsetX(ScreenButtonSprite::button_right_white),ScreenButtonSprite::getOffsetY(ScreenButtonSprite::button_right_white))
          .setIconOffset(4,4).setIconOffsetHover(4,4)
          .setButtonColor(ScreenButtonSimple::blue).setButtonColorHover(ScreenButtonSimple::blue_light)
          .setButtonSize(24,24).setButtonSizeHover(24,24)
          .setOnClick(new CallbackNextButton())
          .setScreenPosition(screen->getWidth()/2+pagination_button_offset_x,screen->getHeight()-pagination_offset_y);
  screen->inject(btnNext,1);
  
  bg1 = new ScreenObject(TextureCache::stageBackground);
  bg1->setResourcePosition(0,0).setResourceSize(32,32).setScreenSize(32,32).setDisplay(false);
  bg2 = new ScreenObject(*bg1);
  bg3 = new ScreenObject(*bg1);
  bg4 = new ScreenObject(*bg1);
  bg5 = new ScreenObject(*bg1);
  bg6 = new ScreenObject(*bg1);
  
  p1 = new ScreenObject(TextureCache::rock);
  p1->setResourceSize(84,84).setScreenSize(30,30).setDisplay(false);
  p2 = new ScreenObject(*p1);
  p3 = new ScreenObject(*p1);
  p4 = new ScreenObject(*p1);
  p5 = new ScreenObject(*p1);
  p6 = new ScreenObject(*p1);
  
  g1 = new Gem();
  g2 = new Gem();
  g3 = new Gem();
  g4 = new Gem();
  g5 = new Gem();
  g6 = new Gem();
  
  cursor = new ScreenObject(TextureCache::sprites);
  cursor->setResourcePosition(564,766).setResourceSize(30,45).setScreenSize(30/2,45/2).setDisplay(false);
  
  frameSel = new ScreenObject(Screen::frameSelector);
  frameSel->setDisplay(false);
  
  screen->inject(bg1,1);
  screen->inject(bg2,1);
  screen->inject(bg3,1);
  screen->inject(bg4,1);
  screen->inject(bg5,1);
  screen->inject(bg6,1);
  
  screen->inject(p1,1);
  screen->inject(p2,1);
  screen->inject(p3,1);
  screen->inject(p4,1);
  screen->inject(p5,1);
  screen->inject(p6,1);
  
  screen->inject(g1,2);
  screen->inject(g2,2);
  screen->inject(g3,2);
  screen->inject(g4,2);
  screen->inject(g5,2);
  screen->inject(g6,2);
  screen->inject(frameSel,3);
  screen->inject(cursor,3);
  
  AnimatorObjectList.addObject(g1);
  AnimatorObjectList.addObject(g2);
  AnimatorObjectList.addObject(g3);
  AnimatorObjectList.addObject(g4);
  AnimatorObjectList.addObject(g5);
  AnimatorObjectList.addObject(g6);
  AnimatorObjectList.addObject(cursor);
  AnimatorObjectList.addObject(frameSel);
  AnimatorObjectList.addObject(timer);
  
  page = 1;
  showPage();
  screen->show();
}

void close(){
  if(screen == NULL)
    return;
  AnimatorObjectList.remObject(g1);
  AnimatorObjectList.remObject(g2);
  AnimatorObjectList.remObject(g3);
  AnimatorObjectList.remObject(g4);
  AnimatorObjectList.remObject(g5);
  AnimatorObjectList.remObject(g6);
  AnimatorObjectList.remObject(cursor);
  AnimatorObjectList.remObject(frameSel);
  AnimatorObjectList.remObject(timer);
  
  delete screen;
  screen = NULL;
}

}}}