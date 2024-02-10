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
#include "Percentage.hpp"
#include "Random.hpp"
#include <cmath>

namespace CrazyCrush {
namespace Percentage {

bool get(Percent& p){
  if(p.range == 1)
    return true;
  unsigned val = Random::get()%p.range;
  if(val < p.value)
    return true;
  return false;
}

bool get(HPercent& p){
  if(get(p.p1)&&get(p.p2)&&get(p.p3)&&get(p.p4))
    return true;
  return false;
}

Percent format(float v){
  float ratio = 0.0;
  float temp = 0.0;
  Percent t;
  bool finded = false;
  for(t.range = 2;t.range<=Random::max+1;t.range*=2){
    ratio = ((float)1)/t.range;
    for(t.value = 1;t.value<t.range;t.value++){
      temp = t.value*ratio;
      if(temp == v){
        finded = true;
        break;
      }else if(temp > v){
        if(t.value != 1){
          if(temp-v > v-(t.value-1)*ratio){
            t.value--;
          }
        }
        break;
      }
    }
    if(finded)
      break;
  }
  if(!finded){
    t.range/=2;
  }
  return t;
}

HPercent formatH(float v){
  HPercent t;
  t.p2.range = t.p3.range = t.p4.range = t.p2.value = t.p3.value = t.p4.value = 1;
  float ratio = ((float)1)/(Random::max+1);
  if(v > ratio){
    t.p1 = format(v);
    return t;
  }
  ratio*=ratio;
  if(v > ratio){
    t.p1 = format(sqrt(v));
    t.p2 = format( v*t.p1.range/((float)t.p1.value) );
    return t;
  }
  t.p1 = format(sqrt(sqrt(v)));
  t.p2 = t.p1;
  t.p3 = t.p1;
  return t;
}

HPercent formatH(float v,float err){
  HPercent t;
  t.p2.range = t.p3.range = t.p4.range = t.p2.value = t.p3.value = t.p4.value = 1;
  float ratio = ((float)1)/(Random::max+1);
  if(err > ratio){
    t.p1 = format(v);
    return t;
  }
  ratio*=ratio;
  if(err > ratio){
    t.p1 = format(sqrt(v));
    t.p2 = format( v*t.p1.range/((float)t.p1.value) );
    return t;
  }
  t.p1 = format(sqrt(sqrt(v)));
  t.p2 = t.p1;
  t.p3 = t.p1;
  t.p4 = format( v*t.p1.range*t.p1.range*t.p1.range/(t.p1.value*t.p1.value*t.p1.value));
  return t;
}

}}