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


    void setFile(const std::string& fileName){
        setFile_(fileName);
    }


    std::string currentFile() const{
        return currentFile_;
    }

    std::string readFileAll(const std::string &fileName);

    std::string readBlock (size_t& BlockSize){

        char buffer[T_BLOCKSIZE];
        std::string res;

        const auto size = th_get_size(tar_);

        for ( unsigned i = 0; i <= size-BlockSize ; i += T_BLOCKSIZE) {
            auto n_buf = tar_block_read(tar_, buffer);
            if (n_buf == EOF) {
                break;
            }
            res += buffer;
        }



        return res;


    }


    std::vector<std::string>fileList();

    ~Tar();

private:

    TAR* tar_;
    std::string fileName_;
    std::string currentFile_;
    OPEN_TYPE openFlag_;

    void setFile_(const std::string & fileName);
    void seekBegin_();

    void verifyOpenRead_();



};
