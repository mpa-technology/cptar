#include <cptar/Tar.hpp>
#include <unistd.h>


Tar::Tar():tar_(nullptr),openFlag_(OPEN_TYPE::NOPEN){
}

void Tar::open(const std::string &fileName){

    openFlag_ = OPEN_TYPE::RDONLY;
    if(const int ret = tar_open(&tar_,fileName.c_str(), nullptr, static_cast<int>(OPEN_TYPE::RDONLY),0,0) ; ret != 0){
        throw TarException("error open file: "+fileName);
    }

}

std::string Tar::readfile(const std::string &fileName){

    verifyOpenRead_();

    seekBegin_();

    setFile_(fileName);

    char buffer[T_BLOCKSIZE];
    std::string res;

    const auto size = th_get_size(tar_);

    for ( unsigned i = 0; i <= size ; i += T_BLOCKSIZE) {
        auto n_buf = tar_block_read(tar_, buffer);
        if (n_buf == EOF) {
            break;
        }
        res += buffer;
    }



    return res;
}

std::vector<std::string> Tar::fileList(){

    verifyOpenRead_();

    seekBegin_();


    std::vector<std::string> result;

    while (th_read(tar_) == 0) {
        const auto filename = th_get_pathname(tar_);


        result.push_back(filename);

        //FIXME:this
        if (TH_ISREG(tar_) && (tar_skip_regfile(tar_) != 0)) {
            continue;
        }



    }

    return result;
}

Tar::~Tar(){
    if(tar_ != nullptr)
        tar_close(tar_);
}

void Tar::setFile_(const std::string &fileName){

    while (th_read(tar_) == 0) {
        const auto filename = th_get_pathname(tar_);


        if(fileName == filename)
            return;

        //FIXME:this
        if (TH_ISREG(tar_) && (tar_skip_regfile(tar_) != 0)) {
            continue;
        }



    }
    throw  std::runtime_error("file not foidn");
}

void Tar::seekBegin_(){
    auto hendel = tar_fd(tar_);
    lseek(hendel, 0, SEEK_SET);
}
