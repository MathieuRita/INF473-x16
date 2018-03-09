#include "SAMSON"
#include "vector"
#include "SBResidue.hpp"





SEProteinScannerGrid::SEProteinScannerGrid(SBIAposition3 minmax, SBQuantity voxsize ) {


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

void SEProteinScannerGrid::fill(int x, int y, int z, SBResidue::ResidueType res) {
    int index=x*nx+y*ny+z;
    grid[index]=res;

}

SBPosition3 SEProteineScannerGrid::getorigin() const {
    return origin;
}

SBResidue::ResiduType* getres(int x, int y , int z) {
    return grid[x*nx+y*ny+z];
}


