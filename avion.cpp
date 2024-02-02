#include "avion.h"
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

Avion::Avion(std::string imagen, sf::Vector2f pos, sf::Vector2f vel, int life)
    : ruta(imagen), posicion(pos), velocidad(vel), vida(life),
      escalarImagen(0.3, 0.3) {
  ima_tex = new sf::Texture;
  ima_tex->loadFromFile(imagen);
  ima_spr = new sf::Sprite;
  rectangulo = {0, 0, (int)ima_tex->getSize().x, (int)ima_tex->getSize().y / 2};
  ima_spr->setTexture(*ima_tex);
  ima_spr->setTextureRect(rectangulo);
  ima_spr->setScale(escalarImagen);
  ima_spr->setOrigin(rectangulo.width / 2.f, rectangulo.height / 2.f);
  ima_spr->setPosition(posicion);
  estado = true;
}

const sf::Sprite &Avion::obtenerSprite() { return *ima_spr; }

const sf::Vector2f Avion::posicionSprite() { return ima_spr->getPosition(); }

const void Avion::moverImagen() { ima_spr->move(velocidad); }

const void Avion::moverImagen(sf::Vector2f vel) { ima_spr->move(vel); }

void Avion::cambiarVelocidad(sf::Vector2f vel) { velocidad = vel; }

sf::Vector2f Avion::verVelocidad() { return velocidad; }

const bool Avion::rotarImagen(const float &angulo) {
  ima_spr->setRotation(angulo);
  return true;
}

void Avion::apuntar(const sf::Vector2f mousePosicion,
                    const sf::Vector2f spritePosicion) {

  ima_spr->setRotation(std::atan2(mousePosicion.y - spritePosicion.y,
                                  mousePosicion.x - spritePosicion.x) *
                       180 / 3.14);
}

float Avion::obtenerRotacion() { return ima_spr->getRotation(); }

void Avion::cambiarPosicion(sf::Vector2f posicion) {
  ima_spr->setPosition(posicion);
}

int Avion::verVida() { return vida; }

void Avion::modificarVida(int life) {
  vida = life;
  if (vida <= 0)
    estado = false;
}

void Avion::seguirObjetivo(sf::Vector2f dir, sf::Vector2f enemigo,
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

sf::Vector2f Avion::tamanioTextura() {
  return sf::Vector2f(ima_tex->getSize());
}

sf::FloatRect Avion::limitesNave() const { return ima_spr->getGlobalBounds(); }

void Avion::modificarEstado(bool e) { estado = e; }

bool Avion::verEstado() { return estado; }

sf::Vector2f Avion::tamanioSprite() {
  sf::FloatRect r = ima_spr->getGlobalBounds();
  return {r.width, r.height};
}
std::string Avion::verRuta() { return ruta; }
bool Avion::verBuscar() { return buscar; }
bool Avion::modificarBuscar(bool b) {
  buscar = b;
  return buscar;
};

Avion::~Avion() {
  delete ima_spr;
  delete ima_tex;
}
