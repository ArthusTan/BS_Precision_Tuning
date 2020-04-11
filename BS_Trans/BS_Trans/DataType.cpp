//
//  DataType.cpp
//  BS_Trans
//
//  Created by 谭铭炜 on 2020/4/2.
//  Copyright © 2020 谭铭炜. All rights reserved.
//

#include "DataType.hpp"
#include <ctype.h>


char __bSymbol[] = "{}()[]<>,";
char __oSymbol[] = "*=~";
vector<string> __tWord = {
    "void",
    // iN -> Integer Type
    "i1", "i8", "i16", "i32", "i64",
    // Floating-Point Type :
    // half         |  16 -bit floating-point value
    // float        |  32 -bit floating-point value
    // double       |  64 -bit floating-point value
    // fp128        |  128-bit floating-point value (112-bit mantissa)
    // x86_fp80     |  80 -bit floating-point value (X87)
    // ppc_fp128    |  128-bit floating-point value (two 64-bits)
    "ppc_fp128", "x86_fp80", "fp128", "double", "float", "half",
    // Other_Types:
    "x86_mmx", "label", "token", "metadata", "opaque"
};
vector<string> __oWord = {
    "icmp", "eq", "ne", "ugt", "uge", "ult", "ule", "sgt", "sge", "slt", "sle", "fcmp", "oeq", "ogt", "oge", "olt", "ole", "one", "ord", "ueq", "une", "uno",
/*Binary Operations*/
    "add", "fadd", "sub", "fsub", "mul", "fmul", "udiv", "sdiv", "fdiv", "urem", "srem", "frem",
/*Bitwise Binary Operations*/
    "shl", "nuw", "nsw", "lshr", "ashr", "exact", "and", "or", "xor"
};
vector<string> __rWord = {
/* Constant */
    "true", "false", "null", "none", "zeroinitializer",
/*Poison Values*/
    "phi", "select", "invoke", "resume", "asm", "sideeffect", "alignstack", "inteldialect", "ret", "catchret", "cleanupret", "br", "indirectbr", "callbr", "switch", "catchswitch", "unreachable", "fneg",
/*Vector Options*/
    "extractelement", "insertelement", "shufflevector",
/*Aggregate Operations*/
    "extractvalue", "insertvalue",
/*Memory Access and Addressing Operations*/
    "alloca", "load", "store", "fence", "cmpxchg", "atomicrmw", "getelementptr", "inbounds",
/*Conversion Operations*/
    "to", "trunc", "zext", "sext", "fptrunc", "fpext", "fptoui", "fptosi", "uitofp", "sitofp", "ptrtoint", "inttoptr", "bitcast", "addrspacecast",
/*Other Operations*/
     "select", "freeze", "call", "global", "undef", "define", "align", "bitcast", "optnone"
};

/* --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- */
string __GET_TYPE(int type)
{
    switch(type)
    {
        case  0: return "TOKEN_TYPE_IDENTIFIER      :";
        case  1: return "TOKEN_TYPE_CONSTANT_NUMBER :";
        case  2: return "TOKEN_TYPE_CONSTANT_STRING :";
        case  3: return "TOKEN_TYPE_RESERVED_WORD   :";
        case  4: return "TOKEN_TYPE_RESERVED_TYPE   :";
        case  5: return "TOKEN_TYPE_BOUNDARY_SYMBOL :";
        case  6: return "TOKEN_TYPE_OPERATOR        :";
        default: return "TOKEN_TYPE_NONE            :";
    }
}

bool __contain(string str, vector<string> word)
{
    for(int i = 0; i < word.size(); i++)
    {
        if(word[i] == str)
        {
            return true;
        }
    }
    return false;
}

/* --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- */

Token::Token(int type, string value){
    this->type  = type;
    this->value = value;
}
Token::Token(Token* token){
    this->type  = token->type;
    this->value = token->value;
}

/* --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- */

TokenQueue::TokenQueue()
{
    this->cache = "";
    this->type = TOKEN_TYPE_NONE;
}
void TokenQueue::addChar(char c)
{
    if(c == 0 || c == '\n' || c == '\377')      // 结束
    {
        this->push_back();
        return;
    }
    if(this->cache.size() == 0)                 // 之前不存在cache
    {
        if(!isspace(c))
        {
            this->cache = c;
            if(c <= '9' && c >= '0'){
                this->type = TOKEN_TYPE_CONSTANT_NUMBER;
            }
            else if(is_bSymbol(c))
            {
                this->type = TOKEN_TYPE_BOUNDARY_SYMBOL;
                this->push_back();
            }
            else if(is_oSymbol(c))
            {
                this->type = TOKEN_TYPE_OPERATOR;
                this->push_back();
            }
            else if(c == '\"'){
                this->type = TOKEN_TYPE_CONSTANT_STRING;
            }
            else
            {
                this->type  = TOKEN_TYPE_IDENTIFIER;
            }
        }
        return ;
    }
    if(this->cache[0] == '\"' && !is_string())  // 可继续拓展的字符串
    {
        this->cache += c;
    }
    else if(isspace(c))                         // 空白字符
    {
        this->push_back();
    }
    else if(is_string() || is_bSymbol(c) || is_oSymbol(c) || c == '\"')
    {
        this->push_back();
        this->addChar(c);
    }
    else    // 标志符 ｜ 保留字
    {
        this->cache += c;
    }
}
bool TokenQueue::is_string() const
{
    if(this->cache.size() < 2)
    {
        return false;
    }
    if(this->cache[0] != '\"' ||
       this->cache[this->cache.size() - 1] != '\"' ||
       this->cache[this->cache.size() - 2] == '\\')
    {
        return false;
    }
    return true;
}
bool TokenQueue::is_bSymbol(char c) const
{
    for(int i=0; i < sizeof(__bSymbol) / sizeof(char); i++)
    {
        if(__bSymbol[i] == c)
        {
            return true;
        }
    }
    return false;
}
bool TokenQueue::is_oSymbol(char c) const
{
    for(int i=0; i < sizeof(__oSymbol) / sizeof(char); i++)
    {
        if(__oSymbol[i] == c)
        {
            return true;
        }
    }
    return false;
}
void TokenQueue::push_back()
{
    if(this->cache == ""){
        this->type = TOKEN_TYPE_NONE;
        return;
    }
    if(this->type == TOKEN_TYPE_CONSTANT_NUMBER && this->cache[this->cache.size() - 1] == ':')
    {
        this->type = TOKEN_TYPE_IDENTIFIER;
    }
    else if(__contain(this->cache, __tWord))
    {
        this->type = TOKEN_TYPE_RESERVED_TYPE;
    }
    else if(__contain(this->cache, __oWord))
    {
        this->type = TOKEN_TYPE_OPERATOR;
    }
    else if(__contain(this->cache, __rWord))
    {
        this->type = TOKEN_TYPE_RESERVED_WORD;
    }
    Token* token = new Token(this->type, this->cache);
    this->tokens.push_back(*token);
    ALERT(__GET_TYPE(this->type) + this->cache);
    this->type = TOKEN_TYPE_NONE;
    this->cache = "";
}
/* --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- */

AbstractSyntaxTreeNode::AbstractSyntaxTreeNode(Token token){
    this->token = new Token(&token);
    this->father = nullptr;
}
void AbstractSyntaxTreeNode::addChild(Token token)
{
    AbstractSyntaxTreeNode* astn = new AbstractSyntaxTreeNode(token);
    astn->father = this;
    this->child.push_back(*astn);
}

/* --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- */

