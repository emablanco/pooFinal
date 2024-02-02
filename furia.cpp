#include "furia.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <iostream>
#include <string>

Furia::Furia(std::string imagen, sf::Vector2f posicion, sf::Vector2f dir,
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

sf::Vector2f Furia::verPosicion() { return ima_spr->getPosition(); }
void Furia::moverObjeto() {
  ima_spr->move(direccion.x * velocidad, direccion.y * velocidad);
}

// const sf::CircleShape Furia::obtenerDisparo() { return *ima_spr; }
const sf::Sprite &Furia::obtenerSprite() { return *ima_spr; }
sf::FloatRect Furia::limitesObjetos() const {
  return ima_spr->getGlobalBounds();
}
bool Furia::verEstado() { return estado; }
void Furia::modificarEstado(bool e) { estado = e; }

void Furia::modificarAlpha(float alpha) {
  color_alpha -= alpha;
  ima_spr->setColor(sf::Color(255, 255, 255, color_alpha));
  if (color_alpha <= 0)
    estado = false;
}
float Furia::verAlpha() { return color_alpha; }

int Furia::verValor() { return valor; }
void Furia::modificarValor(int v) { valor = v; }

void Furia::modificarDireccion(sf::Vector2f dir) { direccion = dir; }
Furia::~Furia(){
	delete ima_spr;
	delete ima_tex;
}
