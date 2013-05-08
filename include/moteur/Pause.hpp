/*
 * Pause.hpp
 *
 *  Created on: 8 mai 2013
 *      Author: Sanpas
 */

#ifndef PAUSE_HPP_
#define PAUSE_HPP_

#include <SFML/Graphics.hpp>

class Pause : public sf::Drawable
{
private:

    bool            _pause;

    sf::Text texte_pause;
    sf::Text texte_pause_fond;
    sf::RectangleShape fond_pause;

    int _pause_frame;

public:
                    Pause();
    virtual         ~Pause();

    virtual void    draw(sf::RenderTarget& target, sf::RenderStates states) const;

    virtual void    mise_a_jour();

    void            clic(int x, int y);

    void            set_active(bool pause);

    bool            est_active();
};


#endif /* PAUSE_HPP_ */
