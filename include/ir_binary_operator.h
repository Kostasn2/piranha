#ifndef PIRANHA_IR_BINARY_OPERATOR_H
#define PIRANHA_IR_BINARY_OPERATOR_H

#include "ir_value.h"

#include "pkey_value_lookup.h" 

namespace piranha {

	class CompilationError;
	class IrNodeDefinition;

	class IrBinaryOperator : public IrValue {
	public:
		enum OPERATOR {
			DOT,
			POINTER,
			ADD,
			SUB,
			MUL,
			DIV
		};

	public:
		IrBinaryOperator(OPERATOR op, IrValue *leftOperand, IrValue *rightOperand);
		~IrBinaryOperator();

		OPERATOR getOperator() const { return m_operator; }
		IrValue *getLeft() const { return m_leftOperand; }
		IrValue *getRight() const { return m_rightOperand; }

		virtual IrParserStructure *resolveLocalName(const std::string &name) const;
		virtual IrParserStructure *getImmediateReference(const IrReferenceQuery &query, IrReferenceInfo *output);

	protected:
		void _expand(IrContextTree *tree);
		virtual NodeOutput *_generateNodeOutput(IrContextTree *context, NodeProgram *program);
		virtual Node *_generateNode(IrContextTree *context, NodeProgram *program);

	protected:
		OPERATOR m_operator;
		IrValue *m_leftOperand;
		IrValue *m_rightOperand;
	};

} /* namespace piranha */

#endif /* PIRANHA_IR_BINARY_OPERATOR_H */
