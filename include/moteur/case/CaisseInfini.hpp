/**
 * @file   CaisseInfini.hpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#ifndef CAISSEINFINI_HPP_
#define CAISSEINFINI_HPP_


/**
 * @brief
 */
class CaisseInfini : public Case
{
        unsigned    _timer;
        bool        _timer_init;

public:

                    CaisseInfini(unsigned x, unsigned y, const sf::Texture & texture);
    virtual         ~CaisseInfini();

    virtual void    mise_a_jour();
};
// class CaisseInfini


#endif /* CAISSEINFINI_HPP_ */
