
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

        this->nx=nx;
        this->ny=ny;
        this->nz=nz;

        grid = new bool[nx*ny*nz];

        for(int i=0;i<nx*ny*nz;i++) {
                    grid[i]=false;
            }

        origin.v[0]=minmax.i[0].i[0]-winsize*voxsize;
        origin.v[1]=minmax.i[1].i[0]-winsize*voxsize;
        origin.v[2]=minmax.i[2].i[0]-winsize*voxsize;

        this->voxsize= voxsize;

}

SEProteinScannerGridBoolean::~SEProteinScannerGridBoolean() {}

void SEProteinScannerGridBoolean::setBoolean(int x, int y, int z, bool b) {
    int index=x*ny*nz+y*nz+z;
    grid[index]=b;

}

SBPosition3 SEProteinScannerGridBoolean::getOrigin() const {
    return origin;
}

bool SEProteinScannerGridBoolean::getBoolean(int x, int y , int z) {
    return grid[x*ny*nz+y*nz+z];
}
