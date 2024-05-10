
%code requires {
  #include <memory>
  #include <string>
  #include "ast.hpp"
  #include "variable.hpp"
}

%{

#include <iostream>
#include <memory>
#include <string>

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
  BaseAST *ast_val;
}


%token INT VOID FLOAT RETURN
%token <str_val> IDENT
%token <int_val> INT_CONST

%type <ast_val> DefUnit DefUnits
%type <ast_val> FuncDef Block Stmt Sents Sent
%type <ast_val> Assignments Assignment
%type <ast_val> Declaration Declarations Declarationlist DeclarationType
%type <int_val> Expr CalExpr Expr_prio1 Expr_prio2 Number
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
  $$ = new string("int");
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


Sent:
  Assignments ';' {
    auto ast =new SentAST();
    ast->content = unique_ptr<BaseAST>($1);
    $$=ast;
  }|
  RETURN Expr ';' {
    auto ast = new SentAST();
    auto retAst=new ReturnAST();
    retAst->retNum=$2; 
    ast->content=unique_ptr<BaseAST>(retAst);
    $$=ast;
  }
  |Declarationlist ';'{
    auto ast = new SentAST();
    ast->content = unique_ptr<BaseAST>($1);
    $$=ast;
  }
  ;

Expr
  : CalExpr {
    $$ = $1;
  }|
  Expr '>' CalExpr{
    $$=($1>$3);
  }
  |Expr '<' CalExpr{
    $$=($1<$3);
  }
  |Expr '>''=' CalExpr{
    $$=($1>=$4);
  }
  |Expr '<''=' CalExpr{
    $$=($1<=$4);
  }
  |Expr '=''=' CalExpr{
    $$=($1==$4);
  }
  |Expr '!''=' CalExpr{
    $$=($1!=$4);
  }
  ;

CalExpr:
  CalExpr '+' Expr_prio1 {
    $$=$1+$3;
  }
  | CalExpr '-' Expr_prio1 {
    $$=$1-$3;
  }
  | Expr_prio1 {
    $$=$1;
  }
  ;

Expr_prio1:
  Expr_prio1 '*' Expr_prio2 {
    $$=$1*$3;
  }
  | Expr_prio1 '/' Expr_prio2 {
    $$=$1/$3;
  }
  | Expr_prio1 '%' Expr_prio2 {
    $$=$1%$3;
  }
  |Expr_prio2 {
    $$=$1;
  }
  ; 

Expr_prio2:
  '(' Expr ')' {
    $$=$2;
  }
  |Number {
    $$=$1;
  }|IDENT{
    int num=0;
    get_sym_val(sym_head,*($1),&num);
    $$=num;
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
  IDENT '=' Expr {
    auto ast = new DeclarationAST();
    ast->ident = *($1);
    set_sym_val(sym_head,sym_tail,*($1),$3);
    ast->value = $3;
    $$ = ast;
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
  IDENT '=' Expr {
    auto ast=new AssignAST();
    ast->ident=*($1);
    ast->value=$3;
    set_sym_val(sym_head,sym_tail,*($1),$3);
    $$=ast;
  }
  ;

Number
  : INT_CONST {
    $$ = $1;
  }
  ;
%%

void yyerror(std::unique_ptr<BaseAST> &ast,std::string s) {
  cerr << "error: " << s << endl;
}