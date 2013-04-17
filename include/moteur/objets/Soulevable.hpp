/**
 * @file   Soulevable.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _SOULEVABLE_HPP_
#define _SOULEVABLE_HPP_

#include "../Objet.hpp"

class Mobile;

/**
 * @brief
 */
class Soulevable : public Objet
{
private:
    Mobile *                _porteur;

public:
                            Soulevable(Case * cse);
                            Soulevable(Mobile * porteur);
    virtual                 ~Soulevable();

    Mobile *                get_porteur();
    const Mobile *          get_porteur() const;

    void                    set_porteur(Mobile * porteur);

    virtual void            deposer(Case * cse);
    virtual Case *          get_case();
    virtual const Case *    get_case() const;

};
// class Soulevable

#endif // _SOULEVABLE_HPP_
