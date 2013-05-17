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
#include <moteur/objets/CaissePiege.hpp>

#include <monde1/pnjs/Idiot.hpp>
#include <monde2/pnjs/CactusMaxi.hpp>
#include <monde2/pnjs/CactusMini.hpp>
#include <monde3/pnjs/CaisseSurvie.hpp>
#include <monde2/pnjs/Tequilla.hpp>
#include <monde2/pnjs/Invisible.hpp>
#include <monde2/pnjs/CactusSuper.hpp>

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
    }// creer_case()


    Objet * creer_objet(const std::string & classe_objet, Case * cse)
    {
        if (classe_objet.compare("Caisse") == 0)
            return new Caisse(cse);

        if (classe_objet.compare("CaissePiege") == 0)
            return new CaissePiege(cse);

        if (classe_objet.compare("Joueur") == 0)
            return new Joueur(cse);

        if (classe_objet.compare("Idiot") == 0)
            return new Idiot(cse);

        if (classe_objet.compare("CactusMaxi") == 0)
            return new CactusMaxi(cse);

        if (classe_objet.compare("CactusMini") == 0)
            return new CactusMini(cse);

        if (classe_objet.compare("CaisseSurvie") == 0)
            return new CaisseSurvie(cse);

        if (classe_objet.compare("Tequilla") == 0)
            return new Tequilla(cse);

        if (classe_objet.compare("Invisible") == 0)
            return new Invisible(cse);

        if (classe_objet.compare("Porteur") == 0)
            return new CactusSuper(cse);

        throw ExceptionRessource(classe_objet, "Classe d'Objet invalide");
    }// creer_objet()
}
