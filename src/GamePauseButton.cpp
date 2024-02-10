/* Universidade Federal do Rio de Janeiro
 * Escola Polit�cnica
 * Departamento de Eletr�nica e Computa��o
 * Prof. Fernando Silva
 * EEL 670 - Linguagem de Programa��o
 *
 * Authors: Daniel Dahis     (dahisdaniel@poli.ufrj.br)
 *          Leonan Fran�a    (leonancfr@poli.ufrj.br)
 *          Gustavo Silva    (diguser@gmail.com)
 *          Michael Douglas  (michaeldouglas@poli.ufrj.br)
 */
#include "GamePauseButton.hpp"
#include "ScreenButtonCircle.hpp"
#include "ZOrder.hpp"
#include "Screen.hpp"
#include "Callback.hpp"
#include "GameControl.hpp"
#include "TextureCache.hpp"
#include "AudioManager.hpp"

namespace CrazyCrush {
namespace Game {
namespace Pause {
namespace Button {

//! Callback para exibir o menu de pausa
class CallbackGamePauseButtonClick : public Callback {
  public:
    void aProcess(){
      CrazyCrush::AudioManager::play("sfx_hit",false,"sfx_hit.ogg");
      CrazyCrush::Game::Control::pauseGame();
    };
};

ScreenButtonCircle button;

void initialize(){
  button.setDisplay(false);
  button.setLabel("Pause");
  button.setScreenPosition(10,Screen::screenHeight-160);
  button.setScreenSize(150,150);
  button.setZIndex(z_order.index_gems);
  button.setLabelOffset(-3,-20);
  button.getLabelObject().setFont(TextureCache::fontSFComic);
  button.setOnClick(new CallbackGamePauseButtonClick());
}

void show(){
  button.setDisplay(true);
}

void hide(){
  button.setDisplay(false);
}

void suspend(){
  button.suspendHover();
}

}}}}