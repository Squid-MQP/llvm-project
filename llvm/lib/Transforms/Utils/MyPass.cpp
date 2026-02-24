#include "llvm/Transforms/Utils/MyPass.h"
#include "llvm/IR/Function.h"

using namespace llvm;

PreservedAnalyses MyPass::run(Function &F,
                                      FunctionAnalysisManager &AM) {
  for (auto&& bb : F) {
    for (auto&& inst : bb) {
      inst.addAnnotationMetadata(StringRef{"test"});
    }
  }
  errs() << F.getName() << "\n";
  return PreservedAnalyses::none();
}
