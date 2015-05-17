#include "easygcc.h"

VOID czed_sep(OPZG* o)
{
	if ( !o->sep ) return;
	
	UINT32 r,c;
		con_getmaxrc(&r,&c);
	
	con_setcolor(o->bk.div,o->fn.div);
	
	while ( c-- )
		putchar('-');
	putchar('\n');
	
	con_setcolor(o->bk.normal,o->fn.normal);
}

static VOID czed_pcolor(OPZG* o, CHAR* c)
{
	CHAR* f = c;
	CHAR nwo[1024];
	
	///filename
	f = strchr(c,':');
		if ( !f ) {printf("!!!ERROR EASYGCC fname[%s]!!!\n",c);return;}
	strncpy(nwo,c,f - c);
	nwo[f-c] = '\0';
	con_setcolor(o->bk.fname,o->fn.fname);
	printf("%s",nwo);
	con_setcolor(o->bk.normal,o->fn.normal);
	printf(":");
	
	/// in function
	c = f + 1;
	if ( strstr(c,"In function") )
	{
		con_setcolor(o->bk.infunction,o->fn.infunction);
		printf("%s",c);
		return;
	}
	else if ( !strncmp(c," error",6) )
	{
		con_setcolor(o->bk.error,o->fn.error);
		printf("%s",c);
		return;
	}
	
	///rc
	f = strchr(c,':');
		if ( !f ) {printf("!!!ERROR EASYGCC rc0!!!\n");return;}
	++f;
	f = strchr(f,':');
		if ( !f ) {printf("!!!ERROR EASYGCC rc1!!!\n");return;}
	strncpy(nwo,c,f - c);
	nwo[f-c] = '\0';
	con_setcolor(o->bk.rc,o->fn.rc);
	printf("%s",nwo);
	con_setcolor(o->bk.normal,o->fn.normal);
	printf(":");
	
	///type msg
	c = f + 1;
	if ( strstr(c,"error") )
	{
		con_setcolor(o->bk.error,o->fn.error);
		printf("%s",c);
	}
	else if ( strstr(c,"warning") )
	{
		con_setcolor(o->bk.warning,o->fn.warning);
		printf("%s",c);
	}
	else if ( strstr(c,"note") )
	{
		con_setcolor(o->bk.note,o->fn.note);
		printf("%s",c);
	}
	else
	{
		printf("!!!EASY GCC COMANDO INATTESO \"%s\"!!!\n",c);
	}
}

VOID czed_chkcolor(OPZG* o, CHAR* s)
{
	if ( strstr(s,"error") || strstr(s,"warning") || strstr(s,"In function") || strstr(s,"note") )
	{
		if ( strchr(s,':') )
		{
			czed_pcolor(o, s);
			return;
		}
	}

	con_setcolor(o->bk.normal, o->fn.normal);
	printf("%s",s);
}
