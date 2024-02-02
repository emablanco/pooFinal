#include "vida.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <iostream>
#include <string>

Vida::Vida(std::string imagen, sf::Vector2f posicion, sf::Vector2f dir,
           float vel, int val)
    : direccion(dir), velocidad(vel), ruta(imagen), estado(true), valor(val) {
  ima_tex = new sf::Texture;
  ima_tex->loadFromFile(ruta);
  ima_spr = new sf::Sprite;
  ima_spr->setTexture(*ima_tex);
  // sf::Vector2i aux = sf::Vector2i(ima_tex->getSize());
  // rectangulo = {0, aux.y / 2, aux.x, aux.y / 2};
  // ima_spr->setTextureRect(rectangulo);
  escalar = {0.3, 0.3};
  ima_spr->setScale(escalar);
  ima_spr->setPosition(posicion);
  // ima_spr->setOrigin((rectangulo.width - rectangulo.width * 2),
  // rectangulo.height / 2.f + rectangulo.height / 3.f);
  ima_spr->setRotation(std::atan2(direccion.y, direccion.x) * 180 / M_PI);

  // std::cout << ima_spr->getRotation() << "\n";
}

sf::Vector2f Vida::verPosicion() { return ima_spr->getPosition(); }
void Vida::moverObjeto() {
  ima_spr->move(direccion.x * velocidad, direccion.y * velocidad);
}

// const sf::CircleShape Vida::obtenerDisparo() { return *ima_spr; }
const sf::Sprite &Vida::obtenerSprite() { return *ima_spr; }
sf::FloatRect Vida::limitesObjetos() const {
  return ima_spr->getGlobalBounds();
}
bool Vida::verEstado() { return estado; }
void Vida::modificarEstado(bool e) { estado = e; }

void Vida::modificarAlpha(float alpha) {
  color_alpha -= alpha;
  ima_spr->setColor(sf::Color(255, 255, 255, color_alpha));
  if (color_alpha <= 0)
    estado = false;
}
float Vida::verAlpha() { return color_alpha; }

int Vida::verValor() { return valor; }
void Vida::modificarValor(int v) { valor = v; }

void Vida::modificarDireccion(sf::Vector2f dir) { direccion = dir; }

Vida::~Vida(){
delete ima_spr;
delete ima_tex;
}
