/**
 * @file   Idiot.cpp
 * @author Bastien Brunnenstein
 */

#include <monde1/pnjs/Idiot.hpp>

#include <moteur/Jeu.hpp>

Idiot::Idiot(Case * cse) : MobileIA(cse, 1.f, 2, Jeu::instance().get_texture("idiot"))
{
}

Idiot::~Idiot()
{
}

void Idiot::mise_a_jour_ia()
{
    switch(rand() % 4)
    {
    case 0:
        bouger(HAUT);
        break;
    case 1:
        bouger(BAS);
        break;
    case 2:
        bouger(GAUCHE);
        break;
    case 3:
        bouger(DROITE);
        break;
    }
}
