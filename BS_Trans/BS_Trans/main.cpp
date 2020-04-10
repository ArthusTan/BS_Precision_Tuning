//
//  main.cpp
//  BS_Trans
//
//  Created by 谭铭炜 on 2020/4/8.
//  Copyright © 2020 谭铭炜. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <vector>
#include "DataType.hpp"

using namespace std;

int main(int argc, const char * argv[])
{
    string path = "/Users/arthustan/workspace-clion/BS_Sample/main.cpp";
    string ordr = "clang " + path + " -emit-llvm -S -c -o test.ll";
    system(ordr.c_str());
    FILE* file = fopen("test.ll", "rb");
    
    //词法分析
    TokenQueue* tQueue = new TokenQueue();
    char tmpChar;
    
    while(!feof(file))
    {
        tmpChar = fgetc(file);
        // 按字符读取程序
        tQueue->addChar(tmpChar);
    }
    //程序结束
    tQueue->addChar(0);
    
    //语法分析
    
    return 0;
}
