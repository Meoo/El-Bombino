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

#include <map>
#include <vector>


/**
 * @brief
 */
class Monde : public sf::Drawable
{
private:
    std::map<std::string, std::vector<sf::Texture> > _textures;

    const std::string   _fichier_rc;
    unsigned            _niveaux_count;
    Niveau **           _niveaux;
    Niveau *            _niveau_courant;

#ifndef NDEBUG
    bool                _pret;
#endif

public:
    explicit            Monde(const std::string & fic);
    virtual             ~Monde();

    Niveau &            get_niveau_courant();
    const Niveau &      get_niveau_courant() const;

    void                charger();
    void                liberer();

    bool                has_texture(const std::string & res) const;
    const sf::Texture & get_texture(const std::string & res) const;

    // Fonction d'affichage de Drawable
    virtual void        draw(sf::RenderTarget & target, sf::RenderStates states) const;

    virtual void        mise_a_jour();

/*TODO protected:*/
    void                set_niveau_courant(unsigned num);

};
// class Monde

#endif // _MONDE_HPP_
