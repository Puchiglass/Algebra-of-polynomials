#ifndef EQ_EXCEPTION_H_
#define EQ_EXCEPTION_H_

#include <string>

#define MAX_COMMENT_LEN 256

enum error_codes
{
    k_NO_ERROR,
    k_NEGATIVE_VALUE,
    k_OVERFLOW,
    k_OUT_OF_MEMORY,
    k_NOT_FOUND,
    k_EMPTY,
    k_INCORRECT_INDEX,
    k_WRONG_OPERATION_PLACEMENT,
    k_WRONG_BRACKETS_QUANTITY,
    k_INCORRECT_OPERATION,
    k_CALCULATE_EMPTY_EXPRESSION,
    k_FILE_SYSTEM_ERROR,
    k_USING_RESERVED_NAME,
    k_USING_PUNCTUATION_MARKS,
    k_UNDEFINED_EXCEPTION,
};
class EqException
{
private:
    void operator=(const EqException& other) = delete;

    // code of error
    error_codes error;
    const std::string k_set_comment[15] = { "NO ERROR", "NEGATIVE VALUE", "OVERFLOW", "OUT OF MEMORY", "NOT FOUND", "EMPTY", "INCORRECT_INDEX", "WRONG OPERATION PLACEMENT", "WRONG BRACKETS QUANTITY", "INCORRECT OPERATION", "CALCULATE EMPTY EXPRESSION", "FILE SYSTEM ERROR", "USING RESERVED NAME", "USING PUNCTUATION MARKS", "UNDEFINED EXCEPTION"};

public:
    // create exception using error_codes::<something>
    EqException(error_codes error_)
        : error(error_)
    {}
    EqException()
        : error(k_NO_ERROR)
    {}
    ~EqException() = default;

    inline const std::string& get_comment() const
    {
        return k_set_comment[error];
    }

    inline int get_error() const
    {
        return error;
    }

};


#endif // EQ_EXCEPTION_H
