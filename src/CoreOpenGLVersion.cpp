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
#include "CoreOpenGLVersion.hpp"

#include <string>

namespace CrazyCrush {
namespace OpenGL {

bool isAbove_1_7_0 = false;
bool isAbove_2_0_0 = false;
unsigned char majorVersion = 0;
unsigned char mediumVersion = 0;
unsigned char minorVersion = 0;

void getOpenGLVersion(irr::video::IVideoDriver* driver){
  std::wstring wversion(driver->getName());
  std::size_t fp = wversion.find(L" ");
  if(fp == std::wstring::npos)
    return;
  wversion = wversion.substr(fp);
  std::string version(wversion.begin(),wversion.end());
  fp = version.find(".");
  if(fp == std::string::npos)
    return;
  std::size_t sp = version.find(".",fp+1);
  if(sp == std::string::npos)
    sp = version.length();
  majorVersion = strtol(version.substr(0,fp).c_str(),NULL,10);
  mediumVersion = strtol(version.substr(fp+1,sp-fp).c_str(),NULL,10);
  try{
    minorVersion = strtol(version.substr(sp+1).c_str(),NULL,10);
  }catch(...){}
  if(majorVersion >= 2){
    isAbove_2_0_0 = true;
    isAbove_1_7_0 = true;
  }else if((majorVersion == 1)&&(mediumVersion>=7)){
    isAbove_1_7_0 = true;
  }
}

}}