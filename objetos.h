#ifndef OBJETOS_H
#define OBJETOS_H

#include "coliciones.h"
#include <SFML/Audio.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <string>
class Objetos : public sf::Drawable, public Coliciones {
private:
  //  sf::CircleShape circulo;
  //  virtual const sf::CircleShape obtenerDisparo() = 0;
  virtual const sf::Sprite &obtenerSprite() = 0;
  virtual sf::FloatRect limitesObjetos() const = 0;
  sf::Sprite spr;

public:
  Objetos();
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  void updateSprite(); // cargara el sprite en la variable spr para ser dibujada
  sf::FloatRect obtenerLimites() const override; // limites comprobar coliciones
  // METODOS VIRTUALES
  virtual sf::Vector2f verPosicion() = 0; // VER LA POSICION DEL SPRITE
  virtual void moverObjeto() = 0;         // MOVER EL OBJETO
  virtual bool verEstado() = 0;           // VER EL ESTADO
  virtual void modificarEstado(bool) = 0; // MODIFICAR EL ESTADO
  virtual void modificarAlpha(float) = 0; // MODIFICAR LA TRANSPARECIA
  virtual float verAlpha() = 0;           // VER EL VALOR DE ALPHA
  virtual int verValor() = 0; // VER PUNTOS -> PARA USAR COMO (DAÑO, VIDA,ETC)
  virtual void modificarValor(int) = 0;              // MODIFICAR LOS PUNTOS
  virtual void modificarDireccion(sf::Vector2f) = 0; // SET DIRECCION DE DESTINO
};
#endif // !DEBUG OBJETOS_H
