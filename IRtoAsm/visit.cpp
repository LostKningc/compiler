#include "../include/IRtoAsm.hpp"
std::map<koopa_raw_binary_t *, std::string> reg_map;
std::map<std::string, int> reg_count;
std::stack<std::string> reg_stack;

/////////////////////////
const char *ir_asm_binaryop[] = {
    [KOOPA_RBO_NOT_EQ] = "snez",
    [KOOPA_RBO_EQ] = "seqz",
    [KOOPA_RBO_GT] = "sgt",
    [KOOPA_RBO_LT] = "slt",
    [KOOPA_RBO_GE] = "slt",
    [KOOPA_RBO_LE] = "sgt",
    [KOOPA_RBO_ADD] = "add",
    [KOOPA_RBO_SUB] = "sub",
    [KOOPA_RBO_MUL] = "mul",
    [KOOPA_RBO_DIV] = "div",
    [KOOPA_RBO_MOD] = "rem",
    [KOOPA_RBO_AND] = "and",
    [KOOPA_RBO_OR] = "or",
    [KOOPA_RBO_XOR] = "xor",
    [KOOPA_RBO_SHL] = "sll",
    [KOOPA_RBO_SHR] = "srl",
    [KOOPA_RBO_SAR] = "sra"};

// 访问 raw program
void Visit(const koopa_raw_program_t &program)
{
    // 执行一些其他的必要操作
    // ...
    // 初始化寄存器栈
    for (int i = 7; i >= 0; --i)
    {
        std::string str = "a" + std::to_string(i);
        reg_stack.push(str);
    }
    for (int i = 6; i >= 0; --i)
    {
        std::string str = "t" + std::to_string(i);
        reg_stack.push(str);
    }

    std::cout << ".text" << std::endl;
    std::cout << ".globl main" << std::endl;

    // 访问所有全局变量
    Visit(program.values);
    // 访问所有函数
    Visit(program.funcs);
}

// 访问 raw slice
void Visit(const koopa_raw_slice_t &slice)
{
    for (size_t i = 0; i < slice.len; ++i)
    {
        auto ptr = slice.buffer[i];
        // 根据 slice 的 kind 决定将 ptr 视作何种元素
        switch (slice.kind)
        {
        case KOOPA_RSIK_FUNCTION:
            // 访问函数
            Visit(reinterpret_cast<koopa_raw_function_t>(ptr));
            break;
        case KOOPA_RSIK_BASIC_BLOCK:
            // 访问基本块
            Visit(reinterpret_cast<koopa_raw_basic_block_t>(ptr));
            break;
        case KOOPA_RSIK_VALUE:
            // 访问指令
            Visit(reinterpret_cast<koopa_raw_value_t>(ptr));
            break;
        default:
            // 我们暂时不会遇到其他内容, 于是不对其做任何处理
            assert(false);
        }
    }
}

// 访问函数
void Visit(const koopa_raw_function_t &func)
{

    std::cout << func->name + 1 << ":" << std::endl;

    // 执行一些其他的必要操作
    // ...
    // 访问所有基本块
    Visit(func->bbs);
}

// 访问基本块
void Visit(const koopa_raw_basic_block_t &bb)
{
    // 执行一些其他的必要操作
    // ...
    // 访问所有指令
    Visit(bb->insts);
}

// 访问指令
void Visit(const koopa_raw_value_t &value)
{
    // 根据指令类型判断后续需要如何访问
    const auto &kind = value->kind;
    // 设置左对齐
    std::cout << std::left;
    switch (kind.tag)
    {
    case KOOPA_RVT_RETURN:
        // 访问 return 指令
        //std::cerr << "return" << std::endl;
        Visit(kind.data.ret);
        break;
    case KOOPA_RVT_INTEGER:
        // 访问 integer 指令
        std::cerr << "integer" << std::endl;
        Visit(kind.data.integer);
        break;
    case KOOPA_RVT_BINARY:
        // 访问 binary 指令
        //std::cerr << "binary" << std::endl;
        Visit(kind.data.binary, value->used_by.len);
        break;
    default:
        // 其他类型暂时遇不到
        //std::cerr << kind.tag << std::endl;
        assert(false);
    }
}

// 访问返回指令
void Visit(const koopa_raw_return_t &ret)
{
    // Visit(ret.value);
    switch (ret.value->kind.tag)
    {
    case KOOPA_RVT_BINARY:
        std::cout << std::setw(6) << "mv" << "a0, " << reg_map[(koopa_raw_binary_t *)&ret.value->kind.data.binary] << std::endl;
        break;
    case KOOPA_RVT_INTEGER:
        // Visit(ret.value);
        std::cout << std::setw(6) << "li" << "a0, " << ret.value->kind.data.integer.value << std::endl;
        break;
    };
    std::cout << "ret" << std::endl;
}

// 访问整数指令
std::string Visit(const koopa_raw_integer_t &integer)
{
    std::string reg;
    if (reg_stack.empty())
        assert(false);
    reg = reg_stack.top();
    reg_stack.pop();
    std::cout << std::setw(6) << "li" << reg << ", " << integer.value << std::endl;
    return reg;
}

void Visit(const koopa_raw_binary_t &binary,uint32_t use_count=0)
{
    std::string reg;
    if (reg_stack.empty())
        assert(false);
    reg = reg_stack.top();
    reg_stack.pop();
    reg_map.insert({(koopa_raw_binary_t *)&binary, reg});
    if(reg_count.find(reg)==reg_count.end() && use_count)reg_count.insert({reg, use_count});
    else if(use_count)reg_count[reg] = use_count;

    // 现在只考虑二元运算的左右值是BINARY还是INTEGER, 在这儿得到左右值在转换为asm形式时对应的字符串
    bool lhs_is_binary = binary.lhs->kind.tag == KOOPA_RVT_BINARY;
    bool rhs_is_binary = binary.rhs->kind.tag == KOOPA_RVT_BINARY;
    bool lhs_is_zero = false, rhs_is_zero = false;
    std::string lhs, rhs;
    if (lhs_is_binary)
        lhs = reg_map[(koopa_raw_binary_t *)&(binary.lhs->kind.data.binary)];
    else
    {
        if (binary.lhs->kind.data.integer.value == 0)
            lhs_is_zero = true;
        lhs = std::to_string(binary.lhs->kind.data.integer.value);
    }
    if (rhs_is_binary)
        rhs = reg_map[(koopa_raw_binary_t *)&(binary.rhs->kind.data.binary)];
    else
    {
        if (binary.rhs->kind.data.integer.value == 0)
            rhs_is_zero = true;
        rhs = std::to_string(binary.rhs->kind.data.integer.value);
    }

    switch (binary.op)
    {
    case KOOPA_RBO_EQ:
    case KOOPA_RBO_NOT_EQ:
        if (lhs_is_binary)
        {
            if (rhs_is_binary)
                std::cout << std::setw(6) << "xor" << reg << ", " << lhs << ", " << rhs << std::endl;
            else
                std::cout << std::setw(6) << "xori" << reg << ", " << lhs << ", " << rhs << std::endl;
        }
        else
        {
            if (rhs_is_binary)
                std::cout << std::setw(6) << "xori" << reg << ", " << rhs << ", " << lhs << std::endl;
            else
            {
                int32_t result;
                if(binary.op == KOOPA_RBO_EQ)result = binary.lhs->kind.data.integer.value == binary.rhs->kind.data.integer.value;
                if(binary.op == KOOPA_RBO_NOT_EQ)result = binary.lhs->kind.data.integer.value != binary.rhs->kind.data.integer.value;
                std::cout << std::setw(6) << "li" << reg << ", " << result << std::endl;
            }
        }
        if (lhs_is_binary || rhs_is_binary)
            std::cout << std::setw(6) << ir_asm_binaryop[binary.op] << reg << ", " << reg << std::endl;
        break;
    case KOOPA_RBO_MUL:
    case KOOPA_RBO_DIV:
    case KOOPA_RBO_MOD:
    case KOOPA_RBO_GT:
    case KOOPA_RBO_LT:
    case KOOPA_RBO_LE:
    case KOOPA_RBO_GE:
    case KOOPA_RBO_SUB:
    case KOOPA_RBO_SHL:
    case KOOPA_RBO_SHR:
    case KOOPA_RBO_SAR:
        if (binary.op == KOOPA_RBO_DIV && rhs_is_zero)
            assert(false);
        if (!lhs_is_binary && !rhs_is_binary)
        {
            int32_t result;
            if (binary.op == KOOPA_RBO_MUL)
                result = binary.lhs->kind.data.integer.value * binary.rhs->kind.data.integer.value;
            if (binary.op == KOOPA_RBO_SUB)
                result = binary.lhs->kind.data.integer.value - binary.rhs->kind.data.integer.value;
            if (binary.op == KOOPA_RBO_DIV)
                result = binary.lhs->kind.data.integer.value / binary.rhs->kind.data.integer.value;
            if (binary.op == KOOPA_RBO_MOD)
                result = binary.lhs->kind.data.integer.value % binary.rhs->kind.data.integer.value;
            if (binary.op == KOOPA_RBO_GT)
                result = binary.lhs->kind.data.integer.value > binary.rhs->kind.data.integer.value;
            if (binary.op == KOOPA_RBO_LT)
                result = binary.lhs->kind.data.integer.value < binary.rhs->kind.data.integer.value;
            if (binary.op == KOOPA_RBO_GE)
                result = binary.lhs->kind.data.integer.value >= binary.rhs->kind.data.integer.value;
            if (binary.op == KOOPA_RBO_LE)
                result = binary.lhs->kind.data.integer.value <= binary.rhs->kind.data.integer.value;
            if (binary.op == KOOPA_RBO_SHL)
                result = binary.lhs->kind.data.integer.value << binary.rhs->kind.data.integer.value;
            if (binary.op == KOOPA_RBO_SHR)
                result = (u_int32_t)binary.lhs->kind.data.integer.value >> binary.rhs->kind.data.integer.value;
            if (binary.op == KOOPA_RBO_SAR)
                result = binary.lhs->kind.data.integer.value >> binary.rhs->kind.data.integer.value;
            std::cout << std::setw(6) << "li" << reg << ", " << result << std::endl;
            break;
        }
        if (!lhs_is_zero && !lhs_is_binary)
        {
            lhs = Visit(binary.lhs->kind.data.integer);
        }
        if (!rhs_is_binary && !rhs_is_zero)
        {
            rhs = Visit(binary.rhs->kind.data.integer);
            reg_stack.push(rhs);
        }
        if (lhs_is_zero)
            lhs = "x0";
        if (rhs_is_zero)
            rhs = "x0";
        std::cout << std::setw(6) << ir_asm_binaryop[binary.op] << reg << ", " << lhs << ", " << rhs << std::endl;
        if (binary.op == KOOPA_RBO_LE || binary.op == KOOPA_RBO_GE)
            std::cout << std::setw(6) << "seqz" << reg << ", " << reg << std::endl;
        if (!lhs_is_zero && !lhs_is_binary)
            reg_stack.push(lhs);
        break;
    case KOOPA_RBO_AND:
    case KOOPA_RBO_OR:
    case KOOPA_RBO_XOR:
    case KOOPA_RBO_ADD:
        int32_t result;
        if (binary.op == KOOPA_RBO_ADD)
            result = binary.lhs->kind.data.integer.value + binary.rhs->kind.data.integer.value;
        if (binary.op == KOOPA_RBO_XOR)
            result = binary.lhs->kind.data.integer.value ^ binary.rhs->kind.data.integer.value;
        if (binary.op == KOOPA_RBO_AND)
            result = binary.lhs->kind.data.integer.value & binary.rhs->kind.data.integer.value;
        if (binary.op == KOOPA_RBO_OR)
            result = binary.lhs->kind.data.integer.value | binary.rhs->kind.data.integer.value;
        if (lhs_is_binary)
        {
            if (rhs_is_binary)
                std::cout << std::setw(6) << ir_asm_binaryop[binary.op] << reg << ", " << lhs << ", " << rhs << std::endl;
            else
                std::cout << std::setw(6) << std::string(ir_asm_binaryop[binary.op]) + 'i' << reg << ", " << lhs << ", " << rhs << std::endl;
        }
        else
        {
            if (rhs_is_binary)
                std::cout << std::setw(6) << std::string(ir_asm_binaryop[binary.op]) + 'i' << reg << ", " << rhs << ", " << lhs << std::endl;
            else
                std::cout << std::setw(6) << "li" << reg << ", " << result << std::endl;
        }
        break;
    };
    if(lhs_is_binary) {
        reg_count[lhs]--;
        if(reg_count[lhs] == 0) {
            reg_stack.push(lhs);
        }
    }
    if (rhs_is_binary) {
        reg_count[rhs]--;
        if(reg_count[rhs] == 0) {
            reg_stack.push(rhs);
        }
    }
    
}


// 访问对应类型指令的函数定义略
// 视需求自行实现
// ...
