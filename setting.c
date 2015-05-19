#include "easygcc.h"

static CHAR *colname[11] = { "div",
							 "infunction",
							 "error",
							 "warning",
							 "note",
							 "normal",
							 "fname",
							 "rc",
							 "idline",
							 "carret",
							 NULL
						   };

static VOID setting_map(INT32* colmap[], ICOL* c)
{
	colmap[0] = &c->div;
	colmap[1] = &c->infunction;
	colmap[2] = &c->error;
	colmap[3] = &c->warning;
	colmap[4] = &c->note;
	colmap[5] = &c->normal;
	colmap[6] = &c->fname;
	colmap[7] = &c->rc;
	colmap[8] = &c->idline;
	colmap[9] = &c->carret;
	colmap[10] = NULL;
}

VOID setting_save(OPZG* o)
{
	CHAR ph[1024];
		sprintf(ph,"%s/%s",pht_homedir(),DIR_SETTING);
		
	if ( !ino_exist(ph) )
	{
		prv_maskreset();
		dir_new(ph,0755);
	}
	
	sprintf(ph,"%s/%s",pht_homedir(),FILE_SETTING);
	FILE* f = fopen(ph,"w");
		if ( !f ) return;
	
	cfg_write("sep",(o->sep)?"true":"false",f);
	cfg_write("fill",(o->fill)?"true":"false",f);
	
	CHAR n[512];
	CHAR v[512];
	
	CHAR** cn = colname;
	INT32* ofc = &o->fn.div;
	INT32* bfc = &o->bk.div;
	
	while ( *cn )
	{
		sprintf(n, "%s%s", NAME_FCOL, *cn);
		sprintf(v, "%d", *ofc);
		cfg_write(n,v,f);
		sprintf(n, "%s%s", NAME_BCOL, *cn);
		sprintf(v, "%d", *bfc);
		cfg_write(n,v,f);
		++cn;
		++ofc;
		++bfc;
	}
	
	fclose(f);
}

VOID setting_load(OPZG* o)
{
	o->sep = TRUE;
	o->fill = FALSE;
	o->fn.div = CON_COLOR_WHYTE;
	o->fn.error = CON_COLOR_RED;
	o->fn.infunction = CON_COLOR_LBLUE;
	o->fn.normal = 0;
	o->fn.note = CON_COLOR_LRED;
	o->fn.warning = CON_COLOR_LYELLOW;
	o->fn.fname = CON_COLOR_LBLUE;
	o->fn.rc = CON_COLOR_WHYTE;
	o->fn.idline = CON_COLOR_LGREEN;
	o->fn.carret = CON_COLOR_BLUE;
	o->bk.div = 0;
	o->bk.error = 0;
	o->bk.fname = 0;
	o->bk.infunction = 0;
	o->bk.normal = 0;
	o->bk.note = 0;
	o->bk.rc = 0;
	o->bk.warning = 0;
	o->bk.idline = 0;
	o->bk.carret = 0;
	
	CHAR ph[1024];
		sprintf(ph, "%s/%s", pht_homedir(), FILE_SETTING);
		
	FILE* f = fopen(ph,"r");
		if ( !f ) {setting_save(o); return;}
	
	CHAR n[512];
	CHAR v[512];
	INT32 *fcmap[9];
	INT32 *bcmap[9];
	INT32 fcl = strlen(NAME_FCOL);
	INT32 bcl = strlen(NAME_BCOL);
	INT32 i;
	
	setting_map(fcmap,&o->fn);
	setting_map(bcmap,&o->bk);
	
	while ( cfg_read(n,v,f) )
	{
		if ( !strncmp(n,NAME_FCOL,fcl) )
		{
			for ( i = 0; i < 9; ++i)
			{
				if ( !strcmp(&n[fcl],colname[i]) )
				{
					*fcmap[i] = atoi(v);
					break;
				}
			}
		}
		else if ( !strncmp(n,NAME_BCOL,bcl) )
		{
			for ( i = 0; i < 9; ++i)
			{
				if ( !strcmp(&n[bcl],colname[i]) )
				{
					*bcmap[i] = atoi(v);
					break;
				}
			}
		}
		else if ( !strcmp(n,"sep") )
		{
			o->sep = (!strcmp(v,"true"))? TRUE : FALSE;
		}
		else if ( !strcmp(n,"fill") )
		{
			o->fill = (!strcmp(v,"true"))? TRUE : FALSE;
		}
	}
	
	fclose(f);
}

static VOID token_save()
{
	CHAR ph[1024];
		sprintf(ph, "%s/%s", pht_homedir(), FILE_TOKEN);
		
	FILE* f = fopen(ph,"w");
		if ( !f ) return;
	
	cfg_write("int","32",f);
	cfg_write("short","32",f);
	cfg_write("char","32",f);
	cfg_write("double","32",f);
	cfg_write("float","32",f);
	cfg_write("long","32",f);
	cfg_write("struct","32",f);
	cfg_write("static","32",f);
	cfg_write("void","32",f);
	cfg_write("if","97",f);
	cfg_write("for","97",f);
	cfg_write("while","97",f);
	cfg_write("do","97",f);
	cfg_write("return","97",f);
	
	fclose(f);
}

static TOKEN* token_new(CHAR* name, INT32 val)
{
	TOKEN* tk = malloc(sizeof(TOKEN));
	strcpy(tk->name,name);
	tk->val = val;
	return tk;
}

VOID token_load(OPZG* o)
{
	lhs_init(&o->tk,HASH_SIZE);
	
	CHAR ph[1024];
		sprintf(ph, "%s/%s", pht_homedir(), FILE_TOKEN);
		
	FILE* f = fopen(ph,"r");
		if ( !f ) token_save();
	if ( !(f=fopen(ph,"r")) ) return;
	
	CHAR n[512];
	CHAR v[512];
	
	while ( cfg_read(n,v,f) )
	{
		ELEMENT* e = element_new(0,token_new(n,atoi(v)),TRUE,NULL);
		lhs_add(&o->tk,mth_hash(n,strlen(n),HASH_SIZE),e);
	}
	
	fclose(f);
}
