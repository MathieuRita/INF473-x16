#ifndef SEPROTEINSCANNERGRIDBOOLEAN_H
#define SEPROTEINSCANNERGRIDBOOLEAN_H
#include "SBResidue.hpp"
#include "SBIAVector3.hpp"




class SEProteinScannerGridBoolean {

 public :

        SEProteinScannerGridBoolean(SBIAPosition3 size, SBQuantity::length voxsize , int winsize);
        virtual ~SEProteinScannerGridBoolean();

        bool* grid;
        SBPosition3 origin;
        SBQuantity::length voxsize;
        int nx;
        int ny;
        int nz;


        SBPosition3                                                         getOrigin() const;
        void                                                           setBoolean(int x, int y, int z, bool b);
        bool                                                        getBoolean(int x, int y, int z);


    };

#endif // SEPROTEINSCANNERGRID_HPP
