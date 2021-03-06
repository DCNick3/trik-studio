/* Copyright 2015-2016 Dmitry Mordvinov
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

#include <QtCore/QRectF>

#include "elementInfo.h"

#include "modelsDeclSpec.h"

namespace qReal {

/// Container for convenient storing node element data for passing it into methods with just one parameter.
class QRGUI_MODELS_EXPORT NodeInfo
{
public:
	NodeInfo();

	NodeInfo(const Id &graphicalId
			, const Id &logicalId
			, LogicalModelAssistInterface &logicalModel
			, GraphicalModelAssistInterface &graphicalModel);

	NodeInfo(const Id &id
			, const Id &logicalId
			, const Id &logicalParent
			, const Id &graphicalParent
			, const QMap<QString, QVariant> &logicalProperties
			, const QMap<QString, QVariant> &graphicalProperties
			, const Id &explosionTarget);

	QDataStream &serialize(QDataStream &out) const;

	QDataStream &deserialize(QDataStream &in);

	QMimeData *mimeData() const;

	static ElementInfo fromMimeData(const QMimeData *mimeData);

	bool isEdge() const;

	Id parent() const;

	QString name() const;

	QPointF position() const;

	Id newId();

	Id newLogicalId();

	void setPos(const QPointF &position);

	const Id &explosionTarget() const;

	const Id &id() const;

	const Id &logicalId() const;

	void setLogicalId(const Id &id);

	const Id &logicalParent() const;

	void setLogicalParent(const Id &parent);

	const Id &graphicalParent() const;

	void setGraphicalParent(const Id &parent);

	const QList<QString> logicalProperties() const;

	QVariant logicalProperty(const QString &propertyName) const;

	void setLogicalProperty(const QString &propertyName, const QVariant &propertyValue);

	void setAllLogicalProperties(const QMap<QString, QVariant> &logicalProperties);

	const QList<QString> graphicalProperties() const;

	QVariant graphicalProperty(const QString &propertyName) const;

	void setGraphicalProperty(const QString &propertyName, const QVariant &propertyValue);

	void setAllGraphicalProperties(const QMap<QString, QVariant> &graphicalProperties);

	/// Gets element info of an edge.
	ElementInfo getInfo() const;

private:
	ElementInfo mInfo;
};

}

QRGUI_MODELS_EXPORT QDataStream &operator<< (QDataStream &out, const qReal::NodeInfo &data);
QRGUI_MODELS_EXPORT QDataStream &operator>> (QDataStream &in, qReal::NodeInfo &data);
QRGUI_MODELS_EXPORT bool operator== (const qReal::NodeInfo &first, const qReal::NodeInfo &second);
