#pragma once
#include <memory>
#include <stack>

namespace parser_namespace
{
class TurtleOperation;
}

namespace semantics_namespace
{

class TurtleState;
class DrawingContext;

class TurtleOperation
{
public:
    static std::unique_ptr<TurtleOperation> createOperation(parser_namespace::TurtleOperation &operation);
    virtual ~TurtleOperation() {}
    virtual void apply(TurtleState &state) = 0;
    virtual void applyAndDraw(TurtleState &state, DrawingContext &context) = 0;

protected:
    static std::stack<TurtleState> stateStack;
};

class TurtleOperationForward : public TurtleOperation
{
public:
    TurtleOperationForward(parser_namespace::TurtleOperation &operation);
    virtual void apply(TurtleState &state);
    virtual void applyAndDraw(TurtleState &state, DrawingContext &context);

private:
    float arg;
};

class TurtleOperationRotate : public TurtleOperation
{
public:
    TurtleOperationRotate(parser_namespace::TurtleOperation &operation);
    virtual void apply(TurtleState &state);
    virtual void applyAndDraw(TurtleState &state, DrawingContext &context);

private:
    float arg;
};

class TurtleOperationPenup : public TurtleOperation
{
public:
    TurtleOperationPenup(parser_namespace::TurtleOperation &operation);
    virtual void apply(TurtleState &state);
    virtual void applyAndDraw(TurtleState &state, DrawingContext &context);

private:
};

class TurtleOperationPendown : public TurtleOperation
{
public:
    TurtleOperationPendown(parser_namespace::TurtleOperation &operation);
    virtual void apply(TurtleState &state);
    virtual void applyAndDraw(TurtleState &state, DrawingContext &context);

private:
};

class TurtleOperationPencolour : public TurtleOperation
{
public:
    TurtleOperationPencolour(parser_namespace::TurtleOperation &operation);
    virtual void apply(TurtleState &state);
    virtual void applyAndDraw(TurtleState &state, DrawingContext &context);

private:
    uint8_t r, g, b;
};

class TurtleOperationGoto : public TurtleOperation
{
public:
    TurtleOperationGoto(parser_namespace::TurtleOperation &operation);
    virtual void apply(TurtleState &state);
    virtual void applyAndDraw(TurtleState &state, DrawingContext &context);

private:
    float x, y;
};

class TurtleOperationPensize : public TurtleOperation
{
public:
    TurtleOperationPensize(parser_namespace::TurtleOperation &operation);
    virtual void apply(TurtleState &state);
    virtual void applyAndDraw(TurtleState &state, DrawingContext &context);

private:
    float arg;
};

class TurtleOperationScale : public TurtleOperation
{
public:
    TurtleOperationScale(parser_namespace::TurtleOperation &operation);
    virtual void apply(TurtleState &state);
    virtual void applyAndDraw(TurtleState &state, DrawingContext &context);

private:
    float arg;
};

class TurtleOperationPushstate : public TurtleOperation
{
public:
    TurtleOperationPushstate(parser_namespace::TurtleOperation &operation);
    virtual void apply(TurtleState &state);
    virtual void applyAndDraw(TurtleState &state, DrawingContext &context);

private:
};

class TurtleOperationPopstate : public TurtleOperation
{
public:
    TurtleOperationPopstate(parser_namespace::TurtleOperation &operation);
    virtual void apply(TurtleState &state);
    virtual void applyAndDraw(TurtleState &state, DrawingContext &context);

private:
};

}
