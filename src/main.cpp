#include <fstream>
#include <iostream>
#include <sstream>

#include "Lexer.h"
#include "Parser.h"
#include "Semantic.h"
#include "Interpreter.h"
#include "ErrorReporter.h"

using namespace Mini;

static std::string readAll(std::istream &in)
{
    std::ostringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);

    std::string source;
    if (argc > 1)
    {
        std::ifstream file(argv[1]);
        if (!file)
        {
            std::cerr << "Could not open file: " << argv[1] << "\n";
            return 1;
        }
        source = readAll(file);
    }
    else
    {
        std::cout << "Enter program (end with Ctrl+D / Ctrl+Z):\n";
        source = readAll(std::cin);
    }

    Lexer lex(source);
    auto tokens = lex.tokenize();         // ✅ get tokens
    Parser parser(tokens);                // ✅ pass tokens to parser
    auto program = parser.parseProgram(); // ✅ now program exists

    if (ErrorReporter::instance().hadError())
    {
        ErrorReporter::instance().printAllAndClear();
        return 1;
    }

    SemanticAnalyzer sema;
    program->accept(sema);
    if (ErrorReporter::instance().hadError())
    {
        ErrorReporter::instance().printAllAndClear();
        return 1;
    }

    Interpreter interp;
    program->accept(interp);
    return 0;
}
