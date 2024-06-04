#pragma once
#ifndef BASICBLOCK_HPP
#define BASICBLOCK_HPP

#include<vector>
#include<string>

using namespace std;
//这个只涉及会创建基本块的部分，比如说函数调用，if else，for while等
class BasicBlockManager{
    
    std::vector<bool> be_end_bl; // 跟踪每个基本块是否已经结束
    public:
    int nowbl = 0; // 当前基本块索引
    int bl_dep = 0; // 基本块深度计数器
    int ifCounter=-1;//用来给if块起名的
    int andCounter=-1;//用来给and块起名的
    int orCounter=-1;//用来给or块起名的
    int whileCounter=-1;//用来给while块起名的
    std::vector<int> while_stack;

    void enterBasicBlock();

    void generateRetOrJump();

    bool CheckEndBl() {
    return be_end_bl[nowbl];
    }

    void BlockJump(string label); 

    //这个部分后面可以改成泛型，我暂时懒得改
    void BlockRet(string ret_value); 
    void BlockRet(int ret_value);
    void BlockRet();

    void BlockBranch(string judge,string label1,string label2);
    void BlockBranch(int judge,string label1,string label2);
    void CreateBasicBlock(string label);
    void AndBranch();
    void OrBranch();
};

#endif  // BLOCK_HPP