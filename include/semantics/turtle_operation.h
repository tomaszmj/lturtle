#pragma once
#include <memory>
#include <stack>

namespace parser
{
class TurtleOperation;
}

namespace semantics
{

class TurtleState;
class DrawingContext;

class TurtleOperation
{
public:
    static std::unique_ptr<TurtleOperation> createOperation(parser::TurtleOperation &operation);
    virtual ~TurtleOperation() {}
    virtual void apply(TurtleState &state) = 0;
    virtual void applyAndDraw(TurtleState &state, DrawingContext &context) = 0;

protected:
    static std::stack<TurtleState> stateStack;
};

class TurtleOperationForward : public TurtleOperation
{
public:
    TurtleOperationForward(parser::TurtleOperation &operation);
    virtual void apply(TurtleState &state);
    virtual void applyAndDraw(TurtleState &state, DrawingContext &context);

private:
    float arg;
};

class TurtleOperationRotate : public TurtleOperation
{
public:
    TurtleOperationRotate(parser::TurtleOperation &operation);
    virtual void apply(TurtleState &state);
    virtual void applyAndDraw(TurtleState &state, DrawingContext &context);

private:
    float arg;
};

class TurtleOperationPenup : public TurtleOperation
{
public:
    TurtleOperationPenup(parser::TurtleOperation &operation);
    virtual void apply(TurtleState &state);
    virtual void applyAndDraw(TurtleState &state, DrawingContext &context);

private:
};

class TurtleOperationPendown : public TurtleOperation
{
public:
    TurtleOperationPendown(parser::TurtleOperation &operation);
    virtual void apply(TurtleState &state);
    virtual void applyAndDraw(TurtleState &state, DrawingContext &context);

private:
};

class TurtleOperationPencolour : public TurtleOperation
{
public:
    TurtleOperationPencolour(parser::TurtleOperation &operation);
    virtual void apply(TurtleState &state);
    virtual void applyAndDraw(TurtleState &state, DrawingContext &context);

private:
    uint8_t r, g, b;
};

class TurtleOperationGoto : public TurtleOperation
{
public:
    TurtleOperationGoto(parser::TurtleOperation &operation);
    virtual void apply(TurtleState &state);
    virtual void applyAndDraw(TurtleState &state, DrawingContext &context);

private:
    float x, y;
};

class TurtleOperationPensize : public TurtleOperation
{
public:
    TurtleOperationPensize(parser::TurtleOperation &operation);
    virtual void apply(TurtleState &state);
    virtual void applyAndDraw(TurtleState &state, DrawingContext &context);

private:
    float arg;
};

class TurtleOperationScale : public TurtleOperation
{
public:
    TurtleOperationScale(parser::TurtleOperation &operation);
    virtual void apply(TurtleState &state);
    virtual void applyAndDraw(TurtleState &state, DrawingContext &context);

private:
    float arg;
};

class TurtleOperationPushstate : public TurtleOperation
{
public:
    TurtleOperationPushstate(parser::TurtleOperation &operation);
    virtual void apply(TurtleState &state);
    virtual void applyAndDraw(TurtleState &state, DrawingContext &context);

private:
};

class TurtleOperationPopstate : public TurtleOperation
{
public:
    TurtleOperationPopstate(parser::TurtleOperation &operation);
    virtual void apply(TurtleState &state);
    virtual void applyAndDraw(TurtleState &state, DrawingContext &context);

private:
};

}
