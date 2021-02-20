#pragma once
#include <exception>
#include <string>

class TarException : public std::exception{

public:


    TarException(const std::string &msg);


    virtual const char *what()const noexcept;


private:
     std::string msg_;

};

