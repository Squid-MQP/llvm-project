#include "llvm/Transforms/Utils/MyPass.h"

using namespace llvm;

PreservedAnalyses MyPass::run(Function &F,
                                      FunctionAnalysisManager &AM) {
  errs() << F.getName() << "\n";
  return PreservedAnalyses::all();
}
