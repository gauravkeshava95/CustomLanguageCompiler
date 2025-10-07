#pragma once
#include <string>
#include <memory>
#include <vector>

namespace Mini
{
    // Forward declare visitor
    struct NumberExpr;
    struct VarExpr;
    struct BinaryExpr;
    struct LetStmt;
    struct AssignStmt;
    struct PrintStmt;
    struct BlockStmt;
    struct WhileStmt;
    struct Program;

    struct ASTVisitor
    {
        virtual ~ASTVisitor() = default;
        virtual void visit(NumberExpr &) = 0;
        virtual void visit(VarExpr &) = 0;
        virtual void visit(BinaryExpr &) = 0;
        virtual void visit(LetStmt &) = 0;
        virtual void visit(AssignStmt &) = 0;
        virtual void visit(PrintStmt &) = 0;
        virtual void visit(BlockStmt &) = 0;
        virtual void visit(WhileStmt &) = 0;
        virtual void visit(Program &) = 0;
    };

    struct Expr
    {
        virtual ~Expr() = default;
        virtual void accept(ASTVisitor &v) = 0;
    };

    struct NumberExpr : Expr
    {
        int value;
        NumberExpr(int v) : value(v) {}
        void accept(ASTVisitor &v) override;
    };

    struct VarExpr : Expr
    {
        std::string name;
        VarExpr(const std::string &n) : name(n) {}
        void accept(ASTVisitor &v) override;
    };

    struct BinaryExpr : Expr
    {
        enum class Op
        {
            Add,
            Sub,
            Mul,
            Div,
            Lt
        };
        Op op;
        std::unique_ptr<Expr> lhs, rhs;
        BinaryExpr(Op o, std::unique_ptr<Expr> l, std::unique_ptr<Expr> r)
            : op(o), lhs(std::move(l)), rhs(std::move(r)) {}
        void accept(ASTVisitor &v) override;
    };

    struct Stmt
    {
        virtual ~Stmt() = default;
        virtual void accept(ASTVisitor &v) = 0;
    };

    struct LetStmt : Stmt
    {
        std::string name;
        std::unique_ptr<Expr> init;
        LetStmt(const std::string &n, std::unique_ptr<Expr> i)
            : name(n), init(std::move(i)) {}
        void accept(ASTVisitor &v) override;
    };

    struct AssignStmt : Stmt
    {
        std::string name;
        std::unique_ptr<Expr> val;
        AssignStmt(const std::string &n, std::unique_ptr<Expr> v)
            : name(n), val(std::move(v)) {}
        void accept(ASTVisitor &v) override;
    };

    struct PrintStmt : Stmt
    {
        std::unique_ptr<Expr> expr;
        PrintStmt(std::unique_ptr<Expr> e) : expr(std::move(e)) {}
        void accept(ASTVisitor &v) override;
    };

    struct BlockStmt : Stmt
    {
        std::vector<std::unique_ptr<Stmt>> statements;
        void accept(ASTVisitor &v) override;
    };

    struct WhileStmt : Stmt
    {
        std::unique_ptr<Expr> condition;
        std::unique_ptr<Stmt> body;
        WhileStmt(std::unique_ptr<Expr> c, std::unique_ptr<Stmt> b)
            : condition(std::move(c)), body(std::move(b)) {}
        void accept(ASTVisitor &v) override;
    };

    struct Program
    {
        std::vector<std::unique_ptr<Stmt>> statements;
        void accept(ASTVisitor &v);
    };

} // namespace Mini
