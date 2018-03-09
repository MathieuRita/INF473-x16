#ifndef SEPROTEINSCANNERGRIDBOOLEAN_H
#define SEPROTEINSCANNERGRIDBOOLEAN_H
#include "SBResidue.hpp"
#include "SBIAVector3.hpp"




class SEProteinScannerGridBoolean: public SBDApp {

    SB_CLASS

public :

        SEProteinScannerGridBoolean(SBIAPosition3 size, SBQuantity::length voxsize , int winsize);
        virtual ~SEProteinScannerGrid();

        Boolean* grid;
        SBPosition3 origin;
        SBQuantity::length voxsize;

        SBPosition3                                                         getOrigin() const;
        void                                                           setBoolean(int x, int y, int z, Boolean b);
        Boolean                                                        getBoolean(int x, int y, int z);


    };

#endif // SEPROTEINSCANNERGRID_HPP
