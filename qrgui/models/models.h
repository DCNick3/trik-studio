#pragma once

#include "qrgui/models/details/graphicalModel.h"
#include "qrgui/models/details/logicalModel.h"
#include "qrgui/models/graphicalModelAssistApi.h"
#include "qrgui/models/logicalModelAssistApi.h"
#include "qrgui/models/exploser.h"

namespace qReal {
namespace models {

class QRGUI_MODELS_EXPORT Models
{
public:
	Models(QString const &workingCopy, EditorManagerInterface const &editorManager);
	~Models();

	QAbstractItemModel *graphicalModel() const;
	QAbstractItemModel *logicalModel() const;

	GraphicalModelAssistApi &graphicalModelAssistApi() const;
	LogicalModelAssistApi &logicalModelAssistApi() const;

	qrRepo::RepoControlInterface &repoControlApi() const;

	qrRepo::LogicalRepoApi const &logicalRepoApi() const;
	qrRepo::LogicalRepoApi &mutableLogicalRepoApi() const;

	qrRepo::GraphicalRepoApi const &graphicalRepoApi() const;

	Exploser &exploser() const;

	void reinit();

private:
	models::details::GraphicalModel *mGraphicalModel;
	models::details::GraphicalPartModel *mGraphicalPartModel;
	models::details::LogicalModel *mLogicalModel;
	qrRepo::RepoControlInterface *mRepoApi;
	Exploser *mExploser;
};

}
}
