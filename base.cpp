#include "base.h"
#include "nave.h"
#include "objetos.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <cmath>
#include <string>
#include <vector>
Base::Base(std::string r, sf::Texture *t)
    : ruta(r),
      ventana(new sf::RenderWindow(
          sf::VideoMode((float)t->getSize().x, (float)t->getSize().y), "Ema")) {

  // FRAME DE LA VENTANA
  ventana->setFramerateLimit(120);
  // WALLPAPERS QUE TENDRA EN MAPA DEL JUGADOR
  sf::Vector2f resolucion = sf::Vector2f(t->getSize());
  wallpapers_tex = t; // textura del wallpapers
  wallpapers_spr = new sf::Sprite;
  wallpapers_spr->setTexture(*wallpapers_tex);
  wallpapers_spr->setOrigin(resolucion.x / 2.f, resolucion.y / 2.f);
  wallpapers_spr->setPosition(0, 0);
  w_tex = new sf::Texture;
  w_spr = new sf::Sprite;
  w_tex->loadFromFile(r);
  w_spr->setOrigin(w_tex->getSize().x / 2.f, w_tex->getSize().y / 2.f);
  w_spr->setTexture(*w_tex);

  // VISOR
  visor = new sf::View;
  visor->setSize(resolucion.x, resolucion.y);
  visor->setCenter(0, 0);
  // EVENTOS
  evento1 = new sf::Event;
  // FUENTES
  fuente.loadFromFile("./fuente/Chernobyl.otf");
  fuentePuntos.loadFromFile("./fuente/HackNerdFont-BoldItalic.ttf");
  // MUSICA
  musica.openFromFile("./sonidos/fondo0.ogg");
  musica.setLoop(true);
  musica.setVolume(20);
  musica.play();
  // SONIDO PARA LOS DISPAROS
  sonidoDeSuperDisparo.loadFromFile("./sonidos/superDisparo.ogg");
  sonidoDeDisparo1.loadFromFile("./sonidos/laser.ogg");
  sonidoDeDisparo2.loadFromFile("./sonidos/disparo1.ogg");
  sonidoDeDisparo3.loadFromFile("./sonidos/disparo2.ogg");
  sonidoDeDisparo4.loadFromFile("./sonidos/disparo3.ogg");
  sonidoDeExplocion1.loadFromFile("./sonidos/explocion0.ogg");
  sonidoDeExplocion2.loadFromFile("./sonidos/explocion1.ogg");
  sonidoDeEscudo.loadFromFile("./sonidos/escudo0.ogg");
  audioDisparo1.setBuffer(sonidoDeDisparo1);
  audioDisparo2.setBuffer(sonidoDeDisparo2);
  audioDisparo3.setBuffer(sonidoDeDisparo3);
  audioDisparo4.setBuffer(sonidoDeDisparo4);
  audioSuperDisparo.setBuffer(sonidoDeSuperDisparo);
  audioExplocion1.setBuffer(sonidoDeExplocion1);
  audioExplocion2.setBuffer(sonidoDeExplocion2);
  audioEscudo.setBuffer(sonidoDeEscudo);
  // VOLUMEN DE LOS DISPAROS
  audioDisparo1.setVolume(50);
  audioDisparo2.setVolume(50);
  audioDisparo3.setVolume(50);
  audioDisparo4.setVolume(50);
  audioExplocion1.setVolume(50);
  audioExplocion2.setVolume(50);
  audioEscudo.setVolume(50);
  audioSuperDisparo.setVolume(50);

  // TEXTO MENU
  iniciar_tex.setFont(fuente);
  iniciar_tex.setCharacterSize(50);
  iniciar_tex.setString("Iniciar Juego");

  salir_tex.setFont(fuente);
  salir_tex.setCharacterSize(50);
  salir_tex.setString("Salir del Juego");

  iniciar_tex.setPosition(150, 50);
  salir_tex.setPosition(180, 100);

  // TEXTO PARA VER LA VDA
  vida_tex.setFont(fuente);
  vida_tex.setCharacterSize(50);
  vida_tex.setFillColor(sf::Color::Green);
  // TEXTO PARA VER EL ESCUDO
  escudo_tex.setFont(fuente);
  escudo_tex.setCharacterSize(50);
  escudo_tex.setFillColor(sf::Color::Blue);
  // TEXTO PARA VER EL ATAQUE ESPECIAL
  furia_tex.setFont(fuente);
  furia_tex.setCharacterSize(50);
  furia_tex.setFillColor(sf::Color::Red);
  // PUNTAJE
  puntaje_tex.setFont(fuente);
  puntaje_tex.setCharacterSize(80);
  puntaje_tex.setFillColor(sf::Color::White);
  // FIN DEL JUEGO - GAME OVER
  gameOver_tex.setFont(fuente);
  gameOver_tex.setCharacterSize(125);
  gameOver_tex.setFillColor(sf::Color::Red);
  gameOver_tex.setString("GAME OVER");
  // TEXTO PARA VER CUANTA VIDA RECIBES
  masVida_tex.setFont(fuentePuntos);
  masVida_tex.setCharacterSize(20);
  masVida_tex.setFillColor(sf::Color::Green);
  // TEXTO PARA VER CUANTO ESCUDO RECIBES
  masEscudo_tex.setFont(fuentePuntos);
  masEscudo_tex.setCharacterSize(20);
  masEscudo_tex.setFillColor(sf::Color::Blue);
  // TEXTO PARA VER CUANTOS ATAQUES ESPECIALES RECIBES
  masFuria_tex.setFont(fuentePuntos);
  masFuria_tex.setCharacterSize(30);
  masFuria_tex.setFillColor(sf::Color::Red);
  // CUANTO ESTEN EN TRUE SE MOSTRARAN EN PANTALLA
  vivo = true;
  estadoVida = false;
  estadoEscudo = false;
  estadoFuria = false;
}

// DIBUJA LOS SPRITES
bool Base::dibujar() {
  ventana->clear(sf::Color::Red);
  ventana->setView(*visor);
  ventana->draw(*wallpapers_spr);
  return ventana->isOpen();
}
bool Base::dibujar(Nave *player1) {
  ventana->clear(sf::Color::Red);
  ventana->setView(*visor);
  ventana->draw(*wallpapers_spr);
  ventana->draw(*player1);
  ventana->display();
  return ventana->isOpen();
}

bool Base::dibujarMenu() {

  ventana->clear(sf::Color::Black);
  ventana->draw(iniciar_tex);
  ventana->draw(salir_tex);
  ventana->display();
  return ventana->isOpen();
}

bool Base::estadoJuego() { return iniciarJuego; }
bool Base::dibujar(
    Nave *player, std::vector<Objetos *> &tiros, std::vector<Nave *> &naves,
    std::vector<Objetos *> &tiros2, std::vector<Objetos *> &chatarra,
    std::vector<Objetos *> &meteoros, Objetos *escudo,
    std::vector<Objetos *> &vida, std::vector<Objetos *> &defenza,
    std::vector<Objetos *> &furia, std::vector<Objetos *> &h_verde,
    std::vector<Objetos *> &h_azul, std::vector<Objetos *> &h_rojo,
    std::vector<Objetos *> &fuego, std::vector<Objetos *> &super,
    std::vector<Nave *> &superEnemigos, std::vector<Objetos *> &superDisparos,
    std::vector<Objetos *> &humo_simple) {
  ventana->clear(sf::Color::Black);
  ventana->setView(*visor);
  ventana->draw(*w_spr);
  ventana->draw(*wallpapers_spr);
  for (size_t i = 0; i < chatarra.size(); i++)
    ventana->draw(*chatarra[i]);
  for (size_t i = 0; i < tiros.size(); i++)
    ventana->draw(*tiros[i]);
  for (size_t i = 0; i < naves.size(); i++)
    ventana->draw(*naves[i]);
  for (size_t i = 0; i < tiros2.size(); i++)
    ventana->draw(*tiros2[i]);
  for (size_t i = 0; i < meteoros.size(); i++)
    ventana->draw(*meteoros[i]);
  for (size_t i = 0; i < vida.size(); i++)
    ventana->draw(*vida[i]);
  for (size_t i = 0; i < defenza.size(); i++)
    ventana->draw(*defenza[i]);
  for (size_t i = 0; i < furia.size(); i++)
    ventana->draw(*furia[i]);
  for (size_t i = 0; i < h_azul.size(); i++)
    ventana->draw(*h_azul[i]);
  for (size_t i = 0; i < h_verde.size(); i++)
    ventana->draw(*h_verde[i]);
  for (size_t i = 0; i < h_rojo.size(); i++)
    ventana->draw(*h_rojo[i]);
  for (size_t i = 0; i < fuego.size(); i++)
    ventana->draw(*fuego[i]);
  for (size_t i = 0; i < super.size(); i++)
    ventana->draw(*super[i]);
  for (size_t i = 0; i < superEnemigos.size(); i++)
    ventana->draw(*superEnemigos[i]);
  for (size_t i = 0; i < superDisparos.size(); i++)
    ventana->draw(*superDisparos[i]);
  for (size_t i = 0; i < humo_simple.size(); i++)
    ventana->draw(*humo_simple[i]);
  if (vivo) {
    ventana->draw(puntaje_tex);
    ventana->draw(vida_tex);
    ventana->draw(escudo_tex);
    ventana->draw(furia_tex);
  } else {
    ventana->draw(gameOver_tex);
    ventana->draw(puntaje_tex);
  }
  if (estadoVida)
    ventana->draw(masVida_tex);
  if (estadoFuria)
    ventana->draw(masFuria_tex);
  if (estadoEscudo)
    ventana->draw(masEscudo_tex);

  ventana->draw(*escudo);
  ventana->draw(*player);

  ventana->display();
  return ventana->isOpen();
}
// DEVUEVE EL ESTADO DE LA VENTANA

bool Base::estadoVentan() {
  while (ventana->isOpen()) {
    while (ventana->pollEvent(*evento1)) {
      if (evento1->type == sf::Event::Closed) {
        ventana->close();
      } else if (!iniciarJuego) {
        if (evento1->type == sf::Event::KeyPressed) {
          if (evento1->key.code == sf::Keyboard::Up) {
            opcionSeleccionada = (opcionSeleccionada == OpcionesMenu::Iniciar)
                                     ? OpcionesMenu::Salir
                                     : OpcionesMenu::Iniciar;
          } else if (evento1->key.code == sf::Keyboard::Down) { // seva a "exit"
            opcionSeleccionada = (opcionSeleccionada == OpcionesMenu::Iniciar)
                                     ? OpcionesMenu::Salir
                                     : OpcionesMenu::Iniciar;
          } else if (evento1->key.code == sf::Keyboard::Enter) {
            if (opcionSeleccionada == OpcionesMenu::Iniciar) {
              // comenzar el juego
              iniciarJuego = !iniciarJuego;
            } else if (opcionSeleccionada == OpcionesMenu::Salir) {
              // salir del juego
              ventana->close();
            }
          }
        }
      }
    }

    // Resaltar la opción seleccionada
    iniciar_tex.setFillColor((opcionSeleccionada == OpcionesMenu::Iniciar)
                                 ? sf::Color::Red
                                 : sf::Color::White);
    salir_tex.setFillColor((opcionSeleccionada == OpcionesMenu::Salir)
                               ? sf::Color::Red
                               : sf::Color::White);
    return ventana->isOpen();
  }
  return ventana->isOpen();
}

// MOVER VISOR
bool Base::moverVisor(const sf::Vector2f &velocidad) {
  visor->move(velocidad);
  return true;
}
// POSICION DEL MOUSE EN LA ventana
sf::Vector2f Base::posicionMouse() {
  // Mouse::getPosition -> representa la posicon del mounse en la ventana
  return sf::Vector2f(sf::Mouse::getPosition(*ventana));
}
sf::Vector2f Base::posicionSprite(const sf::Vector2f &objeto) {
  return sf::Vector2f(ventana->mapCoordsToPixel(objeto));
}

sf::Vector2f Base::direccionNormalizada(sf::Vector2f player) {
  sf::Vector2i mouse = sf::Mouse::getPosition(*ventana);
  sf::Vector2i avion = ventana->mapCoordsToPixel(player);
  sf::Vector2f dir = sf::Vector2f(mouse - avion);
  float aux1 = std::sqrt(std::pow(dir.x, 2) + std::pow(dir.y, 2));
  float aux2 = std::sqrt(std::pow(dir.x, 2) + std::pow(dir.y, 2));
  sf::Vector2f dirN = {dir.x / aux1, dir.y / aux2};
  return dirN;
}
sf::Vector2f Base::direccionNormalizada(sf::Vector2f enemigo,
                                        sf::Vector2f avion) {
  sf::Vector2f dir = sf::Vector2f(enemigo - avion);
  float aux1 = std::sqrt(std::pow(dir.x, 2) + std::pow(dir.y, 2));
  float aux2 = std::sqrt(std::pow(dir.x, 2) + std::pow(dir.y, 2));
  sf::Vector2f dirN = {dir.x / aux1, dir.y / aux2};
  return dirN;
}

sf::Vector2f Base::centroVisor() { return visor->getCenter(); }

// MODIFICAR

void Base::sonidoDisparo1() { audioDisparo1.play(); }
void Base::sonidoDisparo2() { audioDisparo2.play(); }
void Base::sonidoDisparo3() { audioDisparo3.play(); }
void Base::sonidoDisparo4() { audioDisparo3.play(); }
void Base::sonidoExplocion1() { audioExplocion1.play(); }
void Base::sonidoExplocion2() { audioExplocion2.play(); }
void Base::sonidoEscudo() { audioEscudo.play(); }
void Base::sonidoSuperDisparo() { audioSuperDisparo.play(); }

bool Base::verEstadoVida() { return estadoVida; }
bool Base::verEstadoEscudo() { return estadoEscudo; }
bool Base::verEstadoFuria() { return estadoFuria; }
void Base::actualizarMasVida(int vida) {
  if (vida > 0) {
    estadoVida = true;
    masVida_tex.setString("+" + std::to_string(vida));
  }
  if (vida == 0) {
    estadoVida = false;
  }
}
void Base::actualizarMasDefenza(int defenza) {
  if (defenza > 0) {
    estadoEscudo = true;
    masEscudo_tex.setString("+" + std::to_string(defenza));
  }
  if (defenza == 0) {
    estadoEscudo = false;
  }
}
void Base::actualizarMasFuria(int furia) {
  if (furia > 0) {
    estadoFuria = true;
    masFuria_tex.setString("+" + std::to_string(furia));
  }
  if (furia == 0) {
    estadoFuria = false;
  }
}
void Base::actualizarPosicionMasVida() {

  sf::Vector2f aux = visor->getCenter();
  masVida_tex.setPosition(sf::Vector2f(aux.x + 30, aux.y - 60));
}
void Base::actualizarPosicionMasDefenza() {

  sf::Vector2f aux = visor->getCenter();
  masEscudo_tex.setPosition(sf::Vector2f(aux.x + -70, aux.y - 40));
}
void Base::actualizarPosicionMasFuria() {
  sf::Vector2f aux = visor->getCenter();
  masFuria_tex.setPosition(sf::Vector2f(aux.x + 40, aux.y - 40));
}

void Base::actualizarVida(int vida) {
  if (vida <= 9)
    vida_tex.setString("000" + std::to_string(vida));
  else if (vida <= 99)
    vida_tex.setString("00" + std::to_string(vida));
  else if (vida <= 999)
    vida_tex.setString("0" + std::to_string(vida));
  else
    vida_tex.setString(std::to_string(vida));
}

void Base::actualizarEscudo(int escudo) {
  if (escudo <= 9)
    escudo_tex.setString("000" + std::to_string(escudo));
  else if (escudo <= 99)
    escudo_tex.setString("00" + std::to_string(escudo));
  else if (escudo <= 999)
    escudo_tex.setString("0" + std::to_string(escudo));
  else
    escudo_tex.setString(std::to_string(escudo));
}

void Base::actualizarFuria(int furia) {
  if (furia <= 9)
    furia_tex.setString("000" + std::to_string(furia));
  else if (furia <= 99)
    furia_tex.setString("00" + std::to_string(furia));
  else if (furia <= 999)
    furia_tex.setString("0" + std::to_string(furia));
  else
    furia_tex.setString(std::to_string(furia));
}

void Base::actualizarPuntos(int puntos) {
  if (puntos <= 9)
    puntaje_tex.setString("000" + std::to_string(puntos));
  else if (puntos <= 99)
    puntaje_tex.setString("00" + std::to_string(puntos));
  else if (puntos <= 999)
    puntaje_tex.setString("0" + std::to_string(puntos));
  else
    puntaje_tex.setString(std::to_string(puntos));
}

void Base::actualizarPosicionTextos() {
  this->actualizarPosicionPuntos();
  this->actualizarPosicionVida();
  this->actualizarPosicionFuria();
  this->actualizarPosicionEscudo();
  this->actualizarPosicionMasVida();
  this->actualizarPosicionMasDefenza();
  this->actualizarPosicionMasFuria();
}

void Base::actualizarPosicionPuntos() {

  sf::Vector2f centro = visor->getCenter();
  puntaje_tex.setPosition(
      sf::Vector2f(centro.x - puntaje_tex.getGlobalBounds().width / 2,
                   centro.y + ventana->getSize().y / 3.f));
}
void Base::actualizarPosicionVida() {

  sf::Vector2f aux = visor->getCenter();
  vida_tex.setPosition(sf::Vector2f(aux.x - ventana->getSize().x / 2.f,
                                    aux.y - ventana->getSize().y / 2.f));
}

void Base::actualizarPosicionEscudo() {

  sf::Vector2f aux = visor->getCenter();
  escudo_tex.setPosition(
      sf::Vector2f(aux.x - escudo_tex.getGlobalBounds().width / 2.f,
                   aux.y - ventana->getSize().y / 2.f));
}
void Base::actualizarPosicionFuria() {
  sf::Vector2f aux = visor->getCenter();
  furia_tex.setPosition(sf::Vector2f(
      aux.x + (ventana->getSize().x / 2.f - furia_tex.getGlobalBounds().width),
      aux.y - ventana->getSize().y / 2.f));
}
// POSICION EN LA VENANA - GAME OVER
void Base::actualizarPosicionGameOver() {

  sf::Vector2f centro = visor->getCenter();
  sf::Vector2f texto = sf::Vector2f(gameOver_tex.getGlobalBounds().width,
                                    gameOver_tex.getGlobalBounds().height);
  gameOver_tex.setPosition(sf::Vector2f(centro.x - texto.x / 2,
                                        centro.y - ventana->getSize().y / 3.f));
}

// posicion menu
void Base::actualizarPosicionMenu() {

  sf::Vector2f centro = sf::Vector2f(ventana->getSize());
  sf::Vector2f texto1 = sf::Vector2f(iniciar_tex.getGlobalBounds().width,
                                     iniciar_tex.getGlobalBounds().height);
  sf::Vector2f texto2 = sf::Vector2f(salir_tex.getGlobalBounds().width,
                                     salir_tex.getGlobalBounds().height);
  iniciar_tex.setPosition(
      sf::Vector2f(centro.x / 2 - texto1.x * 1.5, centro.y / 2 - 30));
  salir_tex.setPosition(
      sf::Vector2f(centro.x / 2 - texto2.x * 1.5, centro.y / 2 + 80));
}
void Base::actualizarVivo(bool estado) { vivo = estado; }

// DESTRUCTOR DE PUNTEROS

Base::~Base() {
  delete ventana;
  delete wallpapers_spr;
  delete wallpapers_tex;
  delete visor;
  delete evento1;
  delete w_tex;
  delete w_spr;
}
