#include "calculator.h"

int main(int argc, char** argv)
{
    Calculator calculator = Calculator (argc, argv, "person");
    calculator.node();
    return 0;
}
