#ifndef ADASTRA_EXCEPTION_HPP
#define ADASTRA_EXCEPTION_HPP

#include <exception>
#include <string>
#include <sstream>
#include <string_view>

enum class ErrorCode
{
    UndefinedError,
    InvalidInput,
    NotFound,
    OperationFailed
};

class BaseException : public std::exception
{
public:
    explicit BaseException(std::string_view message, ErrorCode code = ErrorCode::UndefinedError) noexcept
        : message_(std::string(message)), code_(code) {}

    virtual const char *what() const noexcept override
    {
        return message_.c_str();
    }

    ErrorCode code() const noexcept
    {
        return code_;
    }

protected:
    std::string message_;
    ErrorCode code_;
};

#define ADASTRA_EXCEPTION(ExceptionName, Message, Code)                     \
    class ExceptionName : public BaseException                              \
    {                                                                       \
    public:                                                                 \
        explicit ExceptionName(std::string_view message = Message) noexcept \
            : BaseException(message, Code) {}                               \
    };

#endif // ADASTRA_EXCEPTION_HPP
