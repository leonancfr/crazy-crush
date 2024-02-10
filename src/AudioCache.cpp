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
#include "AudioCache.hpp"
#include "Irrlicht/IFileSystem.h"
#include "Irrlicht/IReadFile.h"

namespace CrazyCrush {
namespace AudioCache {

cAudio::IAudioSource* sfxPoint = NULL;
cAudio::IAudioSource* gameBg = NULL;

bool initialize(ScreenProgress& progress,cAudio::IAudioManager& audio){
  char* buffer;
  irr::io::IFileSystem* fSys = progress.getDevice()->getFileSystem();
  irr::io::IReadFile* fRead = NULL;
  
  fRead = fSys->createAndOpenFile("sfx_point.ogg");
  buffer = new char[fRead->getSize()];
  if(buffer == NULL)
    return false;
  fRead->read((void*)buffer,fRead->getSize());
  sfxPoint = audio.createFromMemory("sfx_point",buffer,fRead->getSize(),"ogg");
  if(sfxPoint == NULL)
    return false;
  fRead->drop();
  delete buffer;
  progress.incLoaded().drawScene();
  
  fRead = fSys->createAndOpenFile("no_name.ogg");
  buffer = new char[fRead->getSize()];
  if(buffer == NULL)
    return false;
  fRead->read((void*)buffer,fRead->getSize());
  gameBg = audio.createFromMemory("no_name",buffer,fRead->getSize(),"ogg");
  if(gameBg == NULL)
    return false;
  fRead->drop();
  delete buffer;
  progress.incLoaded().drawScene();
  
  return true;
}

unsigned char getTotalAudioLoadNumber(){
  return 2;
}

}}
