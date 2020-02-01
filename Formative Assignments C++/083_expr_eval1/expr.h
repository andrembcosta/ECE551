#pragma once

#include <sstream>
#include <string>

class Expression {
 public:
  virtual ~Expression() {}

  virtual std::string toString() const = 0;
};

class NumExpression : public Expression {
 private:
  long number;

 public:
  explicit NumExpression(long l) : number(l) {}

  virtual ~NumExpression() {}

  virtual std::string toString() const {
    std::stringstream stringBuilder;
    stringBuilder << number;
    std::string toPrint = stringBuilder.str();
    return toPrint;
  }
};

class PlusExpression : public Expression {
 private:
  Expression * lhs;

  Expression * rhs;

 public:
  PlusExpression(Expression * lhs, Expression * rhs) : lhs(lhs), rhs(rhs) {}

  virtual ~PlusExpression() {
    delete lhs;
    delete rhs;
  }

  virtual std::string toString() const {
    std::stringstream stringBuilder;
    stringBuilder << "(" << lhs->toString() << " + " << rhs->toString() << ")";
    std::string toPrint = stringBuilder.str();
    return toPrint;
  }
};
