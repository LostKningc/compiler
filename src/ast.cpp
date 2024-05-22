#include "ast.hpp"
#include"variable.hpp"
#include <iostream>
using namespace std;
extern int now;
extern std::unordered_map<std::string,std::pair<int,bool>> val_table;
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
    switch(type){
        case Btype::BINT:
            std::cout<<"i32 ";
            break;
        case Btype::BVOID:
            std::cout<<"void ";
            break;
        case Btype::BFLOAT:
            std::cout<<"float ";
            break;
        default:
            break;
    }
}

void BlockAST::dump() {
    std::cout<<"{ ";
    stmt->dump();
    std::cout<<" }";
}

void StmtAST::dump() {
    std::cout<<"\%entry:";
    std::cout<<std::endl;
    sents->dump();
}

void SentsAST::dump() {
    for(auto &sent:sents)
    {
        sent->dump();
    }
}

void SentAST::dump() {
    //std::cout<<"Sent { ";
    content->dump();
    //std::cout<<" }";
}

//TODO:完成符号表后
void ConstDeclListAST::dump(){
    ConstDefsAST* defs=dynamic_cast<ConstDefsAST*>(constdefs.get());
    if(defs==nullptr){
        std::cerr << "Exception: " << "dynamic_cast failed"<< std::endl;
    }
    defs->type=this->type;
    constdefs->dump();
}

void VarDeclListAST::dump(){
    vardefs->dump();
}
//TODO:完成符号表后
void ConstDefsAST::dump(){
    for(auto &constdef:constdefs)
    {
        ConstDefAST* def=dynamic_cast<ConstDefAST*>(constdef.get());
        if(def==nullptr){
            std::cerr << "Exception: " << "dynamic_cast failed"<< std::endl;
        }
        def->type=this->type;
        constdef->dump();
    }
}

void VarDefsAST::dump(){
    for(auto &vardef:vardefs){
        vardef->dump();
    }
}
//TODO:完成符号表后
void ConstDefAST::dump(){
    initval->up_calc();
    calc();
}

void VarDefAST::dump(){
    //std::cout<<"VarDef { ";
    std::cout<<"@"<<ident<<" = "<<"alloc ";
    if(type==Btype::BINT) cout<<"i32"<<std::endl;
    //std::cout<<","<<ident<<",";
    if(initval!=nullptr)
    {
        initval->up_calc();
        if(initval->calc_f){
            std::cout<<"store "<<initval->calc()<<", "<<"@"<<ident<<std::endl;
        }
        else{
            initval->dump();
            std::cout<<"store "<<"%"<<now-1<<", "<<"@"<<ident<<std::endl;
        }
    }
    std::cout<<std::endl;
    //std::cout<<" }";
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
    if(val_table[ident].second){
        cerr<<"this is a const,can't be assigned"<<std::endl;
    }else{
        exp->up_calc();
        if(exp->calc_f){
            std::cout<<"store "<<exp->calc()<<", "<<"@"<<ident<<std::endl;
        }
        else{
            exp->dump();
            std::cout<<"store "<<"%"<<now-1<<", "<<"@"<<ident<<std::endl;
        }
    }
}

void ReturnAST::dump() {
    //此处需要更新
    retNum->up_calc();
    if(retNum->calc_f)
        std::cout<<"ret "<<retNum->calc()<<std::endl;
    else{
        retNum->dump();
        std::cout<<"ret "<<"%"<<now-1<<std::endl;
    }
}

void ConstExpAST::dump() {
    exp->dump();
}

//TODO:解决了么
void BinaryExpAST::dump() {
    int now1=0,now2=0;
    if(!exp1->calc_f){
        exp1->dump();
        now1=now-1;
    }

    if(!exp2->calc_f){
        exp2->dump();
        now2=now-1;
    }
    switch(op2){
        case op::ADD:
            std::cout<<"%"<<now<<"= "<<"add ";
            if(exp1->calc_f)
                std::cout<<exp1->calc();
            else
                std::cout<<"%"<<now1;
            std::cout<<", ";
            if(exp2->calc_f)
                std::cout<<exp2->calc();
            else
                std::cout<<"%"<<now2;
            std::cout<<std::endl;
            ++now;
            break;
        case op::SUB:
            if(exp1->calc_f)
                std::cout<<"%"<<now<<"= "<<"sub "<<exp1->calc();
            else
                std::cout<<"%"<<now<<"= "<<"sub "<<"%"<<now1;
            cout << ", ";
            if(exp2->calc_f)
                std::cout<<exp2->calc();
            else
                std::cout<<"%"<<now2;
            std::cout<<std::endl;
            ++now;
            break;
        case op::MUL:
            if(exp1->calc_f)
                std::cout<<"%"<<now<<"= "<<"mul "<<exp1->calc();
            else
                std::cout<<"%"<<now<<"= "<<"mul "<<"%"<<now1;
            cout << ", ";
            if(exp2->calc_f)
                std::cout<<exp2->calc();
            else
                std::cout<<"%"<<now2;
            std::cout<<std::endl;
            ++now;
            break;
        case op::DIV:
            if(exp1->calc_f)
                std::cout<<"%"<<now<<"= "<<"div "<<exp1->calc();
            else
                std::cout<<"%"<<now<<"= "<<"div "<<"%"<<now1;
            cout << ", ";
            if(exp2->calc_f)
                std::cout<<exp2->calc();
            else
                std::cout<<"%"<<now2;
            std::cout<<std::endl;
            ++now;
            break;
        case op::MOD:
            if(exp1->calc_f)
                std::cout<<"%"<<now<<"= "<<"mod "<<exp1->calc();
            else
                std::cout<<"%"<<now<<"= "<<"mod "<<"%"<<now1;
            cout << ", ";
            if(exp2->calc_f)
                std::cout<<exp2->calc();
            else
                std::cout<<"%"<<now2;
            std::cout<<std::endl;
            ++now;
            break;
        case op::GT:
            if(exp1->calc_f)
                std::cout<<"%"<<now<<"= "<<"gt "<<exp1->calc();
            else
                std::cout<<"%"<<now<<"= "<<"gt "<<"%"<<now1;
            cout << ", ";
            if(exp2->calc_f)
                std::cout<<exp2->calc();
            else
                std::cout<<"%"<<now2;
            std::cout<<std::endl;
            ++now;
            break;
        case op::LT:
            if(exp1->calc_f)
                std::cout<<"%"<<now<<"= "<<"lt "<<exp1->calc();
            else
                std::cout<<"%"<<now<<"= "<<"lt "<<"%"<<now1;
            cout << ", ";
            if(exp2->calc_f)
                std::cout<<exp2->calc();
            else
                std::cout<<"%"<<now2;
            std::cout<<std::endl;
            ++now;
            break;
        case op::GE:
            if(exp1->calc_f)
                std::cout<<"%"<<now<<"= "<<"ge "<<exp1->calc();
            else
                std::cout<<"%"<<now<<"= "<<"ge "<<"%"<<now1;
            cout << ", ";
            if(exp2->calc_f)
                std::cout<<exp2->calc();
            else
                std::cout<<"%"<<now2;
            std::cout<<std::endl;
            ++now;
            break;
        case op::LE:
            if(exp1->calc_f)
                std::cout<<"%"<<now<<"= "<<"le "<<exp1->calc();
            else
                std::cout<<"%"<<now<<"= "<<"le "<<"%"<<now1;
            cout << ", ";
            if(exp2->calc_f)
                std::cout<<exp2->calc();
            else
                std::cout<<"%"<<now2;
            std::cout<<std::endl;
            ++now;
            break;
        case op::EQ:
            if(exp1->calc_f)
                std::cout<<"%"<<now<<"= "<<"eq "<<exp1->calc();
            else
                std::cout<<"%"<<now<<"= "<<"eq "<<"%"<<now1;
            cout << ", ";
            if(exp2->calc_f)
                std::cout<<exp2->calc();
            else
                std::cout<<"%"<<now2;
            std::cout<<std::endl;
            ++now;
            break;
        case op::NE:
            if(exp1->calc_f)
                std::cout<<"%"<<now<<"= "<<"ne "<<exp1->calc();
            else
                std::cout<<"%"<<now<<"= "<<"ne "<<"%"<<now1;
            cout << ", ";
            if(exp2->calc_f)
                std::cout<<exp2->calc();
            else
                std::cout<<"%"<<now2;
            std::cout<<std::endl;
            ++now;
            break;
        case op::AND:
            if(exp2->calc_f)
                std::cout<<"%"<<now<<"= "<<"eq "<<0<<", "<<exp2->calc()<<std::endl;
            else
                std::cout<<"%"<<now<<"= "<<"eq "<<0<<", "<<"%"<<now2<<std::endl;
            now2=now++;
            std::cout<<"%"<<now<<"= "<<"eq "<<0<<",%"<<now2<<std::endl;
            now2=now++;
            if(exp1->calc_f)
                std::cout<<"%"<<now<<"= "<<"eq "<<0<<", "<<exp1->calc()<<std::endl;
            else
                std::cout<<"%"<<now<<"= "<<"eq "<<0<<", "<<"%"<<now1<<std::endl;
            now1=now++;
            std::cout<<"%"<<now<<"= "<<"eq "<<0<<",%"<<now1<<std::endl;
            now1=now++;
            std::cout<<"%"<<now<<"= "<<"and "<<"%"<<now1<<",%"<<now2<<std::endl;
            ++now;
            break;
        case op::OR:
            if(exp2->calc_f)
                std::cout<<"%"<<now<<"= "<<"eq "<<0<<", "<<exp2->calc()<<std::endl;
            else
                std::cout<<"%"<<now<<"= "<<"eq "<<0<<",%"<<now2<<std::endl;
            now2=now++;
            std::cout<<"%"<<now<<"= "<<"eq "<<0<<",%"<<now2<<std::endl;
            now2=now++;
            if(exp1->calc_f)
                std::cout<<"%"<<now<<"= "<<"eq "<<0<<", "<<exp1->calc()<<std::endl;
            else
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

void LValAST::dump() {

    if(calc_f)
        std::cout<<"%"<<now<<"= "<<"add 0, "<<val_table[ident].first<<std::endl;
    else
        std::cout<<"%"<<now<<"= "<<"load "<<"@"<<ident<<std::endl;
    ++now;
}

void NumberAST::dump() {
    std::cout<<"%"<<now<<"="<<"add 0, "<<value<<std::endl;
    ++now;
}