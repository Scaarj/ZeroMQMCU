#ifndef TOOLS_H
#define TOOLS_H

#if defined ARDUINO
#include <Arduino.h>
#elif (defined __linux__) || (defined _WIN32)
#include <iostream>
#include <cstring>
#include <cmath>
#endif

#ifdef ARDUINO
// Reload strcmp and sizeof for Arduino
// _sizeof now works for char strings correctly!
inline int strcmp(const char* s1, const char* s2);
#elif (defined __linux__) || (defined _WIN32)
inline int strcmp(const char* s1, const char* s2);
inline int _sizeof(char * const &ptr);
template <typename Key> inline int _sizeof(const Key &key);
#endif

inline bool equalKey(char * const &key1, char * const &key2);
template <typename Key> inline bool equalKey(const Key &key1, const Key &key2);
inline bool lessThanKey(char * const &key1, char * const &key2);
template <typename Key> inline bool lessThanKey(const Key &key1, const Key &key2);
inline int _sizeof(char * const &ptr);
template <typename Key> inline int _sizeof(const Key &key);

bool equalKey(char * const &key1, char * const &key2)
{
    if(strcmp(key1, key2) == 0) {
        return true;
    }
    else return false;
}

template <typename Key> inline bool equalKey(const Key &key1, const Key &key2)
{
    return key1 == key2;
}


bool lessThanKey(char * const &key1, char * const &key2)
{
    if(strcmp(key1, key2) < 0) {
        return true;
    }
    else return false;
}

template <typename Key> inline bool lessThanKey(const Key &key1, const Key &key2)
{
    return key1 < key2;
}

inline int _sizeof(char * const &key)
{
    return strlen(key);
}

template <typename Key> inline int _sizeof(const Key &key)
{
    return sizeof(key);
}

#ifdef ARDUINO
int strcmp(const char* s1, const char* s2)
{
    while(*s1 == *s2)
    {
        if(*s1 == 0 && *s2 == 0)
            return 0;

        s1++;
        s2++;
    }
    return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}
#endif


#endif // TOOLS_H
