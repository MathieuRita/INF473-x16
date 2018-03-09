#ifndef SEPROTEINSCANNERGRID_HPP
#define SEPROTEINSCANNERGRID_HPP
#include "SBResidue.hpp"
#include "SBIAVector3.hpp"




class SEProteinScannerGrid: public SBDApp {

    SB_CLASS

public :

        SEProteinScannerGrid(SBIAPosition3 size, SBQuantity voxsize );
        virtual ~SEProteinScannerGrid();

        SBResidue::ResidueType* grid;
        SBPosition3 origin;
        SBQuantity::length voxsize;

        SBPosition3                                                         getOrigin() const;
        void                                                           setRes(int x, int y, int z, SBResidue::ResidueType res);
        SBResidue::ResidueType                                          getRes(int x, int y, int z);


    };

#endif // SEPROTEINSCANNERGRID_HPP
