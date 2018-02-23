#include "SEColorizerColorScheme.hpp"
#include "SBDDataGraphNode.hpp"
#include <iostream>

/// \class SEColorizerColorScheme
///
/// This class describes a constant color scheme in SAMSON. Please refer to \ref pageColorSchemes "this page" for more information.
///
/// \sa \ref pageColorSchemes


SEColorizerColorScheme::SEColorizerColorScheme() {}
SEColorizerColorScheme::SEColorizerColorScheme(QString gridPath) {}
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

    color[0]=1.0f;
    color[1]=0.5f;
    color[2]=1.0f;
    color[3]=1.0f;

}
