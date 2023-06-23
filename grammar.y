/* -------------------------------------------------------
   The grammar symbols
   ------------------------------------------------------- */

%token	WORD
%token	compound_command

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
program			:	pipeline
			|	command
			|	redirection
			|	logical_expression
			|	compound_command		
			;
or_expression		:	pipeline or pipeline
			|	pipeline or command
			|	pipeline or redirection
			|	pipeline or compound_command
			|	command or pipeline
			|	command or command
			|	command or redirection
			|	command or compound_command
			|	redirection or pipeline
			|	redirection or command
			|	redirection or redirection
			|	redirection or compound_command
			|	compound_command or pipeline
			|	compound_command or command
			|	compound_command or redirection
			|	compound_command or compound_command
			;
or_expression		:	pipeline and pipeline
			|	pipeline and command
			|	pipeline and redirection
			|	pipeline and compound_command
			|	command and pipeline
			|	command and command
			|	command and redirection
			|	command and compound_command
			|	redirection and pipeline
			|	redirection and command
			|	redirection and redirection
			|	redirection oandr compound_command
			|	compound_command and pipeline
			|	compound_command and command
			|	compound_command and redirection
			|	compound_command and compound_command
			;
pipeline		:	command pipe command
			|	pipeline pipe command
			;
command			:	cmd_prefix cmd_name cmd_suffix
			|	cmd_prefix cmd_name
			|	cmd_name cmd_suffix
			|	cmd_name	
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
			;
here_doc		:	dless	here_end
			;
here_end		:	WORD
			;
filename		:	WORD
			;


