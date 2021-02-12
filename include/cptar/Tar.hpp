#pragma once

#include <string>
#include <vector>
#include <stdexcept>

#include <libtar.h>


class Tar{


public:


    enum class OEPN_TYPE{
        RDONLY = 00,
        WRONLY = 01
    };

    Tar();


    void open(const std::string &fileName);

    std::string readfile(const std::string fileName);

    std::vector<std::string>fileList();


    ~Tar();

private:
    TAR* tar_;


    void setFile_(const std::string & fileName);
    void seekBegin_();

};
