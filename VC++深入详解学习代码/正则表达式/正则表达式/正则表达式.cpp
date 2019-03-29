// 正则表达式.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<regex>
#include<string.h>
#include<cstdio>


int _tmain(int argc, _TCHAR* argv[])
{
	regex_t re;
	regmatch_t subs[1024];
	char matched[1024];
	char src[1024] = "beginworldendtestbeginworkendtest";
	char pattern[1024] = "begin(.*?)end";

	int err = regcomp(&re, pattern, REG_EXTENDED);
	if (err) {
		printf("regex error");
		return 1;
	}

	const char *ptr = src;
	// 匹配所有模式字串
	while (strlen(ptr) > 0) {
		memset(subs, 0, sizeof(subs));
		err = regexec(&re, ptr, (size_t)1024, subs, 0);
		if (err == REG_NOMATCH) {
			break;
		}
		else if (err) {
			char errbuf[1024];
			regerror(err, &re, errbuf, sizeof(errbuf));
			printf("errbuf:%s\n", errbuf);
			break;
		}
		int len = subs[0].rm_eo - subs[0].rm_so;
		memcpy(matched, ptr + subs[0].rm_so, len);
		matched[len] = '\0';
		printf("match:%s\n", matched);
		ptr = ptr + subs[0].rm_so + len;
	}

	regfree(&re);

	return 0;
}

