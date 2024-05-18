#include<iostream>
#include<cassert>
#include "irtool.hpp"

void strir2asm(const char *str) {
    //解析字符串str
    koopa_program_t programIR;
    koopa_error_code_t ret=koopa_parse_from_string(str,&programIR);
    assert(ret==KOOPA_EC_SUCCESS);
    //创建一个builder来构建raw program
    koopa_raw_program_builder_t builder=koopa_new_raw_program_builder();
    //将Koopa IR转换为raw program
    koopa_raw_program_t rawProgram=koopa_build_raw_program(builder,programIR);
    //释放programIR
    koopa_delete_program(programIR);

    //处理 raw program
    //TODO
    //需要一个字符串来存储汇编代码
    //我们需要能够访问rawProgram的每一处细节，然后对着些细节处理，映射为汇编代码（string或是文件处理）
    //1.我们需要一个能访问rawProgram的迭代函数
    std::cout<<"    .text"<<std::endl;
    Visit(rawProgram.values);
    Visit(rawProgram.funcs);


    koopa_delete_raw_program_builder(builder);
};


//访问结构中的各处细节
void Visit(const koopa_raw_slice_t &slice){
    for(size_t i=0;i<slice.len;++i){
        auto ptr=slice.buffer[i];
        switch(slice.kind){
            case KOOPA_RSIK_FUNCTION:
                //处理函数
                Visit(reinterpret_cast<const koopa_raw_function_t>(ptr));
                break;
            case KOOPA_RSIK_BASIC_BLOCK:
                //处理基本块
                Visit(reinterpret_cast<const koopa_raw_basic_block_t>(ptr));
                break;
            case KOOPA_RSIK_VALUE:
                //处理值
                Visit(reinterpret_cast<const koopa_raw_value_t>(ptr));
                break;
            default:
                assert(false);
        }
    }
}

//访问函数
void Visit(const koopa_raw_function_t &func){
    //函数处理
    std::cout<<"    .globl "<<func->name+1<<std::endl;
    std::cout<<func->name+1<<":"<<std::endl;
    //处理函数的基本块
    Visit(func->bbs);
}

//访问基本块
void Visit(const koopa_raw_basic_block_t &bb){
    //基本块处理
    
    //处理基本块的指令
    Visit(bb->insts);
}

//访问指令
void Visit(const koopa_raw_value_t &value){
    //根据指令的类型判断后续需要如何访问
    const auto &kind=value->kind;
    switch(kind.tag){
        case KOOPA_RVT_RETURN:
            //处理返回指令
            Visit(kind.data.ret);
            break;
        case KOOPA_RVT_INTEGER:
            //访问Integer指令
            Visit(kind.data.integer);
            break;
        default:
            //其他类型暂时遇不到
            assert(false);
    }
}

//指令细节
//返回指令处理
void Visit(const koopa_raw_return_t
&ret){
    std::cout<<"    li a0,"<<(int32_t)ret.value->kind.data.integer.value<<std::endl;
    std::cout<<"    ret"<<std::endl;
}

//整数指令处理
void Visit(const koopa_raw_integer_t &integer){
    //std::cout<<"    li a0,"<<integer.value<<std::endl;
}



