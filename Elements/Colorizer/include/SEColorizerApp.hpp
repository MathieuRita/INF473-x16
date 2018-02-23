#pragma once 

#include "SBDApp.hpp"
#include "SEColorizerAppGUI.hpp"


/// This class implements the functionality of the app

// SAMSON Element generator pro tip: add non-GUI functionality in this class. The GUI functionality should go in the SEColorizerAppGUI class

class SEColorizerApp : public SBDApp {

    SB_CLASS

public :

	/// \name Constructors and destructors
	//@{

	SEColorizerApp();																													///< Constructs an app
	virtual ~SEColorizerApp();																											///< Destructs the app

	//@}

	/// \name GUI
	//@{

	SEColorizerAppGUI*											getGUI() const;															///< Returns a pointer to the GUI of the app

	//@}
    void                                                        colorize();
};


SB_REGISTER_TARGET_TYPE(SEColorizerApp, "SEColorizerApp", "6A325F0B-7F22-736C-0DAF-2C78316BF58B");
SB_DECLARE_BASE_TYPE(SEColorizerApp, SBDApp);
