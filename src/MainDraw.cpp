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
#include "MainDraw.hpp"

#include "Irrlicht/IFileSystem.h"
#include "Irrlicht/IReadFile.h"
#include "Logger.hpp"
#include "ScreenObject.hpp"
#include "ScreenText.hpp"
#include "ZOrder.hpp"
#include <pthread.h>
#include <queue>
#include <sstream>

namespace CrazyCrush {

irr::IrrlichtDevice* device;
irr::video::IVideoDriver *driver;
MyEventReceiver event;
Protected<bool> shutdownGame(false);
Protected<bool> externalRead(false);
AnimatorObject* lObj;

void draw(){
  driver->beginScene(true, true, irr::video::SColor(255,0,0,0));
  driver->enableMaterial2D(true);
  CrazyCrush::z_order.begin();
  while((lObj = CrazyCrush::z_order.next()) != NULL){
    if(lObj->getType() == AnimatorObject::typeScreenObject){
      if(lObj->getDisplay()){
        driver->draw2DImage(
          ((ScreenObject*)lObj)->getTexture(),
          ((ScreenObject*)lObj)->getScreenRect(),
          ((ScreenObject*)lObj)->getResourceRect(),
          0,
          ((ScreenObject*)lObj)->getImageColor(),
          true
        );
      }
    }else if(lObj->getType() == AnimatorObject::typeScreenText){
      if(lObj->getDisplay()){
        //std::cout << "Text: "<<lObj<<"  "<<((ScreenText*)lObj)->getScreenPositionY()<<std::endl;
        ((ScreenText*)lObj)->getFont()->draw(
          ((ScreenText*)lObj)->getString().c_str(),
          ((ScreenText*)lObj)->getScreenRect(),
          ((ScreenText*)lObj)->getSColor()
        );
      }
    }
  }
  driver->enableMaterial2D(false);
  driver->endScene();
}

//! Estrutura para leitura de arquivo pela engine
typedef struct {
  std::string filename;
  char* pnt;
  unsigned len;
  bool success;
  pthread_cond_t*  tCond;
  pthread_mutex_t* tMutex;
} DataAccess;

pthread_mutex_t queueMutex = PTHREAD_MUTEX_INITIALIZER;
std::queue<DataAccess*> FileReadQueue;

/*  Old
bool readWithWait(std::string file,char* p,const unsigned len){
  DataAccess t;
  t.filename = file;
  t.pnt = p;
  t.len = len;
  t.tMutex = new pthread_mutex_t;
  t.tCond = new pthread_cond_t;
  if(pthread_mutex_init(t.tMutex,NULL)!=0){
    LOG_ERROR("Thread: Failed to initialize pthread mutex.");
    return false;
  }
  if(pthread_cond_init(t.tCond,NULL)!=0){
    LOG_ERROR("Thread: Failed to initialize pthread condition.");
    return false;
  }
  pthread_mutex_lock(&queueMutex);
  FileReadQueue.push(&t);
  
  pthread_mutex_lock(t.tMutex);
  pthread_mutex_unlock(&queueMutex);
  externalRead.set(true);
  pthread_cond_wait(t.tCond,t.tMutex);
  pthread_mutex_unlock(t.tMutex);
  return t.success;
}
*/

bool readWithWait(std::string file,char*& p,unsigned& len){
  DataAccess t;
  bool alocate = (p==NULL);
  t.filename = file;
  t.pnt = p;
  t.len = len;
  t.tMutex = new pthread_mutex_t;
  t.tCond = new pthread_cond_t;
  if(pthread_mutex_init(t.tMutex,NULL)!=0){
    LOG_ERROR("Thread: Failed to initialize pthread mutex.");
    return false;
  }
  if(pthread_cond_init(t.tCond,NULL)!=0){
    LOG_ERROR("Thread: Failed to initialize pthread condition.");
    return false;
  }
  pthread_mutex_lock(&queueMutex);
  FileReadQueue.push(&t);
  
  pthread_mutex_lock(t.tMutex);
  pthread_mutex_unlock(&queueMutex);
  externalRead.set(true);
  pthread_cond_wait(t.tCond,t.tMutex);
  pthread_mutex_unlock(t.tMutex);
  if(alocate){
    p = t.pnt;
    len = t.len;
  }
  return t.success;
}

void irrlicht_thread_read_file(){
  if(!externalRead.get())
    return;
  DataAccess *t;
  pthread_mutex_lock(&queueMutex);
  if(FileReadQueue.size() == 0){
    externalRead.set(false);
    pthread_mutex_unlock(&queueMutex);
    return;
  }
  t = FileReadQueue.front();
  FileReadQueue.pop();
  if(FileReadQueue.size() == 0)
    externalRead.set(false);
  pthread_mutex_unlock(&queueMutex);
  irr::io::IFileSystem* fSys = device->getFileSystem();
  irr::io::IReadFile* fRead = fSys->createAndOpenFile(t->filename.c_str());
  if(fRead == NULL){
    std::stringstream SS;
    SS << "CrazyError: Unable to open file '" << t->filename << "'";
    LOG_ERROR(SS.str().c_str());
    t->success = false;
  }else{
    if(t->pnt == NULL){
      if(t->len == 0){
        t->len = fRead->getSize();
      }
      t->pnt = new char[t->len];
    }
    int readed = fRead->read((void*)t->pnt,t->len);
    if(readed == (int)t->len){
      t->success = true;
    }else{
      std::stringstream SS;
      SS << "CrazyError: Readed "<<readed<<" where is isperated "<<t->len;
      LOG_ERROR(SS.str().c_str());
      t->success = false;
    }
  }
  pthread_mutex_lock(t->tMutex);
  pthread_cond_broadcast(t->tCond);
  pthread_mutex_unlock(t->tMutex);
}

}