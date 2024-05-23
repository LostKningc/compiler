
%code requires {
  #include <memory>
  #include <string>
  #include "ast.hpp"
  #include "variable.hpp"
  #include <cstring>
}

%{

#include <iostream>
#include <memory>
#include <string>
#include <cstring>

#include "ast.hpp"
#include "variable.hpp"

int yylex();
void yyerror(std::unique_ptr<BaseAST> &ast,std::string s);

using namespace std;

extern Val_Table val_table;
%}


%parse-param {std::unique_ptr<BaseAST> &ast}


%union {
  std::string *str_val;
  int int_val;
  op op_val;
  Btype btype_val;
  BaseAST *ast_val;
}


%token INT VOID FLOAT RETURN CONST
%token <str_val> IDENT
%token <int_val> INT_CONST

%type <ast_val> DefUnit DefUnits
%type <ast_val> FuncDef Block Stmt Sents Sent
%type <ast_val> Assignments Assignment
%type <ast_val> Declarationlist ConstDeclList ConstDefs ConstDef ConstExp VarDeclList VarDefs VarDef InitVal
%type <ast_val> RelExp EqExp LAndExp LOrExp
%type <ast_val> Exp AddExp MulExp PrimaryExp UnaryExp OptionExp
%type <op_val> UnaryOp
%type <ast_val> Number LVal
%type <ast_val> FunType
%type <btype_val> BasicType BType

%%

CompUnit
 :DefUnits {
   auto comp_unit = make_unique<CompUnitAST>();
   comp_unit->start = unique_ptr<BaseAST>($1);
   ast = move(comp_unit);
 }

DefUnits
  :DefUnits DefUnit {
    auto ast = new DefUnitsAST();
    ast->def_units = unique_ptr<BaseAST>($1);
    ast->def_unit = unique_ptr<BaseAST>($2);
    $$ = ast;
  }|DefUnit {
    auto ast = new DefUnitsAST();
    ast->def_units = nullptr;
    ast->def_unit = unique_ptr<BaseAST>($1);
    $$ = ast;
  } 
  ;

DefUnit
  : FuncDef {
    auto ast = new DefUnitAST();
    ast->content = unique_ptr<BaseAST>($1);
    $$=ast;
  }
  |Sent {
    auto  ast = new DefUnitAST();
    ast->content = unique_ptr<BaseAST>($1);
    $$=ast;
  }
  ;


FuncDef
  : FunType IDENT '(' ')' Block {
    auto ast=new FuncDefAST();
    ast->type = unique_ptr<BaseAST>($1);
    ast->ident = *unique_ptr<string>($2);
    ast->block = unique_ptr<BaseAST>($5);
    $$=ast;
  }
  ;

//类型

FunType
  : BasicType {
    auto ast = new DeclarationTypeAST();
    ast->type = $1;
    $$ = ast;
  }
  ;


BasicType: INT {
  $$ = Btype::BINT;
}|
  VOID {
    $$ = Btype::BVOID;
  }|
  FLOAT {
    $$ = Btype::BFLOAT;
  }
  ;

//变量用的
BType:INT{
  $$ = Btype::BINT;
};

Block
  : '{' Stmt '}' {
    auto ast=new BlockAST();
    ast->stmt = unique_ptr<BaseAST>($2);
    $$=ast;
  }|'{' '}'{
    auto ast=new BlockAST();
    ast->stmt=nullptr;
    $$=ast;
  }

  ;

Stmt
  : Sents {
    auto ast = new StmtAST();
    ast->sents = unique_ptr<BaseAST>($1);
    $$ = ast;
  }
  ;

Sents
  :Sents Sent{
    SentsAST* Sents = nullptr;

      Sents = dynamic_cast<SentsAST*>($1);
      //后续可能会改进
      if(Sents==nullptr){
        std::cerr << "Exception: " << "dynamic_cast failed"<< std::endl;
      }

    Sents->sents.push_back(unique_ptr<BaseAST>($2));
    $$ = Sents;
  } |
    Sent {
      auto Sents = new SentsAST();
      Sents->sents.push_back(unique_ptr<BaseAST>($1));
      $$ = Sents;
    }
  ;

//TODO:重构ReturnAST
Sent:
  Assignments ';' {
    auto ast =new SentAST();
    ast->content = unique_ptr<BaseAST>($1);
    $$=ast;
  }|
  RETURN Exp ';' {
    auto ast = new SentAST();
    auto retAst=new ReturnAST();
    retAst->retNum=unique_ptr<BaseAST>($2);
    ast->content=unique_ptr<BaseAST>(retAst);
    $$=ast;
  }
  |Declarationlist ';'{
    auto ast = new SentAST();
    ast->content = unique_ptr<BaseAST>($1);
    $$=ast;
  }
  |OptionExp ';'{
    auto ast = new SentAST();
    ast->content = unique_ptr<BaseAST>($1);
    $$=ast;
  }
  | RETURN ';'{
    auto ast = new SentAST();
    auto retAst=new ReturnAST();
    retAst->retNum=nullptr;
    ast->content=unique_ptr<BaseAST>(retAst);
    $$=ast;
  }|
  Block{
    auto ast = new SentAST();
    ast->content = unique_ptr<BaseAST>($1);
    $$=ast;
  }
  ;

  OptionExp:
    Exp{
      auto ast=new OptionExpAST();
      ast->exp=unique_ptr<BaseAST>($1);
      $$=ast;
    }|
    {
      auto ast=new OptionExpAST();
      ast->exp=nullptr;
      $$ = ast;
    }
    ;
//声明变量的办法
//重构DeclearationlistAST
Declarationlist:
  ConstDeclList {
    $$ = $1;
  }|
  VarDeclList {
    $$ = $1;
  };

//构造ConstDecllist树
ConstDeclList:
  CONST BType ConstDefs {
    auto constdecllist = new ConstDeclListAST();
    constdecllist->type = $2;
    constdecllist->constdefs = unique_ptr<BaseAST>($3);
    $$ = constdecllist;
  }
  ;
VarDeclList:
  BType VarDefs {
    auto vardecllist = new VarDeclListAST();
    vardecllist->type = $1;
    vardecllist->vardefs = unique_ptr<BaseAST>($2);
    $$ = vardecllist;
  }
  ;
//构造ConstDefs树(需要更新一个vector)
ConstDefs:
  ConstDef {
    auto Defs = new ConstDefsAST();
    Defs->constdefs.push_back(unique_ptr<BaseAST>($1));
    $$ = Defs;
  }|
  ConstDefs ',' ConstDef {
    ConstDefsAST* defsast = nullptr;
    defsast = dynamic_cast<ConstDefsAST*>($1);
    //后续可能会改进
    if(defsast==nullptr){
        std::cerr << "Exception: " << "dynamic_cast failed"<< std::endl;
      }
    defsast->constdefs.push_back(unique_ptr<BaseAST>($3));
    $$ = defsast;
  }
  ;

//构造VarDefs树(需要更新一个vector)
VarDefs:
  VarDef {
    auto Defs = new VarDefsAST();
    Defs->vardefs.push_back(unique_ptr<BaseAST>($1));
    $$ = Defs;
  }|
  VarDefs ',' VarDef {
    VarDefsAST* defsast = nullptr;
    defsast = dynamic_cast<VarDefsAST*>($1);
    //后续可能会改进
    if(defsast==nullptr){
        std::cerr << "Exception: " << "dynamic_cast failed"<< std::endl;
      }
    defsast->vardefs.push_back(unique_ptr<BaseAST>($3));
    $$ = defsast;
  }
  ;
//构建树
ConstDef:
  IDENT '=' InitVal {
    auto ast = new ConstDefAST();
    ast->ident = *($1);
    ast->initval = unique_ptr<BaseAST>($3);
    $$ = ast;
  }
  ;

VarDef:
  IDENT '=' InitVal {
    auto ast = new VarDefAST();
    ast->ident = *($1);
    ast->initval = unique_ptr<BaseAST>($3);
    $$ = ast;
  }
  |IDENT {
    auto ast = new VarDefAST();
    ast->ident = *($1);
    ast->initval = nullptr;
    $$ = ast;
  }
  ;

//获得变量的值
InitVal:
  ConstExp {
    auto initval = new ConstExpAST();
    initval->exp = unique_ptr<BaseAST>($1);
    $$ = initval;
  }
  ;

ConstExp:
  Exp{
    $$ =$1;
  }
  ;

//表达式的部分
//构造Exp树
Exp
  : LOrExp {
    $$ = $1;
  }
  ;

//构造LOrExp树
LOrExp:
  LOrExp '|''|' LAndExp {
    auto lorexp = new BinaryExpAST();
    lorexp->exp1 = unique_ptr<BaseAST>($1);
    lorexp->exp2 = unique_ptr<BaseAST>($4);
    lorexp->op2=op::OR;
    //lorexp->calc_f=($1->calc_f)&&($4->calc_f);
    $$ = lorexp;
  }
  | LAndExp {
    $$=$1;
  }
  ; 

//构造LAndExp树
LAndExp:
  LAndExp '&''&' EqExp {
    auto landexp = new BinaryExpAST();
    landexp->exp1 = unique_ptr<BaseAST>($1);
    landexp->exp2 = unique_ptr<BaseAST>($4);
    landexp->op2 = op::AND;
    //landexp->calc_f=($1->calc_f)&&($4->calc_f);
    $$ = landexp;
  }
  | EqExp {
    $$=$1;
  }
  ;

//构造EqExp树
EqExp:
  EqExp '=''=' RelExp {
    auto eqexp = new BinaryExpAST();
    eqexp->exp1 = unique_ptr<BaseAST>($1);
    eqexp->exp2 = unique_ptr<BaseAST>($4);
    eqexp->op2 = op::EQ;
    //eqexp->calc_f=($1->calc_f)&&($4->calc_f);
    $$ = eqexp;
  }
  | EqExp '!' '=' RelExp {
    auto eqexp = new BinaryExpAST();
    eqexp->exp1 = unique_ptr<BaseAST>($1);
    eqexp->exp2 = unique_ptr<BaseAST>($4);
    eqexp->op2 = op::NE;
    //eqexp->calc_f=($1->calc_f)&&($4->calc_f);
    $$ = eqexp;
  }
  | RelExp {
    $$=$1;
  }
  ;


//构造RelExp树
RelExp:
  RelExp '>' AddExp {
    auto relexp = new BinaryExpAST();
    relexp->exp1 = unique_ptr<BaseAST>($1);
    relexp->exp2 = unique_ptr<BaseAST>($3);
    relexp->op2 = op::GT;
    //relexp->calc_f=($1->calc_f)&&($3->calc_f);
    $$ = relexp;
  }
  | RelExp '<' AddExp {
    auto relexp = new BinaryExpAST();
    relexp->exp1 = unique_ptr<BaseAST>($1);
    relexp->exp2 = unique_ptr<BaseAST>($3);
    relexp->op2 = op::LT;
    //relexp->calc_f=($1->calc_f)&&($3->calc_f);
    $$ = relexp;
  }
  | RelExp '>''=' AddExp {
    auto relexp = new BinaryExpAST();
    relexp->exp1 = unique_ptr<BaseAST>($1);
    relexp->exp2 = unique_ptr<BaseAST>($4);
    relexp->op2 = op::GE;
    //relexp->calc_f=($1->calc_f)&&($4->calc_f);
    $$ = relexp;
  }
  | RelExp '<''=' AddExp {
    auto relexp = new BinaryExpAST();
    relexp->exp1 = unique_ptr<BaseAST>($1);
    relexp->exp2 = unique_ptr<BaseAST>($4);
    relexp->op2 = op::LE;
    //relexp->calc_f=($1->calc_f)&&($4->calc_f);
    $$ = relexp;
  }
  | AddExp {
    $$=$1;
  }
  ;

//构造AddExp树
AddExp:
  AddExp '+' MulExp {
    auto addexp = new BinaryExpAST();
    addexp->exp1 = unique_ptr<BaseAST>($1);
    addexp->exp2 = unique_ptr<BaseAST>($3);
    addexp->op2 = op::ADD;
    //addexp->calc_f=($1->calc_f)&&($3->calc_f);
    $$ = addexp;
  }
  | AddExp '-' MulExp {
    auto addexp = new BinaryExpAST();
    addexp->exp1 = unique_ptr<BaseAST>($1);
    addexp->exp2 = unique_ptr<BaseAST>($3);
    addexp->op2 = op::SUB;
    //addexp->calc_f=($1->calc_f)&&($3->calc_f);
    $$ = addexp;
  }
  | MulExp {
    $$=$1;
  }
  ;

//构造MulExp树
MulExp:
  MulExp '*' UnaryExp {
    auto mulexp = new BinaryExpAST();
    mulexp->exp1 = unique_ptr<BaseAST>($1);
    mulexp->op2 = op::MUL;
    mulexp->exp2 = unique_ptr<BaseAST>($3);
    //mulexp->calc_f=($1->calc_f)&&($3->calc_f);
    $$ = mulexp;
  }
  | MulExp '/' UnaryExp {
    auto mulexp = new BinaryExpAST();
    mulexp->exp1 = unique_ptr<BaseAST>($1);
    mulexp->op2 = op::DIV;
    mulexp->exp2 = unique_ptr<BaseAST>($3);
    //mulexp->calc_f=($1->calc_f)&&($3->calc_f);
    $$ = mulexp;
  }
  | MulExp '%' UnaryExp {
    auto mulexp = new BinaryExpAST();
    mulexp->exp1 = unique_ptr<BaseAST>($1);
    mulexp->op2 = op::MOD;
    mulexp->exp2 = unique_ptr<BaseAST>($3);
    //mulexp->calc_f=($1->calc_f)&&($3->calc_f);
    $$ = mulexp;
  }
  |UnaryExp {
    $$ = $1;
  }
  ; 


//TODO:构建UnaryExp树
UnaryExp:
  PrimaryExp {
    $$ = $1;
  }
  |UnaryOp UnaryExp {
    auto ast = new UnaryExpAST();
    ast->op1 = $1;
    ast->exp1 = unique_ptr<BaseAST>($2);
    //ast->calc_f=ast->exp1->calc_f;
    $$ = ast;
  }
  ;

UnaryOp: 
  '-' {
    $$ = op::SUB;
  }|
  '+' {
    $$ = op::ADD;
  }
  |'!' {
    $$ = op::NOT;
  }
  ;
//TODO:构建PrimaryExp树
PrimaryExp:
  '(' Exp ')' {
    $$ = $2;
  }
  |Number {
    $$ = $1;
  }|
  LVal {
    $$ = $1;
  }
  ;

Assignments:
  Assignment {
    $$=$1;
  }
  ;

Assignment:
  IDENT '=' Exp {
    auto ast=new AssignAST();
    ast->ident=*($1);
    ast->exp=unique_ptr<BaseAST>($3);
    //set_sym_val(sym_head,sym_tail,*($1),$3);
    $$=ast;
  }
  ;

//TODO:构建Number树
Number
  : INT_CONST {
    auto ast = new NumberAST();
    ast->value = $1;
    ast->calc_f=1;
    $$ = ast;
  }
  ;

LVal:
  IDENT {
    auto ast = new LValAST();
    ast->ident = *($1);
    $$ = ast;
  }
  ; 
%%

void yyerror(std::unique_ptr<BaseAST> &ast,std::string s) {
  extern int yylineno; //define and maintained in lex
  extern char *yytext; //define and maintained in lex
  int len = strlen(yytext);
  int i;
  char buf[512]={0};
  for(i=0;i<len;++i){
    sprintf(buf,"%s%d",buf,yytext[i]);
  }
  fprintf(stderr, "Error: %s at symbol '%s' on line %d\n", s.c_str(), buf,yylineno);
  
}