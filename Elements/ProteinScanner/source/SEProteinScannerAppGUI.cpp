#include "SEProteinScannerAppGUI.hpp"
#include "SEProteinScannerApp.hpp"
#include "SAMSON.hpp"
#include "SBGWindow.hpp"

SEProteinScannerAppGUI::SEProteinScannerAppGUI( SEProteinScannerApp* t ) : SBGApp( t ) {

	ui.setupUi( this );

}

SEProteinScannerAppGUI::~SEProteinScannerAppGUI() {

}

SEProteinScannerApp* SEProteinScannerAppGUI::getApp() const { return static_cast<SEProteinScannerApp*>(SBGApp::getApp()); }

void SEProteinScannerAppGUI::loadSettings( SBGSettings *settings ) {

	if ( settings == NULL ) return;
	
	// SAMSON Element generator pro tip: complete this function so your app can save its GUI state from one session to the next

}

void SEProteinScannerAppGUI::saveSettings( SBGSettings *settings ) {

	if ( settings == NULL ) return;

	// SAMSON Element generator pro tip: complete this function so your app can save its GUI state from one session to the next

}

SBCContainerUUID SEProteinScannerAppGUI::getUUID() const { return SBCContainerUUID( "D66D8C1D-AE31-5F90-6FAC-CF2D6AF04CEE" );}

QPixmap SEProteinScannerAppGUI::getLogo() const { 
	
	// SAMSON Element generator pro tip: this icon will be visible in the GUI title bar. 
	// Modify it to better reflect the purpose of your app.

	return QPixmap(QString::fromStdString(SB_ELEMENT_PATH + "/Resource/icons/SEProteinScannerAppIcon.png"));

}

QString SEProteinScannerAppGUI::getName() const { 

	// SAMSON Element generator pro tip: this string will be the GUI title. 
	// Modify this function to have a user-friendly description of your app inside SAMSON

	return "SEProteinScannerApp"; 

}

int SEProteinScannerAppGUI::getFormat() const { 
	
	// SAMSON Element generator pro tip: modify these default settings to configure the window
	//
	// SBGWindow::Savable : let users save and load interface settings (implement loadSettings and saveSettings)
	// SBGWindow::Lockable : let users lock the window on top
	// SBGWindow::Resizable : let users resize the window
	// SBGWindow::Citable : let users obtain citation information (implement getCitation)
	
	return (SBGWindow::Savable | SBGWindow::Lockable | SBGWindow::Resizable | SBGWindow::Citable);

}

QString SEProteinScannerAppGUI::getCitation() const {

	// SAMSON Element generator pro tip: modify this function to add citation information

	return
		"If you use this app in your work, please cite: <br/>"
		"<br/>"
		"[1] <a href=\"https://www.samson-connect.net\">https://www.samson-connect.net</a><br/>";
	
}


void  SEProteinScannerAppGUI::onScan(){


    getApp()->compute(SBQuantity::angstrom(ui.doubleSpinBoxContactDistance->value()),SBQuantity::angstrom(ui.doubleSpinBoxVoxelSize->value()), ui.spinBoxWindowSize->value());

}
