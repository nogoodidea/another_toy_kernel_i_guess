// header guard
#ifndef PANIC_H
#define PANIC_H


#define PANIC(text) _panic(text,__LINE__,__FILE__)


__attribute__((noreturn)) void _panic(const char *text,int line,const char *file);

#endif //PANIC_H
