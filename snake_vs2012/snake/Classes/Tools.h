#ifndef TOOLS_HPP__
#define TOOLS_HPP__
#include "iconv\iconv.h"
#include <string.h>
#include <stdlib.h>
#include <string>
#include "cocos2d.h"
#include <vector>
using namespace std;
using namespace cocos2d;

class Tools
{
public:
	static int code_convert(const char *from_charset, const char *to_charset, const char *inbuf, size_t inlen, char *outbuf, size_t outlen);
	static string u2a(const char *inbuf);
	static string a2u(const char *inbuf);
};

#endif