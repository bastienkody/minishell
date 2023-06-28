/* -------------------------------------------------------
   The grammar symbols
   ------------------------------------------------------- */

%token	WORD
%token	subcommand

%token	and	or
/*	'&&'	'||'	*/

%token	less	great	dgreat	dless
/*	'<'	'>'	'>>'	'<<' */

%token	pipe
/*	'|'	*/


/* -------------------------------------------------------
   The Grammar
   ------------------------------------------------------- */

%start complete_command
%%
complete_command	:	logical_expression
			|	pipeline
			;
logical_expression	:	pipeline or pipeline
			|	pipeline and pipeline
			;
pipeline		:	simple_command
			|	subcommand
			|	pipeline pipe simple_command
			;
simple_command		:	cmd_prefix cmd_name cmd_suffix
			|	cmd_prefix cmd_name
			|	cmd_name cmd_suffix
			|	cmd_name
			|	cmd_prefix
			;
cmd_name		:	WORD
			;
cmd_prefix		:	redirection
			|	cmd_prefix redirection
			;
cmd_suffix		:	redirection
			|	cmd_suffix redirection
			|	WORD
			|	cmd_suffix WORD
			;
redirection		:	less	filename
			|	great	filename
			|	dgreat	filename
			|	dless	filename
			;
filename		:	WORD
			;


