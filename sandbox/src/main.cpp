#include <iostream>
#include <box/frontend/lexer/lexers.hpp>
#include <box/frontend/parser/parser.hpp>
#include <box/frontend/parser/parser_rule.hpp>

#include <asmjit/asmjit.h>

using namespace asmjit;
using namespace box::frontend;

typedef int (*Func)(int, int);

int main(int argc, char** argv) {
    using namespace x86;

    JitRuntime jit;
    CodeHolder code;
    code.init(jit.environment(), jit.cpuFeatures());
    Compiler cc(&code);

    FuncNode* entry = cc.addFunc(FuncSignatureT<int, int, int>());

    Gp vX = cc.newGpd();
    Gp vY = cc.newGpd();

    entry->setArg(0, vX);
    entry->setArg(1, vY);

    cc.add(vX, vY);
    cc.ret(vX);

    cc.endFunc();
    cc.finalize();

    Func fn;
    Error err = jit.add(&fn, &code);
    if (err) {
        printf("AsmJit: %s\n", DebugUtils::errorAsString(err));
        std::system("pause");
        return 1;
    }

    int result = fn(5, 25);
    printf("%d\n", result);

    jit.release(fn);

    std::system("pause");
    return 0;
}