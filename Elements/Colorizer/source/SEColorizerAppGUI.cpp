#include "SEColorizerAppGUI.hpp"
#include "SEColorizerApp.hpp"
#include "SAMSON.hpp"
#include "SBGWindow.hpp"

SEColorizerAppGUI::SEColorizerAppGUI( SEColorizerApp* t ) : SBGApp( t ) {

	ui.setupUi( this );

}

SEColorizerAppGUI::~SEColorizerAppGUI() {

}

SEColorizerApp* SEColorizerAppGUI::getApp() const { return static_cast<SEColorizerApp*>(SBGApp::getApp()); }

void SEColorizerAppGUI::loadSettings( SBGSettings *settings ) {

	if ( settings == NULL ) return;
	
	// SAMSON Element generator pro tip: complete this function so your app can save its GUI state from one session to the next

}

void SEColorizerAppGUI::saveSettings( SBGSettings *settings ) {

	if ( settings == NULL ) return;

	// SAMSON Element generator pro tip: complete this function so your app can save its GUI state from one session to the next

}

SBCContainerUUID SEColorizerAppGUI::getUUID() const { return SBCContainerUUID( "A0D42756-0C7E-0738-27E6-E4458E2FE312" );}

QPixmap SEColorizerAppGUI::getLogo() const { 
	
	// SAMSON Element generator pro tip: this icon will be visible in the GUI title bar. 
	// Modify it to better reflect the purpose of your app.

	return QPixmap(QString::fromStdString(SB_ELEMENT_PATH + "/resource/icons/SEColorizerAppIcon.png"));

}

QString SEColorizerAppGUI::getName() const { 

	// SAMSON Element generator pro tip: this string will be the GUI title. 
	// Modify this function to have a user-friendly description of your app inside SAMSON

	return "SEColorizerApp"; 

}

int SEColorizerAppGUI::getFormat() const { 
	
	// SAMSON Element generator pro tip: modify these default settings to configure the window
	//
	// SBGWindow::Savable : let users save and load interface settings (implement loadSettings and saveSettings)
	// SBGWindow::Lockable : let users lock the window on top
	// SBGWindow::Resizable : let users resize the window
	// SBGWindow::Citable : let users obtain citation information (implement getCitation)
	
	return (SBGWindow::Savable | SBGWindow::Lockable | SBGWindow::Resizable | SBGWindow::Citable);

}

QString SEColorizerAppGUI::getCitation() const {

	// SAMSON Element generator pro tip: modify this function to add citation information

	return
		"If you use this app in your work, please cite: <br/>"
		"<br/>"
		"[1] <a href=\"https://www.samson-connect.net\">https://www.samson-connect.net</a><br/>";
	
}

void SEColorizerAppGUI::onColorizedClicked(){
    getApp() -> colorize();
}
