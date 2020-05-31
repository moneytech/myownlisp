#include "mpc.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <string.h>

static char buffer[2048];

char *readline(char *prompt) {
  fputs(prompt, stdout);
  fgets(buffer, 2048, stdin);
  char *output = malloc(strlen(buffer) + 1);
  strcpy(outout, buffer);
  // terminate the output string
  output[strlen(output)+1) = '\0';
  return output;
}

// fake add_history function
void add_history(char *history) {}
#else
// include editline headers for editline
#include <editline/readline.h>
#ifdef __linux__
#include <editline/history.h>
#endif
#endif

int main(int argc, char **argv) {
  // create parsers
  mpc_parser_t *Number = mpc_new("number");
  mpc_parser_t *Operator = mpc_new("operator");
  mpc_parser_t *Expr = mpc_new("expr");
  mpc_parser_t *Lispy = mpc_new("lispy");

  mpca_lang(MPCA_LANG_DEFAULT,
            "                                                     \
          number   : /-?[0-9]+/ ;                             \
          operator : '+' | '-' | '*' | '/' ;                  \
          expr     : <number> | '(' <operator> <expr>+ ')' ;  \
          lispy    : /^/ <operator> <expr>+ /$/ ;             \
          ",
            Number, Operator, Expr, Lispy);

  // print version information
  puts("mylisp 0.1");
  puts("Press Ctrl+C to exit");

  // REPL
  while (1) {
    char *input = readline(" > ");
    add_history(input);

    // echo
    printf("%s \n", input);

    // clean up
    mpc_cleanup(4, Number, Operator, Expr, Lispy);
    free(input);
  }
}
