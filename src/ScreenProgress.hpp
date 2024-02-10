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
#ifndef _SCREEN_PROGRESS_HPP_
#define _SCREEN_PROGRESS_HPP_ 1

#include "ScreenObject.hpp"
#include "Irrlicht/IrrlichtDevice.h"
#include "Irrlicht/IVideoDriver.h"
#include "Irrlicht/ITexture.h"
#include "SharedPointer.hpp"

//! Classe para criar e tratar uma tela de progresso
/**
Essa tela só é usada uma única vez, no início do jogo
*/
class ScreenProgress {
  private:
    unsigned bar_size;
    unsigned total_load;
    unsigned total_loaded;
    irr::IrrlichtDevice *device;
    irr::video::IVideoDriver *driver;
    ScreenObject *barRight,*barLeft,*barMiddle,*loadingText;
    SharedPointer<irr::video::ITexture> bar,loadText;
    void instaceObjects();
  public:
    //! Instancia a classe associando o dispositivo da engine em uso
    /**
    \param device: O dispositivo da engine
    */
    ScreenProgress(irr::IrrlichtDevice* device);
    
    //! Instancia a classe associando o dispositivo da engine em uso e definindo a quantidade total de objetos a carregar
    /**
    \param device: O dispositivo da engine
    \param total: Número de pontos total para completar a barra
    */
    ScreenProgress(irr::IrrlichtDevice* device,unsigned total);
    
    //! Instancia a classe associando o dispositivo da engine em uso, definindo a quantidade total do objetos a carregar e a largura da barra
    /**
    \param device: O dispositivo da engine
    \param total: Número de pontos total para completar a barra
    \param bar_size: Largura máxima da barra de progresso
    */
    ScreenProgress(irr::IrrlichtDevice* device,unsigned total,unsigned bar_size);
    
    ~ScreenProgress();
    
    //! Define a quantidade total de objetos a carregar
    void setTotalToLoad(unsigned total);
    
    //! Define a largura máxima da barra de progresso
    void setMaxBarSize(unsigned bar_size);
    
    //! Obtém a total de elementos a carregar
    unsigned getTotalToLoad();
    
    //! Obtém a quantidade de elementos carregados
    unsigned getTotalLoaded();
    
    //! Obtém o dispositivo da engine associado à classe
    irr::IrrlichtDevice* getDevice();
    
    //! Obtém o driver de vídeo associado ao dispositivo da engine associado à classe
    irr::video::IVideoDriver* getDriver();
    
    //! Incrementa, em uma unidade, a quantidade de elementos carregados
    ScreenProgress& incLoaded();
    
    //! Incrementa, em N unidade(s), a quantidade de elementos carregados
    ScreenProgress& incLoaded(unsigned n);
    
    //! Desenha os elementos internos da classe na tela (ie: A barra de progresso)
    bool drawScene();
};

#endif