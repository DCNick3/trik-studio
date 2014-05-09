#include "robotsPlugin.h"

#include <QtWidgets/QApplication>

#include <qrkernel/settingsManager.h>

using namespace qReal;
using namespace interpreterCore;

static int const gridWidth = 25; // Half of element size

RobotsPlugin::RobotsPlugin()
	: mMainWindowInterpretersInterface(nullptr)
{
	mInterpreterCoreTranslator.load(":/interpreterCore_" + QLocale::system().name());
	mInterpreterBaseTranslator.load(":/interpreterBase_" + QLocale::system().name());
	mCommonTwoDModelTranslator.load(":/commonTwoDModel_" + QLocale::system().name());
	QApplication::installTranslator(&mInterpreterCoreTranslator);
	QApplication::installTranslator(&mInterpreterBaseTranslator);
	QApplication::installTranslator(&mCommonTwoDModelTranslator);

	// This will start kit plugins loading and so on so we must to load translators first.
	mRobotsPluginFacade.reset(new RobotsPluginFacade);
}

void RobotsPlugin::init(PluginConfigurator const &configurator)
{
	mRobotsPluginFacade->init(configurator);

	SettingsManager::setValue("IndexGrid", gridWidth);

//	details::Tracer::debug(details::tracer::enums::initialization, "RobotsPlugin::init", "Initializing done");
}

qReal::Customizer *RobotsPlugin::customizationInterface()
{
	return &mRobotsPluginFacade->customizer();
}

QList<ActionInfo> RobotsPlugin::actions()
{
	return mRobotsPluginFacade->actionsManager().actions();
}

QList<HotKeyActionInfo> RobotsPlugin::hotKeyActions()
{
	return mRobotsPluginFacade->actionsManager().hotKeyActionInfos();
}

QPair<QString, PreferencesPage *> RobotsPlugin::preferencesPage()
{
	return qMakePair(QObject::tr("Robots"), mRobotsPluginFacade->robotsSettingsPage());
}

void RobotsPlugin::showRobotSettings()
{
	mMainWindowInterpretersInterface->openSettingsDialog(tr("Robots"));
}

void RobotsPlugin::updateSettings()
{
//	details::Tracer::debug(
//			details::tracer::enums::initialization
//			, "RobotsPlugin::updateSettings", "Updating settings, model and sensors are going to be reinitialized..."
//			);

//	robots::enums::robotModelType::robotModelTypeEnum typeOfRobotModel
//			= static_cast<robots::enums::robotModelType::robotModelTypeEnum>(SettingsManager::value("robotModel").toInt());
//	if (typeOfRobotModel != robots::enums::robotModelType::trik) {
//		mInterpreter.setRobotModelType(typeOfRobotModel);
//	}

//	QString const typeOfCommunication = SettingsManager::value("valueOfCommunication").toString();
//	mInterpreter.setCommunicator(typeOfCommunication);
//	mInterpreter.configureSensors(
//			static_cast<robots::enums::sensorType::SensorTypeEnum>(SettingsManager::instance()->value("port1SensorType").toInt())
//			, static_cast<robots::enums::sensorType::SensorTypeEnum>(SettingsManager::instance()->value("port2SensorType").toInt())
//			, static_cast<robots::enums::sensorType::SensorTypeEnum>(SettingsManager::instance()->value("port3SensorType").toInt())
//			, static_cast<robots::enums::sensorType::SensorTypeEnum>(SettingsManager::instance()->value("port4SensorType").toInt())
//	);
//	m2dModelAction->setVisible(typeOfRobotModel == robots::enums::robotModelType::twoD);
//	mConnectToRobotAction->setVisible(typeOfRobotModel == robots::enums::robotModelType::nxt);
//	if (typeOfRobotModel == robots::enums::robotModelType::twoD) {
//		mInterpreter.setD2ModelWidgetActions(mRunAction, mStopRobotAction);
//	} else {
//		mInterpreter.showD2ModelWidget(false);
//	}

//	updateEnabledActions();

//	details::Tracer::debug(details::tracer::enums::initialization, "RobotsPlugin::updateSettings", "Done updating settings");
}

void RobotsPlugin::closeNeededWidget()
{
//	mInterpreter.stopRobot();
//	mInterpreter.closeD2ModelWidget();
//	mInterpreter.closeWatchList();
}

void RobotsPlugin::activeTabChanged(Id const &rootElementId)
{
//	updateEnabledActions();
//	bool const enabled = rootElementId.type() == robotDiagramType || rootElementId.type() == subprogramDiagramType;
//	mInterpreter.onTabChanged(rootElementId, enabled);
}

void RobotsPlugin::rereadSettings()
{
//	updateTitlesVisibility();
//	mInterpreter.setNoiseSettings();
//	updateBlocksOnPalette();
//	reinitModelType();
}

//void RobotsPlugin::updateBlocksOnPalette()
//{
//	mMainWindowInterpretersInterface->setVisibleForAllElementsInPalette(false);
//	IdList const commonBlocks = mInterpreter->providedBlocks();
//	foreach (Id const &id, commonBlocks) {
//		mMainWindowInterpretersInterface->setElementInPaletteVisible(id, true);
//	}

//	IdList const unsupportedBlocks = mKitPluginManager.selectedKit().unsupportedBlocks();
//	foreach (Id const &id, unsupportedBlocks) {
//		mMainWindowInterpretersInterface->setElementInPaletteEnabled(id, false);
//	}
//}