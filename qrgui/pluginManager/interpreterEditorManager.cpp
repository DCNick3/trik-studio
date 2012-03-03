#include <QtCore/QCoreApplication>
#include <QtGui/QMessageBox>
#include <QtGui/QIcon>
#include <QtCore/QtDebug>

#include "interpreterEditorManager.h"
#include "../../qrkernel/ids.h"
#include "../../qrrepo/repoApi.h"
#include "../umllib/nodeElement.h"
#include "../umllib/edgeElement.h"
#include "../../qrkernel/exception/exception.h"
#include "beep.h"

using namespace qReal;

InterpreterEditorManager::InterpreterEditorManager(QObject *parent)
	: QObject(parent)
{
	qrRepo::RepoApi *repo = new qrRepo::RepoApi("testMetamodel.qrs");
	mEditorRepoApi.insert("test", repo);
}

IdList InterpreterEditorManager::editors() const
{
	IdList result;
	foreach (qrRepo::RepoApi *repo, mEditorRepoApi.values()) {
		foreach (Id elem, repo->elementsByType("MetaEditorDiagramNode"))
			result << Id(repo->name(repo->parent(elem)), repo->name(elem));
	}
	return result;
}

IdList InterpreterEditorManager::diagrams(const Id &editor) const
{
	qrRepo::RepoApi *repoMetaModel = NULL;
	Id edit;
	foreach (qrRepo::RepoApi *repo, mEditorRepoApi.values())
		foreach (Id edi, repo->elementsByType("MetamodelDiagram"))
			if (editor.editor() == repo->name(edi)) {
				repoMetaModel = repo;
				edit = edi;
			}
	IdList const editorChildren = repoMetaModel->children(edit);
	IdList result;
	QString editName = repoMetaModel->name(edit);
	foreach (Id const child, editorChildren)
		if (child.element() == "MetaEditorDiagramNode")
			result << Id(editName, repoMetaModel->name(child));
	return result;
}

IdList InterpreterEditorManager::elements(const Id &diagram) const
{
	IdList result;
	foreach (qrRepo::RepoApi *repo, mEditorRepoApi.values())
		foreach (Id editor, repo->elementsByType("MetamodelDiagram"))
			foreach (Id editorChild, repo->children(editor))
				if (diagram == editorChild)
					result = repo->children(editorChild);
	return result;
}

QString InterpreterEditorManager::friendlyName(const Id &id) const
{
	foreach (qrRepo::RepoApi *repo, mEditorRepoApi.values())
		if (repo->exist(id))
			return repo->name(id);
	return "";
}

bool InterpreterEditorManager::hasElement(Id const &elementId) const
{
	foreach (qrRepo::RepoApi *repo, mEditorRepoApi.values())
		if (repo->exist(elementId))
			return true;
	return false;
}

QString InterpreterEditorManager::propertyDescription(const Id &id, const QString &propertyName) const
{
	QString property = "";
	foreach (qrRepo::RepoApi *repo, mEditorRepoApi.values())
		if (repo->exist(id))
			property = repo->stringProperty(id, propertyName);
	return property;
}

QStringList InterpreterEditorManager::getAllChildrenTypesOf(Id const &parent) const
{
	QStringList result;
	qrRepo::RepoApi *repoMetaModel;
	foreach (qrRepo::RepoApi *repo, mEditorRepoApi.values())
		if (repo->exist(parent))
			repoMetaModel = repo;
	foreach (Id child, repoMetaModel->children(parent))
		result << repoMetaModel->typeName(child);
	return result;
}

bool InterpreterEditorManager::isParentOf(Id const &child, Id const &parent) const // child — EnginesForware, parent — AbstractNode
{
	qrRepo::RepoApi *repoMetaModel;
	foreach (qrRepo::RepoApi *repo, mEditorRepoApi.values())
		if (repo->exist(parent))
			repoMetaModel = repo;
	return (repoMetaModel->parent(child) == parent);
}

IdList InterpreterEditorManager::getConnectedTypes(const Id &id) const
{
	qrRepo::RepoApi *repoMetaModel;
	foreach (qrRepo::RepoApi *repo, mEditorRepoApi.values())
		if (repo->exist(id))
			repoMetaModel = repo;
	return repoMetaModel->connectedElements(id);
}

bool InterpreterEditorManager::isEditor(const Id &id) const
{
	foreach (qrRepo::RepoApi *repo, mEditorRepoApi.values())
		foreach (Id editor, repo->elementsByType("MetamodelDiagram"))
			if(editor == id)
				return true;
	return false;
	//return id.idSize() == 1;
}

bool InterpreterEditorManager::isDiagram(const Id &id) const
{
	qrRepo::RepoApi *repoMetaModel;
	foreach (qrRepo::RepoApi *repo, mEditorRepoApi.values())
		if (repo->exist(id))
			repoMetaModel = repo;
	return (repoMetaModel->name(id) == "MetaEditorDiagramNode");
	//return id.idSize() == 2;
}

bool InterpreterEditorManager::isElement(const Id &id) const
{
	qrRepo::RepoApi *repoMetaModel;
	foreach (qrRepo::RepoApi *repo, mEditorRepoApi.values())
		if (repo->exist(id))
			repoMetaModel = repo;
	return (repoMetaModel->name(id) != "MetamodelDiagram" && repoMetaModel->name(id) != "MetaEditorDiagramNode");
	//return id.idSize() == 3;
}

QString InterpreterEditorManager::getTypeName(const Id &id, const QString &name) const
{
	QString propertyType = "";
	foreach (qrRepo::RepoApi *repo, mEditorRepoApi.values())
		if (repo->exist(id))
			propertyType = repo->property(id, name).typeName();
	return propertyType;
}

QString InterpreterEditorManager::mouseGesture(Id const &id) const
{
	QString mouseGes = "";
	foreach (qrRepo::RepoApi *repo, mEditorRepoApi.values())
		if (repo->exist(id))
			mouseGes = repo->stringProperty(id, "path");
	return mouseGes;
}
////////////////////////////////////////////////////////////

//QIcon InterpreterEditorManager::icon(const Id &id) const
//{
//	SdfIconEngineV2 *engine = new SdfIconEngineV2(":/generated/shapes/" + id.element() + "Class.sdf");
//	// QIcon will take ownership of engine, no need for us to delete
//	return QIcon(engine);
//}

QString InterpreterEditorManager::propertyDisplayedName(Id const &id, QString const &propertyName) const
{
	QString displayedName = "";
	foreach (qrRepo::RepoApi *repo, mEditorRepoApi.values())
			foreach (Id editor, repo->elementsByType("MetamodelDiagram"))
				foreach (Id diagram, repo->children(editor))
					foreach (Id element, repo->children(diagram))
						if (element == id)
							foreach (Id child, repo->children(element))
								if (repo->name(child) == propertyName)
									displayedName = repo->stringProperty(child, "displayedName");
	return displayedName;
}

QString InterpreterEditorManager::getDefaultPropertyValue(Id const &id, QString name) const
{
	QString defaultProperty;
	foreach (qrRepo::RepoApi *repo, mEditorRepoApi.values())
		if (repo->exist(id))
			foreach(Id child, repo->children(id)) {
				if (repo->name(child) == name)
					defaultProperty = repo->stringProperty(child, "defaultValue");
			}
	return defaultProperty;
}

Id InterpreterEditorManager::findElementByType(QString const &type) const
{
	foreach (qrRepo::RepoApi *repo, mEditorRepoApi.values())
		foreach (Id editor, repo->elementsByType("MetamodelDiagram"))
			foreach (Id diagram, repo->children(editor))
				foreach (Id element, repo->children(diagram))
					if (type == repo->name(element))
						return Id(editor.id(), repo->name(diagram), repo->name(element));
	throw Exception("No type " + type + " in loaded plugins");
}

bool InterpreterEditorManager::loadPlugin(QString const &pluginName)
{
	return true;
}

bool InterpreterEditorManager::unloadPlugin(QString const &pluginName)
{
	return true;
}

//TODO:
QString InterpreterEditorManager::description(Id const &id) const
{
	return "";
}
//TODO:
QIcon InterpreterEditorManager::icon(Id const &id) const
{
	return QIcon();
}
//TODO:
Element* InterpreterEditorManager::graphicalObject(Id const &id) const
{
	Beep * beep = new Beep();
	return new NodeElement(beep);
}

IdList InterpreterEditorManager::getContainedTypes(const Id &id) const
{
	IdList containedTypes;
//	foreach (qrRepo::RepoApi *repo, mEditorRepoApi.values())
//		foreach (Id editor, repo->elementsByType("MetamodelDiagram"))
//			foreach (Id diagram, repo->children(editor))
//				foreach (Id element, repo->children(diagram))
//					if (repo->name(element) == "Container")
//						if (repo->from(element) == id)
//							containedTypes << repo->to(element);
	return containedTypes;
}

IdList InterpreterEditorManager::getUsedTypes(const Id &id) const
{
	IdList usedTypes;
	foreach (qrRepo::RepoApi *repo, mEditorRepoApi.values())
		foreach (Id editor, repo->elementsByType("MetamodelDiagram"))
			foreach (Id diagram, repo->children(editor))
				foreach (Id element, repo->children(diagram))
					if (element == id)
						foreach(Id child, repo->children(element))
							if (repo->name(child) == "MetaEntityUsage")
								usedTypes << repo->property(child, "type").value<Id>();
	return usedTypes;
}

QStringList InterpreterEditorManager::getEnumValues(Id const &id, const QString &name) const
{
	QStringList result;
	foreach (qrRepo::RepoApi *repo, mEditorRepoApi.values())
		foreach (Id editor, repo->elementsByType("MetamodelDiagram"))
			foreach (Id diagram, repo->children(editor))
				foreach (Id element, repo->children(diagram))
					if (repo->name(element) == id.element())
						foreach (Id child, repo->children(element))
							if (repo->name(child) == name)
								QString propertyTypeName = repo->typeName(child);


	return QStringList();
}

QStringList InterpreterEditorManager::getPropertyNames(Id const &id) const
{
	QStringList result;
	foreach (qrRepo::RepoApi *repo, mEditorRepoApi.values())
			foreach (Id editor, repo->elementsByType("MetamodelDiagram"))
				foreach (Id diagram, repo->children(editor))
					foreach (Id element, repo->children(diagram))
						if (element == id)
							foreach (Id child, repo->children(element))
								if (repo->name(child) == "MetaEntity Attribute")
									result << repo->stringProperty(id, "displayedName");
	return result;
}

QStringList InterpreterEditorManager::getPropertiesWithDefaultValues(Id const &id) const
{
	return QStringList();
}

IdList InterpreterEditorManager::checkNeededPlugins(qrRepo::LogicalRepoApi const &logicalApi
		, qrRepo::GraphicalRepoApi const &graphicalApi) const
{
	return IdList();
}

QList<ListenerInterface *> InterpreterEditorManager::listeners() const
{
	return QList<ListenerInterface *>();
}

EditorInterface* InterpreterEditorManager::editorInterface(QString const &editor) const
{
	return NULL;
}

bool InterpreterEditorManager::isDiagramNode(Id const &id) const
{
	foreach (qrRepo::RepoApi *repo, mEditorRepoApi.values())
		foreach (Id editor, repo->elementsByType("MetamodelDiagram"))
			foreach (Id diagram, repo->children(editor))
				foreach (Id element, repo->children(diagram))
					if (element == id)
						if (repo->stringProperty(diagram, "nodeName") == repo->name(id))
							return true;
	return false;
}
