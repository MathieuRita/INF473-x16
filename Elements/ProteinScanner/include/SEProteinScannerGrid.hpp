#ifndef SEPROTEINSCANNERGRID_HPP
#define SEPROTEINSCANNERGRID_HPP
#include "SBResidue.hpp"
#include "SBIAVector3.hpp"


class SEProteinScannerGrid {

public :

        SEProteinScannerGrid(SBIAPosition3 size, SBQuantity::length voxsize , int winsize);
        virtual ~SEProteinScannerGrid();

        SBResidue::ResidueType* grid;
        SBPosition3 origin;
        SBQuantity::length voxsize;
        int nx;
        int ny;
        int nz;

        SBPosition3                                                         getOrigin() ;
        void                                                           setRes(int x, int y, int z, SBResidue::ResidueType res);
        SBResidue::ResidueType                                          getRes(int x, int y, int z);


};

#endif // SEPROTEINSCANNERGRID_HPP
