class Calculator;

class Command
{
public:
    virtual ~Command() = default;
    virtual void Execute(Calculator& calc) = 0; //������ �� ������, 
    //virtual void Execute(class Calculator& calc) = 0; - forward declaration
};