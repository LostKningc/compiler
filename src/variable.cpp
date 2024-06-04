#include"variable.hpp"
#include<iostream>

extern int now;
extern Val_Table val_table;
void Val_Table::EnterBlock(){
	if(t_stack.back().field_idx==0){
		t_stack.push_back(Val_Map(1));
		map_counter++;
	}
	else{
		map_counter++;
		t_stack.push_back(Val_Map(map_counter));
	}
}

void Val_Table::ExitBlock(){
	t_stack.pop_back();
}

const Val_Info& Val_Table::get(std::string name) {
	auto beg=t_stack.rbegin(),end=t_stack.rend();
	for(auto it=beg;it!=end;++it){
		auto& table=*it;
		auto val=table.val_map.find(name);
		if(val!=table.val_map.end())return val->second;
	}
	throw std::runtime_error("error: symbol \"" + name + "\" is not declared!!");
}

void Val_Table::Record(std::string name,std::pair<int,bool> val){
	if(t_stack.back().val_map.find(name)!=t_stack.back().val_map.end()){
		throw std::runtime_error("error: symbol \"" + name + "\" is redeclared");
	}
	t_stack.back().val_map[name]=Val_Info(int(val.first),bool(val.second));
}

void Val_Table::Record(std::string name,int value,bool const_flag,bool const_array){
	if(t_stack.back().val_map.find(name)!=t_stack.back().val_map.end()){
		throw std::runtime_error("error: symbol \"" + name + "\" is redeclared");
	}
	t_stack.back().val_map[name]=Val_Info(value,const_flag,const_array);
}

void Val_Table::Record(std::string name,int value,bool const_flag,bool const_array,int array_size){
	if(t_stack.back().val_map.find(name)!=t_stack.back().val_map.end()){
		throw std::runtime_error("error: symbol \"" + name + "\" is redeclared");
	}
	t_stack.back().val_map[name]=Val_Info(value,const_flag,const_array,array_size);
}



Val_Table::Val_Table(){
	map_counter=0;
	t_stack.push_back(Val_Map(map_counter));
}

std::string Val_Table::Get_Name(std::string prim_name){
	auto beg=t_stack.rbegin(),end=t_stack.rend();
	for(auto it=beg;it!=end;++it){
		auto& table=*it;
		auto val=table.val_map.find(prim_name);
		if(val!=table.val_map.end()){
			if(table.field_idx==1)return prim_name;
			else
				return "__filed"+std::to_string(table.field_idx)+"__"+prim_name;
		}
	}
	throw std::runtime_error("error: symbol \"" + prim_name + "\" is not declared!");
}

void Val_Table::add_Param(std::string name){
	params_tmp.push_back(Param_Info(name,0));
}

void Val_Table::add_Param(std::string name,int dimon){
	params_tmp.push_back(Param_Info(name,dimon));
}

void Val_Table::params2block(){
	if(params_tmp.empty())return;
	for(auto& param:params_tmp){
		Record(param.name,1,false,false,param.dimon_size);
		if(param.dimon_size==0){
			//TODO:这里后面要改,目前只有int，先这样了
            std::cout<<"%"<<param.name<<"= "<<"alloc "<<"i32"<<std::endl;
            std::cout<<"store "<<"@"<<val_table.Get_Name(param.name)<<", "<<"%"<<val_table.Get_Name(param.name)<<std::endl;
            val_table.valuePlus1(param.name);
		}
		
	}
	params_tmp.clear();
}

void Val_Table::valuePlus1(std::string name){
	t_stack[1].val_map[name].first++;
}

int Val_Table::get_field_idx(){
	return t_stack.back().field_idx;
}

std::string ArrayManager::get_name(){
	return array_stack.back().name;
}

const std::vector<int>& ArrayManager::get_dimon(){
	return array_stack.back().array_dimon;
}

const std::vector<std::string>& ArrayManager::get_ldimon(){
	return array_stack.back().larray_dimon;
}

int ArrayManager::get_filled_sum(){
	return array_stack.back().filled_sum;
}

bool ArrayManager::get_const_flag(){
	return array_stack.back().const_flag;
}

Btype ArrayManager::get_type(){
	return array_stack.back().type;
}

void ArrayManager::Plus1FilledSum(){
	array_stack.back().filled_sum++;
}

std::vector<std::string> ArrayManager::ConstParseArray(const std::unique_ptr<BaseAST> &ast, int depth){
	std::vector<std::string> result;
	ConstInitValsAST* array=dynamic_cast<ConstInitValsAST*>(ast.get());
	if(array==nullptr){
		throw std::runtime_error("error: ConstInitValsAST cast failed");
	}

	int temp=get_filled_sum();
	int sum_temp=temp;

	int siz=1;
	int las=1,i;
	for(i=get_dimon().size()-1;i>=depth;i--){
		las*=get_dimon()[i];
		if(temp%las){
			continue;
		}else{
			if(temp/las==1){i--;break;}
			else if(temp/las==0) continue;
			else if(temp/las>1){
				if(i>0&&(temp/(las*get_dimon()[i-1]))==0){i--;break;}
				else {
					continue;
				}
			} 
		}
	}

	for(int k=std::max(i+1,depth);k<get_dimon().size();k++)siz*=get_dimon()[k];
	auto& initList=array->array_val_list;

	for(auto& element:initList){
		ConstInitValsAST* initArray=dynamic_cast<ConstInitValsAST*>(element.get());
		ConstExpAST* initExp=dynamic_cast<ConstExpAST*>(element.get());

		if(initArray==nullptr&&initExp==nullptr){
			throw std::runtime_error("error: ConstInitValsAST or ConstExpAST cast failed");
		}

		if(initExp){

			initExp->up_calc();
			if(initExp->calc_f){
				result.push_back(std::to_string(initExp->calc()));
				Plus1FilledSum();
			}
			else{
				throw std::runtime_error("error: array initialization list must be constant expression");
			}
		}
		else if(initArray){
			auto nestedResult=ConstParseArray(element,depth+1);
			result.insert(result.end(),nestedResult.begin(),nestedResult.end());

			int expected_size = 1,last_temp=1;
        	for (int k = get_dimon().size()-1; k>=depth; k--) {
            	last_temp *= get_dimon()[k];
				if(sum_temp%expected_size==0){
					if(sum_temp/expected_size==1){
						expected_size=last_temp;
						break;
					}
					else if(sum_temp/expected_size==0){
						;
					}
					else if(k>0&&(sum_temp/(expected_size*get_dimon()[k-1]))==0){
						expected_size=last_temp;
						break;
					}
					else{
						last_temp*=get_dimon()[k];
					}
				}
				else{
					break;
				}
				expected_size=last_temp;
			
			}
        	if (nestedResult.size() > expected_size) {
            	throw std::runtime_error("error: initialization list exceeds array dimensions !");
        	}
		}
	}
	while(result.size()<siz){
		result.push_back(std::to_string(0));
		Plus1FilledSum();
	}
	if(result.size()!=siz){
		throw std::runtime_error("error: initialization list does not match array dimensions");
	}
	return result;
}

std::vector<std::string> ArrayManager::VarParseArray(const std::unique_ptr<BaseAST> &ast,int depth){
	std::vector<std::string> result;
	InitValsAST* array=dynamic_cast<InitValsAST*>(ast.get());
	int temp=get_filled_sum();
	int sum_temp=temp;

	int siz=1;
	int las=1,i;
	for(i=get_dimon().size()-1;i>=depth;i--){
		las*=get_dimon()[i];
		if(temp%las){
			continue;
		}else{
			if(temp/las==1){i--;break;}
			else if(temp/las==0) continue;
			else if(temp/las>1){
				if(i>0&&(temp/(las*get_dimon()[i-1]))==0){i--;break;}
				else {
					continue;
				}
			} 
		}
	}
	
	for(int k=std::max(i+1,depth);k<get_dimon().size();k++)siz*=get_dimon()[k];
	auto& initList=array->array_val_list;
	for(auto& element:initList){
		InitValsAST* initArray=dynamic_cast<InitValsAST*>(element.get());
		ExpAST* initExp=dynamic_cast<ExpAST*>(element.get());
		//debug info
		if(initArray==nullptr&&initExp==nullptr){
			throw std::runtime_error("error: InitValsAST or ConstExpAST cast failed");
		}
		if(initExp){
			initExp->up_calc();
			if(initExp->calc_f){
				result.push_back(std::to_string(initExp->calc()));
				Plus1FilledSum();
			}
			else{
				if(val_table.get_field_idx()==0){
					throw std::runtime_error("error:gloabl array initialization list must be constant expression");
				}
				initExp->dump();
				result.push_back("%"+std::to_string(now-1));
				Plus1FilledSum();
			}
			sum_temp++;
		}
		else if(initArray){
			auto nestedResult=VarParseArray(element,depth+1);
			result.insert(result.end(),nestedResult.begin(),nestedResult.end());

			int expected_size = 1,last_temp=1;
        	for (int k = get_dimon().size()-1; k>=depth; k--) {
            	last_temp *= get_dimon()[k];
				if(sum_temp%expected_size==0){
					if(sum_temp/expected_size==1){
						expected_size=last_temp;
						break;
					}
					else if(sum_temp/expected_size==0){
						;
					}
					else if(k>0&&(sum_temp/(expected_size*get_dimon()[k-1]))==0){
						expected_size=last_temp;
						break;
					}
					else{
						last_temp*=get_dimon()[k];
					}
				}
				else{
					break;
				}
				expected_size=last_temp;
			
			}
        	if (nestedResult.size() > expected_size) {
            	throw std::runtime_error("error: initialization list exceeds array dimensions !");
        	}
		}
	}

	while(result.size()<siz){
		result.push_back(std::to_string(0));
		Plus1FilledSum();
	}
	if(result.size()!=siz){
		throw std::runtime_error("error: initialization list does not match array dimensions");
	}
	return result;
}

void ArrayManager::InitializeManager(Btype ntype){
	array_stack.push_back(ArrayInfo("",ntype));
}

void ArrayManager::InitializeManager(Btype ntype,bool const_f){
	array_stack.push_back(ArrayInfo("",ntype,const_f));
}

void ArrayManager::KillManager(){
	array_stack.pop_back();
}

void ArrayManager::addArray(const std::unique_ptr<BaseAST> &arraydef){
	ArrayDefsAST* array=dynamic_cast<ArrayDefsAST*>(arraydef.get());	
	array_stack.back().name=array->ident;
	
	auto& dimon_list=array->dimon_list;
	for(auto& dimon:dimon_list){
		ConstExpAST* dimonAST=dynamic_cast<ConstExpAST*>(dimon.get());
		dimonAST->up_calc();
		if(dimonAST->calc_f){
			array_stack.back().array_dimon.push_back(dimonAST->calc());
		}
		else{
			throw std::runtime_error("error: array dimension must be constant expression");
		}
	}
	//加入符号表
	val_table.Record(get_name(),0,false,get_const_flag(),dimon_list.size());
}

void ArrayManager::addLArray(const std::unique_ptr<BaseAST> &arraydef){
	LArrayAST* array=dynamic_cast<LArrayAST*>(arraydef.get());	
	array_stack.back().name=array->ident;
	auto& dimon_list=array->dimon_list;
	for(auto& dimon:dimon_list){
		ExpAST* dimonAST=dynamic_cast<ExpAST*>(dimon.get());
		dimonAST->up_calc();
		if(dimonAST->calc_f){
			array_stack.back().larray_dimon.push_back(std::to_string(dimonAST->calc()));
		}
		else{
			dimonAST->dump();
			array_stack.back().larray_dimon.push_back("%"+std::to_string(now-1));
		}
	}
}

void ArrayManager::addParamArray(const std::unique_ptr<BaseAST> &arraydef){
	FuncArrayAST* array=dynamic_cast<FuncArrayAST*>(arraydef.get());
	if(array==nullptr){
		throw std::runtime_error("error: FuncArrayAST cast failed");
	}
	array_stack.back().name=array->ident;
	val_table.add_Param(get_name(),array->dimon_list.size()+1);
	auto& dimon_list=array->dimon_list;
	for(auto& dimon:dimon_list){
		ConstExpAST* dimonAST=dynamic_cast<ConstExpAST*>(dimon.get());
		dimonAST->up_calc();
		if(dimonAST->calc_f){
			array_stack.back().array_dimon.push_back(dimonAST->calc());
		}
		else{
			throw std::runtime_error("error: array dimension must be constant expression");
		}
	}
}

// 递归生成数组类型描述字符串
std::string ArrayManager::generateArrayType(int depth) {
    if (depth >= get_dimon().size()) {
		if(get_type()==Btype::BINT)
        	return "i32";
		else
			return "void";
    }
    
    int current_dim = get_dimon()[depth];
    std::string inner_type = generateArrayType(depth + 1);
    
    return "[" + inner_type + ", " + std::to_string(current_dim) + "]";
}

// 生成 alloc 语句
std::string ArrayManager::generateAllocStatement(const std::string& var_name) {
    std::string array_type = generateArrayType();
    return "@" + var_name + " = alloc " + array_type;
}


//按aggregate的形式打印数组
void ArrayManager::printArray(const std::vector<std::string> &data){
	if(data.empty())
		std::cout<<"zeroinit";
	else{
		int index = 0;
		std::cout << formatArray(data, get_dimon(), 0, index);
	}
}

std::string ArrayManager::formatArray(const std::vector<std::string>& data, const std::vector<int>& array_dim, int depth, int& index) {
    std::string result = "{";
    int dimSize = array_dim[depth];
    
    for (int i = 0; i < dimSize; ++i) {
        if (depth == array_dim.size() - 1) {
            // 最后一维
            result += data[index++];
        } else {
            // 递归处理下一维
            result += formatArray(data, array_dim, depth + 1, index);
        }
        if (i < dimSize - 1) {
            result += ", ";
        }
    }
    
    result += "}";
    return result;
}

//左值的加载
void ArrayManager::LArrayLoad(){
	bool flag=true;
	for(auto& element:get_ldimon()){
		if(flag){
			std::cout<<"%"<<"ptr"<<ptr_counter<<" = "<<"getelemptr "<<"@"<<val_table.Get_Name(get_name())<<", "<<element<<std::endl;
			flag=false;
		}
		else{
			std::cout<<"%"<<"ptr"<<ptr_counter<<" = "<<"getelemptr "<<"%"<<"ptr"<<ptr_counter-1<<", "<<element<<std::endl;
		}
		ptr_counter++;
	}
}

void ArrayManager::ParamArrayLoad(){;
	bool flag=true;
	for(auto& element:get_ldimon()){
		if(flag){
			std::cout<<"%"<<"ptr"<<ptr_counter<<" = "<<"getptr "<<"@"<<val_table.Get_Name(get_name())<<", "<<element<<std::endl;
			flag=false;
		}
		else{
			std::cout<<"%"<<"ptr"<<ptr_counter<<" = "<<"getelemptr "<<"%"<<"ptr"<<ptr_counter-1<<", "<<element<<std::endl;
		}
		ptr_counter++;
	}
}

std::string ArrayManager::get_current_ptr(){
	return "%ptr"+std::to_string(ptr_counter-1);
}