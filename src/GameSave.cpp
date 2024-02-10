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
#include "GameSave.hpp"
#include "BinaryOperations.hpp"
#include "Logger.hpp"
#include "GameLevel.hpp"
#include <fstream>

namespace CrazyCrush {
namespace Game {
namespace Save {

const unsigned totalLevel = 6;
const unsigned maxRankTimeAttack = 10;
const unsigned sizeOfInt = 32;

const unsigned bufferSize = (maxRankTimeAttack+Game::Level::totalLevel)*4;
bool initied = false;

char *buffer;
std::fstream file;//("save.bin",std::fstream::out|std::fstream::binary|std::fstream::app);

void initialize(){
  if(initied)
    return;
  initied = true;
  buffer = new char[bufferSize];
  for(unsigned i=0;i<bufferSize;i++)
    buffer[i] = 0;
  file.open("save.bin",std::fstream::out|std::fstream::in|std::fstream::binary);
  if(!file.is_open()){
    file.open("save.bin",std::fstream::out);
    file.close();
    file.open("save.bin",std::fstream::out|std::fstream::in|std::fstream::binary);
  }
  if(file.is_open()){
    file.read(buffer,bufferSize);
  }else{
    LOG_ERROR("Failed to open save.bin");
  }
}

unsigned getLevelPoints(unsigned lvl){
  if(!initied) initialize();
  unsigned v,o;
  o = (maxRankTimeAttack+lvl-1)*sizeOfInt;
  formatByte(v,buffer,sizeOfInt,o);
  return v;
}

unsigned getTimeAttackRecord(){
  if(!initied) initialize();
  unsigned v,o;
  o=0;
  formatByte(v,buffer,sizeOfInt,o);
  return v;
}

unsigned getTimeAttackAtPosition(unsigned pos){
  if(!initied) initialize();
  unsigned v,o;
  o=(pos-1)*sizeOfInt;
  formatByte(v,buffer,sizeOfInt,o);
  return v;
}

bool setLevelPoint(unsigned lvl,unsigned value){
  if(!initied) initialize();
  unsigned o = (maxRankTimeAttack+lvl-1)*sizeOfInt;
  formatUnsigned(buffer,value,sizeOfInt,o);
  if(file.is_open()){
    if(!file.good()){
      file.close();
      file.open("save.bin",std::fstream::in|std::fstream::out|std::fstream::binary|std::fstream::trunc);
      if(!file.is_open()||!file.good()){
        LOG_ERROR("Failed to reopen save.bin");
        return false;
      }
    }
    file.seekg(0,file.beg);
    file.write(buffer,bufferSize);
    return true;
  }else{
    LOG_ERROR("save.bin isn't open");
  }
  return false;
}

bool setTimeAttackRecord(unsigned value){
  if(!initied) initialize();
  unsigned o;
  for(unsigned i=1;i<=maxRankTimeAttack;i++){
    if(getTimeAttackAtPosition(i) <= value){
      for(unsigned j=maxRankTimeAttack;j>i;j--){
        o=(j-1)*sizeOfInt;
        formatUnsigned(buffer,getTimeAttackAtPosition(j-1),sizeOfInt,o);
      }
      o = (i-1)*sizeOfInt;
      formatUnsigned(buffer,value,sizeOfInt,o);
      break;
    }
  }
  if(file.is_open()){
    if(!file.good()){
      file.close();
      file.open("save.bin",std::fstream::in|std::fstream::out|std::fstream::binary|std::fstream::trunc);
      if(!file.is_open()||!file.good()){
        LOG_ERROR("Failed to reopen save.bin");
        return false;
      }
    }
    file.seekg(0,file.beg);
    file.write(buffer,bufferSize);
    return true;
  }else{
    LOG_ERROR("save.bin isn't open");
  }
  return false;
}

}}}