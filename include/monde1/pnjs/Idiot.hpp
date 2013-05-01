/**
 * @file   Idiot.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _IDIOT_HPP_
#define _IDIOT_HPP_

#include "../../moteur/objets/MobileIA.hpp"

/**
 * @brief
 */
class Idiot : public MobileIA
{
private:
    Direction _derniere_direction;

public:
    Idiot(Case * cse);
    virtual ~Idiot();

    virtual void mise_a_jour_ia();

    virtual void    laisser_tomber_objet(Case * cse);

private:

};
// class Idiot

#endif // _IDIOT_HPP_
