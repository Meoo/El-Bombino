/**
 * @file   Config.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _CONFIG_HPP_
#define _CONFIG_HPP_

#include <SFML/Graphics/Color.hpp>

#include <string>
#include <cassert>

// Fenêtre principale
const std::string   WINDOW_NAME         ("El Bombino");
const unsigned      WINDOW_WIDTH        = 960;
const unsigned      WINDOW_HEIGHT       = 720;
const unsigned      WINDOW_FRAMERATE    = 50;               //!< Affichages par seconde

// Taille d'une tuile (Case carrée du jeu)
const unsigned      TILE_SIZE           = 48;

// Flammes
const unsigned      FEU_TIME_DEFAULT    = 25;               //!< En nombre d'affichages
const sf::Color     FEU_COLOR_DEFAULT  (0xFF, 0xCC, 0xBB); //!< Rouge légèrement orangé

// Bombe
// > Timer
const unsigned      BOMBE_TIMER_DEFAULT = 100;              //!< En nombre d'affichages
const unsigned      BOMBE_TIMER_MAX     = 200;              //!< En nombre d'affichages
const unsigned      BOMBE_TIMER_MIN     = 50;               //!< En nombre d'affichages

// Joueur
// > Vitesse
const float         JOUEUR_VIT_DEFAULT  = 3;               //!< En pixels par affichage
const float         JOUEUR_VIT_MIN      = 2;
const float         JOUEUR_VIT_MAX      = 4;
const float         JOUEUR_VIT_DELTA    = 0.5;              //!< Variation lorsque le joueur prend un bonus ou malus

// Ressources
const std::string   RC_FOLDER           ("rc/");
const std::string   RC_JEU              ("jeu.txt");

// Debug
#ifdef NDEBUG
#   define LOG(x) ;
#else
#   include <iostream>
#   define LOG(x) std::cout << ( x ) << std::endl;
#endif

#endif // _CONFIG_HPP_
