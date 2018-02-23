#include "SEColorizerApp.hpp"
#include "SEColorizerAppGUI.hpp"
#include "SEColorizerColorScheme.hpp"

#include "SAMSON.hpp"
#include "SBDDataGraphNodeMaterial.hpp"

SEColorizerApp::SEColorizerApp() {

	setGUI(new SEColorizerAppGUI(this));
	getGUI()->loadDefaultSettings();

}

SEColorizerApp::~SEColorizerApp() {

	getGUI()->saveDefaultSettings();
	delete getGUI();

}

SEColorizerAppGUI* SEColorizerApp::getGUI() const { return static_cast<SEColorizerAppGUI*>(SBDApp::getGUI()); }

void SEColorizerApp::colorize(){

    QString title = "Enter the path leading to the grid of proximity";
    QString gridPath = QFileDialog::getOpenFileName(0, title);

#if 1
    // creer le color scheme

    SEColorizerColorScheme* colorScheme = new SEColorizerColorScheme(gridPath);

    // appliquer le color scheme a la selection

    SBPointerIndexer<SBNode> const* selectedNodes = SAMSON::getActiveDocument()->getSelectedNodes();

    SAMSON::beginHolding("Predict active sites");

    SB_FOR(SBNode* node, *selectedNodes) {

        SBNodeMaterial* material = new SBNodeMaterial();
        material->setColorScheme(colorScheme);
        node->addMaterial(material);

    }

    SAMSON::endHolding();
#endif
}
