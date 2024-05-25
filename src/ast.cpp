#include "ast.hpp"
#include"variable.hpp"
#include"basicblock.hpp"
#include <iostream>
using namespace std;

extern int now;
extern int ifCounter;
extern Val_Table val_table;
extern BasicBlockManager bbm;

void CompUnitAST::dump() {
    start->dump();
}

void DefUnitsAST::dump() {
    if(def_units!=nullptr)
    {
        def_units->dump();

    }
    def_unit->dump();
}

void DefUnitAST::dump() {
    content->dump();
}

void FuncDefAST::dump() {
    std::cout<<"fun @"<<ident<<"():";
    type->dump();
    std::cout<<"{ "<<std::endl;
    std::cout<<"%entry:"<<std::endl;
    //进{}和进basicblock不一样
    bbm.enterBasicBlock();
    block->dump();
    std::cout<<" }";
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
    val_table.EnterBlock();
    if(blockitems)
        blockitems->dump();
    val_table.ExitBlock();
}

void StmtAST::dump() {
    sent->dump();
}

void BlockItemsAST::dump() {
    for(auto &item:itemlist)
    {
        item->dump();
    }
}

void BlockItemAST::dump() {
    //std::cout<<"Sent { ";
    if(!bbm.CheckEndBl())
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
    val_table.Record(ident,std::make_pair(0, false));
    std::cout<<"@"<<val_table.Get_Name(ident)<<" = "<<"alloc ";
    if(type==Btype::BINT) cout<<"i32"<<std::endl;
    if(initval!=nullptr)
    {
        initval->up_calc();
        if(initval->calc_f){
            std::cout<<"store "<<initval->calc()<<", "<<"@"<<val_table.Get_Name(ident)<<std::endl;
        }
        else{
            initval->dump();
            std::cout<<"store "<<"%"<<now-1<<", "<<"@"<<val_table.Get_Name(ident)<<std::endl;
        }
    }
    std::cout<<std::endl;
}

//ifelse块的打印
void IfElseAST::dump(){
    exp->up_calc();
    ++ifCounter;
    //给br语句用的then的lable,ifCounter是避免重复命名用的
    std::string thenLable="%then"+to_string(ifCounter);
    std::string elseLable="%else"+to_string(ifCounter);
    std::string mergeLable="%merge"+to_string(ifCounter);
    if(!else_part) elseLable=mergeLable; 
    //打印br语句
    if(exp->calc_f)
        std::cout<<"br "<<exp->calc()<<", "<<thenLable<<", "<<elseLable<<std::endl;
    else{
        exp->dump();
        std::cout<<"br "<<"%"<<now-1<<", "<<thenLable<<", "<<elseLable<<std::endl;
    }
    std::cout<<std::endl;
    //打印thenpart
    std::cout<<thenLable<<":"<<std::endl;
    bbm.enterBasicBlock();
    then_part->dump();
    if(!bbm.CheckEndBl()){
        std::cout<<"jump "<<mergeLable<<std::endl;
        bbm.generateRetOrJump();
    }

    //打印elsepart
    if(else_part){
        std::cout<<elseLable<<":"<<std::endl;
        bbm.enterBasicBlock();
        else_part->dump();
        if(!bbm.CheckEndBl()){
            std::cout<<"jump "<<mergeLable<<std::endl;
            bbm.generateRetOrJump();
        }
    }

    //打印merge部分
    std::cout<<mergeLable<<":"<<std::endl;
    bbm.enterBasicBlock();
}
void AssignsAST::dump() {

}

void AssignAST::dump() {
    if(val_table.get(ident).second){
        cerr<<"this is a const,can't be assigned"<<std::endl;
    }else{
        exp->up_calc();
        if(exp->calc_f){
            std::cout<<"store "<<exp->calc()<<", "<<"@"<<val_table.Get_Name(ident)<<std::endl;
        }
        else{
            exp->dump();
            std::cout<<"store "<<"%"<<now-1<<", "<<"@"<<val_table.Get_Name(ident)<<std::endl;
        }
    }
}

void ReturnAST::dump() {
    //此处需要更新
    if(retNum)
    {
        retNum->up_calc();
        if(retNum->calc_f)
            std::cout<<"ret "<<retNum->calc()<<std::endl;
        else{
           retNum->dump();
            std::cout<<"ret "<<"%"<<now-1<<std::endl;
        }
    }
    else
        std::cout<<"ret"<<std::endl;
    bbm.generateRetOrJump();
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
        std::cout<<"%"<<now<<"= "<<"add 0, "<<val_table.get(ident).first<<std::endl;
    else
        std::cout<<"%"<<now<<"= "<<"load "<<"@"<<val_table.Get_Name(ident)<<std::endl;
    ++now;
}

void NumberAST::dump() {
    std::cout<<"%"<<now<<"="<<"add 0, "<<value<<std::endl;
    ++now;
}

void OptionExpAST::dump() {
    if(exp){
        exp->up_calc();
        if(!exp->calc_f)
            exp->dump();
    }
}