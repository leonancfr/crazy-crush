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
#include "Gem.hpp"

#include "TextureCache.hpp"
#include "GameDefines.hpp"
#include "Random.hpp"
#include "ZOrder.hpp"
#include "Percentage.hpp"

using namespace CrazyCrush;

Gem::Gem():ScreenObject(NULL),gemType(rock),isEnabled(false),isFixed(false),hasTimeEffect(false),effect_icon(NULL){
  this->setScreenSize(TextureCache::gemWidth,TextureCache::gemHeight);
  this->setResourceSize(84,84);
  this->setResourcePosition(0,0);
  this->setDisplay(false);
  this->setSpriteAnimator(&TextureCache::DefaultAnimator);
}

Gem::~Gem(){
  if(effect_icon.get()!=NULL){
    delete effect_icon.get();
  }
}

Gem& Gem::setGem(char t){
  gemType.set(t);
  if((t != rock)&&(isFixed.get())){
    z_order.remObject(this,ZOrder<char>::index_gems+1);
    z_order.addObject(this,ZOrder<char>::index_gems);
    isFixed.set(false);
  }
  switch(t){
    case gem1:
      this->setTexture(TextureCache::gem1);
      break;
    case gem2:
      this->setTexture(TextureCache::gem2);
      break;
    case gem3:
      this->setTexture(TextureCache::gem3);
      break;
    case gem4:
      this->setTexture(TextureCache::gem4);
      break;
    case gem5:
      this->setTexture(TextureCache::gem5);
      break;
    case gem6:
      this->setTexture(TextureCache::gem6);
      break;
    case gem7:
    default:
      this->setTexture(TextureCache::gem0);
      break;
    case rock:
      this->setTexture(TextureCache::rock);
      if(!isFixed.get()){
        isFixed.set(true);
        z_order.addObject(this,ZOrder<char>::index_gems+1);
        z_order.remObject(this,ZOrder<char>::index_gems);
      }
      break;
  }
  return *this;
}

char Gem::getGem(){
  return gemType.get();
}

Gem& Gem::setEnabled(bool v){
  isEnabled.set(v);
  return *this;
}

bool Gem::getEnabled(){
  if(isFixed.get())
    return false;
  return isEnabled.get();
}

bool Gem::getFixed(){
  return isFixed.get();
}

Gem& Gem::randGem(){
  this->setGem((unsigned char)(((unsigned)Random::get())%Game::totalGemsEnabled));
  if(Percentage::get(CrazyCrush::Game::timeBonusGemProbability)){
    //std::cout << "Here one gem with time bonus" << std::endl;
  }
  return *this;
}

bool Gem::operator==(Gem& other){
  return other.getGem()==gemType.get();
}
bool Gem::operator!=(Gem& other){
  return other.getGem()!=gemType.get();
}

void Gem::aSetDisplay(bool d){
  ScreenObject::aSetDisplay(d);
}

void Gem::aSetScreenPosition(int x,int y){
  ScreenObject::aSetScreenPosition(x,y);
}

bool Gem::hasEffect(){
  return false;
}

void Gem::processEffect(){

}