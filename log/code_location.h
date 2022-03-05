#pragma once
#include <string>
namespace basic {
class CodeLocation {
public:
    ~CodeLocation() = default;
    CodeLocation() = delete;

    CodeLocation(const char* file_name, int code_line);

    CodeLocation(const CodeLocation& location) = default;
    CodeLocation(CodeLocation&& location) = default;

    CodeLocation& operator= (const CodeLocation& location);
    CodeLocation& operator= (CodeLocation&& location);

    std::string getFileName() const;
    int getCodeLine() const;

private:
    std::string file_name_;
    int code_line_;
};

// define macro to record current source location
#ifdef WIN32
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

#define CODE_FROM_HERE \
    ::basic::CodeLocation(__FILENAME__, __LINE__)
}