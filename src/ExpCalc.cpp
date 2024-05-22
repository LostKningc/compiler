#include "ast.hpp"
#include <iostream>
#include "variable.hpp"

extern int now;
extern std::unordered_map<std::string,std::pair<int,bool>> val_table;

int ConstDefAST::calc(){
    val_table[ident]=std::pair<int,bool>(initval->calc(),1);
    return val_table[ident].first;
}

int ConstExpAST::calc(){
    return exp->calc();
}

int BinaryExpAST::calc(){
    int tmp1=exp1->calc();
    int tmp2=exp2->calc();
    switch(op2){
        case op::ADD:
            return tmp1+tmp2;
        case op::SUB:
            return tmp1-tmp2;
        case op::MUL:
            return tmp1*tmp2;
        case op::DIV:
            return tmp1/tmp2;
        case op::MOD:
            return tmp1%tmp2;
        case op::GT:
            return tmp1>tmp2;
        case op::LT:
            return tmp1<tmp2;
        case op::GE:
            return tmp1>=tmp2;
        case op::LE:
            return tmp1<=tmp2;
        case op::EQ:
            return tmp1==tmp2;
        case op::NE:
            return tmp1!=tmp2;
        case op::AND:
            return tmp1&&tmp2;
        case op::OR:
            return tmp1||tmp2;
        default:
            //后面看清况再说
            std::cout<<"not defiend calc"<<std::endl;
            return -1;
            break;
    }
}

//直接计算
int UnaryExpAST::calc(){
    int tmp=exp1->calc();
    if(op1==op::SUB){
        return -tmp;
    }
    else if(op1==op::NOT){
        return !tmp;
    }
    return tmp;
}

//只有常量时才能调用
int LValAST::calc(){
    return val_table[ident].first;
}

//更新计算符号位
void ConstExpAST::up_calc(){
    exp->up_calc();
    calc_f=exp->calc_f;
}
void BinaryExpAST::up_calc(){
    exp1->up_calc();
    exp2->up_calc();
    calc_f=exp1->calc_f&&exp2->calc_f;
}
void UnaryExpAST::up_calc(){
    exp1->up_calc();
    calc_f=exp1->calc_f;
}
void NumberAST::up_calc(){
    calc_f=true;
}
void LValAST::up_calc(){
    calc_f=val_table[ident].second;
}
