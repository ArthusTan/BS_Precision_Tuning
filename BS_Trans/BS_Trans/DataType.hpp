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


#define ALERT(str)              printf("...alert : %s\n", (str).c_str())

using namespace std;

/* --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- */

enum{
    TOKEN_TYPE_NONE = -1,           //空置位
    TOKEN_TYPE_IDENTIFIER,          //标志符
    TOKEN_TYPE_CONSTANT_NUMBER,     //常量-number。
    TOKEN_TYPE_CONSTANT_STRING,     //常量-string。
    TOKEN_TYPE_RESERVED_WORD,       //保留字-????
    TOKEN_TYPE_RESERVED_TYPE,       //保留字-type
    TOKEN_TYPE_BOUNDARY_SYMBOL,     //边界符
    TOKEN_TYPE_OPERATOR,            //操作符
};

string __GET_TYPE(int type);

bool __contain(string str, vector<string> word);

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
    void addChar(char c);

private:
    string cache;
    int    type;
    
    int getType(string value);
    void push_back();
    bool is_string() const;
    bool is_bSymbol(char c) const;
    bool is_oSymbol(char c) const;
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
    
    void buildAST(TokenQueue tQueue);
};
/* --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- */
#endif /* DataType_hpp */
