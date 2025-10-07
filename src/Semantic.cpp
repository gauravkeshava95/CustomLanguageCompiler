#include "Semantic.h"
#include <stdexcept>

namespace Mini
{
    void SemanticAnalyzer::visit(VarExpr &v)
    {
        if (declared_.find(v.name) == declared_.end())
            throw std::runtime_error("Undeclared variable: " + v.name);
    }

    void SemanticAnalyzer::visit(BinaryExpr &b)
    {
        b.lhs->accept(*this);
        b.rhs->accept(*this);
    }

    void SemanticAnalyzer::visit(LetStmt &s)
    {
        s.init->accept(*this);
        declared_.insert(s.name);
    }

    void SemanticAnalyzer::visit(AssignStmt &s)
    {
        if (declared_.find(s.name) == declared_.end())
            throw std::runtime_error("Assignment to undeclared variable: " + s.name);
        s.val->accept(*this);
    }

    void SemanticAnalyzer::visit(PrintStmt &s)
    {
        s.expr->accept(*this);
    }

    void SemanticAnalyzer::visit(Program &p)
    {
        for (auto &st : p.statements)
            st->accept(*this);
    }

    void SemanticAnalyzer::visit(WhileStmt &w)
    {
        w.condition->accept(*this);
        if (w.body)
            w.body->accept(*this);
    }

    void SemanticAnalyzer::visit(BlockStmt &b)
    {
        for (auto &st : b.statements)
            st->accept(*this);
    }
}
