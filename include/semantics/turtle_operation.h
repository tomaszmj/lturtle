#pragma once
#include <memory>
#include <vector>
#include <array>

namespace parser_namespace
{
class TurtleOperation;
}

namespace semantics_namespace
{

class TurtleState;
class DrawingContext;
class UtmostTurtleCoordinates;

class TurtleOperation
{
public:
    static std::unique_ptr<TurtleOperation> create(parser_namespace::TurtleOperation &operation);
    static bool emptyStateStack(); // clears contents of stateStack, returns true if it was already empty, false otherwise
    virtual ~TurtleOperation() {}
    virtual std::unique_ptr<TurtleOperation> clone() const = 0;
    virtual void applyAndUpdateUtmostCoordinates(TurtleState &state, UtmostTurtleCoordinates &coords) = 0;
    virtual void applyAndDraw(TurtleState &state, DrawingContext &context) = 0;

protected:
    static std::vector<TurtleState> stateStack;
};

class TurtleOperationForward : public TurtleOperation
{
public:
    TurtleOperationForward(parser_namespace::TurtleOperation &operation);
    TurtleOperationForward(const TurtleOperationForward &other);
    virtual std::unique_ptr<TurtleOperation> clone() const;
    virtual void applyAndUpdateUtmostCoordinates(TurtleState &state, UtmostTurtleCoordinates &coords);
    virtual void applyAndDraw(TurtleState &state, DrawingContext &context);

private:
    float arg;
};

class TurtleOperationRotate : public TurtleOperation
{
public:
    TurtleOperationRotate(parser_namespace::TurtleOperation &operation);
    TurtleOperationRotate(const TurtleOperationRotate &other);
    virtual std::unique_ptr<TurtleOperation> clone() const;
    virtual void applyAndUpdateUtmostCoordinates(TurtleState &state, UtmostTurtleCoordinates &coords);
    virtual void applyAndDraw(TurtleState &state, DrawingContext &context);

private:
    float arg;
};

class TurtleOperationPenup : public TurtleOperation
{
public:
    virtual std::unique_ptr<TurtleOperation> clone() const;
    virtual void applyAndUpdateUtmostCoordinates(TurtleState &state, UtmostTurtleCoordinates &coords);
    virtual void applyAndDraw(TurtleState &state, DrawingContext &context);

private:
};

class TurtleOperationPendown : public TurtleOperation
{
public:
    virtual std::unique_ptr<TurtleOperation> clone() const;
    virtual void applyAndUpdateUtmostCoordinates(TurtleState &state, UtmostTurtleCoordinates &coords);
    virtual void applyAndDraw(TurtleState &state, DrawingContext &context);

private:
};

class TurtleOperationPencolour : public TurtleOperation
{
public:
    TurtleOperationPencolour(parser_namespace::TurtleOperation &operation);
    TurtleOperationPencolour(const TurtleOperationPencolour &other);
    virtual std::unique_ptr<TurtleOperation> clone() const;
    virtual void applyAndUpdateUtmostCoordinates(TurtleState &state, UtmostTurtleCoordinates &coords);
    virtual void applyAndDraw(TurtleState &state, DrawingContext &context);

private:
    std::array<uint8_t, 3> colour;
};

class TurtleOperationGoto : public TurtleOperation
{
public:
    TurtleOperationGoto(parser_namespace::TurtleOperation &operation);
    TurtleOperationGoto(const TurtleOperationGoto &other);
    virtual std::unique_ptr<TurtleOperation> clone() const;
    virtual void applyAndUpdateUtmostCoordinates(TurtleState &state, UtmostTurtleCoordinates &coords);
    virtual void applyAndDraw(TurtleState &state, DrawingContext &context);

private:
    std::pair<float, float> position;
};

class TurtleOperationPensize : public TurtleOperation
{
public:
    TurtleOperationPensize(parser_namespace::TurtleOperation &operation);
    TurtleOperationPensize(const TurtleOperationPensize &other);
    virtual std::unique_ptr<TurtleOperation> clone() const;
    virtual void applyAndUpdateUtmostCoordinates(TurtleState &state, UtmostTurtleCoordinates &coords);
    virtual void applyAndDraw(TurtleState &state, DrawingContext &context);

private:
    float arg;
};

class TurtleOperationScale : public TurtleOperation
{
public:
    TurtleOperationScale(parser_namespace::TurtleOperation &operation);
    TurtleOperationScale(const TurtleOperationScale &other);
    virtual std::unique_ptr<TurtleOperation> clone() const;
    virtual void applyAndUpdateUtmostCoordinates(TurtleState &state, UtmostTurtleCoordinates &coords);
    virtual void applyAndDraw(TurtleState &state, DrawingContext &context);

private:
    float arg;
};

class TurtleOperationPushstate : public TurtleOperation
{
public:
    virtual std::unique_ptr<TurtleOperation> clone() const;
    virtual void applyAndUpdateUtmostCoordinates(TurtleState &state, UtmostTurtleCoordinates &coords);
    virtual void applyAndDraw(TurtleState &state, DrawingContext &context);

private:
};

class TurtleOperationPopstate : public TurtleOperation
{
public:
    virtual std::unique_ptr<TurtleOperation> clone() const;
    virtual void applyAndUpdateUtmostCoordinates(TurtleState &state, UtmostTurtleCoordinates &coords);
    virtual void applyAndDraw(TurtleState &state, DrawingContext &context);

private:
};

}
