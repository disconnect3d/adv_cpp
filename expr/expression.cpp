#include <iostream>
#include <cmath>

typedef double T;

struct Expression {
    virtual T getValue() = 0;
};

struct Value : Expression {
    Value(T val)
    : val(val)
    {}

    T getValue() override { return val; }

private:
    T val;
};

struct UnaryOp : Expression {
    UnaryOp(Expression* arg)
    : _arg(arg)
    {}

    T getValue() override {
        return eval(_arg->getValue());
    }

    virtual T eval(T val) = 0;

private:
    Expression* _arg;
};

struct Sqrt : UnaryOp {
    Sqrt(Expression* e)
    : UnaryOp(e)
    {}

    T eval(T val) override {
        return std::sqrt(val);
    }
};

struct BinaryOp : Expression {
    BinaryOp(Expression* left, Expression* right)
    : _left(left), _right(right)
    {}

    T getValue() override {
        return eval(_left->getValue(), _right->getValue());
    }

    virtual T eval(T left, T right) = 0;

private:
    Expression* _left;
    Expression* _right;
};

struct Add : BinaryOp {
    Add(Expression* l, Expression* r)
    : BinaryOp(l, r)
    {}

    T eval(T left, T right) override {
        return left + right;
    }
};

struct Sub : BinaryOp {
    Sub(Expression* l, Expression* r)
    : BinaryOp(l, r)
    {}

    T eval(T left, T right) override {
        return left - right;
    }
};

int main() {
    Expression* e = new Add(
        new Sub(
            new Value(100), new Sqrt(new Value(100))
        ),
        new Value(100)
    );

    std::cout << e->getValue() << std::endl;

    // lolo TODO FIXME memleakz
}



