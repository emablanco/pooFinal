#include "balasFuria.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <iostream>
#include <string>

BalasFuria::BalasFuria(std::string imagen, sf::Vector2f posicion,
                       sf::Vector2f _direccion, float vel, int val)
    : direccion(_direccion), velocidad(vel), ruta(imagen), estado(true),
      valor(val) {
  ima_tex = new sf::Texture;
  ima_tex->loadFromFile(ruta);
  ima_spr = new sf::Sprite;
  ima_spr->setTexture(*ima_tex);
  //  sf::Vector2i aux = sf::Vector2i(ima_tex->getSize());
  // rectangulo = {0, aux.y / 2, aux.x, aux.y / 2};
  // ima_spr->setTextureRect(rectangulo);
  ima_spr->setOrigin(ima_tex->getSize().x / 2.f, ima_tex->getSize().y / 2.f);
  escalar = {0.3, 0.3};
  ima_spr->setScale(escalar);
  ima_spr->setPosition(posicion);
  ima_spr->setRotation(std::atan2(direccion.y, direccion.x) * 180 / M_PI);
}

sf::Vector2f BalasFuria::verPosicion() { return ima_spr->getPosition(); }
void BalasFuria::moverObjeto() {
  ima_spr->setRotation(ima_spr->getRotation() + 10);
  ima_spr->move(direccion.x * velocidad, direccion.y * velocidad);
}

// const sf::CircleShape BalasFuria::obtenerDisparo() { return *ima_spr; }
const sf::Sprite &BalasFuria::obtenerSprite() { return *ima_spr; }
sf::FloatRect BalasFuria::limitesObjetos() const {
  return ima_spr->getGlobalBounds();
}
bool BalasFuria::verEstado() { return estado; }
void BalasFuria::modificarEstado(bool e) { estado = e; }

void BalasFuria::modificarAlpha(float alpha) {
  color_alpha -= alpha;
  ima_spr->setColor(sf::Color(255, 255, 255, color_alpha));
  if (color_alpha <= 0)
    estado = false;
}
float BalasFuria::verAlpha() { return color_alpha; }

int BalasFuria::verValor() { return valor; }
void BalasFuria::modificarValor(int v) { valor = v; }

void BalasFuria::modificarDireccion(sf::Vector2f dir) { direccion = dir; }

BalasFuria::~BalasFuria() {
  delete ima_spr;
  delete ima_tex;
}
