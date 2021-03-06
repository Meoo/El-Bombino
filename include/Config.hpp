/**
 * @file   Config.hpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
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
const unsigned      WINDOW_FRAMERATE    = 60;               //!< Affichages par seconde

// Taille d'une tuile (Case carrée du jeu)
const unsigned      TILE_SIZE           = 48;

// Flammes
const unsigned      FEU_TIME_DEFAULT    = 20;               //!< En nombre d'affichages
const sf::Color     FEU_COLOR_DEFAULT  (254, 75, 0, 200);   //!< Rouge légèrement orangé

// Bombe
// > Timer
const unsigned      BOMBE_TIMER_DEFAULT = 120;              //!< En nombre d'affichages
const unsigned      BOMBE_TIMER_MAX     = 160;
const unsigned      BOMBE_TIMER_MIN     = 80;
const unsigned      BOMBE_COOLDOWN      = 10;               //!< Pour éviter de poser sur 2 cases sans le faire exprès
const unsigned      BOMBE_POWER_DEFAULT = 2;
const unsigned      BOMBE_POWER_MIN     = 1;
const unsigned      BOMBE_POWER_MAX     = 10;
const unsigned      BOMBE_POWER_DELTA   = 1;

const float         BOMBE_GLACEE_DELTA  = 0.4;

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
const float         JOUEUR_VIT_DELTA    = 0.2;              //!< Variation lorsque le joueur prend un bonus ou malus
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
const unsigned      BONUS_TIMER                         = 360;


// IA
const unsigned      IA_PROTECTION       = 50;               //!< Temps de protection d'une IA lorsqu'elle est touchée

const float      IA_VIT_DELTA        = 0.2;
const float      IA_VIT_MAX          = 2;
const float      IA_VIT_MIN          = 1;
const float      IA_VIT_DEFAULT      = 1;

// Idiot
const unsigned      IDIOT_VIE_DEFAULT           = 1;
const unsigned      IDIOT_VIE_DELTA             = 1;
const unsigned      IDIOT_VIE_MAX               = 2;
const unsigned      IDIOT_VIE_MIN               = 1;
const unsigned      IDIOT_PUISSANCE_DEFAULT     = 1;
const unsigned      IDIOT_PUISSANCE_DELTA       = 1;
const unsigned      IDIOT_PUISSANCE_MIN         = 1;
const unsigned      IDIOT_PUISSANCE_MAX         = 2;
const unsigned      IDIOT_VISIBILITE_DEFAULT    = 3;
const unsigned      IDIOT_COLDOWN_ATT           = 250;
const unsigned      IDIOT_COLDOWN_ATT_RAND      = 250;


// Ressources
const std::string   RC_FOLDER           ("rc/");
const std::string   RC_JEU              ("jeu.txt");
const std::string   RC_ICON             ("icon.png");
const std::string   RC_FONDMENU         ("menu.png");
const std::string   RC_SAUVGARDE        ("sauvegarde.txt");

// Commande du jeu
const sf::Keyboard::Key   CMD_HAUT_DEFAULT        = sf::Keyboard::Up;
const sf::Keyboard::Key   CMD_BAS_DEFAULT         = sf::Keyboard::Down;
const sf::Keyboard::Key   CMD_DROITE_DEFAULT      = sf::Keyboard::Right;
const sf::Keyboard::Key   CMD_GAUCHE_DEFAULT      = sf::Keyboard::Left;
const sf::Keyboard::Key   CMD_BOMBE_DEFAULT       = sf::Keyboard::Space;
const sf::Keyboard::Key   CMD_SPECIA_DEFAULTL     = sf::Keyboard::E;

// Debug
#ifdef NDEBUG
#   define LOG(x) ;
#else
#   include <iostream>
#   define LOG(x) std::cout << ( x ) << std::endl;

extern bool                DEBUG_ALGO;
#endif

// fichier config
#endif // _CONFIG_HPP_
