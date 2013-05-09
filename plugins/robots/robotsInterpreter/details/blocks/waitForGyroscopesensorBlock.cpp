#include "waitforGyroscopeSensorBlock.h"

#include "../../sensorConstants.h"

using namespace qReal;
using namespace interpreters::robots;
using namespace interpreters::robots::details::blocks;

WaitForGyroscopeSensorBlock::WaitForGyroscopeSensorBlock(details::RobotModel * const robotModel)
	: WaitForSensorBlock(robotModel, sensorType::gyroscope)
{
}

void WaitForGyroscopeSensorBlock::responseSlot(int reading)
{
	int const targetPercents = evaluate("Percents").toInt();
	processResponce(reading, targetPercents);
}

interpreters::robots::details::robotParts::Sensor *WaitForGyroscopeSensorBlock::sensor() const
{
	return mRobotModel->soundSensor(mPort);
}

QString WaitForGyroscopeSensorBlock::name() const
{
	return tr("Gyroscope");
}
