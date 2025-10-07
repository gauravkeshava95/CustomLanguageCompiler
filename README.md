CustomLanguageCompiler - 
A self-developed mini compiler and interpreter built from scratch in C++, implementing all major stages of a modern programming language — lexical analysis, parsing, semantic analysis, and interpretation.
This project demonstrates strong knowledge of compiler design, data structures, and object-oriented programming.

🧩 Overview

MiniLang is a custom language that supports:

•Variable declarations (let i = 0;)

•Arithmetic operations (+, -, *, /)

•Comparisons (<)

•Print statements (print(i);)

•While loops for iteration

•The project was designed as a learning-driven compiler to understand how real languages like C or Python translate and execute code under the hood.

🚀 Technical Highlights

•Language Components Implemented:
    -Lexer — tokenizes source code into symbols
    -Parser — constructs an Abstract Syntax Tree (AST)
    -Semantic Analyzer — ensures variables are declared before use
    -Interpreter — executes the AST in runtime
•Built with C++17, CMake, and object-oriented architecture

•Clean modular code — each stage is implemented in its own class/file

•Includes error reporting with source line/column tracking

🧠 Example Program
let i = 0;
while (i < 5) {
    print(i);
    i = i + 1;
}

Output:
0
1
2
3
4

🛠️ Build & Run
# Clone and build
git clone https://github.com/<your-username>/<repo-name>.git
cd <repo-name>
mkdir build && cd build
cmake ..
mingw32-make   # or 'make' / 'ninja' depending on your setup

# Run an example program
./my_compiler ../examples/hello.toy

📂 Project Structure
├── include/
│   ├── AST.h
│   ├── Lexer.h
│   ├── Parser.h
│   ├── Semantic.h
│   ├── Interpreter.h
│   └── ErrorReporter.h
├── src/
│   ├── AST.cpp
│   ├── Lexer.cpp
│   ├── Parser.cpp
│   ├── Semantic.cpp
│   ├── Interpreter.cpp
│   ├── ErrorReporter.cpp
│   └── main.cpp
├── examples/
│   └── hello.toy
└── CMakeLists.txt

💼 What I Learned

•Designed and implemented a complete compiler pipeline in C++.

•Gained deep understanding of lexing, parsing, AST construction, and runtime evaluation.

•Applied data structures like trees, maps, and stacks to manage scopes and expressions.

•Improved code quality through modular design and error-handling mechanisms.

•Strengthened debugging, CMake build, and cross-platform development skills.

🔧 Future Enhancements

•Add if/else and for loops

•Support for boolean expressions and nested scopes

•Convert interpreter to a bytecode virtual machine
