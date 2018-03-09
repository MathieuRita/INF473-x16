#include "SAMSON"
#include "vector"
#include "SBResidue.hpp"
#include "SBIAVector3.hpp"





SEProteinScannerGrid::SEProteinScannerGrid(SBIAPosition3 minmax, SBQuantity::length voxsize ) {


        int nx = (int)((minmax.i[0].i[1]-minmax.i[0].i[0])/voxsize).getValue();
        int ny = (int)((minmax.i[1].i[1]-minmax.i[1].i[0])/voxsize).getValue();
        int nz = (int)((minmax.i[2].i[1]-minmax.i[2].i[0])/voxsize).getValue();

        SBResidue::ResidueType* grid = new ResidueType[nx*ny*nz];

        for(int i=0;i<nx*ny*nz;i++) {
                    grid[i]=SBResidue::ResidueType::Undefined;
            }

        origin.v[0]=minmax.i[0].i[0];
        origin.v[1]=minmax.i[1].i[0];
        origin.v[2]=minmax.i[2].i[0];

        this->voxsize= voxsize;

}

void SEProteinScannerGrid::setRes(int x, int y, int z, SBResidue::ResidueType res) {
    int index=x*nx+y*ny+z;
    grid[index]=res;

}

SBPosition3 SEProteineScannerGrid::getOrigin() const {
    return origin;
}

SBResidue::ResidueType* getRes(int x, int y , int z) {
    return grid[x*nx+y*ny+z];
}


