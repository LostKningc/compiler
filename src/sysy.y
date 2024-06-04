
%code requires {
  #include <memory>
  #include <string>
  #include "ast.hpp"
  #include "variable.hpp"
  #include <cstring>
}

%{
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
%token IF ELSE WHILE BREAK CONTINUE FOR
%token <str_val> IDENT
%token <int_val> INT_CONST

%type <ast_val> DefUnit DefUnits DefUnitList
%type <ast_val> FuncDef Block Stmt BlockItems BlockItem FuncFParams FuncFParam FuncFParamList
%type <ast_val> FuncRParamList FuncRParams FuncArrays FuncArray
%type <ast_val> Assignments Assignment
%type <ast_val> Declarationlist ConstDeclList ConstDefs ConstDef ConstExp VarDeclList VarDefs VarDef InitVal
%type <ast_val> ArrayDefs ArrayDef ConstInitVal ConstVals InitVals
%type <ast_val> LArray LArrays
%type <ast_val> RelExp EqExp LAndExp LOrExp
%type <ast_val> Exp AddExp MulExp PrimaryExp UnaryExp OptionExp
%type <op_val> UnaryOp
%type <ast_val> Number LVal
%type <ast_val> Else
%type <btype_val> BasicType 

%%

CompUnit
 :DefUnitList {
   auto comp_unit = make_unique<CompUnitAST>();
   comp_unit->start = unique_ptr<BaseAST>($1);
   ast = move(comp_unit);
 }

DefUnitList:
  DefUnits {
    $$ = $1;
  };

DefUnits
  :DefUnits DefUnit {
    DefUnitsAST* ast = dynamic_cast<DefUnitsAST*>($1);
    if(ast==nullptr){
      std::cerr << "Exception: " << "dynamic_cast failed"<< std::endl;
    }
    ast->unit_list.push_back(unique_ptr<BaseAST>($2));
    $$ = ast;
  }|DefUnit {
    auto ast = new DefUnitsAST();
    ast->unit_list.push_back(unique_ptr<BaseAST>($1));
    $$ = ast;
  } 
  ;

DefUnit
  : FuncDef {
    auto ast = new DefUnitAST();
    ast->content = unique_ptr<BaseAST>($1);
    $$=ast;
  }|
  Declarationlist ';'{
    auto ast = new DefUnitAST();
    ast->content = unique_ptr<BaseAST>($1);
    $$=ast;
  }
  ;


FuncDef
  : BasicType IDENT '(' FuncFParamList ')' Block {
    auto ast=new FuncDefAST();
    auto typeast=new DeclarationTypeAST();
    typeast->type=$1;
    ast->type = unique_ptr<BaseAST>(typeast);
    ast->ident = *unique_ptr<string>($2);
    ast->params=unique_ptr<BaseAST>($4);
    ast->block = unique_ptr<BaseAST>($6);
    $$=ast;
  }
  ;

//类型
//函数参数定义部分
FuncFParamList:
  FuncFParams {
    $$ = $1;
  }|
  {
    $$ = nullptr;
  }
  ;

FuncFParams:
  FuncFParams ',' FuncFParam {
    FuncFParamsAST* ast = nullptr;
    ast = dynamic_cast<FuncFParamsAST*>($1);
    if(ast==nullptr){
      std::cerr << "Exception: " << "dynamic_cast failed"<< std::endl;
    }
    ast->paramlist.push_back(unique_ptr<BaseAST>($3));
    $$ = ast;
  }|
  FuncFParam {
    auto ast = new FuncFParamsAST();
    ast->paramlist.push_back(unique_ptr<BaseAST>($1));
    $$ = ast;
  }
  ;
  //函数参数定义部分
FuncFParam:
    BasicType IDENT {
      auto ast = new FuncFParamAST();
      ast->type = $1;
      ast->ident = *($2);
      ast->arraydef = nullptr;
      $$ = ast;
    }
    |BasicType FuncArrays{
      auto ast = new FuncFParamAST();
      ast->type = $1;
      ast->ident = "";
      ast->arraydef = unique_ptr<BaseAST>($2);
      $$ = ast;
    }
    ;

FuncArrays:
  FuncArrays '[' ConstExp ']'{
    FuncArrayAST* ast = nullptr;
    ast = dynamic_cast<FuncArrayAST*>($1);
    if(ast==nullptr){
      throw std::runtime_error("error: FuncArrayAST dynamic_cast failed");
    }
    ast->dimon_list.push_back(unique_ptr<BaseAST>($3));
    $$ = ast;
  }|
  FuncArray {
    $$ = $1;
  }
  ;

FuncArray:
  IDENT '[' ']'{
    auto ast = new FuncArrayAST();
    ast->ident = *($1);
    $$ = ast;
  }

/* FunType
  : BasicType {
    auto ast = new DeclarationTypeAST();
    ast->type = $1;
    $$ = ast;
  }
  ; */


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


/* BType:INT{
  $$ = Btype::BINT;
}; */

Block
  : '{' BlockItems '}' {
    auto ast=new BlockAST();
    ast->blockitems = unique_ptr<BaseAST>($2);
    $$=ast;
  }|'{' '}'{
    auto ast=new BlockAST();
    ast->blockitems=nullptr;
    $$=ast;
  }

  ;


BlockItems
  :BlockItems BlockItem{
    BlockItemsAST* Items = nullptr;

      Items = dynamic_cast<BlockItemsAST*>($1);
      //后续可能会改进
      if(Items==nullptr){
        std::cerr << "Exception: " << "dynamic_cast failed"<< std::endl;
      }

    Items->itemlist.push_back(unique_ptr<BaseAST>($2));
    $$ = Items;
  } |
    BlockItem {
      auto Items = new BlockItemsAST();
      Items->itemlist.push_back(unique_ptr<BaseAST>($1));
      $$ = Items;
    }
  ;

//TODO:重构ReturnAST
BlockItem:
  Declarationlist ';'{
    auto ast = new BlockItemAST();
    ast->content = unique_ptr<BaseAST>($1);
    $$=ast;
  }|
  Stmt {
    auto ast = new StmtAST();
    ast->sent = unique_ptr<BaseAST>($1);
    $$ = ast;
  }
  ;

Stmt
  : 
  Assignments ';' {
    auto ast =new BlockItemAST();
    ast->content = unique_ptr<BaseAST>($1);
    $$=ast;
  }|
  RETURN Exp ';' {
    auto ast = new BlockItemAST();
    auto retAst=new ReturnAST();
    retAst->retNum=unique_ptr<BaseAST>($2);
    ast->content=unique_ptr<BaseAST>(retAst);
    $$=ast;
  }
  |OptionExp ';'{
    auto ast = new BlockItemAST();
    ast->content = unique_ptr<BaseAST>($1);
    $$=ast;
  }
  | RETURN ';'{
    auto ast = new BlockItemAST();
    auto retAst=new ReturnAST();
    retAst->retNum=nullptr;
    ast->content=unique_ptr<BaseAST>(retAst);
    $$=ast;
  }|
  Block{
    auto ast = new BlockItemAST();
    ast->content = unique_ptr<BaseAST>($1);
    $$=ast;
  }|
  IF '(' Exp ')' Stmt Else{
    auto ast=new IfElseAST();
    ast->exp=unique_ptr<BaseAST>($3);
    ast->then_part=unique_ptr<BaseAST>($5);
    ast->else_part=unique_ptr<BaseAST>($6);
    $$=ast; 
  }|
  WHILE '(' Exp ')' Stmt{
    auto ast=new WhileAST();
    ast->exp=unique_ptr<BaseAST>($3);
    ast->body=unique_ptr<BaseAST>($5);
    $$=ast;
  }|
  BREAK ';'{
    auto ast=new BreakAST();
    $$=ast;
  }|
  CONTINUE ';'{
    auto ast=new ContinueAST();
    $$=ast;
  }
  ;



Else:
  ELSE Stmt{
    $$=$2;
  }
  |
  {
    $$=nullptr;
  }


OptionExp:
    Exp{
      auto ast=new OptionExpAST();
      ast->exp=unique_ptr<BaseAST>($1);
      $$=ast;
    }
    |
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
  CONST BasicType ConstDefs {
    auto constdecllist = new ConstDeclListAST();
    constdecllist->type = $2;
    constdecllist->constdefs = unique_ptr<BaseAST>($3);
    $$ = constdecllist;
  }
  ;
VarDeclList:
  BasicType VarDefs {
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
//TODO:构建树
ConstDef:
  IDENT '=' ConstInitVal {
    auto ast = new ConstDefAST();
    ast->ident = *($1);
    ast->arraydef = nullptr;
    ast->initval = unique_ptr<BaseAST>($3);
    $$ = ast;
  }
  |
  ArrayDefs '='  ConstInitVal{
    auto ast = new ConstDefAST();
    ast->ident = "";
    ast->arraydef = unique_ptr<BaseAST>($1);
    ast->initval = unique_ptr<BaseAST>($3);
    $$ = ast;
  }
  ;

ConstInitVal:
  ConstExp {
    auto initval = new ConstExpAST();
    initval->exp = unique_ptr<BaseAST>($1);
    $$ = initval;
  }
  |'{' ConstVals '}'{
    $$=$2;
  }|
  '{' '}'{
    auto initvals = new ConstInitValsAST();
    initvals->constexp = nullptr;
    $$ = initvals;
  }
  ;

ConstVals:
  ConstInitVal {
    auto ast = new ConstInitValsAST();
    ast->array_val_list.push_back(unique_ptr<BaseAST>($1));
    $$ = ast;
  }|
  ConstVals ',' ConstInitVal {
    ConstInitValsAST* valsast = nullptr;
    valsast = dynamic_cast<ConstInitValsAST*>($1);
    if(valsast==nullptr){
        throw std::runtime_error("error: ConstInitValsAST dynamic_cast failed");
      }
    valsast->array_val_list.push_back(unique_ptr<BaseAST>($3));
    $$ = valsast;
  }
  ;



//重构这棵树
VarDef:
  IDENT '=' InitVal {
    auto ast = new VarDefAST();
    ast->ident = *($1);
    ast->arraydef = nullptr;
    ast->initval = unique_ptr<BaseAST>($3);
    $$ = ast;
  }
  |IDENT {
    auto ast = new VarDefAST();
    ast->ident = *($1);
    ast->arraydef = nullptr;
    ast->initval = nullptr;
    $$ = ast;
  }
  |ArrayDefs{
    auto ast = new VarDefAST();
    ast->ident = "";
    ast->arraydef = unique_ptr<BaseAST>($1);
    auto initvals = new InitValsAST();
    initvals->exp = nullptr;
    ast->initval = unique_ptr<BaseAST>(initvals);
    $$ = ast;
  }
  |
  ArrayDefs '='  InitVal {
    auto ast = new VarDefAST();
    ast->ident = "";
    ast->arraydef = unique_ptr<BaseAST>($1);
    ast->initval = unique_ptr<BaseAST>($3);
    $$ = ast;
  }
  ;

ArrayDefs:
  ArrayDefs '[' ConstExp ']'{
    ArrayDefsAST* ast = nullptr;
    ast = dynamic_cast<ArrayDefsAST*>($1);
    if(ast==nullptr){
      throw std::runtime_error("error: ArrayDefsAST cast failed");
    }
    ast->dimon_list.push_back(unique_ptr<BaseAST>($3)); 
    $$ = ast;
  }
  |
  ArrayDef {
    $$ = $1;
  }
  ;

ArrayDef:
  IDENT '[' ConstExp ']' {
    auto ast = new ArrayDefsAST();
    ast->ident = *($1);
    ast->dimon_list.push_back(unique_ptr<BaseAST>($3));
    $$ = ast;
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
    ast->arraydef=nullptr;
    ast->exp=unique_ptr<BaseAST>($3);
    //set_sym_val(sym_head,sym_tail,*($1),$3);
    $$=ast;
  }|
  LArrays '=' Exp{
    auto ast=new AssignAST();
    ast->ident="";
    ast->arraydef=unique_ptr<BaseAST>($1);
    ast->exp=unique_ptr<BaseAST>($3);
    $$=ast;
  }
  ;

//获得变量的值
InitVal:
  Exp {
    auto initval = new ExpAST();
    initval->exp = unique_ptr<BaseAST>($1);
    $$ = initval;
  }
  |
  '{' InitVals '}'{
    InitValsAST* ast=dynamic_cast<InitValsAST*>($2);
    if(ast==nullptr){
      throw std::runtime_error("error: ArrayDefsAST cast failed");
    }
    $$ = ast;
  }
  |
  '{' '}'{
    auto initvals = new InitValsAST();
    initvals->exp = nullptr;
    $$ = initvals;
  }
  ;

InitVals:
  InitVal {
    auto ast = new InitValsAST();
    ast->array_val_list.push_back(unique_ptr<BaseAST>($1));
    $$ = ast;
  }|
  InitVals ',' InitVal {
    InitValsAST* valsast = nullptr;
    valsast = dynamic_cast<InitValsAST*>($1);
    if(valsast==nullptr){
        std::cerr << "Exception: " << "dynamic_cast failed"<< std::endl;
      }
    valsast->array_val_list.push_back(unique_ptr<BaseAST>($3));
    $$ = valsast;
  }

ConstExp:
  Exp{
    auto ast=new ConstExpAST();
    ast->exp=unique_ptr<BaseAST>($1);
    $$=ast;
  }
  ;

//表达式的部分
//构造Exp树
Exp
  : LOrExp {
    auto ast=new ExpAST();
    ast->exp=unique_ptr<BaseAST>($1);
    $$=ast;
  }
  ;

 
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

//函数调用
FuncRParamList:
  FuncRParams{
    $$ = $1;
  }|
  {
    $$ = nullptr;
  }
  ;

//函数调用
FuncRParams:
  FuncRParams ',' Exp{
    FuncRParamsAST* ast = nullptr;
    ast = dynamic_cast<FuncRParamsAST*>($1);
    if(ast==nullptr){
      std::cerr << "Exception: " << "dynamic_cast failed"<< std::endl;
    }
    ast->paramlist.push_back(unique_ptr<BaseAST>($3));
    $$ = ast;
  }|
  Exp{
    auto ast = new FuncRParamsAST();
    ast->paramlist.push_back(unique_ptr<BaseAST>($1));
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
  }|
  IDENT '(' FuncRParamList')'{
    auto ast = new FuncCallAST();
    ast->ident = *($1);
    ast->params = unique_ptr<BaseAST>($3);
    $$ = ast;
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
  }|
  LArrays{
    auto ast=new LValAST();
    ast->ident="";
    ast->arraydef = unique_ptr<BaseAST>($1);
    $$=ast;
  }
  ;

LArrays:
  LArrays '[' Exp ']'{
    LArrayAST* ast = nullptr;
    ast = dynamic_cast<LArrayAST*>($1);
    if(ast==nullptr){
      std::cerr << "Exception: " << "dynamic_cast failed"<< std::endl;
    }
    ast->dimon_list.push_back(unique_ptr<BaseAST>($3));
    $$ = ast;
  }|
  LArray{
    $$=$1;
  }
  ;

LArray:
  IDENT '[' Exp ']'{
    auto ast = new LArrayAST();
    ast->ident = *($1);
    ast->dimon_list.push_back(unique_ptr<BaseAST>($3));
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