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
#ifndef _CORE_OPENGL_VERSION_HPP_
#define _CORE_OPENGL_VERSION_HPP_

#include "Irrlicht/IVideoDriver.h"

namespace CrazyCrush {
  //! Espaço reservado a algumas funções diretas com o OpenGL
  namespace OpenGL {
    //! True se a versão do OpenGL for superior a 1.7.0
    extern bool isAbove_1_7_0;
    
    //! True se a versão do OpenGL for superior a 2.0.0
    extern bool isAbove_2_0_0;
    
    //! Valor da versão do OpenGL
    extern unsigned char majorVersion, mediumVersion, minorVersion;
    
    //! Obtém a versão do OpenGL
    /**
    \param driver: Driver usado pela engine
    */
    void getOpenGLVersion(irr::video::IVideoDriver* driver);
  }
}

#endif
