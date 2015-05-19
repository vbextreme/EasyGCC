#include "easygcc.h"

static VOID gcc_cmd(CHAR* cmd, INT32 argc, CHAR** argv)
{
	strcpy(cmd,GCC_NAME);
	
	INT32 i;
	for ( i = 1; i < argc; ++i)
	{
		strcat(cmd,argv[i]);
		strcat(cmd," ");
	}
}

INT32 main(INT32 argc, CHAR** argv )
{
	OPZG o;
	
	setting_load(&o);
	token_load(&o);
	
	czed_sep(&o);
	
	CHAR cmd[2048];
		gcc_cmd(cmd, argc, argv);

	PIPE p;
		pro_pipe(&p);
	
	pro_bash(cmd, &p, PRO_PIPE_RED_ERR);

	while ( (fgets(cmd,2048,p.finp)) )
		czed_parse(&o,cmd);
		//czed_chkcolor(&o, cmd);

	czed_sep(&o);
	
	pro_pipe_close(&p);
	return 0;
}
