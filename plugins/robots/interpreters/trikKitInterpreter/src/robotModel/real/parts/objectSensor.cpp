#include "objectSensor.h"

using namespace trikKitInterpreter::robotModel::real::parts;
using namespace interpreterBase::robotModel;

ObjectSensor::ObjectSensor(const DeviceInfo &info, const PortInfo &port
		, utils::TcpRobotCommunicator &robotCommunicator)
	: robotModel::parts::TrikObjectSensor(info, port)
	, mRobotCommunicator(robotCommunicator)
{
}

void ObjectSensor::init()
{
}

void ObjectSensor::detect()
{
}

void ObjectSensor::read()
{
	emit newData({0, 0, 0});
}
