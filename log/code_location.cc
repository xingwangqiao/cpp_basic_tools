#include "code_location.h"

namespace basic {
CodeLocation::CodeLocation(const char* file_name, int code_line)
                        : file_name_(file_name),
                          code_line_(code_line) { }

CodeLocation& CodeLocation::operator= (const CodeLocation& location) {
    if(this == &location)
        return *this;
    file_name_ = location.file_name_;
    code_line_ = location.code_line_;
    return *this;
}

CodeLocation& CodeLocation::operator= (CodeLocation&& location) {
    if(this == &location)
        return *this;
    file_name_ = location.file_name_;
    code_line_ = location.code_line_;
    return *this;
}

std::string CodeLocation::getFileName() const {
    return file_name_;
}

int CodeLocation::getCodeLine() const {
    return code_line_;
}
}