#include "SEProteinScannerApp.hpp"
#include "SEProteinScannerAppGUI.hpp"
#include "SAMSON.hpp"
#include "vector"
#include "SBResidue.hpp"
#include "SEProteinScannerGrid.hpp"
#include "SBSideChain.hpp"
#include "SEProteinScannerGridBoolean.hpp"
#include <fstream>

SEProteinScannerApp::SEProteinScannerApp() {

	setGUI(new SEProteinScannerAppGUI(this));
	getGUI()->loadDefaultSettings();

}

SEProteinScannerApp::~SEProteinScannerApp() {

	getGUI()->saveDefaultSettings();
	delete getGUI();

}

SEProteinScannerAppGUI* SEProteinScannerApp::getGUI() const { return static_cast<SEProteinScannerAppGUI*>(SBDApp::getGUI()); }


void  SEProteinScannerApp::gridsize(SBIAPosition3& minmax) const {

	SBNodeIndexer nodeIndexer;
	SAMSON::getActiveDocument()->getNodes(nodeIndexer, SBNode::IsType(SBNode::Atom));

	if (nodeIndexer.empty())return;


	SBAtom* atom = static_cast<SBAtom*>(nodeIndexer[0]);
	minmax=atom->getPosition();


	SB_FOR(SBNode* node, nodeIndexer) {

		SBAtom* atom = static_cast<SBAtom*>(node);
		minmax.bound(atom->getPosition());

	}

}


SEProteinScannerGrid* SEProteinScannerApp::gridfill(SBIAPosition3& minmax,SBQuantity::length voxsize, int winsize) const{

	SEProteinScannerGrid* grid= new SEProteinScannerGrid(minmax, voxsize, winsize);

	SBNodeIndexer resIndexer;
	SAMSON::getActiveDocument()->getNodes(resIndexer, SBNode::IsType(SBNode::Residue));

	SB_FOR(SBNode* node, resIndexer) {

		SBResidue* resi = static_cast<SBResidue*>(node);

		SBNodeIndexer atIndexer;
		if (resi->getSideChain()) resi->getSideChain()->getNodes(atIndexer, SBNode::IsType(SBNode::Atom));

		SBQuantity::length xmid(0);
		SBQuantity::length ymid(0);
		SBQuantity::length zmid(0);
		int count=0;

		SB_FOR(SBNode* nodde, atIndexer) {
			count++;
			SBAtom* atom = static_cast<SBAtom*>(nodde);
			SBPosition3 position = atom->getPosition();
			xmid += position.v[0];
			ymid += position.v[1];
			zmid += position.v[2];
		}
		SBPosition3 origin = grid->getOrigin();

		int ixmid=(int)((xmid/count-origin[0])/voxsize).getValue();
		int iymid=(int)((ymid/count-origin[1])/voxsize).getValue();
		int izmid=(int)((zmid/count-origin[2])/voxsize).getValue();

		SBResidue::ResidueType res = resi->getResidueType();

		grid->setRes(ixmid,iymid,izmid,res);

	}

	return grid;

}


bool SEProteinScannerApp::Scan(SBQuantity::length x,SBQuantity::length y, SBQuantity::length z,SBQuantity::length distcont,SBNodeIndexer ligandAtomIndexer) const{
	SBPosition3 centre;
	centre[0]=x;
	centre[1]=y;
	centre[2]=z;
	SB_FOR(SBNode* lig, ligandAtomIndexer) {
		SBAtom* atomlig = static_cast<SBAtom*>(lig);
		SBPosition3 poslig = atomlig->getPosition();
		SBQuantity::length dif = (poslig-centre).norm();
		if (dif<=distcont){
			return true;
		}
	}
	return false;

}

SEProteinScannerGridBoolean*  SEProteinScannerApp::GridBoolFill(SBNodeIndexer ligandAtomIndexer,SBQuantity::length distcont,SBIAPosition3& minmax,SBQuantity::length voxsize,int winsize) const{
	SEProteinScannerGridBoolean* gridb= new SEProteinScannerGridBoolean(minmax, voxsize, winsize);
	int nx = (int)((minmax.i[0].i[1]+2*winsize*voxsize-minmax.i[0].i[0])/voxsize).getValue();
	int ny = (int)((minmax.i[1].i[1]+2*winsize*voxsize-minmax.i[1].i[0])/voxsize).getValue();
	int nz = (int)((minmax.i[2].i[1]+2*winsize*voxsize-minmax.i[2].i[0])/voxsize).getValue();
	SBPosition3 origin = gridb->getOrigin();
	for (int ix= winsize; ix<nx-winsize;ix++){
		for (int iy= winsize; iy<ny-winsize;iy++){
			for (int iz= winsize; iz<nz-winsize;iz++){
				if(SEProteinScannerApp::Scan(origin[0]+ix*voxsize,origin[1]+iy*voxsize,origin[2]+iz*voxsize,distcont,ligandAtomIndexer)){
					gridb->setBoolean(ix,iy,iz,true);
				}
			}
		}

	}
	return gridb;

}

void  SEProteinScannerApp::compute(SBQuantity::length distcont,SBQuantity::length voxsize,int winsize) const{
	SBIAPosition3 minmax;
	gridsize(minmax);
	SEProteinScannerGrid* grid = gridfill(minmax,voxsize,winsize);


	SBNodePredicate* ligandPredicate = SAMSON::makeNodePredicate("a.het and not (n.t a and not (n.t a l n.t a)) and not a.w ");
	SBNodeIndexer ligandAtomIndexer;
	SAMSON::getActiveDocument()->getNodes(ligandAtomIndexer, *ligandPredicate);


	SEProteinScannerGridBoolean* gridbool = GridBoolFill(ligandAtomIndexer,distcont, minmax, voxsize, winsize);

	ofstream fichier("test.txt", ios::app);

	fichier<<"nombre de lignes:"<<(grid->nx-2*winsize)*(grid->ny-2*winsize)*(grid->nz-2*winsize)<<endl;
	fichier<<"demi arete"<<winsize<<endl;
	fichier<<"Size of one Voxel (A)"<<voxsize<<endl;
	for (int ix= winsize; ix<grid->nx-winsize;ix++){
		for (int iy= winsize; iy<grid->ny-winsize;iy++){
			for (int iz= winsize; iz<grid->nz-winsize;iz++){

				for (int jx= ix-winsize; jx<=ix+winsize;jx++){
					for (int jy= iy-winsize; iy<=iy+winsize;jy++){
						for (int jz= iz-winsize; jz<=iz+winsize;jz++){
							fichier<<grid->getRes(jx,jy,jz)<<" ";

						}
					}

				}
				fichier<<gridbool->getBoolean(ix,iy,iz)<<endl;



			}
		}

	}



}
