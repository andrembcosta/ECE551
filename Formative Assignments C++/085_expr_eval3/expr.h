#pragma once

#include <sstream>
#include <string>

class Expression {
 public:
  virtual ~Expression() {}

  virtual std::string toString() const = 0;

  virtual long evaluate() const = 0;
};

class OperationExpression : public Expression {
 protected:
  Expression * lhs;

  Expression * rhs;

  char OperationSign;

 public:
  OperationExpression(Expression * lhs, Expression * rhs) : lhs(lhs), rhs(rhs) {}

  virtual ~OperationExpression() {
    delete lhs;
    delete rhs;
  }

  virtual std::string toString() const {
    std::stringstream stringBuilder;
    stringBuilder << "(" << lhs->toString() << ' ' << OperationSign << ' '
                  << rhs->toString() << ")";
    std::string toPrint = stringBuilder.str();
    return toPrint;
  }
};

class NumExpression : public Expression {
 private:
  long number;

 public:
  explicit NumExpression(long l) : number(l) {}

  virtual ~NumExpression() {}

  virtual long evaluate() const { return number; }

  virtual std::string toString() const {
    std::stringstream stringBuilder;
    stringBuilder << number;
    std::string toPrint = stringBuilder.str();
    return toPrint;
  }
};

class PlusExpression : public OperationExpression {
 public:
  PlusExpression(Expression * lhs, Expression * rhs) : OperationExpression(lhs, rhs) {
    OperationSign = '+';
  }

  virtual long evaluate() const {
    long ans = lhs->evaluate() + rhs->evaluate();
    return ans;
  }

  virtual ~PlusExpression() {}
};

class MinusExpression : public OperationExpression {
 public:
  MinusExpression(Expression * lhs, Expression * rhs) : OperationExpression(lhs, rhs) {
    OperationSign = '-';
  }

  virtual long evaluate() const {
    long ans = lhs->evaluate() - rhs->evaluate();
    return ans;
  }

  virtual ~MinusExpression() {}
};

class TimesExpression : public OperationExpression {
 public:
  TimesExpression(Expression * lhs, Expression * rhs) : OperationExpression(lhs, rhs) {
    OperationSign = '*';
  }

  virtual long evaluate() const {
    long ans = lhs->evaluate() * rhs->evaluate();
    return ans;
  }

  virtual ~TimesExpression() {}
};

class DivExpression : public OperationExpression {
 public:
  DivExpression(Expression * lhs, Expression * rhs) : OperationExpression(lhs, rhs) {
    OperationSign = '/';
  }

  virtual long evaluate() const {
    long ans = lhs->evaluate() / rhs->evaluate();
    return ans;
  }

  virtual ~DivExpression() {}
};
