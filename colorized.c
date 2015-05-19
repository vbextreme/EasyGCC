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


static VOID czed_colorized(OPZG* o, CHAR* s, INT32 mode)
{

	con_setcolor(o->bk.fname,o->fn.fname);
	while ( *s && *s != ':' ) putchar(*s++);

	con_setcolor(o->bk.normal,o->fn.normal);
	putchar(*s++);
	
	if ( mode != 2 )
	{
		con_setcolor(o->bk.idline,o->fn.idline);
		while ( *s && *s != ':' ) putchar(*s++);
		putchar(*s++);
		while ( *s && *s != ':' ) putchar(*s++);
		
		con_setcolor(o->bk.normal,o->fn.normal);
		putchar(*s++);
	}
			
	
	switch ( mode )
	{
		case 0:	con_setcolor(o->bk.error,o->fn.error); break;
		case 1:	con_setcolor(o->bk.warning,o->fn.warning); break;
		case 2:	con_setcolor(o->bk.infunction,o->fn.infunction); break;
		case 3:	con_setcolor(o->bk.note,o->fn.note); break;
	}

	if ( o->fill )
	{
		while ( *s ) putchar(*s++);
		con_setcolor(0,0);
		return;
	}
	
	while ( *s && *s != ':' ) putchar(*s++);

	con_setcolor(o->bk.normal,o->fn.normal);
	putchar(*s++);
	
	con_setcolor(o->bk.rc,o->fn.rc);
	while ( *s ) putchar(*s++);

	con_setcolor(0,0);
}

static BOOL token_find(INT32 typea, TOKEN* s, INT32 typeb, CHAR* val)
{
	return ( !strncmp(s->name,val,typeb) ) ? TRUE : FALSE;
}

static VOID czed_hcol(OPZG* o, CHAR* s)
{
	BOOL bks = TRUE;
	CHAR* entk;
	INT32 l;
	
	while ( *s )
	{
		while (*s && (*s == ' ' || *s == '\t' || *s == '\n' )) putchar(*s++);
		
		if ( bks )
		{
			if ( *s == '^' ) 
			{
				con_setcolor(o->bk.carret,o->fn.carret);
				putchar(*s++);
				con_setcolor(o->bk.normal,o->fn.normal);
				bks = FALSE;
				continue;
			}
			else if (  *s != ' ' && *s != '\t' )	
				bks = FALSE;
			else if ( *s != '\n' )
				bks = TRUE;
		}
		
		entk = str_movetos(s," \t,;.(){}[]\n");
		l = entk - s;
		
		ELEMENT* e = lhs_find(&o->tk,mth_hash(s,l,HASH_SIZE),l,s,(CBKLSTFIND)token_find);
		if ( e )
			con_setcolor(0,((TOKEN*)(e->data))->val);
		
		while ( *s && s <= entk ) putchar(*s++);
		con_setcolor(o->bk.normal, o->fn.normal);
	}
}

VOID czed_parse(OPZG* o, CHAR* s)
{
	if ( !strchr(s,':') )
	{
		czed_hcol(o,s);
		con_setcolor(o->bk.normal, o->fn.normal);
		return;
	}
	
	if ( strstr(s,"error") ) 
		czed_colorized(o,s,0);
	else if ( strstr(s,"warning") )
		czed_colorized(o,s,1);
	else if ( strstr(s,"In function") )
		czed_colorized(o,s,2);
	else if ( strstr(s,"note") )
		czed_colorized(o,s,3);
	else
		czed_hcol(o,s);
	
	con_setcolor(o->bk.normal, o->fn.normal);
}
