#include "escudo.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

Escudo::Escudo(std::string _ruta, sf::Vector2f posicion, float vel, int val)
    : ruta(_ruta), velocidad(vel), valor(val) {
  ima_tex = new sf::Texture;
  ima_tex->loadFromFile(ruta);
  ima_spr = new sf::Sprite;
  ima_spr->setTexture(*ima_tex);
  ima_spr->setScale(0.3, 0.3);
  ima_spr->setPosition(posicion);
  color_alpha = 150;
  direccion = posicion;
  rectangulo = sf::IntRect(ima_spr->getGlobalBounds());
  ima_spr->setOrigin(ima_tex->getSize().x / 2.f, ima_tex->getSize().y / 2.f);
  estado = true;
  ima_spr->setColor(sf::Color(255, 255, 255, color_alpha));
}

sf::Vector2f Escudo::verPosicion() { return ima_spr->getPosition(); }

void Escudo::moverObjeto() {
  ima_spr->setRotation(ima_spr->getRotation() + 1);
  ima_spr->setPosition(direccion);
}

// const sf::CircleShape Escudo::obtenerDisparo() { return *ima_spr; }
const sf::Sprite &Escudo::obtenerSprite() { return *ima_spr; }

sf::FloatRect Escudo::limitesObjetos() const {
  return ima_spr->getGlobalBounds();
}
bool Escudo::verEstado() { return estado; }

void Escudo::modificarEstado(bool e) { estado = e; }

void Escudo::modificarAlpha(float a) {
  color_alpha = a;
  ima_spr->setColor(sf::Color(255, 255, 255, color_alpha));
  if (color_alpha <= 0)
    estado = false;
}

float Escudo::verAlpha() { return color_alpha; }

int Escudo::verValor() { return valor; }

void Escudo::modificarValor(int v) {
  valor = v;
  if (valor < 7000 and valor > 3000) {
    ima_spr->setColor(sf::Color(100, 255, 100, color_alpha));
  }
  if (valor <= 3000 and valor > 0) {
    ima_spr->setColor(sf::Color(100, 255, 250, color_alpha));
  }
  if (valor <= 0) {
    color_alpha = 0;
    estado = false;
    valor = 0;
    ima_spr->setColor(sf::Color(255, 100, 100, color_alpha));
  } else {
    color_alpha = 150;
    ima_spr->setColor(sf::Color(255, 100, 100, color_alpha));
    estado = true;
  }
}

void Escudo::modificarDireccion(sf::Vector2f dir) { direccion = dir; }
Escudo::~Escudo() {
  delete ima_spr;
  delete ima_tex;
}
