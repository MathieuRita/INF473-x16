#include "SEProteinScannerApp.hpp"
#include "SEProteinScannerAppGUI.hpp"

SEProteinScannerApp::SEProteinScannerApp() {

	setGUI(new SEProteinScannerAppGUI(this));
	getGUI()->loadDefaultSettings();

}

SEProteinScannerApp::~SEProteinScannerApp() {

	getGUI()->saveDefaultSettings();
	delete getGUI();

}

SEProteinScannerAppGUI* SEProteinScannerApp::getGUI() const { return static_cast<SEProteinScannerAppGUI*>(SBDApp::getGUI()); }
