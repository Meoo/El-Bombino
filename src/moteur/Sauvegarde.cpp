/*
 * Sauvegarde.cpp
 *
 *  Created on: 9 mai 2013
 *      Author: Sanpas
 */

#include <moteur/Sauvegarde.hpp>
#include <moteur/Jeu.hpp>
#include <moteur/Monde.hpp>
#include <moteur/Niveau.hpp>
#include <moteur/exceptions/ExceptionRessource.hpp>

#include <fstream>


Sauvegarde::Sauvegarde()
{
}

Sauvegarde::~Sauvegarde()
{
}

void Sauvegarde::charger_sauvegarde()
{
    std::fstream fic((RC_FOLDER + RC_SAUVGARDE).c_str(), std::ios_base::in);
    if (!fic)
        throw ExceptionRessource(RC_SAUVGARDE,
                "Impossible d'ouvrir le fichier de sauvegarde");

    fic.exceptions(std::ios_base::failbit | std::ios_base::badbit);
    fic >> std::skipws;

    std::string clef;

    int mode;

    int monde;
    int niveau;
    // Lire jusqu'à EOF
    LOG(std::string("Chargement du fichier de sauvegarde : ") + RC_SAUVGARDE);
    do
    {
        fic >> clef;
        if (clef == "MONDE")
            mode = 1;
        else if (clef == "NIVEAU")
            mode = 2;
        else
        {
            switch (mode)
            {
            case 1: // MONDES
                LOG(std::string("Monde : ") + clef);

                monde = atoi(clef.c_str());
                break;

            case 2: // TEXTURES
                LOG(std::string("Niveau : ") + clef);

                niveau = atoi(clef.c_str());
                break;

            default: // ERREUR
                throw ExceptionRessource(RC_JEU,
                        "Le fichier est mal formé (pas de mode)");
            }
        }
        fic >> std::ws;
    }
    while (!fic.eof());
    LOG("");

    fic.close();

    Jeu::instance().set_monde_courant(monde);
    Jeu::instance().get_monde_courant().set_niveau_courant(niveau);
}

void Sauvegarde::sauver_sauvegarde()
{
}
