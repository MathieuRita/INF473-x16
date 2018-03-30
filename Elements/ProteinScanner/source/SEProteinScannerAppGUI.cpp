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
	
    ui.lineEditPath->setText(settings->loadQStringValue("proteinFolder", ""));
    ui.doubleSpinBoxContactDistance->setValue(settings->loadDoubleValue("contactDistance", 5.0));
    ui.doubleSpinBoxVoxelSize->setValue(settings->loadDoubleValue("voxelSize", 3.0));
    ui.spinBoxWindowSize->setValue(settings->loadIntValue("windowSize", 2));
     ui.lineEditOutputFile->setText(settings->loadQStringValue("outputFile", ""));

}

void SEProteinScannerAppGUI::saveSettings( SBGSettings *settings ) {

	if ( settings == NULL ) return;

    settings->saveValue("proteinFolder", ui.lineEditPath->text());
    settings->saveValue("contactDistance", ui.doubleSpinBoxContactDistance->value());
    settings->saveValue("voxelSize", ui.doubleSpinBoxVoxelSize->value());
    settings->saveValue("windowSize", ui.spinBoxWindowSize->value());
    settings->saveValue("outputFile", ui.lineEditOutputFile->text());
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


    getApp()->compute(SBQuantity::angstrom(ui.doubleSpinBoxContactDistance->value()),SBQuantity::angstrom(ui.doubleSpinBoxVoxelSize->value()), ui.spinBoxWindowSize->value(), ui.lineEditPath->text(),ui.spinBoxRotate->value());

}


void  SEProteinScannerAppGUI::onBrowse(){

    QString path;
    SAMSON::getPathFromUser("Enter protein folder", path);

    ui.lineEditPath->setText(path);

}

void  SEProteinScannerAppGUI::onPredict(){


    getApp()->predict(SBQuantity::angstrom(ui.doubleSpinBoxVoxelSize->value()), ui.spinBoxWindowSize->value(), ui.lineEditOutputFile->text());

}
