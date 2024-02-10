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
#include "Logger.hpp"

#define FSTREAM std::fstream
#define P(a) ((std::fstream*) a )
#define Q(a) (*((std::fstream*) a ))

#include <fstream>

Logger::Logger(const char* file){
  output = new std::fstream(file,std::fstream::out|std::fstream::trunc);
  Q(output)<<"<!DOCTYPE html><head><title>CrazyCrush Log</title><style>body { background:#000; color:ccc; font-family:Verdana; font-size:12px; }table { width: 100%; border:1px dashed #666; background:#444; cellpadding:0; cellspacing:0; }tr:hover {background:#555;}td {padding:1px; color:#aaa; border-right:1px solid #666; border-bottom:1px solid #666;}th {color:#666;border-bottom:1px solid #666;}.level_"<<error   <<" .message:before {content:\"Error: \";color:#f00;}.level_"<<error   <<" td {color:#f00;}.level_"<<warning <<" .message:before {content:\"Warning: \";color:#fa0;}.level_"<<warning <<" td {color:#fa0;}.level_"<<log     <<" .message:before {content:\"Log: \";color:#aaa;}.level_"<<log     <<" td {color:#aaa;}.level_"<<debug   <<" .message:before {content:\"Debug: \";color:#666;}.level_"<<debug   <<" td {color:#666;}.level_"<<info    <<" .message:before {content:\"Information: \";color:#66f;}.level_"<<info    <<" td {color:#66f;}.file {width:20%;}.line {text-align:right;width:50px;}.message {}</style><body><table cellpadding=0 cellspacing=0><tr><th class='line'>line</th><th class='file'>File</th><th class='message'>Message</th></tr>";
  /* unoptmized
  Q(output)<<"<!DOCTYPE html><head><title>CrazyCrush Log</title><style>";
  Q(output)<<"body { background:#000; color:ccc; font-family:Verdana; font-size:12px; }";
  Q(output)<<"table { width: 100%; border:1px dashed #666; background:#444; cellpadding:0; cellspacing:0; }";
  Q(output)<<"tr:hover {background:#555;}";
  Q(output)<<"td {padding:1px; color:#aaa; border-right:1px solid #666; border-bottom:1px solid #666;}";
  Q(output)<<"th {color:#666;border-bottom:1px solid #666;}";
  Q(output)<<".level_"<<error   <<" .message:before {content:\"Error: \";color:#f00;}";
  Q(output)<<".level_"<<error   <<" td {color:#f00;}";
  Q(output)<<".level_"<<warning <<" .message:before {content:\"Warning: \";color:#fa0;}";
  Q(output)<<".level_"<<warning <<" td {color:#fa0;}";
  Q(output)<<".level_"<<log     <<" .message:before {content:\"Log: \";color:#aaa;}";
  Q(output)<<".level_"<<log     <<" td {color:#aaa;}";
  Q(output)<<".level_"<<debug   <<" .message:before {content:\"Debug: \";color:#666;}";
  Q(output)<<".level_"<<debug   <<" td {color:#666;}";
  Q(output)<<".level_"<<info    <<" .message:before {content:\"Information: \";color:#66f;}";
  Q(output)<<".level_"<<info    <<" td {color:#66f;}";
  Q(output)<<".file {width:20%;}";
  Q(output)<<".line {text-align:right;width:50px;}";
  Q(output)<<".message {}";
  Q(output)<<"</style><body><table cellpadding=0 cellspacing=0><tr><th class='line'>line</th><th class='file'>File</th><th class='message'>Message</th></tr>";
  */
  this->msg(__FILE__,__LINE__,"Log started.",info);
}

Logger::~Logger(){
  this->msg(__FILE__,__LINE__,"Log closed successful.",info);
  Q(output)<<"</table></body></html>";
  Q(output).close();
  delete P(output);
}

void Logger::msg(const char* file, const unsigned line, const char* msg, const char type){
  Q(output)<<"<tr class='level_"<<(int)type<<"'><td class='line'>"<<line<<"</td><td class='file'>"<<file<<"</td><td class='message'>"<<msg<<"</td></tr>"<<std::endl;
}

Logger console("CrazyCrush.htm");