#ifndef SEPROTEINSCANNERGRID_HPP
#define SEPROTEINSCANNERGRID_HPP
#include "SBResidue.hpp"

#endif // SEPROTEINSCANNERGRID_HPP

class SEProteinScannerGrid: public SBDApp {

    SB_CLASS

public :

        SEProteinScannerGrid(SBIAposition3 size, SBQuantity voxsize );
        virtual ~SEProteinScannerGrid();

        SBResidue::ResidueType* grid;
        SBPosition3 origin;
        SBQuantity::length voxsize;

        SBPosition3                                                         getorigin() const;
        void                                                           fill(int x, int y, int z, ResiduType res);


    }
