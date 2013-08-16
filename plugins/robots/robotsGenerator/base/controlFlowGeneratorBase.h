#pragma once

#include "controlFlow.h"
#include "primaryControlFlowValidator.h"

namespace qReal {
namespace robots {
namespace generators {

class ControlFlowGeneratorBase : public QObject
{
public:
	ControlFlowGeneratorBase(LogicalModelAssistInterface const &model
			, ErrorReporterInterface &errorReporter
			, GeneratorCustomizer const &customizer
			, Id const &diagramId
			, QObject *parent = 0);

	bool preGenerationCheck();

	virtual ControlFlow *generate();

protected:
	void error(QString const &message, Id const &id = Id());
	enums::semantics::Semantics semanticsOf(Id const &id) const;

private:
	LogicalModelAssistInterface const &mModel;
	ErrorReporterInterface &mErrorReporter;
	GeneratorCustomizer const &mCustomizer;
	Id const mDiagram;
	PrimaryControlFlowValidator mValidator;
};

}
}
}
