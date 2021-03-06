/* Copyright 2007-2015 QReal Research Group
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#pragma once

#include <kitBase/blocksBase/common/deviceBlock.h>

#include "twoDModel/robotModel/parts/marker.h"

namespace twoDModel {
namespace blocks {

/// An interpreter`s implementation for RemoveMarker block. See description in documentation.
class TWO_D_MODEL_EXPORT MarkerUpBlock
		: public kitBase::blocksBase::common::DeviceBlock<robotModel::parts::Marker>
{
	Q_OBJECT

public:
	explicit MarkerUpBlock(kitBase::robotModel::RobotModelInterface &robotModel);

private:
	void doJob(robotModel::parts::Marker &marker) override;
};

}
}
