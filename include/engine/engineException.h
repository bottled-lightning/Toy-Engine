#ifndef ENGINEEXCEPTION_H_
#define ENGINEEXCEPTION_H_

#include <exception>

// Stupid Visual C++
#ifndef _MSC_VER
#define NOEXCEPT noexcept
#else
#define NOEXCEPT
#endif

class engineException : public std::exception {
public:
    engineException(const char *what) : _what(what) { }
    virtual const char *what() const NOEXCEPT override { return _what; }
    virtual ~engineException() NOEXCEPT { }
private:
    const char *_what;
};

#endif
