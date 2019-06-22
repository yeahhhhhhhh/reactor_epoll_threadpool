#ifndef __UTILS__
#define __UTILS__

class Utils
{
private:
    /* data */
public:
    static void die(const char *msg);
    static int send(int fd, char *buf, size_t len);
    static int recv(int fd, char *buf, size_t len);
};


#endif // __UTILS__