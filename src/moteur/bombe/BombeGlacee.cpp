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
}

BombeGlacee::~BombeGlacee()
{
}

void BombeGlacee::exploser()
{
    if (!est_valide()) return;

    //Faire exploser la bombe
    detruire();
    get_case()->enflammer();
    get_case()->enflammer_direction(Case::HAUT, get_puissance(), FEU_TIME_DEFAULT, sf::Color::Blue, &Objet::glacee);
    get_case()->enflammer_direction(Case::BAS, get_puissance(),  FEU_TIME_DEFAULT, sf::Color::Blue, &Objet::glacee);
    get_case()->enflammer_direction(Case::GAUCHE, get_puissance(),  FEU_TIME_DEFAULT, sf::Color::Blue, &Objet::glacee);
    get_case()->enflammer_direction(Case::DROITE, get_puissance(),  FEU_TIME_DEFAULT, sf::Color::Blue, &Objet::glacee);
}
