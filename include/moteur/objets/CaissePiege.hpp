/**
 * @file   CaissePiege.hpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */
#ifndef CAISSEPIEGE_HPP_
#define CAISSEPIEGE_HPP_


#include "Soulevable.hpp"

/**
 * @brief
 */
class CaissePiege : public Soulevable
{
private:
    sf::Sprite      _sprite;

public:
    explicit        CaissePiege(Case * cse);
    virtual         ~CaissePiege();

    // Fonction d'affichage de Drawable
    virtual void    draw(sf::RenderTarget & target, sf::RenderStates states) const;

    virtual void    mise_a_jour();

    virtual void    blesser();
};
// class CaissePiege


#endif /* CAISSEPIEGE_HPP_ */
