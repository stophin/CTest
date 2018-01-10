/* Module name */
%module NanoJNI

%{
/* POSIX system API */
#include <unistd.h>

#include <src\CTest.c>
#include <src\MultiLink.c>
%}

/* uid_t */
typedef unsigned int uid_t;

/* Wrap getuid */
extern uid_t getuid(void);

%include <src\CTest.h>
%include <src\MultiLink.h>
