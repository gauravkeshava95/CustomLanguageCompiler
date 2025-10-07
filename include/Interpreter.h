#pragma once
#include "AST.h"
#include <unordered_map>
#include <string>
#include <iostream>

namespace Mini
{
    class Interpreter : public ASTVisitor
    {
        std::unordered_map<std::string, int> variables;
        int lastValue{0}; // holds last evaluated expr value

    public:
        void visit(NumberExpr &e) override;
        void visit(VarExpr &e) override;
        void visit(BinaryExpr &e) override;

        void visit(LetStmt &s) override;
        void visit(AssignStmt &s) override;
        void visit(PrintStmt &s) override;
        void visit(BlockStmt &b) override;
        void visit(WhileStmt &w) override;
        void visit(Program &p) override;
    };
}
