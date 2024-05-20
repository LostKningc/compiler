#include "../include/IRtoAsm.hpp"
std::map<koopa_raw_binary_t *, std::string> reg_map;
std::stack<std::string> reg_stack;
// 访问 raw program
void Visit(const koopa_raw_program_t &program)
{
    // 执行一些其他的必要操作
    // ...
    // 初始化寄存器栈
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
        Visit(kind.data.ret);
        break;
    case KOOPA_RVT_INTEGER:
        // 访问 integer 指令
        Visit(kind.data.integer);
        break;
    case KOOPA_RVT_BINARY:
        // 访问 binary 指令
        Visit(kind.data.binary);
        break;
    default:
        // 其他类型暂时遇不到
        std::cerr << kind.tag << std::endl;
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

void Visit(const koopa_raw_binary_t &binary)
{
    std::string reg;
    if (reg_stack.empty())
        assert(false);
    reg = reg_stack.top();
    reg_stack.pop();
    reg_map.insert({(koopa_raw_binary_t *)&binary, reg});

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
                std::cout << std::setw(6) << "li" << reg << ", " << (binary.lhs->kind.data.integer.value == binary.rhs->kind.data.integer.value) << std::endl;
        }
        if (lhs_is_binary || rhs_is_binary)
            std::cout << std::setw(6) << "seqz" << reg << ", " << reg << std::endl;
        break;
    case KOOPA_RBO_SUB:
        if(!lhs_is_binary && !rhs_is_binary)
        {
            std::cout << std::setw(6) << "li" << reg << ", " << binary.lhs->kind.data.integer.value - binary.rhs->kind.data.integer.value << std::endl;
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
        std::cout << std::setw(6) << "sub" << reg << ", " << lhs << ", " << rhs << std::endl;
        if (!lhs_is_zero && !lhs_is_binary)
            reg_stack.push(lhs);
        break;
    case KOOPA_RBO_ADD:
        // if (!lhs_is_binary)
        // {
        //     if ()
        // }
        break;
    case KOOPA_RBO_MUL:
        break;
    case KOOPA_RBO_DIV:
        break;
    case KOOPA_RBO_MOD:
        break;
    case KOOPA_RBO_XOR:
        break;
    };
}

// 访问对应类型指令的函数定义略
// 视需求自行实现
// ...
