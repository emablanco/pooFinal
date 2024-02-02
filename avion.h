#ifndef AVION_H
#define AVION_H

#include "nave.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <string>

class Avion : public Nave {

private:
  sf::Sprite *ima_spr = nullptr;
  sf::Texture *ima_tex = nullptr;
  sf::IntRect rectangulo;
  sf::Vector2f escalarImagen;
  std::string ruta;
  sf::Vector2f posicion;
  sf::Vector2f velocidad;
  bool estado = false; // false = muerto; true = vivo
  bool buscar = false; // falso = no lo busca; true = lo busca
  int vida;
  const sf::Sprite &obtenerSprite() override;

public:
  Avion(std::string, sf::Vector2f posicion = {0, 0},
        sf::Vector2f velocidad = {5, 5}, int vida = 1000);
  // POSICION DEL SPRITE
  const sf::Vector2f posicionSprite() override;
  // MOVER EL SPRITE
  const void moverImagen() override;
  // MOVER EL SPRITE
  const void moverImagen(sf::Vector2f) override;
  // ROTAR EL SPRITE
  const bool rotarImagen(const float &) override;
  // APUNTAR AL OBJETIVO
  void apuntar(const sf::Vector2f, const sf::Vector2f) override;
  // VER EL ANGULO DE ROTACION
  float obtenerRotacion() override;
  // CAMBIAR LA POSICION DEL SPRITE
  void cambiarPosicion(sf::Vector2f) override;
  // CAMBIAR LA VELOCIDAD
  void cambiarVelocidad(sf::Vector2f) override;
  // VER LA VIDA ACTUAL
  int verVida() override;
  // ACTUALIZAR VIDA
  void modificarVida(int) override;
  // SEGUIR EL OBJETIVO
  void seguirObjetivo(sf::Vector2f, sf::Vector2f, sf::Vector2f) override;
  // VER LA VELOCIDAD
  sf::Vector2f verVelocidad() override;
  // TAMANIO DE LA TEXTURA
  sf::Vector2f tamanioTextura() override;
  // TAMANIO EL SPRITE
  sf::Vector2f tamanioSprite() override;
  // LIMITES DE LA NAVE PARA COMPROBAR COLICIONES
  sf::FloatRect limitesNave() const override;
  // RUTA DE LA IMAGEN
  std::string verRuta() override;
  // CAMBIAR EL ESTADO DE LA NAVE
  void modificarEstado(bool) override;
  // VER EL ESTADO DE LA NAVE
  bool verEstado() override;
  // VER EL ESTADO DE LA BUSQUEDA
  bool verBuscar() override;
  // MODIFICAR EL ESTADO DE LA BUSQUEDA
  bool modificarBuscar(bool) override;
  ~Avion();
};
#endif // !AVION_H
