#include "llvm/Transforms/Utils/MyPass.h"
#include "llvm/IR/Function.h"
#include <vector>

using namespace llvm;

PreservedAnalyses MyPass::run(Function &F,
                                      FunctionAnalysisManager &AM) {
  for (auto&& bb : F) {
    std::vector<llvm::Instruction*> toFloat;
    std::vector<llvm::Instruction*> toSink;
    for (auto&& inst : bb) {
      if (auto* mdnode = inst.getMetadata(LLVMContext::MD_annotation)) {
        auto* tupl = cast<MDTuple>(mdnode);
        for (const llvm::MDOperand& arg : tupl->operands()) {
          if (isa<MDString>(arg)) {
            auto stringed = cast<MDString>(arg);

            auto name = stringed->getString().str();
            if (name == "Float") {
              errs() << "Recording for float!\n";
              toFloat.push_back(&inst);
            }
            else if (name == "Sink") {
              errs() << "Recording for sink!\n";
              toSink.push_back(&inst);
            }

            //errs() << "v2: " << stringed->getString().str() << "\n";
          }
        }
      }
      else {
        std::string mystr = "test" + std::string{inst.getOpcodeName()};
      inst.addAnnotationMetadata(StringRef{mystr});
      errs() << "Applying annotation" << "\n";
      }
    }

    
    for (auto itr{toFloat.rbegin()}; itr != toFloat.rend(); ++itr) {
      (*itr)->moveBefore(bb.begin());
    }

    for (auto&& sinkMe : toSink) {
      sinkMe->moveBefore(--bb.end());
    }
      
  }
  errs() << F.getName() << "\n";
  return PreservedAnalyses::none();
}
