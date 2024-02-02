#include "avionFinal.h"
#include "nave.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <system_error>

AvionFinal::AvionFinal(std::string imagen, sf::Vector2f pos, sf::Vector2f vel,
                       int life)
    : ruta(imagen), posicion(pos), velocidad(vel), vida(life) {
  ima_tex = new sf::Texture;
  ima_tex->loadFromFile(imagen);
  ima_spr = new sf::Sprite;
  escalarImagen = {0.2, 0.2};
  rectangulo = {0, 0, (int)ima_tex->getSize().x, (int)ima_tex->getSize().y / 2};
  ima_spr->setTexture(*ima_tex);
  // ima_spr->setTextureRect(rectangulo);
  ima_spr->setScale(escalarImagen);
  ima_spr->setOrigin(rectangulo.width / 2.f, rectangulo.height / 2.f);
  ima_spr->setPosition(posicion);
  estado = true;
}

const sf::Sprite &AvionFinal::obtenerSprite() { return *ima_spr; }

const sf::Vector2f AvionFinal::posicionSprite() {
  return ima_spr->getPosition();
}

const void AvionFinal::moverImagen() { ima_spr->move(velocidad); }

const void AvionFinal::moverImagen(sf::Vector2f vel) { ima_spr->move(vel); }

void AvionFinal::cambiarVelocidad(sf::Vector2f vel) { velocidad = vel; }

sf::Vector2f AvionFinal::verVelocidad() { return velocidad; }

const bool AvionFinal::rotarImagen(const float &angulo) {
  ima_spr->setRotation(angulo);
  return true;
}

void AvionFinal::apuntar(const sf::Vector2f mousePosicion,
                         const sf::Vector2f spritePosicion) {

  ima_spr->setRotation(std::atan2(mousePosicion.y - spritePosicion.y,
                                  mousePosicion.x - spritePosicion.x) *
                       180 / 3.14);
}

float AvionFinal::obtenerRotacion() { return ima_spr->getRotation(); }

void AvionFinal::cambiarPosicion(sf::Vector2f posicion) {
  ima_spr->setPosition(posicion);
}

int AvionFinal::verVida() { return vida; }

void AvionFinal::modificarVida(int life) {
  vida = life;
  if (vida <= 0)
    estado = false;
}

void AvionFinal::seguirObjetivo(sf::Vector2f dir, sf::Vector2f enemigo,
                                sf::Vector2f tamanio) {

  ima_spr->move(dir.x * velocidad.x, dir.y * velocidad.y);

  sf::Vector2f distancia = enemigo - ima_spr->getPosition();

  float distanciaTotal =
      std::sqrt(distancia.x * distancia.x + distancia.y * distancia.y);

  float distanciaMinima = 100.0f;

  if (distanciaTotal <= distanciaMinima) {

    ima_spr->setPosition(enemigo - dir * distanciaMinima);
  }
}

sf::Vector2f AvionFinal::tamanioTextura() {
  return sf::Vector2f(ima_tex->getSize());
}

sf::FloatRect AvionFinal::limitesNave() const {
  return ima_spr->getGlobalBounds();
}

void AvionFinal::modificarEstado(bool e) { estado = e; }

bool AvionFinal::verEstado() { return estado; }

sf::Vector2f AvionFinal::tamanioSprite() {
  sf::FloatRect r = ima_spr->getGlobalBounds();
  return {r.width, r.height};
}
std::string AvionFinal::verRuta() { return ruta; }
bool AvionFinal::verBuscar() { return buscar; }
bool AvionFinal::modificarBuscar(bool b) {
  buscar = b;
  return buscar;
};

AvionFinal::~AvionFinal() {
  delete ima_spr;
  delete ima_tex;
}
