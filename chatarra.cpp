#include "chatarra.h"
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

Chatarra::Chatarra(std::string _ruta, sf::Vector2f posicion, int val)
    : ruta(_ruta), valor(val) {
  ima_tex = new sf::Texture;
  ima_tex->loadFromFile(ruta);
  ima_spr = new sf::Sprite;
  ima_spr->setTexture(*ima_tex);
  ima_spr->setScale(0.3, 0.3);
  ima_spr->setPosition(posicion);
  color_alpha = 255;
  velocidad = 0;
  direccion = posicion;
  rectangulo = sf::IntRect(ima_spr->getGlobalBounds());
  ima_spr->setOrigin(rectangulo.width / 2.f, rectangulo.height / 2.f);
  ima_spr->setRotation(rand() % 360);
  estado = true;
}

sf::Vector2f Chatarra::verPosicion() { return ima_spr->getPosition(); }
void Chatarra::moverObjeto() {
  ima_spr->move(direccion.x * velocidad, direccion.y * velocidad);
}

// const sf::CircleShape Chatarra::obtenerDisparo() { return *ima_spr; }
const sf::Sprite &Chatarra::obtenerSprite() { return *ima_spr; }
sf::FloatRect Chatarra::limitesObjetos() const {
  return ima_spr->getGlobalBounds();
}
bool Chatarra::verEstado() { return estado; }
void Chatarra::modificarEstado(bool e) { estado = e; }
void Chatarra::modificarAlpha(float a) {
  color_alpha -= a;
  ima_spr->setColor(sf::Color(255, 255, 255, color_alpha));
  if (color_alpha <= 0)
    estado = false;
}

float Chatarra::verAlpha() { return color_alpha; }
int Chatarra::verValor() { return valor; }
void Chatarra::modificarValor(int v) { valor = v; }

void Chatarra::modificarDireccion(sf::Vector2f dir) { direccion = dir; }

Chatarra::~Chatarra() {
  delete ima_spr;
  delete ima_tex;
}
