#include "SAMSON.hpp"
#include "vector"
#include "SBResidue.hpp"
#include "SBIAVector3.hpp"
#include "SEProteinScannerGrid.hpp"






SEProteinScannerGrid::SEProteinScannerGrid(SBIAPosition3 minmax, SBQuantity::length voxsize, int winsize ) {


        int nx = (int)((minmax.i[0].i[1]+2*winsize*voxsize-minmax.i[0].i[0])/voxsize).getValue();
        int ny = (int)((minmax.i[1].i[1]+2*winsize*voxsize-minmax.i[1].i[0])/voxsize).getValue();
        int nz = (int)((minmax.i[2].i[1]+2*winsize*voxsize-minmax.i[2].i[0])/voxsize).getValue();

        this->nx=nx;
        this->ny=ny;
        this->nz=nz;


        SBResidue::ResidueType* grid = new SBResidue::ResidueType[nx*ny*nz];

        for(int i=0;i<nx*ny*nz;i++) {
                    grid[i]=SBResidue::ResidueType::Undefined;
            }

        SBPosition3 origin;
        origin.v[0]=minmax.i[0].i[0]-winsize*voxsize;
        origin.v[1]=minmax.i[1].i[0]-winsize*voxsize;
        origin.v[2]=minmax.i[2].i[0]-winsize*voxsize;

        this->voxsize= voxsize;

}

SEProteinScannerGrid::~SEProteinScannerGrid() {}

void SEProteinScannerGrid::setRes(int x, int y, int z, SBResidue::ResidueType res) {


    int index=x*ny*nz+y*nz+z;
    grid[index]=res;

}

SBPosition3 SEProteinScannerGrid::getOrigin() {
    return origin;
}

SBResidue::ResidueType SEProteinScannerGrid::getRes(int x, int y , int z) {
    return grid[x*ny*nz+y*nz+z];
}


