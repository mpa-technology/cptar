#pragma once

#include <string>
#include <vector>
#include <stdexcept>

#include <libtar.h>

#include <cptar/TarException.hpp>

class Tar{


public:


    enum class OPEN_TYPE{
        NOPEN = -1,
        RDONLY = 00,
        WRONLY = 01
    };

    Tar();


    void open(const std::string &fileName);

    std::string readfile(const std::string &fileName);

    std::vector<std::string>fileList();


    ~Tar();

private:
    TAR* tar_;
    std::string fileName_;
    OPEN_TYPE openFlag_;

    void setFile_(const std::string & fileName);
    void seekBegin_();

    void verifyOpenRead_(){

        if(!tar_)
            throw TarException("Tar("+fileName_+") not open");
        if(openFlag_ != OPEN_TYPE::RDONLY)
            throw TarException("Tar("+fileName_+") not read mod");
    }



};
