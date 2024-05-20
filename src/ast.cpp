#include "ast.hpp"
#include <iostream>

extern int now;
void CompUnitAST::dump() {
    //std::cout<<"Compunit { \n";
    start->dump();
    // std::cout<<" \n";
    // std::cout<<" }";
    // std::cout<<std::endl;
}

void DefUnitsAST::dump() {
    if(def_units!=nullptr)
    {
        def_units->dump();
        //std::cout<<"\n";
    }
    def_unit->dump();
}

void DefUnitAST::dump() {
    // std::cout<<"DefUnit { ";
    content->dump();
    // std::cout<<" }";
}

void FuncDefAST::dump() {
    //std::cout<<"FuncDef { ";
    std::cout<<"fun @"<<ident<<"():";
    type->dump();
    //std::cout<<","<<ident<<",";
    block->dump();
    //std::cout<<" }";
}

void DeclarationTypeAST::dump() {
    //std::cout<<"DeclarationType { ";
    std::cout<<*type<<" ";
    //std::cout<<"}";
}

void BlockAST::dump() {
    std::cout<<"{ ";
    stmt->dump();
    std::cout<<" }";
}

void StmtAST::dump() {
    std::cout<<"\%entry:";

    sents->dump();
}

void SentsAST::dump() {
    if(sents!=nullptr)
    {
        sents->dump();
        // std::cout<<"\n";
        std::cout<<" ";
    }
    sent->dump();
}

void SentAST::dump() {
    //std::cout<<"Sent { ";
    content->dump();
    //std::cout<<" }";
}

void DeclarationlistAST::dump() {
    // std::cout<<"Declarationlist { ";
    // type->dump();
    // std::cout<<", Declarations { ";
    // decls->dump();
    // std::cout<<" }";
    // std::cout<<" }";
}

void DeclarationsAST::dump() {
    // if(decls!=nullptr)
    //     std::cout<<",";
    // decl->dump();
}

void DeclarationAST::dump() {
    // std::cout<<"Declaration { ";
    // std::cout<<ident<<"("<<value<<")";
    // std::cout<<" }";
}


void AssignsAST::dump() {
    // if(assigns!=nullptr)
    // {
    //     assigns->dump();
    //     std::cout<<",";
    // }
    // assign->dump();
}

void AssignAST::dump() {
    // std::cout<<"Assign { ";
    // std::cout<<ident<<"("<<value<<")";
    // std::cout<<" }";
}

void ReturnAST::dump() {
    retNum->dump();
    std::cout<<"ret "<<"%"<<now-1<<std::endl;
}

//TODO:解决了么
void BinaryExpAST::dump() {
    exp1->dump();
    int now1=now-1;
    exp2->dump();
    int now2=now-1;
    switch(op2){
        case op::ADD:
            std::cout<<"%"<<now<<"= "<<"add "<<"%"<<now1<<",%"<<now2<<std::endl;
            ++now;
            break;
        case op::SUB:
            std::cout<<"%"<<now<<"= "<<"sub "<<"%"<<now1<<",%"<<now2<<std::endl;
            ++now;
            break;
        case op::MUL:
            std::cout<<"%"<<now<<"= "<<"mul "<<"%"<<now1<<",%"<<now2<<std::endl;
            ++now;
            break;
        case op::DIV:
            std::cout<<"%"<<now<<"= "<<"div "<<"%"<<now1<<",%"<<now2<<std::endl;
            ++now;
            break;
        case op::MOD:
            std::cout<<"%"<<now<<"= "<<"mod "<<"%"<<now1<<",%"<<now2<<std::endl;
            ++now;
            break;
        case op::GT:
            std::cout<<"%"<<now<<"= "<<"gt "<<"%"<<now1<<",%"<<now2<<std::endl;
            ++now;
            break;
        case op::LT:
            std::cout<<"%"<<now<<"= "<<"lt "<<"%"<<now1<<",%"<<now2<<std::endl;
            ++now;
            break;
        case op::GE:
            std::cout<<"%"<<now<<"= "<<"ge "<<"%"<<now1<<",%"<<now2<<std::endl;
            ++now;
            break;
        case op::LE:
            std::cout<<"%"<<now<<"= "<<"le "<<"%"<<now1<<",%"<<now2<<std::endl;
            ++now;
            break;
        case op::EQ:
            std::cout<<"%"<<now<<"= "<<"eq "<<"%"<<now1<<",%"<<now2<<std::endl;
            ++now;
            break;
        case op::NE:
            std::cout<<"%"<<now<<"= "<<"ne "<<"%"<<now1<<",%"<<now2<<std::endl;
            ++now;
            break;
        case op::AND:
            std::cout<<"%"<<now<<"= "<<"eq "<<0<<",%"<<now2<<std::endl;
            now2=now++;
            std::cout<<"%"<<now<<"= "<<"eq "<<0<<",%"<<now2<<std::endl;
            now2=now++;
            std::cout<<"%"<<now<<"= "<<"eq "<<0<<",%"<<now1<<std::endl;
            now1=now++;
            std::cout<<"%"<<now<<"= "<<"eq "<<0<<",%"<<now1<<std::endl;
            now1=now++;
            std::cout<<"%"<<now<<"= "<<"and "<<"%"<<now1<<",%"<<now2<<std::endl;
            ++now;
            break;
        case op::OR:
            std::cout<<"%"<<now<<"= "<<"eq "<<0<<",%"<<now2<<std::endl;
            now2=now++;
            std::cout<<"%"<<now<<"= "<<"eq "<<0<<",%"<<now2<<std::endl;
            now2=now++;
            std::cout<<"%"<<now<<"= "<<"eq "<<0<<",%"<<now1<<std::endl;
            now1=now++;
            std::cout<<"%"<<now<<"= "<<"eq "<<0<<",%"<<now1<<std::endl;
            now1=now++;
            std::cout<<"%"<<now<<"= "<<"or "<<"%"<<now1<<",%"<<now2<<std::endl;
            ++now;
            break;
        default:
            //后面看清况再说
            break;
    }
}

//TODO:解决了么？
void UnaryExpAST::dump() {
    exp1->dump();
    if(op1==op::SUB){
        std::cout<<"%"<<now<<"= "<<"sub 0,"<<"%"<<now-1<<std::endl;
        ++now;
    }
    else if(op1==op::NOT){
        std::cout<<"%"<<now<<"= "<<"eq "<<"%"<<now-1<<",0"<<std::endl;
        ++now;
    }
}


void NumberAST::dump() {
    std::cout<<"%"<<now<<"="<<"add 0, "<<value<<std::endl;
    ++now;
}