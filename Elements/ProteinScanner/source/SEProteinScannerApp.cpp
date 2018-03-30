#include "SEProteinScannerApp.hpp"
#include "SEProteinScannerAppGUI.hpp"
#include "SAMSON.hpp"
#include "vector"
#include "SBResidue.hpp"
#include "SEProteinScannerGrid.hpp"
#include "SBSideChain.hpp"
#include "SEProteinScannerGridBoolean.hpp"
#include <fstream>
#include "SBList.hpp"
#include "SBMatrix33.hpp"

#include <QDirIterator>

SEProteinScannerApp::SEProteinScannerApp() {

	setGUI(new SEProteinScannerAppGUI(this));
	getGUI()->loadDefaultSettings();

}

SEProteinScannerApp::~SEProteinScannerApp() {

	getGUI()->saveDefaultSettings();
	delete getGUI();

}

SEProteinScannerAppGUI* SEProteinScannerApp::getGUI() const { return static_cast<SEProteinScannerAppGUI*>(SBDApp::getGUI()); }


SBIAPosition3* SEProteinScannerApp::gridsize() const {

    SBIAPosition3* minmax = new SBIAPosition3;

	SBNodeIndexer nodeIndexer;
	SAMSON::getActiveDocument()->getNodes(nodeIndexer, SBNode::IsType(SBNode::Atom));

    if (nodeIndexer.empty()) {
        return minmax; }


	SBAtom* atom = static_cast<SBAtom*>(nodeIndexer[0]);
    *minmax=atom->getPosition();


	SB_FOR(SBNode* node, nodeIndexer) {

		SBAtom* atom = static_cast<SBAtom*>(node);
        minmax->bound(atom->getPosition());

	}
    return minmax;

}


SEProteinScannerGrid* SEProteinScannerApp::gridfill(SBIAPosition3& minmax,SBQuantity::length voxsize, int winsize) const{

	SEProteinScannerGrid* grid= new SEProteinScannerGrid(minmax, voxsize, winsize);

	SBNodeIndexer resIndexer;
	SAMSON::getActiveDocument()->getNodes(resIndexer, SBNode::IsType(SBNode::Residue));

	SB_FOR(SBNode* node, resIndexer) {

		SBResidue* resi = static_cast<SBResidue*>(node);
        SBResidue::ResidueType res = resi->getResidueType();

		SBNodeIndexer atIndexer;
        //if (resi->getSideChain()) resi->getSideChain()->getNodes(atIndexer, SBNode::IsType(SBNode::Atom));
        resi->getNodes(atIndexer, SBNode::IsType(SBNode::Atom));

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

        if  (ixmid>=grid->nx) {ixmid=grid->nx-1 ;}
        if  (iymid>=grid->ny) {iymid=grid->ny-1 ;}
        if  (izmid>=grid->nz) {izmid=grid->nz-1 ;}

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


void SEProteinScannerApp::rotation(int axe,int nbrot) const {
    if (nbrot==0){return;}
    SBQuantity::dimensionless angle = 2*(*SBConstant::Pi)/nbrot;
    SBVector3 axis;
    SBMatrix33 matRot;

    if(axe==0){
        matRot.makeEulerRotationZYZ (angle, SBQuantity::dimensionless(0),SBQuantity::dimensionless(0) );
    }
    if(axe==1){
        matRot.makeEulerRotationZYZ (SBQuantity::dimensionless(0),angle,SBQuantity::dimensionless(0));
    }
    if(axe==2){
        matRot.makeEulerRotationZYZ (SBQuantity::dimensionless(0),SBQuantity::dimensionless(0),angle);
    }

    SBNodeIndexer nodeIndexer;
    SAMSON::getActiveDocument()->getNodes(nodeIndexer, SBNode::IsType(SBNode::Atom));
    SB_FOR(SBNode* node, nodeIndexer){
        SBAtom* atom = static_cast<SBAtom*>(node);
        atom->setPosition(matRot*atom->getPosition());

    }






}


void  SEProteinScannerApp::compute(SBQuantity::length distcont,SBQuantity::length voxsize,int winsize, const QString& path, int nbrot) const{

    ofstream fichier("/users/misc-b/INF473/jacques.boitreaud/testpourcomparer.txt");

    fichier<<winsize<<endl;
    fichier<<voxsize.getValue()<<endl;

    QDirIterator itC(path, QStringList() << "*.pdb", QDir::Files, QDirIterator::Subdirectories);
    unsigned int numberOfPDBFiles = 0;

    while (itC.hasNext()) {
        numberOfPDBFiles++;
        itC.next();
    }

    fichier<<numberOfPDBFiles<<endl;

    QDirIterator it(path, QStringList() << "*.pdb", QDir::Files, QDirIterator::Subdirectories);

    while (it.hasNext()) {

        QString proteinPath = it.next();

        // load protein

        SBList<std::string> parameters;
        parameters.push_back("1");
        parameters.push_back("0");
        parameters.push_back("0");
        parameters.push_back("1");
        parameters.push_back("1");
        parameters.push_back("0");
        parameters.push_back("1");

        SAMSON::importFromFile(proteinPath.toStdString(), &parameters);
        //rotation
        for(int rx=0;rx<=nbrot;rx++){
            rotation(0,nbrot);
            for(int ry=0;ry<=nbrot;ry++){
                rotation(1,nbrot);
                for(int rz=0;rz<=nbrot;rz++){
                    rotation(2,nbrot);
                    // scan protein
                    SBIAPosition3 minmax = *gridsize();
                    SEProteinScannerGrid* grid = gridfill(minmax,voxsize,winsize);

                    SBNodeIndexer ligandAtomIndexer;
                    SBNodePredicate* ligandPredicate = SAMSON::makeNodePredicate("a.het and not (n.t a and not (n.t a l n.t a)) and not a.w ");
                    SAMSON::getActiveDocument()->getNodes(ligandAtomIndexer, *ligandPredicate);

                    SEProteinScannerGridBoolean* gridbool = GridBoolFill(ligandAtomIndexer,distcont, minmax, voxsize, winsize);

                    fichier<<(grid->nx-2*winsize)*(grid->ny-2*winsize)*(grid->nz-2*winsize)<<endl;

                    // for each sliding window

                    for (int ix= winsize; ix<grid->nx-winsize;ix++){

                        for (int iy= winsize; iy<grid->ny-winsize;iy++){

                            for (int iz= winsize; iz<grid->nz-winsize;iz++){

                                // for the sliding window

                                for (int jx= ix-winsize; jx<=ix+winsize;jx++){

                                    for (int jy= iy-winsize; jy<=iy+winsize;jy++){

                                        for (int jz= iz-winsize; jz<=iz+winsize;jz++){

                                            fichier<<grid->getRes(jx,jy,jz)<<"\t";

                                        }

                                    }

                                }

                                fichier<<gridbool->getBoolean(ix,iy,iz)<<endl;

                            }

                        }

                    }

                    // clean

                    delete grid;
                    delete gridbool;


                }
            }


        }



        SAMSON::undo(); // undo import

    }

    fichier.close();

}

void  SEProteinScannerApp::predict(SBQuantity::length voxsize,int winsize) const{
    ofstream fichier("/users/misc-b/INF473/jacques.boitreaud/predict1a1e.txt");

    fichier<<winsize<<endl;
    fichier<<voxsize.getValue()<<endl;
    SBIAPosition3 minmax = *gridsize();
    SEProteinScannerGrid* grid = gridfill(minmax,voxsize,winsize);

    SBPosition3 origin=grid->getOrigin();
    fichier<<(origin[0]+winsize*voxsize).getValue()<<endl;
    fichier<<(origin[1]+winsize*voxsize).getValue()<<endl;
    fichier<<(origin[2]+winsize*voxsize).getValue()<<endl;
    fichier<<grid->nx-2*winsize<<endl;
    fichier<<grid->ny-2*winsize<<endl;
    fichier<<grid->nz-2*winsize<<endl;
    fichier<<(grid->nx-2*winsize)*(grid->ny-2*winsize)*(grid->nz-2*winsize)<<endl;

    for (int ix= winsize; ix<grid->nx-winsize;ix++){

        for (int iy= winsize; iy<grid->ny-winsize;iy++){

            for (int iz= winsize; iz<grid->nz-winsize;iz++){

                // for the sliding window

                for (int jx= ix-winsize; jx<=ix+winsize;jx++){

                    for (int jy= iy-winsize; jy<=iy+winsize;jy++){

                        for (int jz= iz-winsize; jz<=iz+winsize;jz++){

                            fichier<<grid->getRes(jx,jy,jz)<<"\t";

                        }

                    }

                }

                fichier<<endl;

            }

        }

    }
    delete grid;

}
