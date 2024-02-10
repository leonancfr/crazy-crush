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
#ifndef _BINARY_OPERATIONS_
#define _BINARY_OPERATIONS_ 1

//! Retorna 2^(n-1)
template<typename T>
unsigned byteSizeToHEX(T size){
  switch(size){
    case 1:
      return 0x01;
    case 2:
      return 0x03;
    case 3:
      return 0x07;
    case 4:
      return 0x0F;
    case 5:
      return 0x1F;
    case 6:
      return 0x3F;
    case 7:
      return 0x7F;
    case 8:
      return 0xFF;
  };
  return 0;
}

//! Obtém de um stream de dados (char*) um valor inteiro de tamanho variável a nivel de bits
/**
\param out: Valor obtido
\param in: Stream de entrada
\param size: Tamanho do inteiro (em bits)
\param offset: Offset desde o início do stream (em bits)
*/
template<typename T>
void formatByte(T& out,char* in,unsigned char size,unsigned& offset){
  unsigned char t;
  unsigned char offP8 = offset%8;
  out = 0;
  for(unsigned char s = size;s>=8;s-=8){
    if(offP8!=0){
      t = ((in[offset/8]&byteSizeToHEX(8-offP8))<<offP8) + ((in[1+offset/8]>>(8-offP8))&byteSizeToHEX(offP8));
    }else{
      t = in[offset/8];
    }
    out += t<<(s-8);
    offset+=8;
  }
  unsigned char ss = size%8;
  if(ss != 0){
    if(offP8+ss > 8){
      out += ((in[offset/8]&byteSizeToHEX(8-offP8))<<(ss+offP8-8)) + ((in[1+offset/8]>>(16-(ss+offP8)))&byteSizeToHEX(ss+offP8-8));
    }else{
      out += (in[offset/8]>>(8-(ss+offP8)))&byteSizeToHEX(ss);
    }
  }
  offset+=ss;
}

//! Converte um valor inteiro de tamanho variável em um stream de dados (char*) a nivel de bits
/**
\param out: Stream de saída
\param in: Valor de entrada
\param size: Tamanho do inteiro (em bits)
\param offset: Offset desde o início do stream (em bits)
*/
template<typename T>
void formatUnsigned(char* out,T in,unsigned char size,unsigned& offset){
  for(unsigned char s=(size-1);s>=0;s--){
    out[offset/8] = (out[offset/8]&( (~((0x01)<<(7-offset%8)))&(0xFF) )) + (((in>>s)&0x01) << (7-offset%8));
    offset++;
    if(s == 0)
      break;
  }
}

#endif