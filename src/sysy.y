
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

extern sym_node *sym_head, *sym_tail, *sym_cur;

%}


%parse-param {std::unique_ptr<BaseAST> &ast}


%union {
  std::string *str_val;
  int int_val;
  op op_val;
  BaseAST *ast_val;
}


%token INT VOID FLOAT RETURN
%token <str_val> IDENT
%token <int_val> INT_CONST

%type <ast_val> DefUnit DefUnits
%type <ast_val> FuncDef Block Stmt Sents Sent
%type <ast_val> Assignments Assignment
%type <ast_val> Declaration Declarations Declarationlist DeclarationType
%type <ast_val> RelExp EqExp LAndExp LOrExp
%type <ast_val> Exp AddExp MulExp PrimaryExp UnaryExp
%type <op_val> UnaryOp
%type <ast_val> Number
%type <str_val> BasicType 

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
  : DeclarationType IDENT '(' ')' Block {
    auto ast=new FuncDefAST();
    ast->type = unique_ptr<BaseAST>($1);
    ast->ident = *unique_ptr<string>($2);
    ast->block = unique_ptr<BaseAST>($5);
    $$=ast;
  }
  ;

//类型

DeclarationType
  : BasicType {
    auto ast = new DeclarationTypeAST();
    ast->type = unique_ptr<string>($1);
    $$ = ast;
  }
  ;


BasicType: INT {
  $$ = new string("i32");
}|
  VOID {
    $$ = new string("void");
  }|
  FLOAT {
    $$ = new string("float");
  }
  ;

Block
  : '{' Stmt '}' {
    auto ast=new BlockAST();
    ast->stmt = unique_ptr<BaseAST>($2);
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
    auto ast= new SentsAST();
    ast->sents = unique_ptr<BaseAST>($1);
    ast->sent=unique_ptr<BaseAST>($2);
    $$=ast;
  } |
    Sent {
      auto ast = new SentsAST();
      ast->sents = nullptr;
      ast->sent = unique_ptr<BaseAST>($1);
      $$ = ast;
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
    $$ = eqexp;
  }
  | EqExp '!' '=' RelExp {
    auto eqexp = new BinaryExpAST();
    eqexp->exp1 = unique_ptr<BaseAST>($1);
    eqexp->exp2 = unique_ptr<BaseAST>($4);
    eqexp->op2 = op::NE;
    $$ = eqexp;
  }
  | RelExp {
    $$=$1;
  }
  ;


//构造RelExp树
RelExp:
  AddExp '>' AddExp {
    auto relexp = new BinaryExpAST();
    relexp->exp1 = unique_ptr<BaseAST>($1);
    relexp->exp2 = unique_ptr<BaseAST>($3);
    relexp->op2 = op::GT;
    $$ = relexp;
  }
  | AddExp '<' AddExp {
    auto relexp = new BinaryExpAST();
    relexp->exp1 = unique_ptr<BaseAST>($1);
    relexp->exp2 = unique_ptr<BaseAST>($3);
    relexp->op2 = op::LT;
    $$ = relexp;
  }
  | AddExp '>''=' AddExp {
    auto relexp = new BinaryExpAST();
    relexp->exp1 = unique_ptr<BaseAST>($1);
    relexp->exp2 = unique_ptr<BaseAST>($4);
    relexp->op2 = op::GE;
    $$ = relexp;
  }
  | AddExp '<''=' AddExp {
    auto relexp = new BinaryExpAST();
    relexp->exp1 = unique_ptr<BaseAST>($1);
    relexp->exp2 = unique_ptr<BaseAST>($4);
    relexp->op2 = op::LE;
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
    $$ = addexp;
  }
  | AddExp '-' MulExp {
    auto addexp = new BinaryExpAST();
    addexp->exp1 = unique_ptr<BaseAST>($1);
    addexp->exp2 = unique_ptr<BaseAST>($3);
    addexp->op2 = op::SUB;
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
    $$ = mulexp;
  }
  | MulExp '/' UnaryExp {
    auto mulexp = new BinaryExpAST();
    mulexp->exp1 = unique_ptr<BaseAST>($1);
    mulexp->op2 = op::DIV;
    mulexp->exp2 = unique_ptr<BaseAST>($3);
    $$ = mulexp;
  }
  | MulExp '%' UnaryExp {
    auto mulexp = new BinaryExpAST();
    mulexp->exp1 = unique_ptr<BaseAST>($1);
    mulexp->op2 = op::MOD;
    mulexp->exp2 = unique_ptr<BaseAST>($3);
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
  }
  ;

Declarationlist:
  DeclarationType Declarations {
    auto ast = new DeclarationlistAST();
    ast->type = unique_ptr<BaseAST>($1);
    ast->decls = unique_ptr<BaseAST>($2);
    $$ = ast;
  }
  ;

Declarations:
  Declarations ',' Declaration {
    auto ast = new DeclarationsAST();
    ast->decls = unique_ptr<BaseAST>($1);
    ast->decl = unique_ptr<BaseAST>($3);
    $$ = ast;
  }|Declaration {
    auto ast = new DeclarationsAST();
    ast->decls = nullptr;
    ast->decl = unique_ptr<BaseAST>($1);
    $$ = ast;
  }
  ;

Declaration:
  IDENT {
    auto ast = new DeclarationAST();
    ast->ident = *($1);
    set_sym_val(sym_head,sym_tail,*($1),0);
    ast->value = 0;
    $$ = ast;
  }|
  IDENT '=' Exp {
    auto ast = new DeclarationAST();
    ast->ident = *($1);
    //set_sym_val(sym_head,sym_tail,*($1),$3);
    //ast->value = $3;
    ast->value = 0;
    //$$ = ast;
    $$=0;
  }
  ;

Assignments:
  IDENT '=' Assignments {
    auto assignsAst = new AssignsAST();
    auto assignAst= new AssignAST();
    assignsAst->assigns = unique_ptr<BaseAST>($3);
    assignAst->ident = *($1);
    assignAst->value = (dynamic_cast<AssignAST*>((dynamic_cast<AssignsAST*>((assignsAst->assigns).get()))->assign.get()))->value;
    assignsAst->assign = unique_ptr<BaseAST>(assignAst);
    set_sym_val(sym_head,sym_tail,*($1),assignAst->value);
    $$=assignsAst;
  }|
  Assignment {
    auto ast = new AssignsAST();
    ast->assigns=nullptr;
    ast->assign=unique_ptr<BaseAST>($1);
    $$=ast;
  }
  ;

Assignment:
  IDENT '=' Exp {
    auto ast=new AssignAST();
    ast->ident=*($1);
    //ast->value=$3;
    //set_sym_val(sym_head,sym_tail,*($1),$3);
    $$=ast;
  }
  ;

//TODO:构建Number树
Number
  : INT_CONST {
    auto ast = new NumberAST();
    ast->value = $1;
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