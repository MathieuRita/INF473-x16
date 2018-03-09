#pragma once


/*! \file SEColorizerColorScheme.hpp */


#include "SBDColor.hpp"
#include "SBDDataGraphNodeColorScheme.hpp"

#include <QString>


/// \brief This class describes a constant color scheme


class SEColorizerColorScheme : public SBNodeColorScheme {

 public:

    /// \name Constructors and destructors
    //@{

    SEColorizerColorScheme();																															///< Constructs a color (1.0f, 1.0f, 1.0f, 1.0f)
    SEColorizerColorScheme(QString gridPath);																															///< Constructs a color (1.0f, 1.0f, 1.0f, 1.0f)

    virtual ~SEColorizerColorScheme();																												///< Destructs the color

    //@}

    /// \name Serialization
    //@{

    bool														isSerializable() const;													///< Returns true

    virtual void												serialize(SBCSerializer* serializer, const SBNodeIndexer& nodeIndexer, const SBVersionNumber& sdkVersionNumber = SB_SDK_VERSION_NUMBER, const SBVersionNumber& classVersionNumber = SBVersionNumber(1, 0, 0)) const;										///< Serializes the document
    virtual void												unserialize(SBCSerializer* serializer, const SBNodeIndexer& nodeIndexer, const SBVersionNumber& sdkVersionNumber = SB_SDK_VERSION_NUMBER, const SBVersionNumber& classVersionNumber = SBVersionNumber(1, 0, 0));											///< Unserializes the document

    //@}

    /// \name Colors
    //@{

    virtual void												getColor(float* color, SBDDataGraphNode* node = 0, const SBPosition3& position = SBPosition3::zero) const;										///< Serializes the document

    //@}
    // proximity grid
    bool***                                                    grid;
    SBPosition3                                                origin;
    int                                                        sizeX;
    int                                                        sizeY;
    int                                                        sizeZ;
    SBQuantity::angstrom                                       voxelSize;
};
