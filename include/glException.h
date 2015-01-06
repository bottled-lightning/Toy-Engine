#ifndef INCLUDE_GLEXCEPTION_H_
#define INCLUDE_GLEXCEPTION_H_

#include <exception>

// Stupid Visual C++
#ifndef _MSC_VER
#define NOEXCEPT noexcept
#else
#define NOEXCEPT
#endif

class glException : public std::exception {
public:
    glException(const char *what) : _what(what) { }
    virtual const char *what() const NOEXCEPT override { return _what; }
    virtual ~glException() { }
private:
    const char *_what;
};

#endif
