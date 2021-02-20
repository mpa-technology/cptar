#include <cptar/TarException.hpp>


TarException::TarException(const std::string &msg):msg_(msg){}

const char *TarException::what()const noexcept{
    return msg_.c_str();
}
