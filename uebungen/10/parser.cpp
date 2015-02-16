#include <cassert>
#include <sstream>
#include "token.hpp"
#include "value.hpp"
#include "parser.hpp"
#include "runtime.hpp"
#include "stack.hpp"

namespace LambdaCalc {

Parser::Exception::Exception(const Token& token, const std::string& _msg) {
   std::ostringstream osmsg;
   osmsg << "At " << token << ": " << _msg;
   msg = osmsg.str();
}

Parser::Exception::~Exception() throw() {};

const char* Parser::Exception::what() const throw() {
   return msg.c_str();
}

Parser::Parser(Lex& _lex, SymbolTable& _symtab) :
      lex(_lex), symtab(_symtab), tokenConsumed(true) {
}

FunctionPtr Parser::getFunction() throw(Exception) {
   getToken();
   if (!lex.valid()) {
      return FunctionPtr((Function*) 0);
   }
   bindings.clear();
   FunctionPtr f = parseExpression();
   lex.markFinished();
   return f;
}

void Parser::nextToken() {
   if (tokenConsumed) {
      token = lex.getToken();
   } else {
      tokenConsumed = true;
   }
}

Token Parser::getToken() {
   if (tokenConsumed) {
      token = lex.getToken();
      tokenConsumed = false;
   }
   return token;
}

unsigned int Parser::findBinding(const std::string& varname) {
   unsigned int count = 0;
   for (const Binding& binding: bindings) {
      ++count;
      if (binding.varname == varname) return count;
   }
   return 0;
}

FunctionPtr Parser::parseExpression() throw(Exception) {
   // expr --> identifier
   if (getToken().symbol == Token::IDENT) {
      std::string varname = getToken().identifier;
      nextToken();
      unsigned int index = findBinding(varname);
      if (index) {
	 return FunctionPtr(new Function([=] (StackPtr sp) -> ValuePtr {
	    return (*sp)[index-1];
	 }));
      }
      return FunctionPtr(new Function([this,varname] (StackPtr sp)
	    -> ValuePtr {
	 ValuePtr value = symtab.get(varname);
	 if (value) return value;
	 throw RuntimeException("undefined variable: '" + varname + "'");
      }));
   }

   // expr --> integer
   if (getToken().symbol == Token::INTEGER) {
      int integer = getToken().integer;
      nextToken();
      return FunctionPtr(new Function([=] (StackPtr sp) {
	 return ValuePtr(new Value(integer));
      }));
   }

   // all other variants start with '('
   if (getToken().symbol != Token::LPAREN) {
      throw Exception(getToken(), "identifier, integer or '(' expected");
   }
   nextToken();

   // expr --> '(' lambda identifier expr ')'
   if (getToken().symbol == Token::LAMBDA) {
      nextToken();
      if (getToken().symbol != Token::IDENT) {
	 throw Exception(getToken(), "variable expected");
      }

      // open local scope with the variable and parse function body
      bindings.push_back(getToken().identifier);
      nextToken();
      FunctionPtr value = parseExpression();
      bindings.pop_back();

      if (getToken().symbol != Token::RPAREN) {
	 throw Exception(getToken(), "')' expected");
      }
      nextToken();
      FunctionPtr f = FunctionPtr(new Function([=] (StackPtr sp) {
	 return (*value)(sp);
      }));
      return FunctionPtr(new Function([=] (StackPtr sp) {
	 return ValuePtr(new Value(f, sp));
      }));
   }

   // expr --> '(' define identifier expr ')'
   if (getToken().symbol == Token::DEFINE) {
      nextToken();
      if (getToken().symbol != Token::IDENT) {
	 throw Exception(getToken(), "identifier expected");
      }
      std::string name = getToken().identifier;
      nextToken();
      FunctionPtr expr = parseExpression();
      if (getToken().symbol != Token::RPAREN) {
	 throw Exception(getToken(), "')' expected");
      }
      nextToken();
      return FunctionPtr(new Function([=] (StackPtr sp)
	    -> ValuePtr {
	 ValuePtr value = (*expr)(sp);
	 symtab.define(name, value);
	 return value;
      }));
   }

   // expr --> '(' if expr expr expr')'
   if (getToken().symbol == Token::IF) {
      nextToken();
      FunctionPtr condition = parseExpression();
      FunctionPtr then_part = parseExpression();
      FunctionPtr else_part = parseExpression();
      if (getToken().symbol != Token::RPAREN) {
	 throw Exception(getToken(), "')' expected");
      }
      nextToken();
      return FunctionPtr(new Function([=] (StackPtr sp) -> ValuePtr {
	 ValuePtr cond = (*condition)(sp);
	 if (cond->get_type() != Value::INTEGER || cond->get_integer()) {
	    return (*then_part)(sp);
	 } else {
	    return (*else_part)(sp);
	 }
      }));
   }

   // expr --> '(' expr expr ')'
   FunctionPtr funexpr = parseExpression();
   FunctionPtr paramexpr = parseExpression();
   if (getToken().symbol != Token::RPAREN) {
      throw Exception(getToken(), "')' expected");
   }
   nextToken();
   return FunctionPtr(new Function([=] (StackPtr sp) -> ValuePtr {
      ValuePtr f = (*funexpr)(sp);
      ValuePtr param = (*paramexpr)(sp);
      assert(param);
      if (f->get_type() != Value::FUNCTION) {
	 throw RuntimeException("bad function call");
      }
      FunctionPtr function = f->get_function();
      StackPtr closure = f->get_closure();
      StackPtr nested = StackPtr(new Stack(closure, param));
      return (*function)(nested);
   }));
}

} // namespace LambdaCalc
