
#ifndef HANDLEBARS_HELPERS_H
#define HANDLEBARS_HELPERS_H

#include "handlebars.h"

#ifdef	__cplusplus
extern "C" {
#endif

struct handlebars_stack;
struct handlebars_value;
struct handlebars_vm;

struct handlebars_options {
    struct handlebars_vm * vm;
    long inverse;
    long program;
    struct handlebars_string * name;
    struct handlebars_stack * params;
    struct handlebars_value * scope;
    struct handlebars_value * data;
    struct handlebars_value * hash;
};

typedef struct handlebars_value * (*handlebars_helper_func)(struct handlebars_options * options);

void handlebars_options_deinit(struct handlebars_options * options);
const char ** handlebars_builtins_names(void) HBSARN;
handlebars_helper_func * handlebars_builtins();
handlebars_helper_func handlebars_builtins_find(const char * str, unsigned int len);

struct handlebars_value * handlebars_builtin_block_helper_missing(struct handlebars_options * options) HBSARN;
struct handlebars_value * handlebars_builtin_each(struct handlebars_options * options) HBSARN;
struct handlebars_value * handlebars_builtin_helper_missing(struct handlebars_options * options) HBSARN;
struct handlebars_value * handlebars_builtin_lookup(struct handlebars_options * options) HBSARN;
struct handlebars_value * handlebars_builtin_log(struct handlebars_options * options) HBSARN;
struct handlebars_value * handlebars_builtin_if(struct handlebars_options * options) HBSARN;
struct handlebars_value * handlebars_builtin_unless(struct handlebars_options * options) HBSARN;
struct handlebars_value * handlebars_builtin_with(struct handlebars_options * options) HBSARN;

#ifdef	__cplusplus
}
#endif

#endif
