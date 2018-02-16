#include "SEColorizerApp.hpp"
#include "SEColorizerAppGUI.hpp"

SEColorizerApp::SEColorizerApp() {

	setGUI(new SEColorizerAppGUI(this));
	getGUI()->loadDefaultSettings();

}

SEColorizerApp::~SEColorizerApp() {

	getGUI()->saveDefaultSettings();
	delete getGUI();

}

SEColorizerAppGUI* SEColorizerApp::getGUI() const { return static_cast<SEColorizerAppGUI*>(SBDApp::getGUI()); }
