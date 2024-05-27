#include"basicblock.hpp"
#include<iostream>


void BasicBlockManager::enterBasicBlock(){
    bl_dep++;
    nowbl = bl_dep;
    if (be_end_bl.size() <= nowbl) {
        be_end_bl.push_back(false); // 确保状态数组大小足够并初始化为 false
    }
}

void BasicBlockManager::generateRetOrJump() {
    // 生成 ret 或 jump 指令
        be_end_bl[nowbl] = true; // 标记当前基本块已经结束
}

void BasicBlockManager::BlockJump(string label) {
    if(!CheckEndBl()){
        cout<<"jump "<<"%"<<label<<endl;
        generateRetOrJump();
    }
}

void BasicBlockManager::BlockRet(string ret_value) {
    if(!CheckEndBl()){
        cout<<"ret "<<ret_value<<endl;
        generateRetOrJump();
    }
}

void BasicBlockManager::BlockRet(int ret_value) {
    if(!CheckEndBl()){
        cout<<"ret "<<ret_value<<endl;
        generateRetOrJump();
    }
}

void BasicBlockManager::BlockRet() {
    if(!CheckEndBl()){
        cout<<"ret"<<endl;
        generateRetOrJump();
    }
}

void BasicBlockManager::BlockBranch(string judge,string label1,string label2){
    if(!CheckEndBl()){
        cout<<"br "<<judge<<", %"<<label1<<", %"<<label2<<endl;
        generateRetOrJump();
    }
}

void BasicBlockManager::BlockBranch(int judge,string label1,string label2){
    if(!CheckEndBl()){
        cout<<"br "<<judge<<", %"<<label1<<", %"<<label2<<endl;
        generateRetOrJump();
    }
}

void BasicBlockManager::CreateBasicBlock(string lable){
    std::cout<<"%"<<lable<<":"<<std::endl;
    //进{}和进basicblock不一样
    enterBasicBlock();
}

void BasicBlockManager::AndBranch(){
    andCounter++;
}

void BasicBlockManager::OrBranch(){
    orCounter++;
}
