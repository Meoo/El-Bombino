/**
 * @file   Usine.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/Usine.hpp>
#include <moteur/Jeu.hpp>
#include <moteur/exceptions/ExceptionRessource.hpp>

#include <moteur/Case.hpp>
#include <moteur/case/Mur.hpp>
#include <moteur/case/CaisseInfini.hpp>
#include <moteur/case/Vide.hpp>

#include <moteur/Objet.hpp>
#include <moteur/objets/Joueur.hpp>
#include <moteur/objets/Caisse.hpp>

#include <monde1/pnjs/Idiot.hpp>

namespace Usine
{
    Case * creer_case(const std::string & classe_case, unsigned x, unsigned y, const std::string & texture_case)
    {
        if (classe_case.compare("Sol") == 0)
            return new Case(x, y, Jeu::instance().get_texture(texture_case));

        if (classe_case.compare("Mur") == 0)
            return new Mur(x, y, Jeu::instance().get_texture(texture_case));

        if (classe_case.compare("CaisseInfini") == 0)
            return new CaisseInfini(x, y, Jeu::instance().get_texture(texture_case));

        if (classe_case.compare("Vide") == 0)
            return new Vide(x,y,Jeu::instance().get_texture(texture_case));
        throw ExceptionRessource(classe_case, "Classe de Case invalide");
    }

    Objet * creer_objet(const std::string & classe_objet, Case * cse)
    {
        if (classe_objet.compare("Caisse") == 0)
            return new Caisse(cse);

        if (classe_objet.compare("Joueur") == 0)
            return new Joueur(cse);

        if (classe_objet.compare("Idiot") == 0)
            return new Idiot(cse);

        throw ExceptionRessource(classe_objet, "Classe d'Objet invalide");
    }
}
