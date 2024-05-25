#pragma once
#ifndef BASICBLOCK_HPP
#define BASICBLOCK_HPP

#include<vector>

using namespace std;

class BasicBlockManager{
    public:
    std::vector<bool> be_end_bl; // 跟踪每个基本块是否已经结束
    int nowbl = 0; // 当前基本块索引
    int bl_dep = 0; // 基本块深度计数器

    void enterBasicBlock();

    void generateRetOrJump();

    bool CheckEndBl() {
    return be_end_bl[nowbl];
}
};

#endif  // BLOCK_HPP