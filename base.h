#ifndef BASE_H
#define BASE_H

#include "balas.h"
#include "chatarra.h"
#include "escudo.h"
#include "meteoro.h"
#include "nave.h"
#include "objetos.h"
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <cmath>
#include <string>
#include <vector>

// SE PUEDE HACER CON UN STRUCT
enum class OpcionesMenu { Iniciar, Salir };

class Base {

private:
  // VENTANA
  std::string ruta;
  sf::RenderWindow *ventana = nullptr;
  sf::Texture *wallpapers_tex = nullptr;
  sf::Sprite *wallpapers_spr = nullptr;
  sf::View *visor = nullptr;
  sf::Event *evento1 = nullptr;
  sf::Texture *w_tex = nullptr;
  sf::Sprite *w_spr = nullptr;

  // SONIDO Y TEXTO
  sf::Music musica;
  sf::Sound audioSuperDisparo;
  sf::Sound audioDisparo1;
  sf::Sound audioDisparo2;
  sf::Sound audioDisparo3;
  sf::Sound audioDisparo4;
  sf::Sound audioExplocion1;
  sf::Sound audioExplocion2;
  sf::Sound audioEscudo;
  sf::SoundBuffer sonidoDeDisparo1;
  sf::SoundBuffer sonidoDeDisparo2;
  sf::SoundBuffer sonidoDeDisparo3;
  sf::SoundBuffer sonidoDeDisparo4;
  sf::SoundBuffer sonidoDeExplocion1;
  sf::SoundBuffer sonidoDeExplocion2;
  sf::SoundBuffer sonidoDeSuperDisparo;
  sf::SoundBuffer sonidoDeEscudo;

  sf::Font fuente;
  sf::Font fuentePuntos;
  sf::Text iniciar_tex;
  sf::Text salir_tex;
  sf::Text vida_tex;
  sf::Text escudo_tex;
  sf::Text furia_tex;
  sf::Text puntaje_tex;
  sf::Text gameOver_tex;
  sf::Text masVida_tex;
  sf::Text masEscudo_tex;
  sf::Text masFuria_tex;
  bool vivo;
  bool estadoVida;
  bool estadoEscudo;
  bool estadoFuria;
  bool iniciarJuego = false;

  OpcionesMenu opcionSeleccionada = OpcionesMenu::Iniciar;

public:
  Base(std::string, sf::Texture *);

  // SONIDO Y TEXTO
  void sonidoDisparo1();
  void sonidoDisparo2();
  void sonidoDisparo3();
  void sonidoDisparo4();
  void sonidoSuperDisparo();
  void sonidoExplocion1();
  void sonidoExplocion2();
  void sonidoEscudo();
  bool estadoJuego();

  void actualizarPuntos(int);
  void actualizarVida(int);
  void actualizarEscudo(int);
  void actualizarFuria(int);
  void actualizarPosicionTextos();
  void actualizarPosicionPuntos();
  void actualizarPosicionVida();
  void actualizarPosicionEscudo();
  void actualizarPosicionFuria();
  void actualizarPosicionGameOver();
  void actualizarVivo(bool);
  void actualizarMasVida(int);
  void actualizarMasDefenza(int);
  void actualizarMasFuria(int);
  void actualizarPosicionMasFuria();
  void actualizarPosicionMasDefenza();
  void actualizarPosicionMasVida();
  void actualizarPosicionMenu();
  bool verEstadoVida();
  bool verEstadoEscudo();
  bool verEstadoFuria();
  // DIBUJAR
  bool dibujar();
  bool dibujarMenu();
  // DIBIJAR PLAYER
  bool dibujar(Nave *);
  bool dibujar(Nave *, std::vector<Objetos *> &, std::vector<Nave *> &,
               std::vector<Objetos *> &, std::vector<Objetos *> &,
               std::vector<Objetos *> &, Objetos *, std::vector<Objetos *> &,
               std::vector<Objetos *> &, std::vector<Objetos *> &,
               std::vector<Objetos *> &, std::vector<Objetos *> &,
               std::vector<Objetos *> &, std::vector<Objetos *> &,
               std::vector<Objetos *> &, std::vector<Nave *> &,
               std::vector<Objetos *> &, std::vector<Objetos *> &);
  // VER ESTADO VENTANA
  bool estadoVentan();
  // MOVER VISOR
  bool moverVisor(const sf::Vector2f &);
  // POSICION MOUSE
  sf::Vector2f posicionMouse();
  // POSICION SPRITE VENTANA
  sf::Vector2f posicionSprite(const sf::Vector2f &);
  const sf::Vector2f verResolucion();
  // VER EVENTO

  sf::Vector2f direccionNormalizada(sf::Vector2f);
  sf::Vector2f direccionNormalizada(sf::Vector2f, sf::Vector2f);
  sf::Vector2f centroVisor();
  ~Base();
};

#endif // !BASE_H
