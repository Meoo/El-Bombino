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

public:
    Idiot(Case * cse);
    virtual ~Idiot();

    virtual void mise_a_jour_ia();

private:

};
// class Idiot

#endif // _IDIOT_HPP_
