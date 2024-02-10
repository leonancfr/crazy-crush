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
#include "GameTimeAttackRank.hpp"
#include "ScreenWindow.hpp"
#include "Screen.hpp"
#include "Callback.hpp"
#include "ScreenButtonSimple.hpp"
#include "ScreenText.hpp"
#include "TextureCache.hpp"
#include "GameSave.hpp"
#include "AudioManager.hpp"
#include <sstream>
#include <string>

namespace CrazyCrush {
namespace Game {
namespace TimeAttack {
namespace Rank {

const unsigned width_all = 300;

const unsigned font_size = 17;
const int font_offset_y = 50;
const int font_offset_x = 50;
const unsigned height_all = font_offset_y + 10*font_size+32+5;

ScreenWindow *screen = NULL;
ScreenButtonSimple *btnClose;
ScreenText *lblTop,*lblP1,*lblP2,*lblP3,*lblP4,*lblP5,*lblP6,*lblP7,*lblP8,*lblP9,*lblP10;
ScreenText *lblV1,*lblV2,*lblV3,*lblV4,*lblV5,*lblV6,*lblV7,*lblV8,*lblV9,*lblV10;

//! Callback para fechar o menu de Rank do modo TimeAttack
class CallbackCloseRankMenu : public Callback {
  public:
    void aProcess() {
      CrazyCrush::AudioManager::play("sfx_wing",false,"sfx_wing.ogg");
      CrazyCrush::Game::TimeAttack::Rank::close();
    }
};

void show(){
  if(screen != NULL){
    screen->show();
    return;
  }
  screen = new ScreenWindow();
  screen->setType(ScreenWindow::type_2);
  screen->setSize(width_all,height_all);
  screen->setPosition((Screen::screenWidth-width_all)/2,(Screen::screenHeight-height_all)/2);
  
  btnClose = new ScreenButtonSimple();
  btnClose->getLabelObject().setScreenAlign(ScreenText::center).setScreenVAlign(ScreenText::middle);
  btnClose->setLabel("Close")
           .setLabelOffset(0,ScreenButtonSimple::defaultScreenHeight(0)/2)
           .setLabelOffsetHover(0,ScreenButtonSimple::defaultScreenHeight(0)/2)
           .setButtonColor(ScreenButtonSimple::green)
           .setButtonColorHover(ScreenButtonSimple::green_light)
           .setButtonSize(ScreenButtonSimple::defaultScreenWidth(0),ScreenButtonSimple::defaultScreenHeight(0))
           .setButtonSizeHover(ScreenButtonSimple::defaultScreenWidth(0),ScreenButtonSimple::defaultScreenHeight(0))
           .setScreenPosition((width_all-ScreenButtonSimple::defaultScreenWidth(0))/2,height_all-ScreenButtonSimple::defaultScreenHeight(0)-5);
  btnClose->setOnClick(new CallbackCloseRankMenu());
  screen->inject(btnClose,1);
  
  lblTop = new ScreenText(TextureCache::fontSFComic);
  lblTop->setString("TimeAttack Rank").setColor(255,238,142,13).setScreenPosition(width_all/2,0).setScreenAlign(ScreenText::center);
  screen->inject(lblTop,1);
  
  lblP1 = new ScreenText(TextureCache::font1);
  lblP1->setString("1:").setColor(255,0,0,0).setScreenPosition(font_offset_x,font_offset_y+0*font_size);
  lblP2 = new ScreenText(TextureCache::font1);
  lblP2->setString("2:").setColor(255,0,0,0).setScreenPosition(font_offset_x,font_offset_y+1*font_size);
  lblP3 = new ScreenText(TextureCache::font1);
  lblP3->setString("3:").setColor(255,0,0,0).setScreenPosition(font_offset_x,font_offset_y+2*font_size);
  lblP4 = new ScreenText(TextureCache::font1);
  lblP4->setString("4:").setColor(255,0,0,0).setScreenPosition(font_offset_x,font_offset_y+3*font_size);
  lblP5 = new ScreenText(TextureCache::font1);
  lblP5->setString("5:").setColor(255,0,0,0).setScreenPosition(font_offset_x,font_offset_y+4*font_size);
  lblP6 = new ScreenText(TextureCache::font1);
  lblP6->setString("6:").setColor(255,0,0,0).setScreenPosition(font_offset_x,font_offset_y+5*font_size);
  lblP7 = new ScreenText(TextureCache::font1);
  lblP7->setString("7:").setColor(255,0,0,0).setScreenPosition(font_offset_x,font_offset_y+6*font_size);
  lblP8 = new ScreenText(TextureCache::font1);
  lblP8->setString("8:").setColor(255,0,0,0).setScreenPosition(font_offset_x,font_offset_y+7*font_size);
  lblP9 = new ScreenText(TextureCache::font1);
  lblP9->setString("9:").setColor(255,0,0,0).setScreenPosition(font_offset_x,font_offset_y+8*font_size);
  lblP10 = new ScreenText(TextureCache::font1);
  lblP10->setString("10:").setColor(255,0,0,0).setScreenPosition(font_offset_x,font_offset_y+9*font_size);
  
  screen->inject(lblP1,1);
  screen->inject(lblP2,1);
  screen->inject(lblP3,1);
  screen->inject(lblP4,1);
  screen->inject(lblP5,1);
  screen->inject(lblP6,1);
  screen->inject(lblP7,1);
  screen->inject(lblP8,1);
  screen->inject(lblP9,1);
  screen->inject(lblP10,1);
  
  lblV1 = new ScreenText(TextureCache::font1);
  lblV1->setString("no record").setColor(255,0,0,0).setScreenPosition(width_all-font_offset_x,font_offset_y+0*font_size).setScreenAlign(ScreenText::right);
  lblV2 = new ScreenText(TextureCache::font1);
  lblV2->setString("no record").setColor(255,0,0,0).setScreenPosition(width_all-font_offset_x,font_offset_y+1*font_size).setScreenAlign(ScreenText::right);
  lblV3 = new ScreenText(TextureCache::font1);
  lblV3->setString("no record").setColor(255,0,0,0).setScreenPosition(width_all-font_offset_x,font_offset_y+2*font_size).setScreenAlign(ScreenText::right);
  lblV4 = new ScreenText(TextureCache::font1);
  lblV4->setString("no record").setColor(255,0,0,0).setScreenPosition(width_all-font_offset_x,font_offset_y+3*font_size).setScreenAlign(ScreenText::right);
  lblV5 = new ScreenText(TextureCache::font1);
  lblV5->setString("no record").setColor(255,0,0,0).setScreenPosition(width_all-font_offset_x,font_offset_y+4*font_size).setScreenAlign(ScreenText::right);
  lblV6 = new ScreenText(TextureCache::font1);
  lblV6->setString("no record").setColor(255,0,0,0).setScreenPosition(width_all-font_offset_x,font_offset_y+5*font_size).setScreenAlign(ScreenText::right);
  lblV7 = new ScreenText(TextureCache::font1);
  lblV7->setString("no record").setColor(255,0,0,0).setScreenPosition(width_all-font_offset_x,font_offset_y+6*font_size).setScreenAlign(ScreenText::right);
  lblV8 = new ScreenText(TextureCache::font1);
  lblV8->setString("no record").setColor(255,0,0,0).setScreenPosition(width_all-font_offset_x,font_offset_y+7*font_size).setScreenAlign(ScreenText::right);
  lblV9 = new ScreenText(TextureCache::font1);
  lblV9->setString("no record").setColor(255,0,0,0).setScreenPosition(width_all-font_offset_x,font_offset_y+8*font_size).setScreenAlign(ScreenText::right);
  lblV10 = new ScreenText(TextureCache::font1);
  lblV10->setString("no record").setColor(255,0,0,0).setScreenPosition(width_all-font_offset_x,font_offset_y+9*font_size).setScreenAlign(ScreenText::right);
  
  screen->inject(lblV1,1);
  screen->inject(lblV2,1);
  screen->inject(lblV3,1);
  screen->inject(lblV4,1);
  screen->inject(lblV5,1);
  screen->inject(lblV6,1);
  screen->inject(lblV7,1);
  screen->inject(lblV8,1);
  screen->inject(lblV9,1);
  screen->inject(lblV10,1);
  
  std::stringstream SS;
  std::string S;
  unsigned v=0;
  for(unsigned i=1;i<=Game::Save::maxRankTimeAttack;i++){
    v = Game::Save::getTimeAttackAtPosition(i);
    if(v == 0)
      continue;
    S="";
    SS.str(S);
    SS<<v;
    switch(i){
      default:
      case 1:
        lblV1->setString(SS.str().c_str());
        break;
      case 2:
        lblV2->setString(SS.str().c_str());
        break;
      case 3:
        lblV3->setString(SS.str().c_str());
        break;
      case 4:
        lblV4->setString(SS.str().c_str());
        break;
      case 5:
        lblV5->setString(SS.str().c_str());
        break;
      case 6:
        lblV6->setString(SS.str().c_str());
        break;
      case 7:
        lblV7->setString(SS.str().c_str());
        break;
      case 8:
        lblV8->setString(SS.str().c_str());
        break;
      case 9:
        lblV9->setString(SS.str().c_str());
        break;
      case 10:
        lblV10->setString(SS.str().c_str());
        break;
    }
  }
  
  screen->show();
}

void close(){
  if(screen == NULL)
    return;
  screen->close();
  delete screen;
  screen = NULL;
}

}}}}