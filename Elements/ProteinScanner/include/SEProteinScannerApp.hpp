#pragma once 

#include "SBDApp.hpp"
#include "SEProteinScannerAppGUI.hpp"
#include "SEProteinScannerGrid.hpp"
#include "SEProteinScannerGridBoolean.hpp"


/// This class implements the functionality of the app

// SAMSON Element generator pro tip: add non-GUI functionality in this class. The GUI functionality should go in the SEProteinScannerAppGUI class

class SEProteinScannerApp : public SBDApp {

	SB_CLASS

public :

	/// \name Constructors and destructors
	//@{

	SEProteinScannerApp();																													///< Constructs an app
	virtual ~SEProteinScannerApp();																											///< Destructs the app

	//@}

	/// \name GUI
	//@{

	SEProteinScannerAppGUI*											getGUI() const;															///< Returns a pointer to the GUI of the app


	//@}
    SBIAPosition3*                                                   gridsize() const;

    SEProteinScannerGrid*                                           gridfill(SBIAPosition3& minmax,SBQuantity::length voxsize, int winsize) const;

    bool                                                            Scan(SBQuantity::length x,SBQuantity::length y, SBQuantity::length z,SBQuantity::length distcont,SBNodeIndexer ligandAtomIndexer) const;

    SEProteinScannerGridBoolean*                                    GridBoolFill(SBNodeIndexer ligandAtomIndexer,SBQuantity::length distcont,SBIAPosition3& minmax,SBQuantity::length voxsize,int winsize) const;

    void                                                            compute(SBQuantity::length contdist,SBQuantity::length voxsize,int winsize, const QString& path, int nbrot) const;

    void                                                            predict(SBQuantity::length voxsize,int winsize, QString filename) const;

    void                                                            rotation(int axe,int nbrot) const ;

    /* void                                                            predictdatabase(SBQuantity::length voxsize,int winsize) const{ */

};


SB_REGISTER_TARGET_TYPE(SEProteinScannerApp, "SEProteinScannerApp", "99C0A760-9364-6814-14D1-FB1D6DE66634");
SB_DECLARE_BASE_TYPE(SEProteinScannerApp, SBDApp);
