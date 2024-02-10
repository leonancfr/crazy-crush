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
#ifndef _SCREEN_HOVER_HPP_
#define _SCREEN_HOVER_HPP_ 1

#include "Callback.hpp"
#include <stack>
#include <pthread.h>

//! Classe abstrata para definir uma região da tela com um evento (por mouse)
/**
Observação: Para maior comodidade e praticidade, esta classe se auto-adiciona à lista ScreenHoverList ao ser instanciada. Assim como se auto-remove quando é destruída ou marcada para destruir
*/
class ScreenHover {
  private:
    bool enabled;
    std::stack<bool> stackEnabled;
    Callback *callback,*hover,*out;
    pthread_mutex_t mutexEnabled,mutexClick,mutexHover,mutexOut;
  public:
    ScreenHover();
    virtual ~ScreenHover();
    
    //! Função a ser extendida que retorna true se a coordenada passada (x,y) está dentro da região que a classe "cobre"
    virtual bool isHover(int x,int y)=0;
    
    //! Associa um Callback ao evento OnClick da região
    /**
    Esse ponteiro será apagado internamente
    */
    ScreenHover& setClickEvent(Callback* callback);
    
    //! Associa um Callback ao evento OnHover da região
    /**
    Esse ponteiro será apagado internamente
    */
    ScreenHover& setHoverEvent(Callback* callback);
    
    //! Associa um Callback ao evento OnOut da região
    /**
    Esse ponteiro será apagado internamente
    */
    ScreenHover& setOutEvent(Callback* callback);
    
    //! Processa o Callback associado ao evento OnHover
    /**
    Internamente usa a função isHover() para verificar se o mouse está sobre a região informada pela classe
    \return Se o mouse está sobre a região informada pela classe
    */
    bool mouseHover(int x,int y);
    
    //! Processa o Callback associado ao evento OnClick
    /**
    Internamente usa a função isHover() para verificar se o mouse está sobre a região informada pela classe
    \return Se o mouse está sobre a região informada pela classe
    */
    bool mouseClick(int x,int y);
    
    //! Processa o Callback associado ao evento OnOut
    /**
    Não precisa verificar se o mouse está fora da região delimitada pela classe
    */
    void mouseOut();
    
    //! Se a região delimitada pela classe deve ser usada
    /**
    Assim remove a necessidade de tirar a classe da lista ScreenHoverList toda vez que a região delimitada por esta classe não for mais usada
    */
    bool isEnabled();
    
    //! Define se a região delimitada pela classe será usada
    void setEnabled(bool value);
    
    
    //! Suspende o estado atual
    /**
    Joga o estado atual da classe numa pilha e desativa a classe: setEnabled(false)
    */
    void suspend();
    
    //! Retorna o último estado da classe
    /**
    Caso a pilha esteja vazia desativa a classe, caso contrário, usa o último estado da pilha (e o remove)
    */
    void resume();
    
    //! Limpa a pilha e atribui um novo estado
    /**
    Limpa complematamente a pilha e atribui ao estado atual, o parâmetro passado
    */
    void resetStack(bool value);
    
    //! Agenda a destruição deste objeto
    void destroy();
};

//! Elimina os ScreenHover da pilha de destruição
/**
Recomenda-se usar esta função fora de quaisquer tipo de Callback
*/
void realScreenHoverDestroy();

#endif