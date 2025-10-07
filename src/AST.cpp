#include "AST.h"

namespace Mini
{
    void NumberExpr::accept(ASTVisitor &v) { v.visit(*this); }
    void VarExpr::accept(ASTVisitor &v) { v.visit(*this); }
    void BinaryExpr::accept(ASTVisitor &v) { v.visit(*this); }
    void LetStmt::accept(ASTVisitor &v) { v.visit(*this); }
    void AssignStmt::accept(ASTVisitor &v) { v.visit(*this); }
    void PrintStmt::accept(ASTVisitor &v) { v.visit(*this); }
    void BlockStmt::accept(ASTVisitor &v) { v.visit(*this); }
    void WhileStmt::accept(ASTVisitor &v) { v.visit(*this); }
    void Program::accept(ASTVisitor &v) { v.visit(*this); }
}
