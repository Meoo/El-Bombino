/**
 * @file   MobileIA.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/objets/MobileIA.hpp>
#include <moteur/objets/Soulevable.hpp>

MobileIA::MobileIA(Case* cse, float vitesse, unsigned vies, const sf::Texture & texture)
    : Mobile(cse, vitesse), _vies(vies), _texture(texture), _protection(0), _clignote(false)
{
    assert(vies > 0);
    _sprite.setOrigin(_texture.getSize().x / 2, _texture.getSize().y - _texture.getSize().x / 2);
    _sprite.setTexture(_texture);
}

MobileIA::~MobileIA()
{
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
}

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
}

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
}
