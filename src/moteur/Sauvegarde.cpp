/**
 * @file   Sauvegarde.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
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

    int mode = 0;

    int         monde       = 0;
    int         niveau      = 0;
    float       vitesse     = JOUEUR_VIT_DEFAULT;
    unsigned    puissance = BOMBE_POWER_DEFAULT;
    unsigned    nb_bombe  = JOUEUR_NB_BOMBES_DEFAULT;
    unsigned    vies      = JOUEUR_VIE_DEFAULT;
    bool        bonus_bombe         = false;
    bool        bonus_soulevable    = false;
    // Lire jusqu'à EOF
    LOG(std::string("Chargement du fichier de sauvegarde : ") + RC_SAUVGARDE);
    do
    {
        fic >> clef;
        if (clef == "MONDE")
            mode = 1;
        else if (clef == "NIVEAU")
            mode = 2;
        else if (clef == "BOMBE")
            mode = 3;
        else if (clef == "PUISSANCE")
            mode = 4;
        else if (clef == "VITESSE")
            mode = 5;
        else if (clef == "VIES")
            mode = 6;
        else if (clef == "BONUS_BOMBE")
            mode = 7;
        else if (clef == "BONUS_SOULEVABLE")
            mode = 8;
        else
        {
            switch (mode)
            {
            case 1: // MONDE
                LOG(std::string("Monde : ") + clef);

                monde = atoi(clef.c_str());
                break;

            case 2: // NIVEAU
                LOG(std::string("Niveau : ") + clef);

                niveau = atoi(clef.c_str());
                break;

            case 3: // BOMBE
                LOG(std::string("Bombe : ") + clef);

                nb_bombe = atoi(clef.c_str());
                break;

            case 4: // PUISSANCE
                LOG(std::string("Puissance : ") + clef);

                puissance = atoi(clef.c_str());
                break;

            case 5: // VITESSE
                LOG(std::string("Vitesse : ") + clef);

                vitesse = atof(clef.c_str());
                break;

            case 6: // VIE
                LOG(std::string("Vie : ") + clef);

                vies = atoi(clef.c_str());
                break;

            case 7: // BONUS_BOMBE
                LOG(std::string("Bonus bombe : ") + clef);

                bonus_bombe = atoi(clef.c_str());
                break;

            case 8: // BONUS_SOULEVABLE
                LOG(std::string("Bonus soulevable : ") + clef);

                bonus_soulevable = atoi(clef.c_str());
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

    Jeu::instance().charger_donnees_joueur(vitesse, nb_bombe, puissance, vies, bonus_soulevable, bonus_bombe);
    Jeu::instance().set_monde_courant(monde);
    Jeu::instance().get_monde_courant().set_niveau_courant(niveau);
}// charger_sauvegarde()


void Sauvegarde::sauver_sauvegarde()
{
    std::fstream fic((RC_FOLDER + RC_SAUVGARDE).c_str(), std::ios_base::out);
    if (!fic)
        throw ExceptionRessource(RC_SAUVGARDE,
                "Impossible d'ouvrir le fichier de sauvegarde");

    fic.exceptions(std::ios_base::failbit | std::ios_base::badbit);

    fic << "MONDE" << std::endl;
    fic << Jeu::instance().get_num_monde_courant() << std::endl;
    fic << "NIVEAU" << std::endl;
    fic << Jeu::instance().get_monde_courant().get_num_niveau_courant() << std::endl;
    fic << "BOMBE" << std::endl;
    fic << Jeu::instance().get_nb_bombe_joueur() << std::endl;
    fic << "PUISSANCE" << std::endl;
    fic << Jeu::instance().get_puissance_joueur() << std::endl;
    fic << "VITESSE" << std::endl;
    fic << Jeu::instance().get_vitesse_joueur() << std::endl;
    fic << "VIES" << std::endl;
    fic << Jeu::instance().get_vie_joueur() << std::endl;
    fic << "BONUS_SOULEVABLE" << std::endl;
    fic << Jeu::instance().get_bonus_soulevable_joueur() << std::endl;
    fic << "BONUS_BOMBE" << std::endl;
    fic << Jeu::instance().get_bonus_bombe_special_joueur();

}// sauver_sauvegarde()


// fin implementation class Sauvegarde
