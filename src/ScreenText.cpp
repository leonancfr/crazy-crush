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
#include "ScreenText.hpp"

ScreenText::ScreenText(SharedPointer<irr::gui::IGUIFont>* f){
  mutexFont = PTHREAD_MUTEX_INITIALIZER;
  mutexString = PTHREAD_MUTEX_INITIALIZER;
  mutexColor = PTHREAD_MUTEX_INITIALIZER;
  mutexScreenPosition = PTHREAD_MUTEX_INITIALIZER;
  mutexOutScreenPosition = PTHREAD_MUTEX_INITIALIZER;
  mutexDisplay = PTHREAD_MUTEX_INITIALIZER;
  
  if(f != NULL)
  font = *f;
  align = left;
  animatorQueue = new AnimatorQueue();
  animatorQueue->setObject(this);
}

ScreenText::ScreenText(SharedPointer<irr::gui::IGUIFont>& f){
  mutexFont = PTHREAD_MUTEX_INITIALIZER;
  mutexString = PTHREAD_MUTEX_INITIALIZER;
  mutexColor = PTHREAD_MUTEX_INITIALIZER;
  mutexScreenPosition = PTHREAD_MUTEX_INITIALIZER;
  mutexOutScreenPosition = PTHREAD_MUTEX_INITIALIZER;
  mutexDisplay = PTHREAD_MUTEX_INITIALIZER;
  
  font = f;
  align = left;
  animatorQueue = new AnimatorQueue();
  animatorQueue->setObject(this);
}

ScreenText::ScreenText(ScreenText& other){
  mutexFont = PTHREAD_MUTEX_INITIALIZER;
  mutexString = PTHREAD_MUTEX_INITIALIZER;
  mutexColor = PTHREAD_MUTEX_INITIALIZER;
  mutexScreenPosition = PTHREAD_MUTEX_INITIALIZER;
  mutexOutScreenPosition = PTHREAD_MUTEX_INITIALIZER;
  mutexDisplay = PTHREAD_MUTEX_INITIALIZER;
  
  pthread_mutex_lock(&other.mutexFont);
  pthread_mutex_lock(&other.mutexString);
  pthread_mutex_lock(&other.mutexColor);
  pthread_mutex_lock(&other.mutexScreenPosition);
  pthread_mutex_lock(&other.mutexOutScreenPosition);
  pthread_mutex_lock(&other.mutexDisplay);
  
  font = other.font;
  str = other.str;
  wstr = other.wstr;
  color = other.color;
  align = other.align;
  screenPositionX = other.screenPositionX;
  screenPositionY = other.screenPositionY;
  oScreenPositionX = other.oScreenPositionX;
  oScreenPositionY = other.oScreenPositionY;
  display = other.display;
  animatorQueue = new AnimatorQueue();
  animatorQueue->setObject(this);
  (*animatorQueue) = *(other.animatorQueue);
  
  pthread_mutex_unlock(&other.mutexFont);
  pthread_mutex_unlock(&other.mutexString);
  pthread_mutex_unlock(&other.mutexColor);
  pthread_mutex_unlock(&other.mutexScreenPosition);
  pthread_mutex_unlock(&other.mutexOutScreenPosition);
  pthread_mutex_unlock(&other.mutexDisplay);
}

ScreenText::~ScreenText(){}

ScreenText& ScreenText::setFont(SharedPointer<irr::gui::IGUIFont>* f){
  pthread_mutex_lock(&mutexFont);
  if(f == NULL)
    font.set(NULL);
  else
    font = *f;
  pthread_mutex_unlock(&mutexFont);
  return *this;
}

ScreenText& ScreenText::setFont(SharedPointer<irr::gui::IGUIFont>& f){
  pthread_mutex_lock(&mutexFont);
  font = f;
  pthread_mutex_unlock(&mutexFont);
  return *this;
}

ScreenText& ScreenText::setString(const char* s){
  pthread_mutex_lock(&mutexString);
  str = s;
  wstr = std::wstring(str.begin(),str.end());
  pthread_mutex_unlock(&mutexString);
  return *this;
}

ScreenText& ScreenText::setString(std::string& s){
  pthread_mutex_lock(&mutexString);
  str = s;
  wstr = std::wstring(str.begin(),str.end());
  pthread_mutex_unlock(&mutexString);
  return *this;
}

ScreenText& ScreenText::setColor(irr::video::SColor& c){
  pthread_mutex_lock(&mutexColor);
  color = c;
  pthread_mutex_unlock(&mutexColor);
  return *this;
}

ScreenText& ScreenText::setColor(unsigned char a,unsigned char r,unsigned char g,unsigned char b){
  pthread_mutex_lock(&mutexColor);
  color = irr::video::SColor(a,r,g,b);
  pthread_mutex_unlock(&mutexColor);
  return *this;
}

ScreenText& ScreenText::setAlpha(unsigned char a){
  pthread_mutex_lock(&mutexColor);
  color.setAlpha(a);
  pthread_mutex_unlock(&mutexColor);
  return *this;
}

ScreenText& ScreenText::setScreenPosition(int x,int y){
  pthread_mutex_lock(&mutexScreenPosition);
  pthread_mutex_lock(&mutexOutScreenPosition);
  screenPositionX = oScreenPositionX = x;
  screenPositionY = oScreenPositionY = y;
  pthread_mutex_unlock(&mutexScreenPosition);
  pthread_mutex_unlock(&mutexOutScreenPosition);
  return *this;
}

ScreenText& ScreenText::setScreenAlign(unsigned char a){
  pthread_mutex_lock(&mutexOutScreenPosition);
  align = a;
  if((align != left)&&(align!=center)&&(align!=right))
    align = left;
  pthread_mutex_unlock(&mutexOutScreenPosition);
  return *this;
}

ScreenText& ScreenText::setScreenVAlign(unsigned char a){
  pthread_mutex_lock(&mutexOutScreenPosition);
  valign = a;
  if((valign != top)&&(valign!=middle)&&(valign!=center)&&(align!=bottom))
    valign = top;
  pthread_mutex_unlock(&mutexOutScreenPosition);
  return *this;
}

ScreenText& ScreenText::setDisplay(bool d){
  pthread_mutex_lock(&mutexDisplay);
  display = d;
  pthread_mutex_unlock(&mutexDisplay);
  return *this;
}

irr::gui::IGUIFont* ScreenText::getFont(){
  irr::gui::IGUIFont* t;
  pthread_mutex_lock(&mutexFont);
  t = font.get();
  pthread_mutex_unlock(&mutexFont);
  return t;
}

std::string ScreenText::getString(){
  std::string t;
  pthread_mutex_lock(&mutexString);
  t = str;
  pthread_mutex_unlock(&mutexString);
  return t;
}

bool ScreenText::getDisplay(){
  bool r = false;
  pthread_mutex_lock(&mutexFont);
  pthread_mutex_lock(&mutexDisplay);
  if(font.get() != NULL)
    r = display;
  pthread_mutex_unlock(&mutexFont);
  pthread_mutex_unlock(&mutexDisplay);
  return r;
}

unsigned char ScreenText::getScreenAlign(){
  unsigned char a;
  pthread_mutex_lock(&mutexOutScreenPosition);
  a = align;
  pthread_mutex_unlock(&mutexOutScreenPosition);
  return a;
}

unsigned char ScreenText::getScreenVAlign(){
  unsigned char a;
  pthread_mutex_lock(&mutexOutScreenPosition);
  a = valign;
  pthread_mutex_unlock(&mutexOutScreenPosition);
  return a;
}

irr::core::rect<irr::s32> ScreenText::getScreenRect(){
  irr::core::rect<irr::s32> t;
  pthread_mutex_lock(&mutexFont);
  pthread_mutex_lock(&mutexString);
  pthread_mutex_lock(&mutexOutScreenPosition);
  irr::s32 Y = oScreenPositionY;
  irr::core::dimension2d<irr::u32> tx = font->getDimension(wstr.c_str());
  if((valign == middle)||(valign == center)){
    Y -= tx.Height/2;
  }else if(valign == bottom){
    Y -= tx.Height;
  }
  if((font.get() == NULL)||(align == left)){
    t = irr::core::rect<irr::s32>(oScreenPositionX,Y,oScreenPositionX,Y);
  }else{
    if(align == right){
      t = irr::core::rect<irr::s32>(
        oScreenPositionX-tx.Width,
        Y,
        oScreenPositionX-tx.Width,
        Y
      );
    }else{
      t = irr::core::rect<irr::s32>(
        oScreenPositionX-(tx.Width/2),
        Y,
        oScreenPositionX-(tx.Width/2),
        Y
      );
    }
  }
  pthread_mutex_unlock(&mutexFont);
  pthread_mutex_unlock(&mutexString);
  pthread_mutex_unlock(&mutexOutScreenPosition);
  return t;
}

irr::video::SColor ScreenText::getSColor(){
  irr::video::SColor t;
  pthread_mutex_lock(&mutexColor);
  t = color;
  pthread_mutex_unlock(&mutexColor);
  return t;
}

void ScreenText::aSetDisplay(bool b){
  this->setDisplay(b);
}

void ScreenText::aSetScreenSize(unsigned w,unsigned h){}

void ScreenText::aSetScreenPosition(int x,int y){
  this->setScreenPosition(x,y);
}

void ScreenText::aSetImageColor(irr::video::SColor* a){}

irr::video::SColor* ScreenText::getColor(){
  return NULL;
}

unsigned ScreenText::getScreenWidth(){
  unsigned v=0;
  pthread_mutex_lock(&mutexFont);
  pthread_mutex_lock(&mutexString);
  irr::core::dimension2d<irr::u32> tx = font->getDimension(wstr.c_str());
  v = tx.Width;
  pthread_mutex_unlock(&mutexFont);
  pthread_mutex_unlock(&mutexString);
  return v;
}

unsigned ScreenText::getScreenHeight(){
  unsigned v=0;
  pthread_mutex_lock(&mutexFont);
  pthread_mutex_lock(&mutexString);
  irr::core::dimension2d<irr::u32> tx = font->getDimension(wstr.c_str());
  v = tx.Height;
  pthread_mutex_unlock(&mutexFont);
  pthread_mutex_unlock(&mutexString);
  return v;
}

int ScreenText::getScreenPositionX(){
  return screenPositionX;
}

int ScreenText::getScreenPositionY(){
  return screenPositionY;
}

ScreenText& ScreenText::setAnimatorQueue(AnimatorQueue& o){
  (*animatorQueue) = o;
  return *this;
}

ScreenText& ScreenText::appendMorph(ObjectMorph* o){
  animatorQueue->appendMorph(o);
  return *this;
}

ScreenText& ScreenText::appendCallback(Callback* c){
  animatorQueue->appendCallback(c);
  return *this;
}

unsigned char ScreenText::getType(){
  return AnimatorObject::typeScreenText;
}

void ScreenText::processTime(irr::u32 time){

}