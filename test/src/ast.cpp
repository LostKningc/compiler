#include "ast.hpp"
#include <iostream>
void CompUnitAST::dump() {
    std::cout<<"Compunit { \n";
    start->dump();
    std::cout<<" \n";
    std::cout<<" }";
    std::cout<<std::endl;
}

void DefUnitsAST::dump() {
    if(def_units!=nullptr)
    {
        def_units->dump();
        std::cout<<"\n";
    }
    def_unit->dump();
}

void DefUnitAST::dump() {
    // std::cout<<"DefUnit { ";
    content->dump();
    // std::cout<<" }";
}

void FuncDefAST::dump() {
    std::cout<<"FuncDef { ";
    type->dump();
    std::cout<<","<<ident<<",";
    block->dump();
    std::cout<<" }";
}

void DeclarationTypeAST::dump() {
    std::cout<<"DeclarationType { ";
    std::cout<<*type<<" ";
    std::cout<<"}";
}

void BlockAST::dump() {
    std::cout<<"Block { ";
    stmt->dump();
    std::cout<<" }";
}

void StmtAST::dump() {
    std::cout<<"Stmt { ";
    sents->dump();
    std::cout<<" }";
}

void SentsAST::dump() {
    if(sents!=nullptr)
    {
        sents->dump();
        std::cout<<",";
    }
    sent->dump();
}

void SentAST::dump() {
    std::cout<<"Sent { ";
    content->dump();
    std::cout<<" }";
}

void DeclarationlistAST::dump() {
    std::cout<<"Declarationlist { ";
    type->dump();
    std::cout<<", Declarations { ";
    decls->dump();
    std::cout<<" }";
    std::cout<<" }";
}

void DeclarationsAST::dump() {
    if(decls!=nullptr)
        std::cout<<",";
    decl->dump();
}

void DeclarationAST::dump() {
    std::cout<<"Declaration { ";
    std::cout<<ident<<"("<<value<<")";
    std::cout<<" }";
}


void AssignsAST::dump() {
    if(assigns!=nullptr)
    {
        assigns->dump();
        std::cout<<",";
    }
    assign->dump();
}

void AssignAST::dump() {
    std::cout<<"Assign { ";
    std::cout<<ident<<"("<<value<<")";
    std::cout<<" }";
}

void ReturnAST::dump() {
    std::cout<<"Return { "<<retNum<<" }";
}

