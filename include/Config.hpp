/**
 * @file   Config.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _CONFIG_HPP_
#define _CONFIG_HPP_

#include <SFML/Graphics/Color.hpp>
#include <SFML/Window.hpp>

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
const sf::Color     FEU_COLOR_DEFAULT  (0xFF, 0xCC, 0xBB);  //!< Rouge légèrement orangé

// Bombe
// > Timer
const unsigned      BOMBE_TIMER_DEFAULT = 100;              //!< En nombre d'affichages
const unsigned      BOMBE_TIMER_MAX     = 200;
const unsigned      BOMBE_TIMER_MIN     = 50;
const unsigned      BOMBE_COOLDOWN      = 10;               //!< Pour éviter de poser sur 2 cases sans le faire exprès
const unsigned      BOMBE_POWER_DEFAULT = 2;
const unsigned      BOMBE_POWER_MIN     = 1;
const unsigned      BOMBE_POWER_MAX     = 10;
const unsigned      BOMBE_POWER_DELTA   = 1;

// Objet souleve
// > Timer
const unsigned      OBJET_SOULEVE_COOLDOWN  = 10;

// CaisseInfini
// > Timer
const unsigned      CAISSEINFINI_COLDOWN    = 250;

// Joueur
// > Vitesse
const float         JOUEUR_VIT_DEFAULT  = 3;                //!< En pixels par affichage
const float         JOUEUR_VIT_MIN      = 2;
const float         JOUEUR_VIT_MAX      = 4;
const float         JOUEUR_VIT_DELTA    = 0.5;              //!< Variation lorsque le joueur prend un bonus ou malus
const unsigned      JOUEUR_NB_BOMBES_DEFAULT    = 2;
const unsigned      JOUEUR_NB_BOMBES_DELTA      = 1;
const unsigned      JOUEUR_NB_BOMBES_MIN        = 1;
const unsigned      JOUEUR_NB_BOMBES_MAX        = 10;
const unsigned      JOUEUR_VIE_DEFAULT          = 2;
const unsigned      JOUEUR_VIE_DELTA            = 1;


//Bonus
const unsigned      BONUS_NB_DIFFERENTS_PNJ             = 2; //!< Nombres de bonus differents que peut faire apparaitre un pnj.
const unsigned      BONUS_NB_DIFFERENTS_CAISSE          = 7; //!< Nombres de bonus differents que peut faire apparaitre les caisses
const unsigned      BONUS_BONUS_NB_DIFFERENTS_CAISSE    = 4; //!< Nombres de bonus (bonus) differents que peut faire apparaitre les caisses
const unsigned      BONUS_MALUS_NB_DIFFERENTS_CAISSE    = 3; //!< Nombres de bonus (malus) differents que peut faire apparaitre les caisses
const unsigned      BONUS_TIMER                         = 250;


// IA
const unsigned      IA_PROTECTION       = 50;               //!< Temps de protection d'une IA lorsqu'elle est touchée


// Idiot
const unsigned      IDIOT_PUISSANCE_DEFAULT     = 2;
const unsigned      IDIOT_PUISSANCE_DELTA       = 1;
const unsigned      IDIOT_PUISSANCE_MIN         = 1;
const unsigned      IDIOT_PUISSANCE_MAX         = 4;
const unsigned      IDIOT_VISIBILITE_DEFAULT    = 3;
const unsigned      IDIOT_COLDOWN_ATT           = 25;


// Ressources
const std::string   RC_FOLDER           ("rc/");
const std::string   RC_JEU              ("jeu.txt");
const std::string   RC_ICON             ("icon.png");


// Commande du jeu



// Debug
#ifdef NDEBUG
#   define LOG(x) ;
#else
#   include <iostream>
#   define LOG(x) std::cout << ( x ) << std::endl;
#endif

#endif // _CONFIG_HPP_
