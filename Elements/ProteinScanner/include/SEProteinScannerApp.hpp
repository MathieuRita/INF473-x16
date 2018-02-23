#pragma once 

#include "SBDApp.hpp"
#include "SEProteinScannerAppGUI.hpp"


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
    void                                                            gridsize(SBIAPosition3& minmax) const;

};


SB_REGISTER_TARGET_TYPE(SEProteinScannerApp, "SEProteinScannerApp", "99C0A760-9364-6814-14D1-FB1D6DE66634");
SB_DECLARE_BASE_TYPE(SEProteinScannerApp, SBDApp);
