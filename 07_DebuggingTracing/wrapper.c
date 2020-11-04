#define _GNU_SOURCE

#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

typedef int (*some_type)(const char *pathname);


int unlink(const char *pathname)
{
    char forbidden_str[] = "FIX";
    if(strstr(pathname, forbidden_str)){
        errno = EPERM;
        return 1;
    } else {
        some_type real_unlink = (some_type)dlsym(RTLD_NEXT, 'unlink');
        return real_unlink(pathname);
    }
    
}
