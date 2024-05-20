#include "IRtoAsm.hpp"
#include <fstream>

int IRanalysis(std::string inputfile, std::string outputfile)
{
    std::ifstream in(inputfile);
    std::string str = "";
    std::string temp;
    while (getline(in, temp))
    {
        str += temp;
        str += "\n";
    }
    // 解析输入的 Koopa IR 程序

    std::ofstream out(outputfile);

    koopa_program_t program;
    koopa_error_code_t ret = koopa_parse_from_string(str.c_str(), &program);
    assert(ret == KOOPA_EC_SUCCESS); // 确保解析时没有出错
    // 创建一个 raw program builder, 用来构建 raw program
    koopa_raw_program_builder_t builder = koopa_new_raw_program_builder();
    // 将 Koopa IR 程序转换为 raw program
    koopa_raw_program_t raw = koopa_build_raw_program(builder, program);
    // 释放 Koopa IR 程序占用的内存
    koopa_delete_program(program);

    std::streambuf *coutbuf = std::cout.rdbuf();
    std::cout.rdbuf(out.rdbuf());

    Visit(raw);
    
    std::cout.rdbuf(coutbuf);
    out.close();
    
    koopa_delete_raw_program_builder(builder);

    return 0;
}