#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/Analysis/LoopInfo.h"

#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/LegacyPassManager.h"


#define CPU_BYTES 1					//if you want N = 8, 16, 24, 32... blocks in parallel put this 
									//macro at 1, 2, 3, 4...

#define UNIFORM_ALLOCATION 8		//the scalar uint8_t variables are allocated with the same
									//size as the arrays for uniformity (it causes a segmentation
									//fault otherwise). You must set this macro to the dimension
									//of the array.

using namespace llvm;

namespace{
	
	struct BitSlicer : public FunctionPass{
		static char ID;
		//static int TYPE_OK;
		static int INSTR_TYPE;
		static int LAST_INSTR_TYPE;
		static int done;
		BitSlicer() : FunctionPass(ID) {}
		std::vector<Instruction *> eraseList;
		std::vector<AllocaInst *>  AllocInstBuff;
		std::vector<StringRef> InstrNames;
		
		bool runOnFunction(Function &F){
			int i;
			for(BasicBlock& B : F){
				errs() << "\nBLOCK:\n\n";
				B.dump();
				for(Instruction& I : B){
					IRBuilder<> builder(&I);
					//errs() << "instr name: " << I.getName().str() << "\n";
					if(isa<AllocaInst>(&I)){
						INSTR_TYPE = 0;
					}
					else if(isa<StoreInst>(&I)){
						INSTR_TYPE = 1;
					}
					else{
						INSTR_TYPE = 2;
					}
					
					switch(INSTR_TYPE){
					
						case 0:	
						{
								auto *all = dyn_cast<AllocaInst>(&I);
								
								if(all->getAllocatedType()->isIntegerTy(8) ||
									(all->getAllocatedType()->isArrayTy() && 
									all->getAllocatedType()->getArrayElementType()->isIntegerTy(8))){
									//AllocInstBuff.push_back(all);
									AllocaInst *ret;
									
									for(i=0;i<8*CPU_BYTES;i++){
										ret = builder.CreateAlloca(all->getAllocatedType(), 0, "bsliced");
										AllocInstBuff.push_back(ret);
										InstrNames.push_back(ret->getName());
										if(i==0)
											all->replaceAllUsesWith(ret);
										
									}
									eraseList.push_back(&I);
									done = 1;
									LAST_INSTR_TYPE = 0;
								}
						
						break;
						}
						
						case 1: 
						{
								auto *st = dyn_cast<StoreInst>(&I);
								
								if(st->getValueOperand()->getType()->isIntegerTy(8)){
									int j=0;
									Type *sliceTy = IntegerType::getInt8Ty(I.getModule()->getContext());
									
									Value *bit_index_value = ConstantInt::get(sliceTy, 0);
									Value *bit_index_addr = builder.CreateAlloca(sliceTy, 0, "bit_index");
									Value *bit_inc = ConstantInt::get(sliceTy, 1);
									
									builder.CreateStore(bit_index_value, bit_index_addr);
									
									for(auto &name: InstrNames){
											if(st->getPointerOperand()->getName().equals(name)){
												for(i=0;i<8;){
													Value *bit_index = builder.CreateLoad(bit_index_addr,"bit_index");
													Value *mask = ConstantInt::get(sliceTy, 0x01<<i);
													Value *bit_and = builder.CreateAnd(st->getValueOperand(), mask, "bit_and");
													Value *slice = builder.CreateLShr(bit_and,bit_index,"bit_shiftR");
													Value *bit_index_inc = builder.CreateAdd(bit_index, bit_inc);
													builder.CreateStore(bit_index_inc, bit_index_addr);
													i++;
													builder.CreateStore(slice, AllocInstBuff.at(j));
													j++; //the first name was found, I don't need any more to follow the outer
												}		//loop, so I can use j to collect the 7 subsequent addresses I need.
											}			//FIXME: what about the arrays? Shall wee keep it like their big jumps?
											j++;
										}
										
									/*if(!isa<Constant>(st->getValueOperand())){
										for(auto &name: InstrNames){
											if(st->getPointerOperand()->getName().equals(name)){
												for(i=0;i<8*CPU_BYTES;i++){
													builder.CreateStore(,);
												}
											}
											j++;
										}
									}
									*/
									eraseList.push_back(&I);
									done = 1;
									LAST_INSTR_TYPE = 1;
									
								}
						break;
						}
						
					}
				}
			}
			for(auto &EI: eraseList){
				EI -> eraseFromParent();
			}
			
			if(done)
				return true;
			return false;
		}
	};
}

char BitSlicer::ID = 0;
//int BitSlicer::TYPE_OK = 0;
int BitSlicer::INSTR_TYPE = 0;
int BitSlicer::LAST_INSTR_TYPE = 0;
int BitSlicer::done = 0;

static void registerBitSlicerPass(const PassManagerBuilder &,
                         legacy::PassManagerBase &PM) {
  PM.add(new BitSlicer());
}
static RegisterStandardPasses
  RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
registerBitSlicerPass);





