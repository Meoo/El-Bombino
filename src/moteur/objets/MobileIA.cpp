/**
 * @file   MobileIA.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/objets/MobileIA.hpp>
#include <moteur/objets/Soulevable.hpp>
#include <moteur/Jeu.hpp>

MobileIA::MobileIA(Case* cse, float vitesse, unsigned vies, const sf::Texture & texture)
    : Mobile(cse, vitesse), _vies(vies), _texture(texture), _protection(0), _clignote(false)
{
    assert(vies > 0);
    _sprite.setOrigin(_texture.getSize().x / 2, _texture.getSize().y - _texture.getSize().x / 2);
    _sprite.setTexture(_texture);
    Jeu::instance().get_monde_courant().get_niveau_courant().ajouter_pnj(this);
}


MobileIA::~MobileIA()
{
    Jeu::instance().get_monde_courant().get_niveau_courant().delete_pnj(this);
}


void MobileIA::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // Si l'IA est protégée contre les dégats, elle clignote
    _clignote = !_clignote;
    if (_protection > 0 && _clignote) return;

    if (get_objet_souleve() != NULL)
    {
        target.draw(*get_objet_souleve(), states);
        target.draw(_sprite, states);
    }
    else
        target.draw(_sprite, states);
}// draw()


void MobileIA::mise_a_jour()
{
    Mobile::mise_a_jour();

    if (!est_en_mouvement())
    {
        mise_a_jour_ia();
    }

    if (_protection > 0)
        --_protection;

    // TODO Gérer la direction
    _sprite.setPosition(get_position_ecran());
}// mise_a_jour()


void MobileIA::blesser()
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
}// blesser()


void MobileIA::glacee()
{
    if (_protection == 0)
    {
        if (get_objet_souleve() != NULL && get_objet_souleve()->est_valide())
            get_objet_souleve()->glacee();

        if(get_vitesse() - BOMBE_GLACEE_DELTA > IA_VIT_MIN)
            set_vitesse(get_vitesse() - BOMBE_GLACEE_DELTA);
        else
            set_vitesse(IA_VIT_MIN);
        _protection = IA_PROTECTION;
    }
}

const unsigned MobileIA::get_vies() const
{
    return _vies;
}// get_vies()


unsigned MobileIA::get_vies()
{
    return _vies;
}// get_vies()


void MobileIA::set_vies(unsigned vies)
{
    assert(vies <= 0);
    _vies = vies;
}// set_vies()


void MobileIA::appliquer_bonus(Bonus::bonus_t type_bonus)
{
    switch (type_bonus) {
        case Bonus::BONUS_BOMBE:
            break;
        case Bonus::BONUS_PUISSANCE:
            break;
        case Bonus::BONUS_VIE:
            ++_vies;
            break;
        case Bonus::BONUS_VITESSE:
            if(get_vitesse()+IA_VIT_DELTA < IA_VIT_MAX)
                set_vitesse(get_vitesse()+ IA_VIT_DELTA);
            else
                set_vitesse(IA_VIT_MAX);
            break;
        case Bonus::MALUS_BOMBE:
            break;
        case Bonus::MALUS_PUISSANCE:
            break;
        case Bonus::MALUS_VITESSE:
            if(get_vitesse() - IA_VIT_DELTA > IA_VIT_MIN)
                set_vitesse(get_vitesse() - IA_VIT_DELTA);
            else
                set_vitesse(IA_VIT_MIN);
            break;
        default:
            break;
    }
}// appliquer_bonus()


// fin implementation class MobileIA
