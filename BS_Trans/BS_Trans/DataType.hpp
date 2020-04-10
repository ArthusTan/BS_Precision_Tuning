//
//  DataType.hpp
//  BS_Trans
//
//  Created by 谭铭炜 on 2020/4/2.
//  Copyright © 2020 谭铭炜. All rights reserved.
//

#ifndef DataType_hpp
#define DataType_hpp

#include <stdio.h>
#include <string>
#include <vector>

#define tqcValue this->cacheValue

using namespace std;
/* --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- */
enum{
    TOKEN_TYPE_NONE = 0,            //空置位 - 0
    TOKEN_TYPE_IDENTIFIER,          //标志符 - 1
    TOKEN_TYPE_CONSTANT,            //常量。 - 2
    TOKEN_TYPE_RESERVED_WORD,       //保留字 - 3
    TOKEN_TYPE_BOUNDARY_SYMBOL,     //边界符 - 4
    TOKEN_TYPE_OPERATOR             //操作符 - 5
    // (bitcode中是否存在操作符的概念？)
};
/* --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- */
class Token
{
public:
    int type;
    string value;
    
    Token(int type, string value);
    Token(Token* token);
    Token getToken(string str);
};
/* --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- */
class TokenQueue
{
public:
    vector<Token> tokens;
    
    TokenQueue();
    void clear();
    void addChar(char c);

private:
    string cacheValue;
    int    cacheType;
    bool isOneToken(string value) const;
    int  getType(string value) const;
};
/* --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- */
class AbstractSyntaxTreeNode
{
public:
    Token* token;
    AbstractSyntaxTreeNode* father;
    vector<AbstractSyntaxTreeNode> child;
    
    AbstractSyntaxTreeNode(Token token);
    void addChild(Token token);
    
    
};
/* --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- */
class AbstractSyntaxTree
{
public:
    Token root;
    AbstractSyntaxTree();
    
    void clear();
    void buildAST(TokenQueue tQueue);
};
/* --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- */
#endif /* DataType_hpp */
