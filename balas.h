#ifndef BALAS_H
#define BALAS_H

#include "objetos.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <cstdio>
#include <string>

class Balas : public Objetos {
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
  const sf::Sprite &obtenerSprite() override; // sprite para dibujar
  float color_alpha;
  int valor;

public:
  // RUTA,POSICION,DIRECCION,VELOCIDAD
  Balas(std::string, sf::Vector2f, sf::Vector2f, float velocidad = 4.f,
        int valor = 25);

  sf::Vector2f verPosicion() override;           // POSICION DEL SPRITE
  void moverObjeto() override;                   // MOVER SPRITE
  sf::FloatRect limitesObjetos() const override; // PARA COMPROBAR COLICIONES
  bool verEstado() override;                     // VER EL ESTADO
  void modificarEstado(bool) override;           // MODIFICAR EL ESTADO
  void modificarAlpha(float) override;           // MODIFICAR LA TRANSPARENCIA
  float verAlpha() override;                     // VER EL VALOR DE ALPHA
  int verValor() override;           // VER EL VALOR (DANIO,VIDA,ETC)
  void modificarValor(int) override; // ACTUALIZAR VALOR
  void modificarDireccion(sf::Vector2f) override; // MODIFICAR LA DIRECCION
  ~Balas();
};
#endif // !DEBUG BALAS_H
