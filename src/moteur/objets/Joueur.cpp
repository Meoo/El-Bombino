/**
 * @file   Joueur.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/objets/Joueur.hpp>
#include <moteur/objets/Bombe.hpp>
#include <moteur/Jeu.hpp>
#include <moteur/Case.hpp>

#include <SFML/Window.hpp>

Joueur::Joueur(Case * cse) :
        Mobile(cse, JOUEUR_VIT_DEFAULT), _sprite(Jeu::instance().get_texture("joueur")),
        _case_deposer_objet(NULL),_bombe_cooldown(BOMBE_COOLDOWN), _objet_souleve_cooldown(OBJET_SOULEVE_COOLDOWN),
        _nb_bombes_simultanee(JOUEUR_NB_BOMBES_DEFAULT), _puissance_bombe(BOMBE_POWER_DEFAULT),
        _vies(JOUEUR_VIE_DEFAULT), _clignote(false), _protection(0)
{
    _sprite.setOrigin(_sprite.getTexture()->getSize().x / 2,
            _sprite.getTexture()->getSize().y
                    - _sprite.getTexture()->getSize().x / 2);
    Jeu::instance().get_monde_courant().get_niveau_courant().ajouter_joueur(this);
}

Joueur::~Joueur()
{
    Jeu::instance().get_monde_courant().get_niveau_courant().delete_joueur();
}

void Joueur::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
     _clignote = !_clignote;
    if (_protection > 0 && _clignote) return;

    if (get_objet_souleve() != NULL)
    {
        if (_case_deposer_objet == NULL)
        {
            target.draw(_sprite, states);
            target.draw(*get_objet_souleve(), states);
        }
        else
        {
            target.draw(*get_objet_souleve(), states);
            target.draw(_sprite, states);
        }
    }
    else
        target.draw(_sprite, states);
}

const sf::Vector2f Joueur::get_position_objet_souleve() const
{
    if (_case_deposer_objet != NULL)
        return sf::Vector2f(
                get_objet_souleve()->get_case()->get_x() * TILE_SIZE
                        + TILE_SIZE / 2,
                get_objet_souleve()->get_case()->get_y() * TILE_SIZE
                        + TILE_SIZE / 2);
    else
        return Mobile::get_position_objet_souleve();
}

void Joueur::mise_a_jour()
{
    Mobile::mise_a_jour();

    if (_bombe_cooldown > 0)
        --_bombe_cooldown;

    if (_objet_souleve_cooldown > 0)
        --_objet_souleve_cooldown;

    if (_protection > 0)
        --_protection;

    // Gérer déplacement
    if (!est_en_mouvement())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            bouger(HAUT);

        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            bouger(BAS);

        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            bouger(GAUCHE);

        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            bouger(DROITE);
    }

    // Gérer charger une bombe
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        // Si le joueur ne porte pas d'objets
        if (get_objet_souleve() == NULL)
        {
            // Petit cooldown
            if (_bombe_cooldown == 0 && Jeu::instance().get_monde_courant().get_niveau_courant().get_bombes_actives().size() < _nb_bombes_simultanee)
            {
                // Alors il peut sortir une bombe
                _case_deposer_objet = this->get_case();
                _bombe_cooldown = BOMBE_COOLDOWN;
                new Bombe(this, BOMBE_TIMER_DEFAULT, _puissance_bombe);
            }
        }
    }

    // soulever l'objet present dans la direction
    // ou poser l'objet si il est en notre posetion
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
    {
        if (_objet_souleve_cooldown == 0)
        {
            if(get_objet_souleve() == NULL)
            {
                Soulevable * soulevable = NULL;

                // Essayer de récupérer un soulevable sur une case à coté
                if(get_direction() == HAUT && get_case()->get_case_haut()->get_objet() != NULL)
                {
                    soulevable = dynamic_cast<Soulevable *>(get_case()->get_case_haut()->get_objet());
                }
                else if (get_direction() == BAS && get_case()->get_case_bas()->get_objet() != NULL)
                {
                    soulevable = dynamic_cast<Soulevable *>(get_case()->get_case_bas()->get_objet());
                }
                else if (get_direction() == DROITE && get_case()->get_case_droite()->get_objet() != NULL)
                {
                    soulevable = dynamic_cast<Soulevable *>(get_case()->get_case_droite()->get_objet());
                }
                else if (get_direction() == GAUCHE && get_case()->get_case_gauche()->get_objet() != NULL)
                {
                    soulevable = dynamic_cast<Soulevable *>(get_case()->get_case_gauche()->get_objet());
                }

                // Si c'est bon, le soulever
                if(soulevable)
                {
                    soulevable->set_porteur(this);
                }
            }
            else
            {
                // Si on as un objet à ses pieds, le soulever
                if (_case_deposer_objet != NULL)
                {
                    _case_deposer_objet = NULL;
                }

                // Sinon déposer l'objet sur une case à coté
                else if(get_direction() == HAUT)
                {
                    get_objet_souleve()->deposer(get_case()->get_case_haut());
                }
                else if (get_direction() == BAS)
                {
                    get_objet_souleve()->deposer(get_case()->get_case_bas());
                }
                else if (get_direction() == DROITE)
                {
                    get_objet_souleve()->deposer(get_case()->get_case_droite());
                }
                else if (get_direction() == GAUCHE)
                {
                    get_objet_souleve()->deposer(get_case()->get_case_gauche());
                }
            }

            _objet_souleve_cooldown = OBJET_SOULEVE_COOLDOWN;
        }
    }

    // Gérer le dépot automatique au sol de la bombe
    if (get_objet_souleve() != NULL && _case_deposer_objet != NULL && _case_deposer_objet != this->get_case())
    {
        get_objet_souleve()->deposer(_case_deposer_objet);
        _case_deposer_objet->get_objet()->mise_a_jour();
        _case_deposer_objet = NULL;
    }

    // TODO Gérer la direction
    _sprite.setPosition(get_position_ecran());

}

void Joueur::appliquer_bonus(Bonus::bonus_t type_bonus)
{
    switch (type_bonus) {
        case Bonus::BONUS_BOMBE:
            if(_nb_bombes_simultanee + JOUEUR_NB_BOMBES_DELTA < JOUEUR_NB_BOMBES_MAX)
                _nb_bombes_simultanee += JOUEUR_NB_BOMBES_DELTA;
            else
                _nb_bombes_simultanee = JOUEUR_NB_BOMBES_MAX;
            break;
        case Bonus::BONUS_PUISSANCE:
            if(_puissance_bombe + BOMBE_POWER_DELTA < BOMBE_POWER_MAX)
                _puissance_bombe += BOMBE_POWER_DELTA;
            else
                _puissance_bombe = BOMBE_POWER_MAX;
            break;
        case Bonus::BONUS_VIE:
            ++_vies;
            break;
        case Bonus::BONUS_VITESSE:
            if(get_vitesse()+JOUEUR_VIT_DELTA < JOUEUR_VIT_MAX)
                set_vitesse(get_vitesse()+ JOUEUR_VIT_DELTA);
            else
                set_vitesse(JOUEUR_VIT_MAX);
            break;
        case Bonus::MALUS_BOMBE:
            if(_nb_bombes_simultanee - JOUEUR_NB_BOMBES_DELTA > JOUEUR_NB_BOMBES_MIN)
                _nb_bombes_simultanee -= JOUEUR_NB_BOMBES_DEFAULT;
            else
                _nb_bombes_simultanee = JOUEUR_NB_BOMBES_MIN;
            break;
        case Bonus::MALUS_PUISSANCE:
            if(_puissance_bombe - BOMBE_POWER_DELTA > BOMBE_POWER_MIN)
                _puissance_bombe -= BOMBE_POWER_DELTA;
            else
                _puissance_bombe = BOMBE_POWER_MIN;
            break;
        case Bonus::MALUS_VIE:
            --_vies;
            break;
        case Bonus::MALUS_VITESSE:
            if(get_vitesse()-JOUEUR_VIT_DELTA > JOUEUR_VIT_MIN)
                set_vitesse(get_vitesse()-JOUEUR_VIT_DELTA);
            else
                set_vitesse(JOUEUR_VIT_MIN);
        default:
            break;
    }
}

void Joueur::blesser()
{
    if (_protection == 0 && _vies > 0)
    {
        if (get_objet_souleve() != NULL && get_objet_souleve()->est_valide())
            get_objet_souleve()->blesser();

        --_vies;
        if (_vies == 0)
            detruire();
        else
            _protection = IA_PROTECTION;
    }
}

bool Joueur::est_joueur()
{
    return true;
}

const unsigned Joueur::get_nb_bombe_simultanee() const
{
    return _nb_bombes_simultanee;
}

unsigned Joueur::get_nb_bombe_simultanee()
{
    return _nb_bombes_simultanee;
}

const unsigned Joueur::get_puissance_bombe() const
{
    return _puissance_bombe;
}

unsigned Joueur::get_puissance_bombe()
{
    return _puissance_bombe;
}

const unsigned Joueur::get_vie() const
{
    return _vies;
}

unsigned Joueur::get_vie()
{
    return _vies;
}
