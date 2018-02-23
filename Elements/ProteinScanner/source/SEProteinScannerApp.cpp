#include "SEProteinScannerApp.hpp"
#include "SEProteinScannerAppGUI.hpp"
#include "SAMSON.hpp"
#include "vector"

SEProteinScannerApp::SEProteinScannerApp() {

    setGUI(new SEProteinScannerAppGUI(this));
    getGUI()->loadDefaultSettings();

}

SEProteinScannerApp::~SEProteinScannerApp() {

    getGUI()->saveDefaultSettings();
    delete getGUI();

}

SEProteinScannerAppGUI* SEProteinScannerApp::getGUI() const { return static_cast<SEProteinScannerAppGUI*>(SBDApp::getGUI()); }

void  SEProteinScannerApp::gridsize(SBIAPosition3& minmax) {

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

std::vector<std::vector<std::vector<int>>> SEProteinScannerApp::gridfill(SBIAPosition3& minmax,SBQuantity voxsize){
    int nbrvoxx = (int)((minmax.i[0].i[1]-minmax.i[0].i[0])/voxsize).getValue();
    int nbrvoxy = (int)((minmax.i[1].i[1]-minmax.i[1].i[0])/voxsize).getValue();
    int nbrvoxz = (int)((minmax.i[2].i[1]-minmax.i[2].i[0])/voxsize).getValue();
    SBQuantity orx = minmax.i[0].i[0];
    SBQuantity ory = minmax.i[1].i[0];
    SBQuantity orz = minmax.i[2].i[0];

    std::vector<std::vector<std::vector<int>>> grid;

    for(int x=0;x<nbrvoxx;x++){
        for(int y=0;y<nbrvoxy;y++){
            for(int z=0;z<nbrvoxz;z++){
                SBNodeIndexer resIndexer;
                SAMSON::getActiveDocument()->getNodes(resIndexer, SBNode::IsType(SBNode::SideChain));
                SB_FOR(SBNode* node, nodeIndexer) {
                    SBNodeIndexer atIndexer;
                    node->getNodes(atIndexer, SBNode::IsType(SBNode::Atom));
                    SBQuantity xmid=0;
                    SBQuantity ymid=0;
                    SBQuantity zmid=0;
                    int count=0;

                    SB_FOR(SBNode* atom, atIndexer) {
                        count++;
                        SBAtom* atom = static_cast<SBAtom*>(atom);
                        SBPosition3 position = atom->getPosition();
                        xmid += position.v[0];
                        ymid += position.v[1];
                        zmid += position.v[2];
                    }
                    xmid=xmid/count;
                    ymid=xmid/count;
                    zmid=xmid/count;





                }







            }
        }
    }

}


