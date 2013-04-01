/**
 * @file   Config.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _CONFIG_HPP_
#define _CONFIG_HPP_

#include <string>

// Fenêtre principale
const std::string   WINDOW_NAME         ("El Bombino");
const unsigned      WINDOW_WIDTH        = 960;
const unsigned      WINDOW_HEIGHT       = 720;
const unsigned      WINDOW_FRAMERATE    = 50;               //!< Affichages par seconde

// Taille d'une tuile (Case carrée du jeu)
const unsigned      TILE_SIZE           = 48;

// Flammes
const unsigned      FIRE_DEFAULT_TIME   = 25;               //!< En nombre d'affichages
const sf::Color     FIRE_DEFAULT_COLOR  (0xFF, 0x33, 0x00); //!< Rouge légèrement orangé

#endif // _CONFIG_HPP_
