#ifndef SUPERBALAS_H
#define SUPERBALAS_H

#include "objetos.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <cstdio>
#include <string>

class SuperBalas : public Objetos {
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
  SuperBalas(std::string, sf::Vector2f, sf::Vector2f, float velocidad = 4.f,
             int valor = 25);

  sf::Vector2f verPosicion() override;
  void moverObjeto() override;
  sf::FloatRect limitesObjetos() const override;
  bool verEstado() override;
  void modificarEstado(bool) override;
  void modificarAlpha(float) override;
  float verAlpha() override;
  int verValor() override;
  void modificarValor(int) override;
  void modificarDireccion(sf::Vector2f) override;
  ~SuperBalas();
};
#endif // !DEBUG SUPERBALAS_H
