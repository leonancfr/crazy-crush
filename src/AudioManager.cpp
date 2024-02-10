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
#include "AudioManager.hpp"
#include "AudioCache.hpp"
#include "cAudio/cAudio.h"
#include "Logger.hpp"
#include "MainDraw.hpp"
#include <vector>
#include <string>
#include <sstream>

namespace CrazyCrush {
namespace AudioManager {

cAudio::IAudioManager* audioMgr = NULL;

std::vector<std::string> audioList;

bool initialize(){
  audioMgr = cAudio::createAudioManager(true);
  if(audioMgr != NULL)
    return true;
  return false;
}

unsigned char getTotalProgress(){
  return AudioCache::getTotalAudioLoadNumber();
}

bool preLoadAudio(ScreenProgress& progress){
  return AudioCache::initialize(progress,*audioMgr);
}

bool play(const char* name,bool loop, const char* filename){
  cAudio::IAudioSource* t = audioMgr->getSoundByName(name);
  if(t == NULL){
    if(filename == NULL)
      return false;
    if(!open(name, filename))
      return false;
    t = audioMgr->getSoundByName(name);
    if(t == NULL){
      LOG_ERROR("Erro bizarro!");
      return false;
    }
  }
  if(!t->isValid()){
    std::stringstream SS;
    SS << "Stream " << name << " é inválido";
    LOG_ERROR(SS.str().c_str());
    return false;
  }
  t->stop();
  return t->play2d(loop);
}

bool pause(const char* aName){
  cAudio::IAudioSource* t = audioMgr->getSoundByName(aName);
  if(t == NULL)
    return false;
  t->pause();
  return true;
}

bool stop(const char* aName){
  cAudio::IAudioSource* t = audioMgr->getSoundByName(aName);
  if(t == NULL)
    return false;
  t->stop();
  return true;
}

bool close(const char* name){
  cAudio::IAudioSource* t = audioMgr->getSoundByName(name);
  if(t == NULL)
    return false;
  for(unsigned i=0;i<audioList.size();i++){
    if(audioList[i].compare(name) == 0){
      audioList.erase(audioList.begin()+i);
      break;
    }
  }
  audioMgr->release(t);
  return true;
}

bool open(const char* name, const char* filename){
  cAudio::IAudioSource* t = audioMgr->getSoundByName(name);
  if(t != NULL)
    return false;
  unsigned size = 0;
  char* buffer = NULL;
  std::string fileName(filename);
  if(!readWithWait(fileName,buffer,size)){
    LOG_ERROR("Falha ao abrir um stream de áudio");
    return false;
  }
  t = audioMgr->createFromMemory(name,buffer,size,fileName.substr(fileName.rfind(".")+1).c_str());
  audioList.push_back(name);
  delete buffer;
  if(t == NULL){
    LOG_ERROR("Falha ao iniciar stream de dado");
    return false;
  }
  return true;
}

bool setVolume(const char* aName,float v){
  cAudio::IAudioSource* t = audioMgr->getSoundByName(aName);
  if(t == NULL)
    return false;
  if(v>1.0)
    v = 1.0;
  t->setVolume(v);
  return true;
}

float getVolume(const char* aName){
  cAudio::IAudioSource* t = audioMgr->getSoundByName(aName);
  if(t == NULL)
    return 0.0;
  return t->getVolume();
}

void suspend(){
  if(AudioCache::sfxPoint->isPlaying())
    AudioCache::sfxPoint->pause();
  if(AudioCache::gameBg->isPlaying())
    AudioCache::gameBg->pause();
  for(unsigned i=0;i<audioList.size();i++){
    cAudio::IAudioSource* t = audioMgr->getSoundByName(audioList[i].c_str());
    if(t == NULL)
      continue;
    if(t->isPlaying())
      t->pause();
  }
}

void resume(){
  if(AudioCache::sfxPoint->isPaused())
    AudioCache::sfxPoint->play2d();
  if(AudioCache::gameBg->isPaused())
    AudioCache::gameBg->play2d();
  for(unsigned i=0;i<audioList.size();i++){
    cAudio::IAudioSource* t = audioMgr->getSoundByName(audioList[i].c_str());
    if(t == NULL)
      continue;
    if(t->isPaused())
      t->play2d();
  }
}

void destroy(){
  audioMgr->stopAllSounds();
  audioMgr->release(AudioCache::sfxPoint);
  AudioCache::sfxPoint = NULL;
  audioMgr->release(AudioCache::gameBg);
  AudioCache::gameBg = NULL;
  for(unsigned i=0;i<audioList.size();i++){
    cAudio::IAudioSource* t = audioMgr->getSoundByName(audioList[i].c_str());
    if(t != NULL)
      audioMgr->release(t);
  }
  audioMgr->shutDown();
  cAudio::destroyAudioManager(audioMgr);
}

void setMasterVolume(float v){
  audioMgr->setMasterVolume(v>1.0?1.0:v);
}

float getMasterVolume(){
  return audioMgr->getMasterVolume();
}

}}