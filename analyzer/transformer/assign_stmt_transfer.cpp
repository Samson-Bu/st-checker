#include "assign_stmt_transfer.h"
#include "../../parser/ST_parser.h"

/**
* public methods
*/
/*
* constructor
*/
Assign_stmt_transfer::Assign_stmt_transfer(symbol_c *_assignment)
{
    statement = _assignment;
    assignment_statement_c *stmt = (assignment_statement_c *)statement;

    str_left_var = ST_parser::parse(stmt->l_exp);

    std::string str_r_exp_type = stmt->r_exp->absyntax_cname();
    if (str_r_exp_type.compare("add_expression_c") == 0)
    {
        //SYM_REF2(add_expression_c, l_exp, r_exp, bool deprecated_operation;)
        add_expression_c *r_exp = (add_expression_c *)stmt->r_exp;
        str_op = "+";
        str_right_var1 = ST_parser::parse(r_exp->l_exp);
        str_right_var2 = ST_parser::parse(r_exp->r_exp);
    }
    else if (str_r_exp_type.compare("sub_expression_c") == 0)
    {
        //SYM_REF2(sub_expression_c, l_exp, r_exp, bool deprecated_operation;)
        sub_expression_c *r_exp = (sub_expression_c *)stmt->r_exp;
        str_op = "-";
        str_right_var1 = ST_parser::parse(r_exp->l_exp);
        str_right_var2 = ST_parser::parse(r_exp->r_exp);

    }
    else /* unary expression */
    {
        //SYM_TOKEN(integer_c)
        //SYM_REF2(boolean_literal_c, type, value)
        // variable
        str_right_var1 = ST_parser::parse(stmt->r_exp);
    }

}

/*
* de-constructor
*/
Assign_stmt_transfer::~Assign_stmt_transfer()
{
}


/**
* external visible methods - inherited methods
*/
Value_set *Assign_stmt_transfer::op_transform(Value_set *_vs0)
{
    Value_set *ret = new Value_set(_vs0);
    assignment_statement_c *stmt = (assignment_statement_c *)statement;

    str_left_var = ST_parser::parse(stmt->l_exp);
    left_var = _vs0->contains_var(str_left_var);

    std::string str_r_exp_type = stmt->r_exp->absyntax_cname();

    /* binary expression*/
    if (str_r_exp_type.compare("add_expression_c") == 0)
    {
        //SYM_REF2(add_expression_c, l_exp, r_exp, bool deprecated_operation;)
        add_expression_c *r_exp = (add_expression_c *)stmt->r_exp;
        str_op = "+";
        str_right_var1 = ST_parser::parse(r_exp->l_exp);
        str_right_var2 = ST_parser::parse(r_exp->r_exp);

        if (left_var->get_str_type().compare(Var::TYPE_INT) == 0)
        {
            int_value si1, si2;
            if (is_number(str_right_var1))
            {
                si1 = Strided_interval::get_singleton_set(to_number(str_right_var1));
                right_var1 = 0;
            }
            else
            {
                right_var1 = _vs0->contains_var(str_right_var1);
                if (right_var1 != 0)
                {
                    si1 = _vs0->get_int_value_by(right_var1);
                }
                else
                {
                    std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! add_expression--int" << std::endl;
                    exit(0);
                }
            }

            if (is_number(str_right_var2))
            {
                si2 = Strided_interval::get_singleton_set(to_number(str_right_var2));
                right_var2 = 0;
            }
            else
            {
                right_var2 = _vs0->contains_var(str_right_var2);
                if (right_var2 != 0)
                {
                    si2 = _vs0->get_int_value_by(right_var2);
                }
                else
                {
                    std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! add_expression--int" << std::endl;
                    exit(0);
                }
            }
            ret->set_var_value(left_var, _vs0->get_int_value_by(left_var)->op_union(si1->op_add(si2)));

//            std::cout << si1->format() << "  " << si2->format() << std::endl;
//            std::cout << ret->get_int_value(left_var)->format() << std::endl;

        }
        /* need to be tested*/
        else if (left_var->get_str_type().compare(Var::TYPE_BYTE) == 0)
        {
            Bits_vector_8 *bv1, *bv2;
            if (is_byte(str_right_var1))
            {
                bv1 = Bits_vector_8::get_instance(str_right_var1);
                right_var1 = 0;
            }
            else
            {
                right_var1 = _vs0->contains_var(str_right_var1);
                if (right_var1 != 0)
                {
                    bv1 = _vs0->get_byte_value_by(right_var1);
                }
                else
                {
                    std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! add_expression--byte" << std::endl;
                    exit(0);
                }
            }

            if (is_byte(str_right_var2))
            {
                bv2 = Bits_vector_8::get_instance(str_right_var2);
                right_var2 = 0;
            }
            else
            {
                right_var2 = _vs0->contains_var(str_right_var2);
                if (right_var2 != 0 )
                {
                    bv2 = _vs0->get_byte_value_by(right_var2);
                }
                else
                {
                    std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! add_expression--byte" << std::endl;
                    exit(0);
                }
            }

        }

    }
    else if (str_r_exp_type.compare("sub_expression_c") == 0)
    {
        //SYM_REF2(sub_expression_c, l_exp, r_exp, bool deprecated_operation;)
        sub_expression_c *r_exp = (sub_expression_c *)stmt->r_exp;
        str_op = "-";
        str_right_var1 = ST_parser::parse(r_exp->l_exp);
        str_right_var2 = ST_parser::parse(r_exp->r_exp);

        if (left_var->get_str_type().compare(Var::TYPE_INT) == 0)
        {
            int_value si1, si2;
            if (is_number(str_right_var1))
            {
                si1 = Strided_interval::get_singleton_set(to_number(str_right_var1));
                right_var1 = 0;
            }
            else
            {
                right_var1 = _vs0->contains_var(str_right_var1);
                if (right_var1 != 0)
                {
                    si1 = _vs0->get_int_value_by(right_var1);
                }
                else
                {
                    std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! sub_expression--int" << std::endl;
                    exit(0);
                }
            }

            if (is_number(str_right_var2))
            {
                si2 = Strided_interval::get_singleton_set(to_number(str_right_var2));
                right_var2 = 0;
            }
            else
            {
                right_var2 = _vs0->contains_var(str_right_var2);
                if (right_var2 != 0)
                {
                    si2 = _vs0->get_int_value_by(right_var2);
                }
                else
                {
                    std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! sub_expression--int" << std::endl;
                    exit(0);
                }
            }

            ret->set_var_value(left_var, _vs0->get_int_value_by(left_var)->op_union(si1->op_sub(si2)));
        }
        /* need to be tested*/
        else if (left_var->get_str_type().compare(Var::TYPE_BYTE) == 0)
        {

        }

    }
    else /* unary expression */
    {
        //SYM_TOKEN(integer_c)
        //SYM_REF2(boolean_literal_c, type, value)
        // variable
        str_right_var1 = ST_parser::parse(stmt->r_exp);

        if (left_var->get_str_type().compare(Var::TYPE_BOOL) == 0)
        {
            Bits_vector_1 *bv;
            if (is_bool(str_right_var1))
            {

                right_var1 = 0;
                bv = Bits_vector_1::get_instance(str_right_var1);
            }
            else
            {
                right_var1 = _vs0->contains_var(str_right_var1);
                if (right_var1 != 0)
                {
                    bv = _vs0->get_bool_value_by(right_var1);
                }
                else
                {
                    std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! unary_expression--bool" << std::endl;
                    exit(0);
                }
            }
            ret->set_var_value(left_var, (bool_value)_vs0->get_bool_value_by(left_var)->op_union(bv));

        }
        /* need to be tested*/
        else if (left_var->get_str_type().compare(Var::TYPE_BYTE) == 0)
        {

        }
        else if (left_var->get_str_type().compare(Var::TYPE_INT) == 0)
        {
            int_value si;
            if (is_number(str_right_var1))
            {
                right_var1 = 0;
                si = Strided_interval::get_singleton_set(to_number(str_right_var1));
            }
            else
            {
                right_var1 = _vs0->contains_var(str_right_var1);
                if (right_var1 != 0)
                {
                    si = _vs0->get_int_value_by(right_var1);
                }
                else
                {
                    std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! unary_expression--int" << std::endl;
                    exit(0);
                }
            }
            ret->set_var_value(left_var, _vs0->get_int_value_by(left_var)->op_union(si));
        }

    }


    return ret;
}


/**
* getters and setters
*/
std::string Assign_stmt_transfer::get_str_left_var()
{
    return str_left_var;
}

Var *Assign_stmt_transfer::get_left_var()
{
    return left_var;
}

std::string Assign_stmt_transfer::get_str_right_var1()
{
    return str_right_var1;
}

Var *Assign_stmt_transfer::get_right_var1()
{
    return right_var1;
}

std::string Assign_stmt_transfer::get_str_right_var2()
{
    return str_right_var2;
}

Var *Assign_stmt_transfer::get_right_var2()
{
    return right_var2;
}

std::string Assign_stmt_transfer::get_str_op()
{
    return str_op;
}

symbol_c *Assign_stmt_transfer::get_statement()
{
    return statement;
}


/**
* helpers - inherited methods
*/
bool Assign_stmt_transfer::equal(Abstract_value_set_transfer *_other)
{
    Assign_stmt_transfer *other = (Assign_stmt_transfer *)_other;

    return statement == other->get_statement();
}

std::ostream &Assign_stmt_transfer::print(std::ostream &_out)
{
    return _out << str_left_var << " <-- " << str_right_var1 << " " << str_op << " " << str_right_var2;
}


/**
* helpers - debug only
*/
std::string Assign_stmt_transfer::to_string()
{
    return (str_left_var + " <-- " + str_right_var1 + " " + str_op + " " + str_right_var2);
}
