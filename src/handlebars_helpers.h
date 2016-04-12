
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
    struct handlebars_value * scope;
    struct handlebars_value * data;
    struct handlebars_value * hash;
};

typedef struct handlebars_value * (*handlebars_helper_func)(
    int argc,
    struct handlebars_value * argv[],
    struct handlebars_options * options
);

#define HANDLEBARS_HELPER_ARGS int argc, struct handlebars_value * argv[], struct handlebars_options * options

void handlebars_options_deinit(struct handlebars_options * options) HBS_ATTR_NONNULL_ALL;

/**
 * @brief Get a NULL-terminated array of the names of all built-in helpers
 * @return The array
 */
const char ** handlebars_builtins_names(void) HBS_ATTR_RETURNS_NONNULL;

/**
 * @brief Get a NULL-terminated array of all built-in helper functions
 * @return The array
 */
handlebars_helper_func * handlebars_builtins(void) HBS_ATTR_RETURNS_NONNULL;

/**
 * @brief Get a built-in helper by name
 * @param[in] str
 * @param[in] len
 * @return The helper function pointer
 */
handlebars_helper_func handlebars_builtins_find(const char * str, unsigned int len) HBS_ATTR_NONNULL_ALL;

struct handlebars_value * handlebars_builtin_block_helper_missing(HANDLEBARS_HELPER_ARGS) HBS_ATTR_NONNULL_ALL HBS_ATTR_RETURNS_NONNULL;
struct handlebars_value * handlebars_builtin_each(HANDLEBARS_HELPER_ARGS) HBS_ATTR_NONNULL_ALL HBS_ATTR_RETURNS_NONNULL;
struct handlebars_value * handlebars_builtin_helper_missing(HANDLEBARS_HELPER_ARGS) HBS_ATTR_NONNULL_ALL HBS_ATTR_RETURNS_NONNULL;
struct handlebars_value * handlebars_builtin_lookup(HANDLEBARS_HELPER_ARGS) HBS_ATTR_NONNULL_ALL HBS_ATTR_RETURNS_NONNULL;
struct handlebars_value * handlebars_builtin_log(HANDLEBARS_HELPER_ARGS) HBS_ATTR_NONNULL_ALL HBS_ATTR_RETURNS_NONNULL;
struct handlebars_value * handlebars_builtin_if(HANDLEBARS_HELPER_ARGS) HBS_ATTR_NONNULL_ALL HBS_ATTR_RETURNS_NONNULL;
struct handlebars_value * handlebars_builtin_unless(HANDLEBARS_HELPER_ARGS) HBS_ATTR_NONNULL_ALL HBS_ATTR_RETURNS_NONNULL;
struct handlebars_value * handlebars_builtin_with(HANDLEBARS_HELPER_ARGS) HBS_ATTR_NONNULL_ALL HBS_ATTR_RETURNS_NONNULL;

#ifdef	__cplusplus
}
#endif

#endif
