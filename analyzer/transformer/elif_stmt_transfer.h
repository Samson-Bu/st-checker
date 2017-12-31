#ifndef ELIF_STMT_TRANSFER
#define ELIF_STMT_TRANSFER

#include <string>

#include "Abstract_transfer.h"
#include "../domain/Value_set.h"

class Elif_stmt_transfer : public Abstract_transfer
{
    // weight transfers for false edges in CFG

    /**
    * public methods
    */
public:
    Elif_stmt_transfer();
    Elif_stmt_transfer(symbol_c *);
    virtual ~Elif_stmt_transfer();

    Value_set *Transform(symbol_c *, Value_set *);
    std::string format();

    /**
    * private attributes
    */
private:
    std::string op;
    std::string str_left_var, str_right_var;

    key left_var, right_var;
};

#endif // ELIF_STMT_TRANSFER
