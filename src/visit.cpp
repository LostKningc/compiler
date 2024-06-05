#include "../include/IRtoAsm.hpp"
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

std::map<koopa_raw_binary_t *, std::string> reg_map;
std::map<koopa_raw_value_t, int> stack_map;
std::map<std::string, int> reg_count;
std::stack<std::string> reg_stack;
int size_of_stack_frame = 0;
std::string func_name = "";
bool call_flag;

// binary操作符对应的汇编指令
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
    // 初始化寄存器栈
    // for (int i = 7; i >= 0; --i)
    // {
    //     std::string str = "a" + std::to_string(i);
    //     reg_stack.push(str);
    // }
    for (int i = 6; i >= 0; --i)
    {
        std::string str = "t" + std::to_string(i);
        reg_stack.push(str);
    }

    std::cout << std::left;
    std::cout << ".data" << std::endl;

    // 访问所有全局变量
    Visit(program.values);

    std::cout << std::left;
    std::cout << ".text" << std::endl;
    std::cout << ".globl main" << std::endl;

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
    if (0 == func->bbs.len)
    {
        return;
    }

    stack_map.clear();
    func_name = func->name + 1;
    std::cout << func_name << ":" << std::endl;
    size_of_stack_frame = 0;
    int max_arg_count = 0;
    call_flag = false;
    // 统计一个函数中需要在栈帧中分配内存的指令数
    for (size_t i = 0; i < func->bbs.len; i++)
    {
        koopa_raw_basic_block_t bb = (koopa_raw_basic_block_t)(func->bbs.buffer[i]);
        for (size_t j = 0; j < bb->insts.len; ++j)
        {
            auto ptr = reinterpret_cast<koopa_raw_value_t>(bb->insts.buffer[j]);
            if (ptr->ty->tag != KOOPA_RTT_UNIT)
            {
                size_of_stack_frame += 4;
            }
            if (ptr->kind.tag == KOOPA_RVT_CALL)
            {
                call_flag = true;
                koopa_raw_call_t call = ptr->kind.data.call;
                if (call.args.len > max_arg_count)
                {
                    max_arg_count = call.args.len;
                }
            }
        }
    }

    if (call_flag)
    {
        if (max_arg_count > 8)
        {
            size_of_stack_frame += 4 * (max_arg_count - 8);
        }
        size_of_stack_frame += 4;
    }
    max_arg_count = 4 * MAX(max_arg_count - 8, 0) - 4;
    // 将栈帧分配给临时变量
    for (size_t i = 0; i < func->bbs.len; i++)
    {
        koopa_raw_basic_block_t bb = (koopa_raw_basic_block_t)(func->bbs.buffer[i]);
        for (size_t j = 0; j < bb->insts.len; ++j)
        {
            auto ptr = reinterpret_cast<koopa_raw_value_t>(bb->insts.buffer[j]);
            if (ptr->ty->tag != KOOPA_RTT_UNIT)
            {
                stack_map.insert({(koopa_raw_value_t)ptr, max_arg_count += 4});
                if (ptr->kind.tag == KOOPA_RVT_ALLOC)
                {
                    if (ptr->ty->data.pointer.base->tag == KOOPA_RTT_ARRAY)
                    {
                        max_arg_count += 4 * cal_array_length(*ptr->ty->data.pointer.base);
                        size_of_stack_frame += 4 * cal_array_length(*ptr->ty->data.pointer.base);
                    }
                    else
                    {
                        size_of_stack_frame += 4;
                        max_arg_count += 4;
                    }
                }
            }
        }
    }

    size_of_stack_frame += 112;

    size_of_stack_frame = -((size_of_stack_frame + 15) / 16) * 16;

    // 将参数添加进stack_map
    for (int i = 0; i < MIN(func->params.len, 8); i++)
    {
        koopa_raw_value_t value = (koopa_raw_value_t)(func->params.buffer[i]);
        stack_map.insert({value, (i - 10)});
    }
    for (int i = 8; i < func->params.len; i++)
    {
        koopa_raw_value_t value = (koopa_raw_value_t)(func->params.buffer[i]);
        stack_map.insert({value, (-size_of_stack_frame) + 4 * (i - 8)});
    }

    if (size_of_stack_frame < -2048)
    {
        std::cout << std::setw(6) << "li t1, " << size_of_stack_frame << std::endl;
        std::cout << std::setw(6) << "add sp, sp, t1" << std::endl;
    }
    else
    {
        std::cout << std::setw(6) << "addi sp, sp, " << size_of_stack_frame << std::endl;
    }

    // 保存ra
    if (call_flag)
    {
        std::cout << std::setw(6) << "sw ra, " << -size_of_stack_frame - 4 << "(sp)" << std::endl;
    }

    Visit(func->bbs);
}

// 访问基本块
void Visit(const koopa_raw_basic_block_t &bb)
{
    // 访问所有指令
    std::cout << func_name << '_' << bb->name + 1 << ":" << std::endl;
    Visit(bb->insts);
}

// 访问指令
void Visit(const koopa_raw_value_t &value)
{
    // 根据指令类型判断后续需要如何访问
    const auto &kind = value->kind;
    // 设置左对齐
    switch (kind.tag)
    {
    case KOOPA_RVT_RETURN:
        // 访问 return 指令
        // std::cerr << "return" << std::endl;
        Visit(kind.data.ret);
        break;
    case KOOPA_RVT_INTEGER:
        // 访问 integer 指令
        // std::cerr << "integer" << std::endl;
        Visit(kind.data.integer);
        break;
    case KOOPA_RVT_BINARY:
        // 访问 binary 指令
        // std::cerr << "binary" << std::endl;
        Visit(kind.data.binary, value, value->used_by.len);
        break;
    case KOOPA_RVT_ALLOC:
        // 访问 alloc 指令
        std::cout << std::setw(6) << "li" << reg_stack.top() << ", " << stack_map[value] + 4 << std::endl;
        std::cout << std::setw(6) << "add" << reg_stack.top() << ", " << reg_stack.top() << ", " << "sp" << std::endl;
        std::cout << std::setw(6) << "sw" << reg_stack.top() << ", " << stack_map[value] << "(sp)" << std::endl;
        break;
    case KOOPA_RVT_LOAD:
        // 访问 load 指令
        Visit(kind.data.load, value);
        break;
    case KOOPA_RVT_STORE:
        // 访问 store 指令
        Visit(kind.data.store);
        break;
    case KOOPA_RVT_BRANCH:
        // 访问 branch 指令
        Visit(kind.data.branch);
        break;
    case KOOPA_RVT_JUMP:
        // 访问 jump 指令
        Visit(kind.data.jump);
        break;
    case KOOPA_RVT_CALL:
        // 访问 call 指令
        Visit(kind.data.call, value);
        break;
    case KOOPA_RVT_GLOBAL_ALLOC:
        // 访问 global_alloc 指令
        Visit(kind.data.global_alloc, value);
        break;
    case KOOPA_RVT_GET_ELEM_PTR:
        // 访问 get_elem_ptr 指令
        Visit(kind.data.get_elem_ptr, value);
        break;
    case KOOPA_RVT_GET_PTR:
        // 访问 get_ptr 指令
        Visit(kind.data.get_ptr, value);
        break;
    default:
        // 其他类型暂时遇不到
        std::cerr << kind.tag << std::endl;
        assert(false);
    }

    std::cout << std::endl;
}

// 访问返回指令
void Visit(const koopa_raw_return_t &ret)
{
    // Visit(ret.value);
    if (ret.value != nullptr)
    {
        switch (ret.value->kind.tag)
        {
        case KOOPA_RVT_INTEGER:
            // Visit(ret.value);
            std::cout << std::setw(6) << "li" << "a0, " << ret.value->kind.data.integer.value << std::endl;
            break;
        default:
            if (stack_map[ret.value] >= 0)
            {
                std::cout << std::setw(6) << "lw" << "a0, " << stack_map[ret.value] << "(sp)" << std::endl;
            }
            else if (stack_map[ret.value] != -10)
            {
                std::cout << std::setw(6) << "mv" << "a0, a" << stack_map[ret.value] + 10 << std::endl;
            }
            break;
        };
    }

    // 恢复ra
    if (call_flag)
    {
        std::cout << std::setw(6) << "lw ra, " << -size_of_stack_frame - 4 << "(sp)" << std::endl;
    }

    if (size_of_stack_frame < -2047)
    {
        std::cout << std::setw(6) << "li t1, " << -size_of_stack_frame << std::endl;
        std::cout << std::setw(6) << "add sp, sp, t1" << std::endl;
    }
    else
    {
        std::cout << std::setw(6) << "addi sp, sp, " << -size_of_stack_frame << std::endl;
    }

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

// 访问二元运算指令
void Visit(const koopa_raw_binary_t &binary, const koopa_raw_value_t &value, const uint32_t use_count = 0)
{
    std::string reg;
    if (reg_stack.empty())
        assert(false);
    reg = reg_stack.top();
    reg_stack.pop();
    // 现在只考虑二元运算的左右值是BINARY还是INTEGER, 在这儿得到左右值在转换为asm形式时对应的字符串
    bool lhs_is_integer = binary.lhs->kind.tag == KOOPA_RVT_INTEGER;
    bool rhs_is_integer = binary.rhs->kind.tag == KOOPA_RVT_INTEGER;
    bool lhs_is_zero = false, rhs_is_zero = false;
    std::string lhs, rhs;
    if (!lhs_is_integer)
    {
        if (stack_map[binary.lhs] >= 0)
        {
            std::string lhs_reg;
            if (reg_stack.empty())
                assert(false);
            lhs_reg = reg_stack.top();
            reg_stack.pop();
            lhs = std::to_string(stack_map[binary.lhs]);
            std::cout << std::setw(6) << "lw " << lhs_reg << ", " << lhs << "(sp)" << std::endl;
            lhs = lhs_reg;
        }
        else
        {
            lhs = "a" + std::to_string(stack_map[binary.lhs] + 10);
        }
    }
    else
    {
        if (binary.lhs->kind.data.integer.value == 0)
            lhs_is_zero = true;
        lhs = std::to_string(binary.lhs->kind.data.integer.value);
    }
    if (!rhs_is_integer)
    {
        if (stack_map[binary.rhs] >= 0)
        {
            std::string rhs_reg;
            if (reg_stack.empty())
                assert(false);
            rhs_reg = reg_stack.top();
            reg_stack.pop();
            rhs = std::to_string(stack_map[binary.rhs]);
            std::cout << std::setw(6) << "lw " << rhs_reg << ", " << rhs << "(sp)" << std::endl;
            rhs = rhs_reg;
        }
        else
        {
            rhs = "a" + std::to_string(stack_map[binary.rhs] + 10);
            std::cerr << stack_map[binary.rhs] << std::endl;
        }
    }
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
        if (!lhs_is_integer)
        {
            if (!rhs_is_integer)
                std::cout << std::setw(6) << "xor" << reg << ", " << lhs << ", " << rhs << std::endl;
            else
                std::cout << std::setw(6) << "xori" << reg << ", " << lhs << ", " << rhs << std::endl;
        }
        else
        {
            if (!rhs_is_integer)
                std::cout << std::setw(6) << "xori" << reg << ", " << rhs << ", " << lhs << std::endl;
            else
            {
                int32_t result;
                if (binary.op == KOOPA_RBO_EQ)
                    result = binary.lhs->kind.data.integer.value == binary.rhs->kind.data.integer.value;
                if (binary.op == KOOPA_RBO_NOT_EQ)
                    result = binary.lhs->kind.data.integer.value != binary.rhs->kind.data.integer.value;
                std::cout << std::setw(6) << "li" << reg << ", " << result << std::endl;
            }
        }
        if (!lhs_is_integer || !rhs_is_integer)
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
        if (lhs_is_integer && rhs_is_integer)
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
        if (!lhs_is_zero && lhs_is_integer)
        {
            lhs = Visit(binary.lhs->kind.data.integer);
        }
        if (rhs_is_integer && !rhs_is_zero)
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
        if (!lhs_is_zero && lhs_is_integer)
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
        if (!lhs_is_integer)
        {
            if (!rhs_is_integer)
                std::cout << std::setw(6) << ir_asm_binaryop[binary.op] << reg << ", " << lhs << ", " << rhs << std::endl;
            else
                std::cout << std::setw(6) << std::string(ir_asm_binaryop[binary.op]) + 'i' << reg << ", " << lhs << ", " << rhs << std::endl;
        }
        else
        {
            if (!rhs_is_integer)
                std::cout << std::setw(6) << std::string(ir_asm_binaryop[binary.op]) + 'i' << reg << ", " << rhs << ", " << lhs << std::endl;
            else
                std::cout << std::setw(6) << "li" << reg << ", " << result << std::endl;
        }
        break;
    };

    std::cout << std::setw(6) << "sw" << reg << ", " << stack_map[value] << "(sp)" << std::endl;

    if (!lhs_is_integer && stack_map[binary.lhs] >= 0)
        reg_stack.push(lhs);
    if (!rhs_is_integer && stack_map[binary.rhs] >= 0)
        reg_stack.push(rhs);

    reg_stack.push(reg);
}

// store指令
void Visit(const koopa_raw_store_t &store)
{
    std::string reg;
    bool reg_push = true;
    if (reg_stack.empty())
        assert(false);
    reg = reg_stack.top();
    reg_stack.pop();
    bool value_is_imm = store.value->kind.tag == KOOPA_RVT_INTEGER;
    if (value_is_imm)
    {
        std::cout << std::setw(6) << "li" << reg << ", " << store.value->kind.data.integer.value << std::endl;
    }
    else if (stack_map[(koopa_raw_value_t)(store.value)] >= 0)
    {
        std::cout << std::setw(6) << "lw" << reg << ", " << stack_map[(koopa_raw_value_t)(store.value)] << "(sp)" << std::endl;
    }
    else
    {
        reg_stack.push(reg);
        reg_push = false;
        reg = "a" + std::to_string(stack_map[(koopa_raw_value_t)(store.value)] + 10);
    }

    if (store.dest->kind.tag == KOOPA_RVT_GLOBAL_ALLOC)
    {
        std::cout << std::setw(6) << "la" << reg_stack.top() << ", " << store.dest->name + 1 << std::endl;
        std::cout << std::setw(6) << "sw" << reg << ", " << "0(" << reg_stack.top() << ")" << std::endl;
    }
    else
    {
        std::cout << std::setw(6) << "lw" << reg_stack.top() << ", " << stack_map[(koopa_raw_value_t)(store.dest)] << "(sp)" << std::endl;
        std::cout << std::setw(6) << "sw" << reg << ", " << 0 << '(' << reg_stack.top() << ')' << std::endl;
    }

    if (reg_push)
    {
        reg_stack.push(reg);
    }
}

// load指令
void Visit(const koopa_raw_load_t &load, const koopa_raw_value_t &value)
{
    std::string reg;
    if (reg_stack.empty())
        assert(false);
    reg = reg_stack.top();
    reg_stack.pop();
    if (load.src->kind.tag == KOOPA_RVT_GLOBAL_ALLOC)
    {
        std::cout << std::setw(6) << "la" << reg << ", " << load.src->name + 1 << std::endl;
        std::cout << std::setw(6) << "lw" << reg << ", " << "0(" << reg << ")" << std::endl;
    }
    else
    {
        std::cout << std::setw(6) << "lw" << reg << ", " << stack_map[load.src] << "(sp)" << std::endl;
        std::cout << std::setw(6) << "lw" << reg << ", " << 0 << '(' << reg << ')' << std::endl;
    }
    std::cout << std::setw(6) << "sw" << reg << ", " << stack_map[value] << "(sp)" << std::endl;
    reg_stack.push(reg);
}

// branch指令
void Visit(const koopa_raw_branch_t &branch)
{
    if (reg_stack.empty())
    {
        assert(false);
    }
    std::string reg = reg_stack.top();
    if (branch.cond->kind.tag == KOOPA_RVT_INTEGER)
    {
        std::cout << std::setw(6) << "li" << reg << ", " << branch.cond->kind.data.integer.value << std::endl;
    }
    else
    {
        if (stack_map[branch.cond] >= 0)
        {
            std::cout << std::setw(6) << "lw" << reg << ", " << stack_map[branch.cond] << "(sp)" << std::endl;
        }
        else
        {
            reg = "a" + std::to_string(stack_map[branch.cond] + 10);
        }
    }

    std::cout << std::setw(6) << "beqz" << reg << ", " << func_name + '_' << branch.false_bb->name + 1 << std::endl;
    std::cout << std::setw(6) << "j" << func_name + '_' << branch.true_bb->name + 1 << std::endl;
}

void Visit(const koopa_raw_jump_t &jump)
{
    std::cout << std::setw(6) << "j" << func_name + '_' << jump.target->name + 1 << std::endl;
}

// 访问 call 指令
void Visit(const koopa_raw_call_t &call, const koopa_raw_value_t &fa_value)
{
    std::stack<std::string> regs;
    for (int i = 0; i < call.args.len; i++)
    {
        koopa_raw_value_t value = (koopa_raw_value_t)(call.args.buffer[i]);
        if (i < 8)
        {
            save_regs("a" + std::to_string(i));
            regs.push("a" + std::to_string(i));
            switch (value->kind.tag)
            {
            case KOOPA_RVT_INTEGER:
                std::cout << std::setw(6) << "li" << 'a' << i << ", " << value->kind.data.integer.value << std::endl;
                break;
            default:
                if (stack_map[value] >= 0)
                {
                    std::cout << std::setw(6) << "lw" << 'a' << i << ", " << stack_map[value] << "(sp)" << std::endl;
                }
                else
                {
                    std::cout << std::setw(6) << "mv" << 'a' << i << ", a" << stack_map[value] + 10 << std::endl;
                }
                break;
            }
        }
        else
        {
            std::string reg = reg_stack.top();
            switch (value->kind.tag)
            {
            case KOOPA_RVT_INTEGER:
                std::cout << std::setw(6) << "li" << reg << ", " << value->kind.data.integer.value << std::endl;
                std::cout << std::setw(6) << "sw" << reg << ", " << 4 * (i - 8) << "(sp)" << std::endl;
                break;
            default:
                std::cout << std::setw(6) << "lw" << reg << ", " << stack_map[value] << "(sp)" << std::endl;
                std::cout << std::setw(6) << "sw" << reg << ", " << 4 * (i - 8) << "(sp)" << std::endl;
                break;
            }
        }
    }
    std::cout << std::setw(6) << "call" << call.callee->name + 1 << std::endl;

    if (call.callee->ty->data.function.ret->tag != KOOPA_RTT_UNIT)
    {
        // std::cerr << call.callee->ty->tag << std::endl;
        std::cout << std::setw(6) << "sw" << "a0, " << stack_map[fa_value] << "(sp)" << std::endl;
    }

    while (!regs.empty())
    {
        restore_regs(regs.top());
        regs.pop();
    }
}
// 访问 global_alloc 指令
void Visit(const koopa_raw_global_alloc_t &global_alloc, const koopa_raw_value_t &value)
{
    std::cout << ".global " << value->name + 1 << std::endl;
    std::cout << value->name + 1 << ':' << std::endl;
    switch (global_alloc.init->kind.tag)
    {
    case KOOPA_RVT_INTEGER:
        std::cout << ".word " << global_alloc.init->kind.data.integer.value << std::endl;
        break;
    case KOOPA_RVT_ZERO_INIT:
        if (global_alloc.init->ty->tag == KOOPA_RTT_ARRAY)
        {
            std::cout << ".zero " << cal_array_length(*global_alloc.init->ty) * 4 << std::endl;
        }
        else
        {
            std::cout << ".zero 4" << std::endl;
        }
        break;
    case KOOPA_RVT_AGGREGATE:
    {
        std::list<int32_t> init_list;
        koopa_raw_aggregate_t _aggregate = global_alloc.init->kind.data.aggregate;
        analysis_aggregate(_aggregate, init_list);
        int zero_count = 0;
        bool zero_flag = false;
        for (auto i : init_list)
        {
            if(i == 0)
            {
                zero_flag = true;
                zero_count++;
            }
            else 
            {
                if(zero_flag){
                    std::cout << ".zero " << zero_count * 4 << std::endl;
                    zero_flag = false;
                    zero_count = 0;
                }
                std::cout << ".word " << i << std::endl;
            }
        }
        break;
    }

    default:
        std::cerr << global_alloc.init->kind.tag << std::endl;
        assert(false);
    }
}

// 访问 get_elem_ptr 指令
void Visit(const koopa_raw_get_elem_ptr_t &get_elem_ptr, const koopa_raw_value_t &value)
{

    auto src_reg = reg_stack.top();
    reg_stack.pop();
    std::string index_reg = reg_stack.top();
    if (get_elem_ptr.src->kind.tag == KOOPA_RVT_GLOBAL_ALLOC)
    {
        std::cout << std::setw(6) << "la" << src_reg << ", " << get_elem_ptr.src->name + 1 << std::endl;
    }
    else
    {
        if (stack_map[get_elem_ptr.src] >= 0)
        {
            std::cout << std::setw(6) << "lw" << src_reg << ", " << stack_map[get_elem_ptr.src] << "(sp)" << std::endl;
        }
        else
        {
            std::cout << std::setw(6) << "mv" << src_reg << ", a" << stack_map[get_elem_ptr.src] + 10 << std::endl;
        }
    }

    if (get_elem_ptr.index->kind.tag == KOOPA_RVT_INTEGER)
    {
        std::cout << std::setw(6) << "li" << index_reg << ", " << get_elem_ptr.index->kind.data.integer.value * cal_array_length(*get_elem_ptr.src->ty->data.array.base->data.array.base) << std::endl;
        std::cout << std::setw(6) << "slli" << index_reg << ", " << index_reg << ", 2" << std::endl;
    }
    else
    {

        if (stack_map[get_elem_ptr.index] >= 0)
        {
            std::cout << std::setw(6) << "lw" << index_reg << ", " << stack_map[get_elem_ptr.index] << "(sp)" << std::endl;
            std::cout << std::setw(6) << "slli" << index_reg << ", " << index_reg << ", 2" << std::endl;
        }
        else
        {
            index_reg = "a" + std::to_string(stack_map[get_elem_ptr.index] + 10);
            std::cout << std::setw(6) << "slli" << reg_stack.top() << ", " << index_reg << ", 2" << std::endl;
            index_reg = reg_stack.top();
        }
    }
    std::cout << std::setw(6) << "add" << src_reg << ", " << src_reg << ", " << index_reg << std::endl;
    std::cout << std::setw(6) << "sw" << src_reg << ", " << stack_map[value] << "(sp)" << std::endl;
    reg_stack.push(src_reg);
}

// 访问 get_ptr 指令
void Visit(const koopa_raw_get_ptr_t &get_ptr, const koopa_raw_value_t &value)
{
    // std::string reg;
    // if (reg_stack.empty())
    //     assert(false);
    // reg = reg_stack.top();
    // reg_stack.pop();
    // if (get_ptr.src->kind.tag == KOOPA_RVT_GLOBAL_ALLOC)
    // {
    //     std::cout << std::setw(6) << "la" << reg << ", " << get_ptr.src->name + 1 << std::endl;
    // }
    // else
    // {
    //     std::cout << std::setw(6) << "lw" << reg << ", " << stack_map[get_ptr.src] << "(sp)" << std::endl;
    // }
    // std::cout << std::setw(6) << "addi" << reg << ", " << reg << ", " << get_ptr.index->kind.data.integer.value * cal_array_length(*get_ptr.src->ty->data.pointer.base) * 4 << std::endl;
    // std::cout << std::setw(6) << "sw" << reg << ", " << stack_map[value] << "(sp)" << std::endl;
    // reg_stack.push(reg);

    auto src_reg = reg_stack.top();
    reg_stack.pop();
    std::string index_reg = reg_stack.top();
    if (get_ptr.src->kind.tag == KOOPA_RVT_GLOBAL_ALLOC)
    {
        std::cout << std::setw(6) << "la" << src_reg << ", " << get_ptr.src->name + 1 << std::endl;
    }
    else
    {
        if (stack_map[get_ptr.src] >= 0)
        {
            std::cout << std::setw(6) << "lw" << src_reg << ", " << stack_map[get_ptr.src] << "(sp)" << std::endl;
        }
        else
        {
            std::cout << std::setw(6) << "mv" << src_reg << ", a" << stack_map[get_ptr.src] + 10 << std::endl;
        }
    }

    if (get_ptr.index->kind.tag == KOOPA_RVT_INTEGER)
    {
        std::cout << std::setw(6) << "li" << index_reg << ", " << get_ptr.index->kind.data.integer.value * cal_array_length(*get_ptr.src->ty->data.pointer.base) << std::endl;
        std::cout << std::setw(6) << "slli" << index_reg << ", " << index_reg << ", 2" << std::endl;
    }
    else
    {

        if (stack_map[get_ptr.index] >= 0)
        {
            std::cout << std::setw(6) << "lw" << index_reg << ", " << stack_map[get_ptr.index] << "(sp)" << std::endl;
            std::cout << std::setw(6) << "slli" << index_reg << ", " << index_reg << ", 2" << std::endl;
        }
        else
        {
            index_reg = "a" + std::to_string(stack_map[get_ptr.index] + 10);
            std::cout << std::setw(6) << "slli" << reg_stack.top() << ", " << index_reg << ", 2" << std::endl;
            index_reg = reg_stack.top();
        }
    }
    std::cout << std::setw(6) << "add" << src_reg << ", " << src_reg << ", " << index_reg << std::endl;
    std::cout << std::setw(6) << "sw" << src_reg << ", " << stack_map[value] << "(sp)" << std::endl;
    reg_stack.push(src_reg);
}

void save_regs(std::string reg)
{
    int count = reg[1] - '0';
    if (reg[0] == 'a')
    {
        std::cout << std::setw(6) << "sw" << reg << ", " << -size_of_stack_frame - 84 - count * 4 << "(sp)" << std::endl;
    }
}

void restore_regs(std::string reg)
{
    int count = reg[1] - '0';
    if (reg[0] == 'a')
    {
        std::cout << std::setw(6) << "lw" << reg << ", " << -size_of_stack_frame - 84 - count * 4 << "(sp)" << std::endl;
    }
}

int cal_array_length(const koopa_raw_type_kind &base)
{
    if (base.tag == KOOPA_RTT_INT32)
    {
        return 1;
    }
    else
    {
        int length = 0;
        length = cal_array_length(*base.data.array.base) * base.data.array.len;
        return length;
    }
}

void analysis_aggregate(const koopa_raw_aggregate_t &aggregate, std::list<int32_t> &init_list)
{
    for (size_t i = 0; i < aggregate.elems.len; i++)
    {
        koopa_raw_value_t value = (koopa_raw_value_t)(aggregate.elems.buffer[i]);
        if (value->kind.tag == KOOPA_RVT_INTEGER)
        {
            init_list.push_back(value->kind.data.integer.value);
        }
        else
        {
            analysis_aggregate(value->kind.data.aggregate, init_list);
        }
    }
}
