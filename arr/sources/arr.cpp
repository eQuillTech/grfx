// arrays - P. Ahrenkiel

#include "arr.hpp"

namespace arr {

int err = 0;

//
int check_err()
{
    int res = err;
    err = 0;
    return res;
}

//
void clear_err() { err = 0; }

} // namespace arr
