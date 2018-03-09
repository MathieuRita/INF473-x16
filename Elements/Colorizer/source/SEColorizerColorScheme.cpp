#include "SEColorizerColorScheme.hpp"
#include "SBDDataGraphNode.hpp"
#include <iostream>
#include <fstream>
#include <QString>
#include "SAMSON.hpp"
using namespace std;

/// \class SEColorizerColorScheme
///
/// This class describes a constant color scheme in SAMSON. Please refer to \ref pageColorSchemes "this page" for more information.
///
/// \sa \ref pageColorSchemes


SEColorizerColorScheme::SEColorizerColorScheme() {}

SEColorizerColorScheme::SEColorizerColorScheme(QString gridPath) {
    ifstream fichier(gridPath.toStdString(), ios::in);  // on ouvre le fichier en lecture
    if(fichier)  // si l'ouverture a réussi
    {
        double ox, oy, oz,vs;
        fichier >> vs >> ox>> oy>> oz >> sizeX >> sizeY >> sizeZ;;
        voxelSize = SBQuantity::angstrom(vs);
        origin.v[0] = SBQuantity::angstrom(ox);
        origin.v[1] = SBQuantity::angstrom(oy);
        origin.v[2] = SBQuantity::angstrom(oz);

        grid = new bool**[sizeX];
        for (int x = 0; x <sizeX; x++){
            grid[x] = new bool*[sizeY];
        }
        for (int x = 0; x <sizeX; x++){
            for(int y = 0; y<sizeY;y++){
                grid[x][y] = new bool[sizeZ];
            }
        }

        for (int x = 0; x <sizeX; x++){
            for(int y = 0; y<sizeY;y++){
                for(int z = 0; z<sizeZ ; z++){
                    fichier>>grid[x][y][z];
                }
            }
        }

        fichier.close();  // on ferme le fichier
    }
    else  // sinon
        cerr << "Impossible d'ouvrir le fichier !" << endl;
}


SEColorizerColorScheme::~SEColorizerColorScheme() {}

bool SEColorizerColorScheme::isSerializable() const { return false; }

void SEColorizerColorScheme::serialize(SBCSerializer* serializer, const SBNodeIndexer& nodeIndexer, const SBVersionNumber& sdkVersionNumber, const SBVersionNumber& classVersionNumber) const {

}

void SEColorizerColorScheme::unserialize(SBCSerializer* serializer, const SBNodeIndexer& nodeIndexer, const SBVersionNumber& sdkVersionNumber, const SBVersionNumber& classVersionNumber) {

}

void SEColorizerColorScheme::getColor(float* color, SBNode* node, const SBPosition3& position) const {

    //regarde les 8 sommets les plus proches dans le document
    //on lui applique une formule telle que 0 est sur le ligant et 1 en est eloigne
    //on colorie 0 en rouget et 1 en blanc et gradient de couleur entre les 2

    if (node->getType()!=SBNode::Atom) return;

    SBAtom* atom = static_cast<SBAtom*>(node);
    SBPosition3 position1 = atom->getPosition();

    int x = (int)((SBQuantity::angstrom(position1.v[0])-origin.v[0])/voxelSize).getValue();
    int y = (int)((SBQuantity::angstrom(position1.v[1])-origin.v[1])/voxelSize).getValue();
    int z = (int)((SBQuantity::angstrom(position1.v[2])-origin.v[2])/voxelSize).getValue();

    color[0] = 1.0f;
    color[1] = 1.0f;
    color[2] = 1.0f;
    color[3] = 1.0f;

    if (x<0) return;
    if (y<0) return;
    if (z<0) return;

    if (x+1>sizeX-1) return;
    if (y+1>sizeY-1) return;
    if (z+1>sizeZ-1) return;

    float distance = 0.0f;
    float weightedSum = 0.0f;


    for (int i = x; i <x+2; i++){
        for(int j = y; j<y+2;j++){
            for(int k = z; k<z+2 ; k++){
                distance += (float) ((SBQuantity::angstrom((position1-(SBPosition3(i*voxelSize+origin.v[0],j*voxelSize+origin.v[1],k*voxelSize+origin.v[2]))).norm())).getValue());
                weightedSum += (float)(1-grid[i][j][k])*((float)SBQuantity::angstrom((position1-(SBPosition3(i*voxelSize+origin.v[0],j*voxelSize+origin.v[1],k*voxelSize+origin.v[2]))).norm()).getValue());
            }
        }
    }

    color[0] = 1.0f-weightedSum/distance;
    color[1] = 0.0f;
    color[2] = 0.0f;
    color[3] = 1.0f;

}
