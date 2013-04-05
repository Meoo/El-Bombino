/**
 * @file   Monde.hpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#ifndef _MONDE_HPP_
#define _MONDE_HPP_

#include "../Config.hpp"
#include "Niveau.hpp"

#include <SFML/Graphics.hpp>

/**
 * @brief
 */
class Monde : public sf::Drawable
{
private:
    const std::string   _fichier_rc;
    unsigned            _niveaux_count;
    Niveau **           _niveaux;
    Niveau *            _niveau_courant;

public:
                        Monde(const std::string & fic);
    virtual             ~Monde();

    Niveau *            get_niveau_courant();
    const Niveau *      get_niveau_courant() const;

    void                charger();
    void                liberer();

    const sf::Texture & get_texture(const std::string & res) const;

    // Fonction d'affichage de Drawable
    virtual void        draw(sf::RenderTarget & target, sf::RenderStates states) const;

    virtual void        mise_a_jour();

protected:
    void                set_niveau_courant(unsigned num);

};
// class Monde

#endif // _MONDE_HPP_
