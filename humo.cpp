#include "humo.h"
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

Humo::Humo(std::string _ruta, sf::Vector2f posicion, int val)
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

sf::Vector2f Humo::verPosicion() { return ima_spr->getPosition(); }
void Humo::moverObjeto() {
  ima_spr->move(direccion.x * velocidad, direccion.y * velocidad);
}

// const sf::CircleShape Humo::obtenerDisparo() { return *ima_spr; }
const sf::Sprite &Humo::obtenerSprite() { return *ima_spr; }
sf::FloatRect Humo::limitesObjetos() const {
  return ima_spr->getGlobalBounds();
}
bool Humo::verEstado() { return estado; }
void Humo::modificarEstado(bool e) { estado = e; }
void Humo::modificarAlpha(float a) {
  color_alpha -= a;
  ima_spr->setColor(sf::Color(255, 255, 255, color_alpha));
  if (color_alpha <= 0)
    estado = false;
}

float Humo::verAlpha() { return color_alpha; }
int Humo::verValor() { return valor; }
void Humo::modificarValor(int v) { valor = v; }

void Humo::modificarDireccion(sf::Vector2f dir) { direccion = dir; }
Humo::~Humo(){
	delete ima_spr;
	delete ima_tex;
}
