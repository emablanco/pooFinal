#ifndef CHATARRA_H
#define CHATARRA_H

#include "objetos.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <cstdio>
#include <string>

class Chatarra : public Objetos {
private:
  // sf::CircleShape circulo;
  sf::Sprite *ima_spr = nullptr;
  sf::Texture *ima_tex = nullptr;
  sf::Vector2f direccion;
  float velocidad;
  sf::IntRect rectangulo;
  sf::Vector2f escalar;
  std::string ruta;
  bool estado;
  const sf::Sprite &obtenerSprite() override;
  float color_alpha;
  int valor;

public:
  // RUTA,POSICION,DIRECCION,VELOCIDAD
  Chatarra(std::string, sf::Vector2f, int valor = 0);

  sf::Vector2f verPosicion() override;           // VER LA POSICION DEL SPRITE
  void moverObjeto() override;                   // MOVER EL OBJETO
  sf::FloatRect limitesObjetos() const override; // limites comprobar coliciones
  bool verEstado() override;                     // VER EL ESTADO
  void modificarEstado(bool) override;           // MODIFICAR EL ESTADO
  void modificarAlpha(float) override;           // MODIFICAR LA TRANSPARECIA
  float verAlpha() override;                     // VER EL VALOR DE ALPHA
  int verValor() override; // VER PUNTOS -> PARA USAR COMO (DAÑO, VIDA,ETC)
  void modificarValor(int) override;              // MODIFICAR LOS PUNTOS
  void modificarDireccion(sf::Vector2f) override; // SET DIRECCION DE DESTINO
  ~Chatarra();
};
#endif // !DEBUG CHATARRA_H
