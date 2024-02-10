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
#include "ScreenObject.hpp"
#include "CoreOpenGLVersion.hpp"
#include "ZOrder.hpp"

/*-------------------------------------------------------------+
 |  _____                            _              _       _  |
 | |_   _|                          | |            | |     | | |
 |   | |  _ __ ___  _ __   ___  _ __| |_ __ _ _ __ | |_ ___| | |
 |   | | | '_ ` _ \| '_ \ / _ \| '__| __/ _` | '_ \| __/ _ \ | |
 |  _| |_| | | | | | |_) | (_) | |  | || (_| | | | | ||  __/_| |
 | |_____|_| |_| |_| .__/ \___/|_|   \__\__,_|_| |_|\__\___(_) |
 |                 | |                                         |
 |                 |_|                                         |
 +-------------------------------------------------------------+
 | Observe atentamente a ordem que os mutex são bloqueados.    |
 | Para evitar que duas threads se prendam.                    |
 +-------------------------------------------------------------*/

ScreenObject::ScreenObject(SharedPointer<irr::video::ITexture>* nTexture){
  spriteAnimator = NULL;
  if(nTexture != NULL)
    mTexture = *nTexture;
  oScreenWidth = screenWidth = 0;
  oScreenHeight = screenHeight = 0;
  oScreenPositionX = screenPositionX = 0;
  oScreenPositionY = screenPositionY = 0;
  oResourceWidth = resourceWidth = 0;
  oResourceHeight = resourceHeight = 0;
  if(CrazyCrush::OpenGL::isAbove_1_7_0){
    oResourcePositionX = resourcePositionX = 0;
    oResourcePositionY = resourcePositionY = 0;
  }else{
    oResourcePositionX = resourcePositionX = 1;
    oResourcePositionY = resourcePositionY = 1;
  }
  spriteAnimatorTime = 0;
  mDisplay = false;
  animatorQueue = new AnimatorQueue();
  animatorQueue->setObject(this);
  
  // Initialize all mutex
  mutexTexture = PTHREAD_MUTEX_INITIALIZER;
  mutexScreenPosition = PTHREAD_MUTEX_INITIALIZER;
  mutexScreenSize = PTHREAD_MUTEX_INITIALIZER;
  mutexResourcePosition = PTHREAD_MUTEX_INITIALIZER;
  mutexResourceSize = PTHREAD_MUTEX_INITIALIZER;
  mutexDisplay = PTHREAD_MUTEX_INITIALIZER;
  mutexColor = PTHREAD_MUTEX_INITIALIZER;
  mutexOutScreenPosition = PTHREAD_MUTEX_INITIALIZER;
  mutexOutScreenSize = PTHREAD_MUTEX_INITIALIZER;
  mutexOutResourcePosition = PTHREAD_MUTEX_INITIALIZER;
  mutexOutResourceSize = PTHREAD_MUTEX_INITIALIZER;
  mutexOutColor = PTHREAD_MUTEX_INITIALIZER;
}

ScreenObject::ScreenObject(SharedPointer<irr::video::ITexture>& nTexture){
  spriteAnimator = NULL;
  mTexture = nTexture;
  oScreenWidth = screenWidth = 0;
  oScreenHeight = screenHeight = 0;
  oScreenPositionX = screenPositionX = 0;
  oScreenPositionY = screenPositionY = 0;
  oResourceWidth = resourceWidth = 0;
  oResourceHeight = resourceHeight = 0;
  if(CrazyCrush::OpenGL::isAbove_1_7_0){
    oResourcePositionX = resourcePositionX = 0;
    oResourcePositionY = resourcePositionY = 0;
  }else{
    oResourcePositionX = resourcePositionX = 1;
    oResourcePositionY = resourcePositionY = 1;
  }
  spriteAnimatorTime = 0;
  mDisplay = false;
  animatorQueue = new AnimatorQueue();
  animatorQueue->setObject(this);
  
  // Initialize all mutex
  mutexTexture = PTHREAD_MUTEX_INITIALIZER;
  mutexScreenPosition = PTHREAD_MUTEX_INITIALIZER;
  mutexScreenSize = PTHREAD_MUTEX_INITIALIZER;
  mutexResourcePosition = PTHREAD_MUTEX_INITIALIZER;
  mutexResourceSize = PTHREAD_MUTEX_INITIALIZER;
  mutexDisplay = PTHREAD_MUTEX_INITIALIZER;
  mutexColor = PTHREAD_MUTEX_INITIALIZER;
  mutexOutScreenPosition = PTHREAD_MUTEX_INITIALIZER;
  mutexOutScreenSize = PTHREAD_MUTEX_INITIALIZER;
  mutexOutResourcePosition = PTHREAD_MUTEX_INITIALIZER;
  mutexOutResourceSize = PTHREAD_MUTEX_INITIALIZER;
  mutexOutColor = PTHREAD_MUTEX_INITIALIZER;
}

ScreenObject::ScreenObject(ScreenObject& other){
  // Bloqueia geral
  pthread_mutex_lock(&other.mutexTexture);
  pthread_mutex_lock(&other.mutexScreenPosition);
  pthread_mutex_lock(&other.mutexScreenSize);
  pthread_mutex_lock(&other.mutexResourcePosition);
  pthread_mutex_lock(&other.mutexResourceSize);
  pthread_mutex_lock(&other.mutexDisplay);
  pthread_mutex_lock(&other.mutexColor);
  pthread_mutex_lock(&other.mutexOutScreenPosition);
  pthread_mutex_lock(&other.mutexOutScreenSize);
  pthread_mutex_lock(&other.mutexOutResourcePosition);
  pthread_mutex_lock(&other.mutexOutResourceSize);
  pthread_mutex_lock(&other.mutexOutColor);

  spriteAnimator = other.spriteAnimator;
  animatorQueue = new AnimatorQueue();
  *animatorQueue = *(other.animatorQueue);
  animatorQueue->setObject(this);
  mTexture = other.mTexture;
  oMColor = mColor = other.mColor;
  oScreenWidth = screenWidth = other.screenWidth;
  oScreenHeight = screenHeight = other.screenHeight;
  oScreenPositionX = screenPositionX = other.screenPositionX;
  oScreenPositionY = screenPositionY = other.screenPositionY;
  oResourceWidth = resourceWidth = other.resourceWidth;
  oResourceHeight = resourceHeight = other.resourceHeight;
  oResourcePositionX = resourcePositionX = other.resourcePositionX;
  oResourcePositionY = resourcePositionY = other.resourcePositionY;
  spriteAnimatorTime = other.spriteAnimatorTime;
  mDisplay = other.mDisplay;
  
  pthread_mutex_unlock(&other.mutexTexture);
  pthread_mutex_unlock(&other.mutexScreenPosition);
  pthread_mutex_unlock(&other.mutexScreenSize);
  pthread_mutex_unlock(&other.mutexResourcePosition);
  pthread_mutex_unlock(&other.mutexResourceSize);
  pthread_mutex_unlock(&other.mutexDisplay);
  pthread_mutex_unlock(&other.mutexColor);
  pthread_mutex_unlock(&other.mutexOutScreenPosition);
  pthread_mutex_unlock(&other.mutexOutScreenSize);
  pthread_mutex_unlock(&other.mutexOutResourcePosition);
  pthread_mutex_unlock(&other.mutexOutResourceSize);
  pthread_mutex_unlock(&other.mutexOutColor);
  // Geral tá liberado
  
  // Initialize all mutex
  mutexTexture = PTHREAD_MUTEX_INITIALIZER;
  mutexScreenPosition = PTHREAD_MUTEX_INITIALIZER;
  mutexScreenSize = PTHREAD_MUTEX_INITIALIZER;
  mutexResourcePosition = PTHREAD_MUTEX_INITIALIZER;
  mutexResourceSize = PTHREAD_MUTEX_INITIALIZER;
  mutexDisplay = PTHREAD_MUTEX_INITIALIZER;
  mutexColor = PTHREAD_MUTEX_INITIALIZER;
  mutexOutScreenPosition = PTHREAD_MUTEX_INITIALIZER;
  mutexOutScreenSize = PTHREAD_MUTEX_INITIALIZER;
  mutexOutResourcePosition = PTHREAD_MUTEX_INITIALIZER;
  mutexOutResourceSize = PTHREAD_MUTEX_INITIALIZER;
  mutexOutColor = PTHREAD_MUTEX_INITIALIZER;
}

ScreenObject& ScreenObject::operator=(ScreenObject& other){
  spriteAnimator = other.spriteAnimator;
  *animatorQueue = *(other.animatorQueue);
  animatorQueue->setObject(this);
  mTexture = other.mTexture;
  mColor = other.mColor;
  screenWidth = other.screenWidth;
  screenHeight = other.screenHeight;
  screenPositionX = other.screenPositionX;
  screenPositionY = other.screenPositionY;
  resourceWidth = other.resourceWidth;
  resourceHeight = other.resourceHeight;
  resourcePositionX = other.resourcePositionX;
  resourcePositionY = other.resourcePositionY;
  mDisplay = other.mDisplay;
  return *this;
}

ScreenObject::~ScreenObject(){
  CrazyCrush::z_order.remObject(this);
}

ScreenObject& ScreenObject::setTexture(SharedPointer<irr::video::ITexture>& nTexture){
  pthread_mutex_lock(&mutexTexture);
  mTexture = nTexture;
  pthread_mutex_unlock(&mutexTexture);
  return *this;
}

ScreenObject& ScreenObject::setTexture(SharedPointer<irr::video::ITexture>* nTexture){
  pthread_mutex_lock(&mutexTexture);
  if(nTexture == NULL){
    mTexture.set(NULL);
  }else{
    mTexture = *nTexture;
  }
  pthread_mutex_unlock(&mutexTexture);
  return *this;
}

ScreenObject& ScreenObject::setSpriteAnimator(SpriteAnimator* nSAnimator){
  spriteAnimator = nSAnimator;
  return *this;
}

ScreenObject& ScreenObject::setAnimatorQueue(AnimatorQueue& nAQueue){
  *animatorQueue = nAQueue;
  animatorQueue->setObject(this);
  return *this;
}

ScreenObject& ScreenObject::setScreenSize(unsigned X,unsigned Y){
  pthread_mutex_lock(&mutexScreenSize);
  pthread_mutex_lock(&mutexOutScreenSize);
  if(CrazyCrush::OpenGL::isAbove_1_7_0){
    screenWidth = X;
    screenHeight = Y;
    oScreenWidth = X;
    oScreenHeight = Y;
  }else{
    screenWidth = X;
    screenHeight = Y;
    oScreenWidth = X;
    oScreenHeight = Y;
  }
  pthread_mutex_unlock(&mutexScreenSize);
  pthread_mutex_unlock(&mutexOutScreenSize);
  return *this;
}

ScreenObject& ScreenObject::setScreenPosition(int X,int Y){
  pthread_mutex_lock(&mutexScreenPosition);
  pthread_mutex_lock(&mutexOutScreenPosition);
  screenPositionX = X;
  screenPositionY = Y;
  oScreenPositionX = X;
  oScreenPositionY = Y;
  pthread_mutex_unlock(&mutexScreenPosition);
  pthread_mutex_unlock(&mutexOutScreenPosition);
  return *this;
}

ScreenObject& ScreenObject::setResourceSize(unsigned X,unsigned Y){
  pthread_mutex_lock(&mutexResourceSize);
  pthread_mutex_lock(&mutexOutResourceSize);
  if(CrazyCrush::OpenGL::isAbove_1_7_0){
    resourceWidth = X;
    resourceHeight = Y;
    oResourceWidth = X;
    oResourceHeight = Y;
  }else{
    resourceWidth = X-1;
    resourceHeight = Y-1;
    oResourceWidth = X-1;
    oResourceHeight = Y-1;
  }
  pthread_mutex_unlock(&mutexResourceSize);
  pthread_mutex_unlock(&mutexOutResourceSize);
  return *this;
}

ScreenObject& ScreenObject::setResourcePosition(int X,int Y){
  pthread_mutex_lock(&mutexResourcePosition);
  pthread_mutex_lock(&mutexOutResourcePosition);
  if(CrazyCrush::OpenGL::isAbove_1_7_0){
    resourcePositionX = X;
    resourcePositionY = Y;
    oResourcePositionX = X;
    oResourcePositionY = Y;
  }else{
    resourcePositionX = X+1;
    resourcePositionY = Y+1;
    oResourcePositionX = X+1;
    oResourcePositionY = Y+1;
  }
  pthread_mutex_unlock(&mutexResourcePosition);
  pthread_mutex_unlock(&mutexOutResourcePosition);
  return *this;
}

ScreenObject& ScreenObject::setImageColor(irr::video::SColor* nColor){
  pthread_mutex_lock(&mutexColor);
  pthread_mutex_lock(&mutexOutColor);
  mColor.setColor(nColor);
  oMColor.setColor(nColor);
  pthread_mutex_unlock(&mutexColor);
  pthread_mutex_unlock(&mutexOutColor);
  return *this;
}

ScreenObject& ScreenObject::setImageAlpha(irr::u8 alpha){
  pthread_mutex_lock(&mutexColor);
  pthread_mutex_lock(&mutexOutColor);
  mColor.setAlpha(alpha);
  oMColor.setAlpha(alpha);
  pthread_mutex_unlock(&mutexColor);
  pthread_mutex_unlock(&mutexOutColor);
  return *this;
}

ScreenObject& ScreenObject::setDisplay(bool nDisplay){
  pthread_mutex_lock(&mutexDisplay);
  mDisplay = nDisplay;
  pthread_mutex_unlock(&mutexDisplay);
  return *this;
}

ScreenObject& ScreenObject::startSpriteAnimation(irr::u32 time){
  spriteAnimatorTime = time;
  return *this;
}

ScreenObject& ScreenObject::stopSpriteAnimation(){
  spriteAnimatorTime = 0;
  return *this;
}

ScreenObject& ScreenObject::resetSpriteAnimation(){
  spriteAnimatorTime = 0;
  pthread_mutex_lock(&mutexResourcePosition);
  pthread_mutex_lock(&mutexResourceSize);
  pthread_mutex_lock(&mutexOutResourcePosition);
  pthread_mutex_lock(&mutexOutResourceSize);
  
  oResourcePositionX = resourcePositionX;
  oResourcePositionY = resourcePositionY;
  oResourceWidth = resourceWidth;
  oResourceHeight = resourceHeight;
  
  pthread_mutex_unlock(&mutexResourcePosition);
  pthread_mutex_unlock(&mutexResourceSize);
  pthread_mutex_unlock(&mutexOutResourcePosition);
  pthread_mutex_unlock(&mutexOutResourceSize);
  return *this;
}

irr::video::ITexture* ScreenObject::getTexture(){
  irr::video::ITexture* t;
  pthread_mutex_lock(&mutexTexture);
  t = mTexture.get();
  pthread_mutex_unlock(&mutexTexture);
  return t;
}

SpriteAnimator* ScreenObject::getSpriteAnimator(){
  return spriteAnimator;
}
AnimatorQueue& ScreenObject::getAnimatorQueue(){
  return *animatorQueue;
}

irr::core::rect<irr::s32> ScreenObject::getScreenRect(){
  irr::core::rect<irr::s32> t;
  pthread_mutex_lock(&mutexOutScreenPosition);
  pthread_mutex_lock(&mutexOutScreenSize);
  t = irr::core::rect<irr::s32>(
    oScreenPositionX,oScreenPositionY,
    oScreenPositionX+oScreenWidth,oScreenPositionY+oScreenHeight
  );
  pthread_mutex_unlock(&mutexOutScreenPosition);
  pthread_mutex_unlock(&mutexOutScreenSize);
  return t;
}
irr::core::rect<irr::s32> ScreenObject::getResourceRect(){
  irr::core::rect<irr::s32> t;
  pthread_mutex_lock(&mutexOutResourcePosition);
  pthread_mutex_lock(&mutexOutResourceSize);
  t = irr::core::rect<irr::s32>(
    oResourcePositionX,oResourcePositionY,
    oResourcePositionX+oResourceWidth,oResourcePositionY+oResourceHeight
  );
  pthread_mutex_unlock(&mutexOutResourcePosition);
  pthread_mutex_unlock(&mutexOutResourceSize);
  return t;
}

irr::video::SColor* ScreenObject::getImageColor(){
  irr::video::SColor* t;
  pthread_mutex_lock(&mutexOutColor);
  t = oMColor.getColor();
  pthread_mutex_unlock(&mutexOutColor);
  return t;
}

bool ScreenObject::getDisplay(){
  bool t;
  pthread_mutex_lock(&mutexDisplay);
  t = mDisplay;
  pthread_mutex_unlock(&mutexDisplay);
  return t;
}

unsigned ScreenObject::getScreenWidth(){
  unsigned t;
  pthread_mutex_lock(&mutexScreenSize);
  t = screenWidth;
  pthread_mutex_unlock(&mutexScreenSize);
  return t;
}

unsigned ScreenObject::getScreenHeight(){
  unsigned t;
  pthread_mutex_lock(&mutexScreenSize);
  t = screenHeight;
  pthread_mutex_unlock(&mutexScreenSize);
  return t;
}

int ScreenObject::getScreenPositionX(){
  int t;
  pthread_mutex_lock(&mutexScreenPosition);
  t = screenPositionX;
  pthread_mutex_unlock(&mutexScreenPosition);
  return t;
}

int ScreenObject::getScreenPositionY(){
  int t;
  pthread_mutex_lock(&mutexScreenPosition);
  t = screenPositionY;
  pthread_mutex_unlock(&mutexScreenPosition);
  return t;
}

irr::video::SColor* ScreenObject::getColor(){
  irr::video::SColor* t;
  pthread_mutex_lock(&mutexColor);
  t = mColor.getColor();
  pthread_mutex_unlock(&mutexColor);
  return t;
}

ScreenObject& ScreenObject::startAnimator(irr::u32 time){
  animatorQueue->startAnimation(time);
  return *this;
}

ScreenObject& ScreenObject::appendMorph(ObjectMorph* objMorph){
  objMorph->setObject(this);
  animatorQueue->appendMorph(objMorph);
  return *this;
}

ScreenObject& ScreenObject::appendCallback(Callback* call){
  animatorQueue->appendCallback(call);
  return *this;
}

void ScreenObject::processTime(irr::u32 time){
  if((spriteAnimator!=NULL)&&(spriteAnimatorTime != 0)){
    pthread_mutex_lock(&mutexResourcePosition);
    pthread_mutex_lock(&mutexResourceSize);
    pthread_mutex_lock(&mutexOutResourcePosition);
    pthread_mutex_lock(&mutexOutResourceSize);
    
    irr::core::rect<irr::s32> resp = spriteAnimator->getResourceRect(time-spriteAnimatorTime, resourcePositionX,resourcePositionY,resourcePositionX+resourceWidth,resourcePositionY+resourceHeight);
    oResourcePositionX = resp.UpperLeftCorner.X;
    oResourcePositionY = resp.UpperLeftCorner.Y;
    oResourceWidth = resp.getWidth();
    oResourceHeight = resp.getHeight();
    
    pthread_mutex_unlock(&mutexResourcePosition);
    pthread_mutex_unlock(&mutexResourceSize);
    pthread_mutex_unlock(&mutexOutResourcePosition);
    pthread_mutex_unlock(&mutexOutResourceSize);
  }
  if(animatorQueue->isRunning()){
    
    irr::core::rect<irr::s32> resp = animatorQueue->getScreenRect(time);
    pthread_mutex_lock(&mutexScreenPosition);
    pthread_mutex_lock(&mutexScreenSize);
    pthread_mutex_lock(&mutexOutScreenPosition);
    pthread_mutex_lock(&mutexOutScreenSize);
    
    oScreenPositionX = resp.UpperLeftCorner.X;
    oScreenPositionY = resp.UpperLeftCorner.Y;
    oScreenWidth = resp.getWidth();
    oScreenHeight = resp.getHeight();
    
    pthread_mutex_unlock(&mutexScreenPosition);
    pthread_mutex_unlock(&mutexScreenSize);
    pthread_mutex_unlock(&mutexOutScreenPosition);
    pthread_mutex_unlock(&mutexOutScreenSize);
  }
}

void ScreenObject::aSetDisplay(bool b){
  this->setDisplay(b);
}

void ScreenObject::aSetScreenSize(unsigned w,unsigned h){
  this->setScreenSize(w,h);
}

void ScreenObject::aSetScreenPosition(int x,int y){
  this->setScreenPosition(x,y);
}

void ScreenObject::aSetImageColor(irr::video::SColor* c){
  this->setImageColor(c);
}

unsigned char ScreenObject::getType(){
  return AnimatorObject::typeScreenObject;
}