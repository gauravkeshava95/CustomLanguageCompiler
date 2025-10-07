#pragma once
#include <string>
#include <unordered_set>
#include "AST.h"

namespace Mini
{
    class SemanticAnalyzer : public ASTVisitor
    {
        std::unordered_set<std::string> declared_;

    public:
        void visit(NumberExpr &) override {}
        void visit(VarExpr &v) override;
        void visit(BinaryExpr &b) override;
        void visit(LetStmt &s) override;
        void visit(AssignStmt &s) override;
        void visit(PrintStmt &s) override;
        void visit(Program &p) override;
        void visit(WhileStmt &w) override;
        void visit(BlockStmt &b) override;
    };
}
