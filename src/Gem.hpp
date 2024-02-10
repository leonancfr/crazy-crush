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
#ifndef _GEM_HPP_
#define _GEM_HPP_ 1

#include "ScreenObject.hpp"
#include "Protected.hpp"

//! Extensão do ScreenObject para manipular mais fácil as pedras
class Gem : public ScreenObject {
  private:
    Protected<char> gemType;
    Protected<bool> isEnabled,isFixed,hasTimeEffect;
    Protected<ScreenObject*> effect_icon;
  public:
    //! Tipo de pedras possíveis
    enum {gem1,gem2,gem3,gem4,gem5,gem6,gem7,rock};
    
    Gem();
    ~Gem();
    
    //! Define um tipo de pedra para o objeto
    /**
    \param type: Um dos tipos enumerados acima
    \return O objeto
    */
    Gem& setGem(char type);
    
    //! Define se a pedra está habilitada
    /**
    \param value: Valor a ser definido
    \return O objeto
    */
    Gem& setEnabled(bool value);
    
    //! Define que a peça atual será uma pedra aleatória
    /**
    Obedecendo ao Game::totalGemsEnabled
    \return O objeto
    */
    Gem& randGem();
    
    //! Compara duas pedras
    /**
    \param other: A outra pedra a comparar
    \return Se as pedras são iguais
    */
    bool operator==(Gem& other);
    
    //! Compara duas pedras
    /**
    \param other: A outra pedra a comparar
    \return Se as pedras são diferentes
    */
    bool operator!=(Gem&);
    
    //! Obtém o tipo atual da pedra
    /**
    \return Um dos valores do tipo enumerado acima
    */
    char getGem();
    
    //! Se a pedra está habilitada
    /**
    Verifica se a pedra está habilitada e pode ser movida
    */
    bool getEnabled();
    
    //! Se a peça está fixada
    /**
    Usado para saber se a peça pode ou não ser movida
    */
    bool getFixed();
    
    //! Se a pedra possui bônus de tempo
    /**
    Bônus de tempo ainda não implementado
    */
    bool getTimeEffect();
    
    //! Se a pedra possui algum tipo de "efeito especial"
    /**
    Não implementado nessa versão
    */
    bool hasEffect();
    
    //! Processa o "efeito especial", se houver
    /**
    Não implementado nessa versão
    */
    void processEffect();
    
    void aSetDisplay(bool);
    void aSetScreenPosition(int,int);
};

#endif