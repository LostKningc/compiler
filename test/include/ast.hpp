#ifndef AST_HPP
#define AST_HPP

#include <memory>
#include <string>
// 所有 AST 的基类
class BaseAST {
 public:
  virtual ~BaseAST() = default;
};

// CompUnit 是 BaseAST
class CompUnitAST : public BaseAST {
 public:
  // 用智能指针管理对象
  std::unique_ptr<BaseAST> func_def;
};

// FuncDef 也是 BaseAST
class FuncDefAST : public BaseAST {
 public:
  std::unique_ptr<BaseAST> type;
  std::string ident;
  std::unique_ptr<BaseAST> block;
};

// FuncType 也是 BaseAST
class FuncTypeAST : public BaseAST {
 public:
  std::unique_ptr<std::string> type;
};

// BasicType 也是 BaseAST

//Block 也是 BaseAST
class BlockAST : public BaseAST {
 public:
  std::unique_ptr<BaseAST> stmt;
};

//Stmt 也是 BaseAST
class StmtAST : public BaseAST {
 public:
  std::unique_ptr<BaseAST> sents;
};

//Sents 也是 BaseAST
class SentsAST : public BaseAST {
 public:
  std::unique_ptr<BaseAST> sents;
  std::unique_ptr<BaseAST> sent;
};

//Sent 也是 BaseAST
class SentAST : public BaseAST {
 public:
  std::unique_ptr<BaseAST> content;
};

//AssignmentAST 也是 BaseAST
class AssignsAST: public BaseAST {
 public:
  std::unique_ptr<BaseAST> assigns;
  std::unique_ptr<BaseAST> assign;
};

class AssignAST : public BaseAST {
 public:
  std::string ident;
  int value;
};

class ReturnAST: public BaseAST {
 public:
  int retNum;
};

#endif  // AST_HPP