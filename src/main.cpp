#include <cassert>
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include<fstream>
#include<sstream>
#include "variable.hpp"
#include "ast.hpp"
#include "irtool.hpp"
using namespace std;

// 声明 lexer 的输入, 以及 parser 函数
// 为什么不引用 sysy.tab.hpp 呢? 因为首先里面没有 yyin 的定义
// 其次, 因为这个文件不是我们自己写的, 而是被 Bison 生成出来的
// 你的代码编辑器/IDE 很可能找不到这个文件, 然后会给你报错 (虽然编译不会出错)
// 看起来会很烦人, 于是干脆采用这种看起来 dirty 但实际很有效的手段
sym_node *sym_head=nullptr, *sym_tail=nullptr, *sym_cur=nullptr;

extern FILE *yyin;
extern int yyparse(std::unique_ptr<BaseAST> &ast);


void parseGrammar(string fname);
void riscvASM(string infile,string outfile);

int main(int argc, const char *argv[]) {
  // 解析命令行参数. 测试脚本/评测平台要求你的编译器能接收如下参数:
  // compiler 模式 输入文件 -o 输出文件
  assert(argc == 5);
  auto mode = argv[1];
  auto input = argv[2];
  auto output = argv[4];
  string parsefilename;
  string irfilename;

  // 打开输入文件, 并且指定 lexer 在解析的时候读取这个文件
  yyin = fopen(input, "r");
  assert(yyin);
  if(yyin == nullptr) {
    cerr << "Failed to open input file: " << input << endl;
    return 1;
  }
  //区分不同的mode
  if(mode[1]=='k'){
    parsefilename=output;
    parseGrammar(parsefilename);
    return 0;
  }
  
  parsefilename="parse_result.koopa";
  //语法分析
  parseGrammar(parsefilename);
  //采用-riscv模式
  if(mode[1]=='r'){
    irfilename=output;
    riscvASM(parsefilename,irfilename);
    return 0;
  }
  //
  //保存文件
  // //语法分析阶段
  // std::ofstream outFile(output);
  //   if (!outFile) {
  //       std::cerr << "Failed to open file for writing.\n";
  //       return 1;
  //   }
  //   std::streambuf *coutBuf = std::cout.rdbuf();

  // // 将标准输出重定向到文件
  //   std::cout.rdbuf(outFile.rdbuf());

  // // 调用 parser 函数, parser 函数会进一步调用 lexer 解析输入文件的
  // unique_ptr<BaseAST> ast;
  // auto ret = yyparse(ast);
  // assert(!ret);
  // ast->dump();
  //  // 恢复标准输出流的缓冲区指针
  // std::cout.rdbuf(coutBuf);
  // outFile.close();
  // // 输出解析得到的 AST, 其实就是个字符串
  return 0;
}

//语法分析阶段，为了区分不同指令 flag 单设的函数
void parseGrammar(string fname){
    //打开输出文件，用其来存储语法分析的结果
    std::ofstream outFile(fname);
    if (!outFile) {
        std::cerr << "Failed to open file for writing.\n";
        return;
    }
    std::streambuf *coutBuf = std::cout.rdbuf();
    std::cout.rdbuf(outFile.rdbuf());
    // 调用 parser 函数, parser 函数会进一步调用 lexer 解析输入文件的
    unique_ptr<BaseAST> ast;
    auto ret = yyparse(ast);
    assert(!ret);
    ast->dump();
   // 恢复标准输出流的缓冲区指针
    std::cout.rdbuf(coutBuf);
    outFile.close();
}

void riscvASM(string infile,string outfile){
    //读入koopa文件
    std::ifstream inFile(infile.c_str());
    std::stringstream buffer;
    buffer << inFile.rdbuf();
    std::string ircontents = buffer.str();
    inFile.close();

    //打开输出文件，用其来存储语法分析的结果
    std::ofstream outFile(outfile);
    if (!outFile) {
        std::cerr << "Failed to open file for writing.\n";
        return;
    }
    std::streambuf *coutBuf = std::cout.rdbuf();
    std::cout.rdbuf(outFile.rdbuf());
    // 调用对IR处理的工具
    strir2asm(ircontents.c_str());
    // 恢复标准输出流的缓冲区指针
    std::cout.rdbuf(coutBuf);
    outFile.close();
}