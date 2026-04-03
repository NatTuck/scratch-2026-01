
#include <fcntl.h>
#include <string>
#include <unistd.h>

class File {
    int fd;

public:
    File(std::string path)
    {
        this->fd = open(path.c_str(), O_CREAT | O_TRUNC | O_WRONLY, 0644);
    }

    void put(std::string msg)
    {
        write(this->fd, msg.c_str(), msg.length());
    }

    ~File()
    {
        close(this->fd);
    }
};

int
main(int argc, char* argv[])
{
    File hello("hello.txt");
    hello.put("Hello, file");

    return 0;
}
