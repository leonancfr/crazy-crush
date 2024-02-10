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
#include "GameLevelFile.hpp"

#include "GameDefines.hpp"
#include "GameControl.hpp"
#include "GamePointsMatrix.hpp"
#include "Logger.hpp"
#include "MatrixBool.hpp"
#include "DecodeValue.hpp"
#include "MainDraw.hpp"
#include "Screen.hpp"
#include "BinaryOperations.hpp"
#include <fstream>
#include <vector>
#include <sstream>

namespace CrazyCrush {
namespace Game {
namespace LevelFile {

MatrixBool fixedPositions(Screen::num_rows,Screen::num_columns);

unsigned packetSize2 = packetSize;

bool openLevelText(std::string filename,bool inEngine){
  std::string buffer;
  if(!inEngine){
    std::fstream file(filename.c_str(),std::ios::in);
    if(!file.is_open())
      return false;
    while(file.good()){
      std::getline(file,buffer);
      if(!buffer.empty()){
        break;
      }
    }
    if(buffer.empty())
      return false;
    file.close();
  }else{
    return false;
  }
  std::vector<std::string> contents;
  std::string fieldLine;
  unsigned start = 0;
  unsigned i = 0;
  for(; i<buffer.length();i++){
    if(buffer.at(i) == ' ' ){
  	  if((i!=buffer.length()-1)&&(buffer.at(i+1) == ' ')) continue;
      if(start == i) continue;
      fieldLine = std::string(&(buffer.at(start)), i-start);
      if(fieldLine.length() != 0) // warranty, maybe not necessary
        contents.push_back( fieldLine );
      start = ++i;
    }
  }
  if(contents.size() != (1+1+Screen::num_columns+Screen::num_columns*Screen::num_rows)){
    std::stringstream SS;
    SS << "Era esperado " << (1+1+Screen::num_columns+Screen::num_columns*Screen::num_rows) << " elementos, foram encontrados " << contents.size();
    LOG_ERROR(SS.str().c_str());
    return false;
  }
  Game::totalGemsEnabled = common::decodeValue(contents[0]);
  Game::Control::setLevelTotalTime(common::decodeValue(contents[1]));
  for(unsigned j=0;j<Screen::num_columns;j++){
    Game::stageTopPositionStart[j] = common::decodeValue(contents[2+j]);
  }
  Game::Points::erase();
  unsigned val = 0;
  for(unsigned i=0;i<Screen::num_rows;i++){
    for(unsigned j=0;j<Screen::num_columns;j++){
      val = common::decodeValue(contents[2+Screen::num_columns+i*Screen::num_columns+j]);
      if(val >= 4){
        Screen::matrix.at(i,j)->setGem(Gem::rock);
      }else{
        Screen::matrix.at(i,j)->randGem();
        Game::Points::setPoint(i,j,val);
      }
    }
  }
  return true;
}

bool openLevel(std::string filename,bool inEngine){
  char *buffer = new char[packetSize];
  for(unsigned i=0;i<packetSize;i++)
    buffer[i] = 0;
  if(!inEngine){
    std::fstream file(filename.c_str(),std::ios::in|std::ios::binary);
    if(!file.is_open())
      return false;
    file.read(buffer,packetSize);
    file.close();
  }else{
    packetSize2 = packetSize;
    if(!CrazyCrush::readWithWait(filename,buffer,packetSize2)){
      return false;
    }
  }
  unsigned offset = 0;
  formatByte(Game::totalGemsEnabled,buffer,3,offset);
  unsigned totalTime = 0;
  formatByte(totalTime,buffer,32,offset);
  Game::Control::setLevelTotalTime(totalTime);
  unsigned val;
  for(unsigned j=0;j<Screen::num_columns;j++){
    formatByte(val,buffer,4,offset);
    Game::stageTopPositionStart[j] = val;
  }
  Game::Points::erase();
  for(unsigned i=0;i<Screen::num_rows;i++){
    for(unsigned j=0;j<Screen::num_columns;j++){
      formatByte(val,buffer,3,offset);
      if(val >= 0x04){
        Screen::matrix.at(i,j)->setGem(Gem::rock);
        Screen::updateScreenPosition(*Screen::matrix.at(i,j),i,j);
      }else{
        Screen::matrix.at(i,j)->randGem();
        Game::Points::setPoint(i,j,val&0x03);
      }
    }
  }
  return true;
}

bool saveLevel(std::string filename){
  std::fstream file(filename.c_str(),std::ios::out|std::ios::binary|std::ios::trunc);
  if(!file.is_open())
    return false;
  char buffer[packetSize];
  for(unsigned i=0;i<packetSize;i++)
    buffer[i] = 0;
  unsigned offset = 0;
  formatUnsigned(buffer,Game::totalGemsEnabled,3,offset);
  formatUnsigned(buffer,Game::Control::getLevelTotalTime(),32,offset);
  for(unsigned j=0;j<Screen::num_columns;j++){
    formatUnsigned(buffer,Game::stageTopPositionStart[j],4,offset);
  }
  for(unsigned i=0;i<Screen::num_rows;i++){
    for(unsigned j=0;j<Screen::num_columns;j++){
      if(Screen::matrix.at(i,j)->getGem() == Gem::rock){
        formatUnsigned(buffer,4,3,offset);
      }else{
        formatUnsigned(buffer,Game::Points::getPoint(i,j),3,offset);
      }
    }
  }
  file.write(buffer,packetSize);
  file.close();
  return true;
}

#ifdef DEBUG
/*
void printHex(char* str,unsigned len){
  for(unsigned i=0;i<len;i++){
    std::cout << std::hex << (unsigned)((unsigned char)str[i]) << " ";
  }
  std::cout << std::dec << std::endl;
}

void debug(){
  char buffer[20];
  buffer[8] = '\0';
  unsigned a = 0x69;
  unsigned b = 0xFF;
  unsigned c = 0xFF;
  unsigned d = 0xA5;
  std::cout << a << " " << b << " " << c << " " << d << std::endl;
  printHex(buffer,8);
  unsigned offset = 0;
  formatUnsigned(buffer,a,8,offset);
  formatUnsigned(buffer,b,3,offset);
  formatUnsigned(buffer,c,4,offset);
  formatUnsigned(buffer,d,6,offset);
  a = b = c = d = 0;
  std::cout << a << " " << b << " " << c << " " << d << std::endl;
  printHex(buffer,8);
  offset = 0;
  formatByte(a,buffer,8,offset);
  formatByte(b,buffer,3,offset);
  formatByte(c,buffer,4,offset);
  formatByte(d,buffer,6,offset);
  std::cout << a << " " << b << " " << c << " " << d << std::endl;
  printHex(buffer,8);
}*/
void debug(){}
#endif



}}}