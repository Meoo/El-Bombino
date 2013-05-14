/**
 * @file   BombeGlacee.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/Jeu.hpp>
#include <moteur/bombe/BombeGlacee.hpp>
#include <moteur/objets/Bombe.hpp>
#include <moteur/Case.hpp>

BombeGlacee::BombeGlacee(Mobile* porteur, unsigned timer, unsigned puissance): Bombe(porteur, timer, puissance)
{
    get_sprite().setTexture(Jeu::instance().get_texture("bombeglacee"),true);
}

BombeGlacee::~BombeGlacee()
{
}

void BombeGlacee::exploser()
{
    if (!est_valide()) return;

    //Faire exploser la bombe
    detruire();
    get_case()->enflammer(FEU_TIME_DEFAULT, sf::Color(37, 253, 233), &Objet::glacee);
    get_case()->enflammer_direction(nsUtil::HAUT, get_puissance(), FEU_TIME_DEFAULT, sf::Color(37, 253, 233), &Objet::glacee);
    get_case()->enflammer_direction(nsUtil::BAS, get_puissance(),  FEU_TIME_DEFAULT, sf::Color(37, 253, 233), &Objet::glacee);
    get_case()->enflammer_direction(nsUtil::GAUCHE, get_puissance(),  FEU_TIME_DEFAULT, sf::Color(37, 253, 233), &Objet::glacee);
    get_case()->enflammer_direction(nsUtil::DROITE, get_puissance(),  FEU_TIME_DEFAULT, sf::Color(37, 253, 233), &Objet::glacee);
}// exploser()



// fin implementation Class BombeGlacee
