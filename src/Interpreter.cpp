#include "Interpreter.h"

namespace Mini
{
    void Interpreter::visit(NumberExpr &e)
    {
        lastValue = e.value;
    }

    void Interpreter::visit(VarExpr &e)
    {
        lastValue = variables[e.name];
    }

    void Interpreter::visit(BinaryExpr &e)
    {
        e.lhs->accept(*this);
        int lhs = lastValue;
        e.rhs->accept(*this);
        int rhs = lastValue;

        switch (e.op)
        {
        case BinaryExpr::Op::Add:
            lastValue = lhs + rhs;
            break;
        case BinaryExpr::Op::Sub:
            lastValue = lhs - rhs;
            break;
        case BinaryExpr::Op::Mul:
            lastValue = lhs * rhs;
            break;
        case BinaryExpr::Op::Div:
            lastValue = lhs / rhs;
            break;
        case BinaryExpr::Op::Lt:
            lastValue = lhs < rhs;
            break;
        }
    }

    void Interpreter::visit(LetStmt &s)
    {
        s.init->accept(*this);
        variables[s.name] = lastValue;
    }

    void Interpreter::visit(AssignStmt &s)
    {
        s.val->accept(*this);
        variables[s.name] = lastValue;
    }

    void Interpreter::visit(PrintStmt &s)
    {
        s.expr->accept(*this);
        std::cout << lastValue << "\n";
    }

    void Interpreter::visit(BlockStmt &b)
    {
        for (auto &st : b.statements)
            st->accept(*this);
    }

    void Interpreter::visit(WhileStmt &w)
    {
        w.condition->accept(*this);
        while (lastValue)
        {
            if (w.body)
                w.body->accept(*this);
            w.condition->accept(*this);
        }
    }

    void Interpreter::visit(Program &p)
    {
        for (auto &st : p.statements)
            st->accept(*this);
    }
}
