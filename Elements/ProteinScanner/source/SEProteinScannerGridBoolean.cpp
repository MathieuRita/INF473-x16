#include "SAMSON"
#include "vector"
#include "SEProteinScannerGridBoolean.hpp"
#include "SBResidue.hpp"
#include "SBIAVector3.hpp"
#include "SAMSON.hpp"
#include "vector"





SEProteinScannerGridBoolean::SEProteinScannerGridBoolean(SBIAPosition3 minmax, SBQuantity::length voxsize, int winsize ) {


        int nx = (int)((minmax.i[0].i[1]+2*winsize*voxsize-minmax.i[0].i[0])/voxsize).getValue();
        int ny = (int)((minmax.i[1].i[1]+2*winsize*voxsize-minmax.i[1].i[0])/voxsize).getValue();
        int nz = (int)((minmax.i[2].i[1]+2*winsize*voxsize-minmax.i[2].i[0])/voxsize).getValue();

        Boolean* grid = new Boolean[nx*ny*nz];

        for(int i=0;i<nx*ny*nz;i++) {
                    grid[i]=0;
            }

        SBPosition3 origin;
        origin.v[0]=minmax.i[0].i[0]-winsize*voxsize;
        origin.v[1]=minmax.i[1].i[0]-winsize*voxsize;
        origin.v[2]=minmax.i[2].i[0]-winsize*voxsize;

        this->voxsize= voxsize;

}

void SEProteinScannerGridBoolean::setBoolean(int x, int y, int z, Boolean b) {
    int index=x*nx+y*ny+z;
    grid[index]=b;

}

SBPosition3 SEProteinScannerGridBoolean::getOrigin() const {
    return origin;
}

Boolean SEProteinScannerGridBoolean::getBoolean(int x, int y , int z) {
    return grid[x*nx+y*ny+z];
}
