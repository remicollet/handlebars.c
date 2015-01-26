
#ifndef HANDLEBARS_TOKEN_PRINTER_H
#define HANDLEBARS_TOKEN_PRINTER_H

#define HANDLEBARS_TOKEN_PRINT_NEWLINES 1

#ifdef	__cplusplus
extern "C" {
#endif

struct handlebars_token;
struct handlebars_token_list;

char * handlebars_token_print(struct handlebars_token * token, int flags);

char * handlebars_token_list_print(struct handlebars_token_list * list, int flags);

#ifdef	__cplusplus
}
#endif

#endif
