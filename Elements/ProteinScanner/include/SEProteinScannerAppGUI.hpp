#pragma once


#include "SBGApp.hpp" 
#include "ui_SEProteinScannerAppGUI.h"

class SEProteinScannerApp;

/// This class implements the GUI of the app

// SAMSON Element generator pro tip: add GUI functionality in this class. The non-GUI functionality should go in the SEProteinScannerApp class

class SEProteinScannerAppGUI : public SBGApp {

	Q_OBJECT

public:

	/// \name Constructors and destructors
	//@{

	SEProteinScannerAppGUI(SEProteinScannerApp* t);																									///< Constructs a GUI for the app
	virtual ~SEProteinScannerAppGUI();																										///< Destructs the GUI of the app

	//@}

	/// \name App
	//@{

	SEProteinScannerApp*												getApp() const;															///< Returns a pointer to the app

	//@}

	/// \name Identity
	//@{

	virtual SBCContainerUUID									getUUID() const;														///< Returns the widget UUID
	virtual QString												getName() const;														///< Returns the widget name (used as a title for the embedding window)
	virtual QPixmap												getLogo() const;														///< Returns the widget logo
	int															getFormat() const;														///< Returns the widget format
	virtual QString												getCitation() const;													///< Returns the citation information

	//@}

	///\name Settings
	//@{

	void														loadSettings(SBGSettings* settings);										///< Load GUI settings
	void														saveSettings(SBGSettings* settings);										///< Save GUI settings

	//@}

public slots:

	// SAMSON Element generator pro tip: add slots here to interact with your app

private:

	Ui::SEProteinScannerAppGUIClass									ui;

};

