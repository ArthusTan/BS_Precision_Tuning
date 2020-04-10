//
//  DataType.cpp
//  BS_Trans
//
//  Created by 谭铭炜 on 2020/4/2.
//  Copyright © 2020 谭铭炜. All rights reserved.
//

#include "DataType.hpp"


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
    tqcValue = "";
}
void TokenQueue::addChar(char c)
{
    if(!isOneToken(tqcValue + c) || c == 0)
    {
        Token* token = new Token(getType(tqcValue), tqcValue);
        
        ALERT_TOKEN(token->type, token->value);
        
        this->tokens.push_back(*token);
        
        tqcValue = c;
    }
}
bool TokenQueue::isOneToken(string value) const
{
    ;
    return false;
}

long TokenQueue::contain(string value) const
{
    long index = -1;
    const long MAX_INDEX = tokens.size();
    for(long i = 0; i < MAX_INDEX; i++)
    {
        string tmpValue = tokens.at(i).value;
        if(tmpValue == value)
        {
            index = i;
            break;
        }
    }
    return index;
}

int TokenQueue::getType(string value) const
{
    return TOKEN_TYPE_NONE;
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

