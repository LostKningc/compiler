#include "ast.hpp"
#include"variable.hpp"
#include"basicblock.hpp"
#include"funcmanager.hpp"
#include <iostream>
using namespace std;

extern int now;
extern Val_Table val_table;
extern BasicBlockManager bbm;
extern FuncManager funcm;
extern ArrayManager arraym;

void CompUnitAST::dump() {
    start->dump();
}

void DefUnitsAST::dump() {
    for(auto &unit:unit_list)
    {   
        if(unit!=nullptr)
            unit->dump();
    }
}

void DefUnitAST::dump() {
    content->dump();
}

void FuncDefAST::dump() {
    std::cout<<"fun @"<<ident<<"(";
    if(params)
        params->dump();
    std::cout<<")";
    Btype btype=dynamic_cast<DeclarationTypeAST*>(type.get())->type;
    if(btype!=Btype::BVOID)
    {
        std::cout<<" : ";
        printType(btype);
    }
    funcm.add_Func(ident,btype);
    std::cout<<"{ "<<std::endl;
    bbm.CreateBasicBlock("entry");
    block->dump();
    if(btype==Btype::BVOID){
        std::cout<<"ret"<<std::endl;
        bbm.generateRetOrJump();
    }
    std::cout<<" }"<<std::endl;
}

void FuncFParamsAST::dump() {
    auto it=paramlist.begin();
    for(;it!=paramlist.end();it++)
    {   
        if(it!=paramlist.begin())
            std::cout<<", ";
        (*it)->dump();
    }
}

void FuncFParamAST::dump() {
    if(arraydef==nullptr)
        variable_dump();
    else
        array_dump();
}

void FuncFParamAST::variable_dump() {
    std::cout<<"@"<<ident<<": ";
    printType(type);
    val_table.add_Param(ident);
}

void FuncFParamAST::array_dump() {
    arraym.InitializeManager(type);
    arraym.addParamArray(arraydef);
    std::cout<<"@"<<arraym.get_name()<<": *"<<arraym.generateArrayType(0);
    arraym.KillManager();
}

void FuncCallAST::dump() {
    int num=0;
    if(params){
        funcm.startCall();
        FuncRParamsAST* rparams=dynamic_cast<FuncRParamsAST*>(params.get());
        num=rparams->paramlist.size();
        params->dump();
        funcm.endCall();
    }    
    if(funcm.get_Functype(ident)==Btype::BVOID)
        std::cout<<"call @"<<ident<<"(";
    else{
        std::cout<<"%"<<now<<"= "<<"call @"<<ident<<"(";
        ++now;
    }
    if(params)
        funcm.PopStack(num);
    std::cout<<")"<<std::endl;
}

void FuncRParamsAST::dump() {
    for(auto &para:paramlist)
    {   
        para->up_calc();
        if(para->calc_f){
            std::cout<<"%"<<now<<"= "<<"add 0, "<<para->calc()<<std::endl;
            now++;
        }
        else
            para->dump();
        funcm.EnterStack("%"+to_string(now-1));
    }
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
    val_table.params2block();
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

void ConstInitValsAST::dump(){
    constexp->dump();
}

void BlockItemAST::dump() {
    if(!bbm.CheckEndBl())
        content->dump();
    // else{
    //     //debug info
    //     std::cout<<"------好像不对呢------"<<std::endl;
    //     content->dump();
    //     std::cout<<"------------------------"<<std::endl;
    // }
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
    if(arraydef==nullptr){
        initval->up_calc();
        calc();
    }else{
        arraym.InitializeManager(type,true);
        arraym.addArray(arraydef);
        std::vector<std::string> arrayinitval=arraym.ConstParseArray(initval,0);

        if(val_table.get_field_idx()==0){
            std::cout<<"global ";
            std::cout<<arraym.generateAllocStatement(val_table.Get_Name(arraym.get_name()))<<", ";
            arraym.printArray(arrayinitval);
        }else{
            std::cout<<arraym.generateAllocStatement(val_table.Get_Name(arraym.get_name()))<<std::endl;
            std::cout<<"store ";
            arraym.printArray(arrayinitval);
            std::cout<<", "<<"@"<<val_table.Get_Name(arraym.get_name());
        }
        std::cout<<std::endl;     
        arraym.KillManager();  
    }
} 

void VarDefAST::dump(){
    if(arraydef==nullptr)
        variable_dump();
    else
        array_dump();
}

void VarDefAST::variable_dump(){
     val_table.Record(ident,std::make_pair(0, false));

    if(val_table.get_field_idx()!=0){
        std::cout<<"@"<<val_table.Get_Name(ident)<<" = "<<"alloc ";
        printType(type);
        std::cout<<std::endl;
        if(initval!=nullptr){
            initval->up_calc();
            if(initval->calc_f){
                std::cout<<"store "<<initval->calc()<<", "<<"@"<<val_table.Get_Name(ident)<<std::endl;
            }
            else{
                initval->dump();
                std::cout<<"store "<<"%"<<now-1<<", "<<"@"<<val_table.Get_Name(ident)<<std::endl;
            }
        }
    }else{
        std::cout<<"global "<<"@"<<val_table.Get_Name(ident)<<" = "<<"alloc ";
        printType(type);
        std::cout<<", ";
        if(initval!=nullptr){
            initval->up_calc();
            if(initval->calc_f){
                std::cout<<initval->calc()<<std::endl;
            }
            else{
                initval->dump();
                std::cout<<"%"<<now-1<<std::endl;
            }
        }else{
            std::cout<<"zeroinit";
        }
    }
    std::cout<<std::endl;
}

void VarDefAST::array_dump(){
    arraym.InitializeManager(type);
    arraym.addArray(arraydef);
    InitValsAST* initvalue_ast=dynamic_cast<InitValsAST*>(initval.get());
    std::vector<std::string> arrayinitval;
    
    if(val_table.get_field_idx()==0){
        if(!initvalue_ast->array_val_list.empty())
            arrayinitval=arraym.VarParseArray(initval,0);
        std::cout<<"global ";
        std::cout<<arraym.generateAllocStatement(val_table.Get_Name(arraym.get_name()))<<", ";
        if(initvalue_ast->array_val_list.empty())
            std::cout<<"zeroinit";
        else
            arraym.printArray(arrayinitval);
    }else{
        if(!initvalue_ast->array_val_list.empty())
            arrayinitval=arraym.VarParseArray(initval,0);
        std::cout<<arraym.generateAllocStatement(val_table.Get_Name(arraym.get_name()))<<std::endl;
        std::cout<<"store ";
        if(initvalue_ast->array_val_list.empty())
            std::cout<<"zeroinit";
        else
            arraym.printArray(arrayinitval);
        std::cout<<", "<<"@"<<val_table.Get_Name(arraym.get_name());
    }
    std::cout<<std::endl;
    arraym.KillManager();
}

//ifelse块的打印
void IfElseAST::dump(){
    exp->up_calc();
    ++bbm.ifCounter;
    if(bbm.CheckEndBl()) return;
    //给br语句用的then的lable,ifCounter是避免重复命名用的
    std::string thenLable="then"+to_string(bbm.ifCounter);
    std::string elseLable="else"+to_string(bbm.ifCounter);
    std::string mergeLable="merge"+to_string(bbm.ifCounter);
    if(!else_part) elseLable=mergeLable; 
    //打印br语句
    if(exp->calc_f)
        bbm.BlockBranch(exp->calc(),thenLable,elseLable);
    else{
        exp->dump();
        bbm.BlockBranch("%"+to_string(now-1),thenLable,elseLable);
    }
    
    std::cout<<std::endl;
    //打印thenpart
    bbm.CreateBasicBlock(thenLable);
    then_part->dump();
    bbm.BlockJump(mergeLable);

    //打印elsepart
    if(else_part){
        bbm.CreateBasicBlock(elseLable);
        else_part->dump();
        bbm.BlockJump(mergeLable); 
    }

    //打印merge部分
    bbm.CreateBasicBlock(mergeLable);

}

void WhileAST::dump(){
    exp->up_calc();
    ++bbm.whileCounter;
    if(bbm.CheckEndBl()) return;
    //给br语句用的then的lable,ifCounter是避免重复命名用的
    std::string whileLable="while_entry"+to_string(bbm.whileCounter);
    std::string bodyLable="while_body"+to_string(bbm.whileCounter);
    std::string mergeLable="while_end"+to_string(bbm.whileCounter);
    //打印br语句
    bbm.BlockJump(whileLable);
    bbm.CreateBasicBlock(whileLable);
    bbm.while_stack.push_back(bbm.whileCounter);
    if(exp->calc_f)
        bbm.BlockBranch(exp->calc(),bodyLable,mergeLable);
    else{
        exp->dump();
        bbm.BlockBranch("%"+to_string(now-1),bodyLable,mergeLable);
    }
    std::cout<<std::endl;
    //打印body部分
    bbm.CreateBasicBlock(bodyLable);
    body->dump();
    bbm.BlockJump(whileLable);
    //打印merge部分
    bbm.CreateBasicBlock(mergeLable);
    bbm.while_stack.pop_back();
}

void BreakAST::dump(){
    bbm.BlockJump("while_end"+to_string(bbm.while_stack.back()));
}

void ContinueAST::dump(){
    bbm.BlockJump("while_entry"+to_string(bbm.while_stack.back()));
}

void AssignsAST::dump() {

}

void::AssignAST::dump() {
    if(arraydef)
        array_dump();
    else
        variable_dump();
}

void AssignAST::variable_dump() {
    if(val_table.get(ident).const_var){
        cerr<<"this is a const,can't be assigned"<<std::endl;
    }else{
        std::string val_name;
        if(val_table.get(ident).value==0)
            val_name="@"+val_table.Get_Name(ident);
        else if(val_table.get(ident).value==1){
            //TODO:这里后面要改,目前只有int，先这样了
            std::cout<<"%"<<ident<<"= "<<"alloc "<<"i32"<<std::endl;
            std::cout<<"store "<<"@"<<val_table.Get_Name(ident)<<", "<<"%"<<ident<<std::endl;
            //std::cerr << val_table.Get_Name(ident) <<endl;
            val_name="%"+ident;
            val_table.valuePlus1(ident);
        }
        else{
            val_name="%"+ident;
        }
        exp->up_calc();
        if(exp->calc_f){
            std::cout<<"store "<<exp->calc()<<", "<<val_name<<std::endl;
        }
        else{
            exp->dump();
            std::cout<<"store "<<"%"<<now-1<<", "<<val_name<<std::endl;
        }
    }
}

void AssignAST::array_dump(){
    arraym.InitializeManager(Btype::BINT);
    arraym.addLArray(arraydef);
    if(val_table.get(arraym.get_name()).array_const){
        cerr<<"this is a const,can't be assigned"<<std::endl;
    }
    else{
        std::string val_name;
        if(val_table.get(arraym.get_name()).value==0){
            arraym.LArrayLoad();
            val_name=arraym.get_current_ptr();
        }
        else if(val_table.get(arraym.get_name()).value==1){
            
            arraym.ParamArrayLoad();
            val_name=arraym.get_current_ptr();
        }
        exp->up_calc();
        if(exp->calc_f){
            std::cout<<"store "<<exp->calc()<<", "<<val_name<<std::endl;
        }
        else{
            exp->dump();
            std::cout<<"store "<<"%"<<now-1<<", "<<val_name<<std::endl;
        }
    }
    arraym.KillManager();
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


void ExpAST::dump() {
    exp->dump();
}

void ConstExpAST::dump() {
    exp->dump();
}

//TODO:解决了么
void BinaryExpAST::dump() {
    std::string lable1="";
    std::string lable2="";
    int orCounter=0;
    int andCounter=0;
    int res1=1;
    int now1=0,now2=0;
    if((!exp1->calc_f)&&(op2!=op::AND&&op2!=op::OR)){
        exp1->dump();
        now1=now-1;
    }

    if((!exp2->calc_f)&&(op2!=op::AND&&op2!=op::OR)){
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
            if(exp1->calc_f){
                res1=exp1->calc();
                std::cout<<"%"<<now<<"= "<<"eq "<<0<<", "<<res1<<std::endl; 
                now1=now++;
                std::cout<<"%"<<now<<"= "<<"eq "<<0<<",%"<<now1<<std::endl;
                if(!res1){
                    now++;
                    return;
                }
                now1=now++;            
            }
            else{
                exp1->dump();
                now1=now-1;

                bbm.AndBranch();
                //短路求值用这个做标记
                andCounter=bbm.andCounter;
                lable1="and1part"+to_string(andCounter);
                lable2="and2part"+to_string(andCounter);
                std::cout<<"%"<<now<<"= "<<"eq "<<0<<", "<<"%"<<now1<<std::endl;
                now1=now++;
                std::cout<<"%"<<now<<"= "<<"eq "<<0<<", "<<"%"<<now1<<std::endl;
                now1=now++;
                std::cout<<"%"<<"and"<<andCounter<<" = "<<"alloc i32"<<std::endl;
                std::cout<<"store"<<" %"<<now1<<", "<<"%"<<"and"<<andCounter<<std::endl;
                bbm.BlockBranch("%"+to_string(now1),lable1,lable2);
                bbm.CreateBasicBlock(lable1);
            }
            if(exp2->calc_f)
                std::cout<<"%"<<now<<"= "<<"eq "<<0<<", "<<exp2->calc()<<std::endl;
            else{
                exp2->dump();
                now2=now-1;
                std::cout<<"%"<<now<<"= "<<"eq "<<0<<", "<<"%"<<now2<<std::endl;
            }
            now2=now++;
            std::cout<<"%"<<now<<"= "<<"eq "<<0<<",%"<<now2<<std::endl;
            now2=now++;
            std::cout<<"%"<<now<<"= "<<"and "<<"%"<<now1<<",%"<<now2<<std::endl;
            if(!exp1->calc_f){
                std::cout<<"store"<<" %"<<now<<", "<<"%"<<"and"<<andCounter<<std::endl;           
            }
            now++;
            if(!exp1->calc_f){
                bbm.BlockJump(lable2);
                bbm.CreateBasicBlock(lable2);
                std::cout<<"%"<<now<<"= "<<"load "<<"%"<<"and"<<andCounter<<std::endl;
                now++;
            }
            break;
        case op::OR:
            if(exp1->calc_f){
                res1=exp1->calc();
                std::cout<<"%"<<now<<"= "<<"eq "<<0<<", "<<res1<<std::endl;
                now1=now++;
                std::cout<<"%"<<now<<"= "<<"eq "<<0<<", "<<"%"<<now1<<std::endl;
                if(res1){
                    now++;
                    return;
                }
                now1=now++;
            }else{
                exp1->dump();
                now1=now-1;

                bbm.OrBranch();
                orCounter=bbm.orCounter;
                //短路求值用这个做标记
                lable1="or1part"+to_string(orCounter);
                lable2="or2part"+to_string(orCounter);
                std::cout<<"%"<<now<<"= "<<"eq "<<0<<", "<<"%"<<now1<<std::endl;
                now1=now++;
                std::cout<<"%"<<now<<"= "<<"eq "<<0<<", "<<"%"<<now1<<std::endl;
                now1=now++;

                std::cout<<"%"<<"or"<<orCounter<<" = "<<"alloc i32"<<std::endl;
                std::cout<<"store"<<" %"<<now1<<", "<<"%"<<"or"<<orCounter<<std::endl;

                bbm.BlockBranch("%"+to_string(now1),lable1,lable2);
                bbm.CreateBasicBlock(lable2);
            }
            if(exp2->calc_f){
                std::cout<<"%"<<now<<"= "<<"eq "<<0<<", "<<exp2->calc()<<std::endl;
            }
            else{
                exp2->dump();
                now2=now-1;
                std::cout<<"%"<<now<<"= "<<"eq "<<0<<", "<<"%"<<now2<<std::endl;
            }
            now2=now++;
            std::cout<<"%"<<now<<"= "<<"eq "<<0<<",%"<<now2<<std::endl;
            now2=now++;
            std::cout<<"store"<<" %"<<now-1<<", "<<"%"<<"or"<<orCounter<<std::endl;
            std::cout<<"%"<<now<<"= "<<"or "<<"%"<<now1<<",%"<<now2<<std::endl;
            if(!exp1->calc_f){
                std::cout<<"store"<<" %"<<now<<", "<<"%"<<"or"<<orCounter<<std::endl;           
            }
            now++;
            if(!exp1->calc_f){
                bbm.BlockJump(lable1);
                bbm.CreateBasicBlock(lable1);
                std::cout<<"%"<<now<<"= "<<"load "<<"%"<<"or"<<orCounter<<std::endl;
                now++;
            }
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
    if(ident=="")
        Array_dump();
    else
        Variable_dump();
}

void LValAST::Variable_dump() {
    if(calc_f)
        std::cout<<"%"<<now<<"= "<<"add 0, "<<val_table.get(ident).value<<std::endl;
    else{
        int tmp=val_table.get(ident).value;
        if(tmp==0){
            if(val_table.get(ident).array_size==0)
                std::cout<<"%"<<now<<"= "<<"load "<<"@"<<val_table.Get_Name(ident)<<std::endl;
            else if(val_table.get(ident).array_size>0){
                std::cout<<"%"<<now<<"= "<<"getelemptr "<<"@"<<val_table.Get_Name(ident)<<", "<<0<<std::endl;
            }
        }
        else if(tmp==1){
            if(val_table.get(ident).array_size==0)
                std::cout<<"%"<<now<<"= "<<"add 0,"<<"@"<<val_table.Get_Name(ident)<<std::endl;
            else if(val_table.get(ident).array_size>0)
                std::cout<<"%"<<now<<"= "<<"getptr "<<"@"<<val_table.Get_Name(ident)<<", "<<0<<std::endl;
        }
        else{
            std::cout<<"%"<<now<<"= "<<"load "<<"%"<<val_table.Get_Name(ident)<<std::endl;
        }
    }
    ++now;
}

void LValAST::Array_dump() {
    arraym.InitializeManager(Btype::BINT);
    arraym.addLArray(arraydef);
    if(val_table.get(arraym.get_name()).value==0)
        arraym.LArrayLoad();
    else
        arraym.ParamArrayLoad();
    
    if(val_table.get(arraym.get_name()).array_size>arraym.get_ldimon().size()){
        std::cout<<"%"<<now<<" = "<<"getelemptr "<<arraym.get_current_ptr()<<", "<<0<<std::endl;
        now++;
    }else if(val_table.get(arraym.get_name()).array_size==arraym.get_ldimon().size()){
        std::cout<<"%"<<now<<" = load "<<arraym.get_current_ptr()<<std::endl;
	    now++;
    }
    arraym.KillManager();
};


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

void printType(Btype type){
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

