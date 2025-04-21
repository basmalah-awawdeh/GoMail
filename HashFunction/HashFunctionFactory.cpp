#include "HashFunctionFactory.h"
#include "StdHash.h"
#include "DoubleHash.h"

std::shared_ptr<HashFunc> MakeHash::CreateHashFunc(int input){
    if(input==1){
        return std::make_shared<StdHash>();
    }
    if(input==2){
        return std::make_shared<StdDoubleHash>();
    }
    return std::make_shared<StdHash>();
}
