#pragma once
#ifndef AST_HPP
#define AST_HPP

#include <memory>
#include <string>
// 所有 AST 的基类
class BaseAST {
 public:
  virtual ~BaseAST() = default;
  virtual void dump() = 0;
};

// CompUnit 是 BaseAST
class CompUnitAST : public BaseAST {
 public:
  // 用智能指针管理对象
  std::unique_ptr<BaseAST> start;
  void dump();
};

//DefUnits 也是 BaseAST
class DefUnitsAST : public BaseAST {
 public:
  std::unique_ptr<BaseAST> def_units;
  std::unique_ptr<BaseAST> def_unit;
  void dump();
};
//DefUnit 也是 BaseAST
class DefUnitAST : public BaseAST {
 public:
  std::unique_ptr<BaseAST> content;
  void dump();
};
// FuncDef 也是 BaseAST
class FuncDefAST : public BaseAST {
 public:
  std::unique_ptr<BaseAST> type;
  std::string ident;
  std::unique_ptr<BaseAST> block;
  void dump();
};


// DeclarationType 也是 BaseAST
class DeclarationTypeAST: public BaseAST {
 public:
  std::unique_ptr<std::string> type;
  void dump();
};

// BasicType 也是 BaseAST

//Block 也是 BaseAST
class BlockAST : public BaseAST {
 public:
  std::unique_ptr<BaseAST> stmt;
  void dump();
};

//Stmt 也是 BaseAST
class StmtAST : public BaseAST {
 public:
  std::unique_ptr<BaseAST> sents;
  void dump();
};

//Sents 也是 BaseAST
class SentsAST : public BaseAST {
 public:
  std::unique_ptr<BaseAST> sents;
  std::unique_ptr<BaseAST> sent;
  void dump();
};

//Sent 也是 BaseAST
class SentAST : public BaseAST {
 public:
  std::unique_ptr<BaseAST> content;
  void dump();
};
//AssignmentAST 也是 BaseAST
class AssignsAST: public BaseAST {
 public:
  std::unique_ptr<BaseAST> assigns;
  std::unique_ptr<BaseAST> assign;
  void dump();
};

class AssignAST : public BaseAST {
 public:
  std::string ident;
  int value;
  void dump();
};

class DeclarationlistAST: public BaseAST {
 public:
  std::unique_ptr<BaseAST> type;
  std::unique_ptr<BaseAST> decls;
  void dump();
}; 

class DeclarationsAST: public BaseAST {
 public:
  std::unique_ptr<BaseAST> decls;
  std::unique_ptr<BaseAST> decl;
  void dump();
};

class DeclarationAST : public BaseAST {
 public:
  std::string ident;
  int value;
  void dump();
};

class ReturnAST: public BaseAST {
 public:
  int retNum;
  void dump();
};

#endif  // AST_HPP