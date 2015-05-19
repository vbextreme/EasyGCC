#ifndef __EASYGCC_H__
#define __EASYGCC_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <easytype.h>
#include <easystring.h>
#include <easyfile.h>
#include <easyprocess.h>
#include <easyconsole.h>
#include <easymath.h>
#include <easylist.h>

#ifdef FAKE_GCC
	#define GCC_NAME "gcc.fake "
#else
	#define GCC_NAME "gcc "
#endif

#define NAME_FCOL    "fncol_"
#define NAME_BCOL    "bkcol_"
#define DIR_SETTING  "/.config/easygcc"
#define FILE_SETTING DIR_SETTING "/setting"
#define FILE_TOKEN   DIR_SETTING "/token"
#define HASH_SIZE    512

typedef struct _TOKEN
{
	CHAR name[512];
	INT32 val;
}TOKEN;

typedef struct _ICOL
{
	INT32 div;
	INT32 infunction;
	INT32 error;
	INT32 warning;
	INT32 note;
	INT32 normal;
	INT32 fname;
	INT32 rc;
	INT32 idline;
	INT32 carret;
}ICOL;

typedef struct _OPZG
{
	BOOL sep;
	BOOL fill;
	ICOL bk;
	ICOL fn;
	HASHL tk;
}OPZG;

VOID setting_save(OPZG* o);
VOID setting_load(OPZG* o);
VOID token_load(OPZG* o);

VOID czed_sep(OPZG* o);
VOID czed_parse(OPZG* o, CHAR* s);


#endif
