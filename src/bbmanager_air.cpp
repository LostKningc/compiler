#include"basicblock.hpp"


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

