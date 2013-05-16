/**
 * @file   CaissePiege.hpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */
#ifndef CAISSEPIEGE_HPP_
#define CAISSEPIEGE_HPP_


#include "Caisse.hpp"

/**
 * @brief
 */
class CaissePiege : public Caisse
{
private:
    bool            _explosive;

public:
    explicit        CaissePiege(Case * cse);
    virtual         ~CaissePiege();

    virtual void    blesser();

    virtual void    glacee();

    virtual void    laisser_tomber_objet(Case * cse);
};
// class CaissePiege


#endif /* CAISSEPIEGE_HPP_ */
