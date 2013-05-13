/*
 * BombeGlacee.cpp
 *
 *  Created on: 10 mai 2013
 *      Author: Sanpas
 */

#include <moteur/bombe/BombeGlacee.hpp>
#include <moteur/objets/Bombe.hpp>
#include <moteur/Case.hpp>

BombeGlacee::BombeGlacee(Mobile* porteur, unsigned timer, unsigned puissance): Bombe(porteur, timer, puissance)
{
    get_sprite().setColor(sf::Color(37, 253, 233));
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
