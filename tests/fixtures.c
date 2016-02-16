
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <assert.h>
#include <ctype.h>

#include "handlebars_value.h"
#include "handlebars_vm.h"

#define CONTEXT options->vm->ctx
#define FIXTURE_FN(hash) static struct handlebars_value * fixture_ ## hash(struct handlebars_options * options)
#define FIXTURE_STRING(string) \
    struct handlebars_value * value = handlebars_value_ctor(CONTEXT); \
    handlebars_value_string(value, string); \
    return value;
#define FIXTURE_INTEGER(integer) \
    struct handlebars_value * value = handlebars_value_ctor(CONTEXT); \
    handlebars_value_integer(value, integer); \
    return value;

FIXTURE_FN(20974934)
{
    // "function (arg) { return typeof arg; }"
    struct handlebars_value * arg = handlebars_stack_get(options->params, 0);
    if( arg->type == HANDLEBARS_VALUE_TYPE_NULL ) {
        handlebars_value_delref(arg);
        FIXTURE_STRING("undefined");
    } else {
        handlebars_value_delref(arg);
        FIXTURE_STRING("not undefined");
    }
}

FIXTURE_FN(49286285)
{
    struct handlebars_value * arg = handlebars_stack_get(options->params, 0);
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    char * r1 = handlebars_value_get_strval(arg);
    char * r2 = handlebars_talloc_strdup(result, "bar");
    handlebars_talloc_strdup_append(r2, r1);
    handlebars_value_string(result, r2);
    handlebars_value_delref(arg);
    return result;
}

FIXTURE_FN(126946175)
{
    // "function () {\n        return true;\n      }"
    struct handlebars_value * value = handlebars_value_ctor(CONTEXT);
    handlebars_value_boolean(value, 1);
    return value;
}

FIXTURE_FN(169151220)
{
    // "function () {\n        return 'LOL';\n      }"
    FIXTURE_STRING("LOL");
}

FIXTURE_FN(276040703)
{
    // "function () {\n      return 'Colors';\n    }"
    FIXTURE_STRING("Colors");
}

FIXTURE_FN(454102302)
{
    // "function (value) { return value + ''; }"
    // @todo implement undefined?
    struct handlebars_value * prefix = handlebars_stack_get(options->params, 0);
    assert(prefix->type == HANDLEBARS_VALUE_TYPE_NULL);
    const char * tmp = "undefined";
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, tmp);
    return result;
}

FIXTURE_FN(459219799)
{
    // "function (prefix, options) {\n        return '<a href=\"' + prefix + '\/' + this.url + '\">' + options.fn(this) + '<\/a>';\n    }"
    struct handlebars_value * prefix = handlebars_stack_get(options->params, 0);
    struct handlebars_value * url = handlebars_value_map_find(options->scope, "url");
    char * res = handlebars_vm_execute_program(options->vm, options->program, options->scope);
    char * tmp = handlebars_talloc_asprintf(
            options->vm,
            "<a href=\"%s/%s\">%s</a>",
            handlebars_value_get_strval(prefix),
            handlebars_value_get_strval(url),
            res
    );
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, tmp);

    handlebars_value_delref(prefix);
    handlebars_value_delref(url);
    handlebars_talloc_free(tmp);
    handlebars_talloc_free(res);
    return result;
}

FIXTURE_FN(461441956)
{
    // "function () {\n        return 'blah';\n      }"
    FIXTURE_STRING("blah");
}

FIXTURE_FN(464915369)
{
    // "function () {\n        return 'fail';\n      }"
    FIXTURE_STRING("fail");
}

FIXTURE_FN(471141295)
{
    // "function () {\n        return 'dude';\n      }"
    FIXTURE_STRING("dude");
}

static int value_for_510017722 = 1;
FIXTURE_FN(510017722)
{
    // "function (options) {\n          if( typeof value === 'undefined' ) { value = 1; } return options.fn({value: 'bar'}, {blockParams: options.fn.blockParams === 1 ? [value++, value++] : undefined});\n        }"
    struct handlebars_value * context = handlebars_value_from_json_string(CONTEXT, "{\"value\": \"bar\"}");
    struct handlebars_value * block_params = handlebars_value_ctor(CONTEXT);
    handlebars_value_array_init(block_params);
    struct handlebars_value * bp1 = handlebars_value_ctor(CONTEXT);
    struct handlebars_value * bp2 = handlebars_value_ctor(CONTEXT);
    handlebars_value_integer(bp1, value_for_510017722++);
    handlebars_value_integer(bp2, value_for_510017722++);
    handlebars_stack_push(block_params->v.stack, bp1);
    handlebars_stack_push(block_params->v.stack, bp2);
    char * tmp = handlebars_vm_execute_program_ex(options->vm, options->program, context, NULL, block_params);
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, tmp);

    handlebars_talloc_free(tmp);
    handlebars_value_delref(bp1);
    handlebars_value_delref(bp2);
    handlebars_value_delref(block_params);
    handlebars_value_delref(context);
    return result;
}

FIXTURE_FN(585442881)
{
    // "function (cruel, world, options) {\n        return options.fn({greeting: 'Goodbye', adj: cruel, noun: world});\n      }"
    struct handlebars_value * cruel = handlebars_stack_get(options->params, 0);
    struct handlebars_value * world = handlebars_stack_get(options->params, 1);
    struct handlebars_value * context = handlebars_value_ctor(CONTEXT);
    handlebars_value_map_init(context);
    struct handlebars_value * greeting = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(greeting, "Goodbye");
    handlebars_map_add(context->v.map, "greeting", greeting);
    handlebars_map_add(context->v.map, "adj", cruel);
    handlebars_map_add(context->v.map, "noun", world);
    char * tmp = handlebars_vm_execute_program(options->vm, options->program, context);
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, tmp);

    handlebars_talloc_free(tmp);
    handlebars_value_delref(greeting);
    handlebars_value_delref(context);
    handlebars_value_delref(cruel);
    handlebars_value_delref(world);
    return result;
}

FIXTURE_FN(620640779)
{
    // "function (times, times2) {\n      if (typeof times !== 'number') { times = 'NaN'; }\n      if (typeof times2 !== 'number') { times2 = 'NaN'; }\n      return 'Hello ' + times + ' ' + times2 + ' times';\n    }"
    struct handlebars_value * times = handlebars_stack_get(options->params, 0);
    struct handlebars_value * times2 = handlebars_stack_get(options->params, 1);
    // @todo this should be a float perhaps?
    /* if( times->type != HANDLEBARS_VALUE_TYPE_FLOAT || times->type != HANDLEBARS_VALUE_TYPE_INTEGER ) {
        handlebars_value_string(times, "NaN");
    }
    if( times2->type != HANDLEBARS_VALUE_TYPE_FLOAT || times2->type != HANDLEBARS_VALUE_TYPE_INTEGER ) {
        handlebars_value_string(times2, "NaN");
    } */
    char * tmp = handlebars_talloc_asprintf(
            options->vm,
            "Hello %s %s times",
            handlebars_value_get_strval(times),
            handlebars_value_get_strval(times2)
    );
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, tmp);
    handlebars_talloc_free(tmp);
    return result;
}

FIXTURE_FN(620828131)
{
    // "function (cruel, world) { return 'Goodbye ' + cruel + ' ' + world; }"
    struct handlebars_value * cruel = handlebars_stack_get(options->params, 0);
    struct handlebars_value * world = handlebars_stack_get(options->params, 1);

    char * tmp = handlebars_talloc_asprintf(
            options->vm,
            "Goodbye %s %s",
            handlebars_value_get_strval(cruel),
            handlebars_value_get_strval(world)
    );
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, tmp);
    handlebars_talloc_free(tmp);
    return result;
}

FIXTURE_FN(665715952)
{
    // "function () {}"
    return NULL;
}

FIXTURE_FN(662835958)
{
    // "function () { return {first: 'Alan', last: 'Johnson'}; }",
    struct handlebars_value * value = handlebars_value_from_json_string(CONTEXT, "{\"first\": \"Alan\", \"last\": \"Johnson\"}");
    handlebars_value_convert(value);
    return value;
}

FIXTURE_FN(690821881)
{
    // this one is actually a partial
    // "function partial(context) {\n      return context.name + ' (' + context.url + ') ';\n    }"
    struct handlebars_value * context = handlebars_stack_get(options->params, 0);
    struct handlebars_value * name = handlebars_value_map_find(context, "name");
    struct handlebars_value * url = handlebars_value_map_find(context, "url");
    char * tmp = handlebars_talloc_asprintf(
            options->vm,
            "%s (%s) ",
            handlebars_value_get_strval(name),
            handlebars_value_get_strval(url)
    );
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, tmp);
    handlebars_talloc_free(tmp);
    return result;
}

FIXTURE_FN(666457330)
{
    // "function (options) {\n          if (options.hash.print === true) {\n            return 'GOODBYE ' + options.hash.cruel + ' ' + options.fn(this);\n          } else if (options.hash.print === false) {\n            return 'NOT PRINTING';\n          } else {\n            return 'THIS SHOULD NOT HAPPEN';\n          }\n        }"
    struct handlebars_value * print = handlebars_value_map_find(options->hash, "print");
    if( print->type != HANDLEBARS_VALUE_TYPE_BOOLEAN ) {
        FIXTURE_STRING("THIS SHOULD NOT HAPPEND");
    } else if( handlebars_value_get_boolval(print) ) {
        struct handlebars_value * cruel = handlebars_value_map_find(options->hash, "cruel");
        char * res = handlebars_vm_execute_program(options->vm, options->program, options->scope);
        char * tmp = handlebars_talloc_asprintf(
                options->vm,
                "GOODBYE %s %s",
                handlebars_value_get_strval(cruel),
                res
        );
        handlebars_talloc_free(res);
        struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
        handlebars_value_string(result, tmp);
        handlebars_talloc_free(tmp);
        return result;
    } else {
        FIXTURE_STRING("NOT PRINTING");
    }
}

FIXTURE_FN(730081660)
{
    // "function (options) {\n          return 'GOODBYE ' + options.hash.cruel + ' ' + options.fn(this) + ' ' + options.hash.times + ' TIMES';\n        }"
    struct handlebars_value * cruel = handlebars_value_map_find(options->hash, "cruel");
    struct handlebars_value * times = handlebars_value_map_find(options->hash, "times");
    char * res = handlebars_vm_execute_program(options->vm, options->program, options->scope);
    char * tmp = handlebars_talloc_asprintf(
            options->vm,
            "GOODBYE %s %s %s TIMES",
            handlebars_value_get_strval(cruel),
            res,
            handlebars_value_get_strval(times)
    );
    handlebars_talloc_free(res);
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, tmp);
    handlebars_talloc_free(tmp);
    return result;
}

FIXTURE_FN(730672213)
{
    if( 0 == strcmp(options->name, "link_to") ) {
        struct handlebars_value * mesg = handlebars_stack_get(options->params, 0);
        char * tmp = handlebars_talloc_asprintf(
                options->vm,
                "<a>%s</a>",
                handlebars_value_get_strval(mesg)
        );
        struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
        handlebars_value_string(result, tmp);
        handlebars_talloc_free(tmp);
        result->flags |= HANDLEBARS_VALUE_FLAG_SAFE_STRING;
        return result;
    } else {
        return NULL;
    }
}

FIXTURE_FN(739773491)
{
    // "function (arg) {\n        return arg;\n      }"
    return handlebars_stack_get(options->params, 0);
}

FIXTURE_FN(748362646)
{
    // "function (options) { return '<a href=\"' + this.name + '\">' + options.fn(this) + '<\/a>'; }"
    struct handlebars_value * name = handlebars_value_map_find(options->scope, "name");
    char * res = handlebars_vm_execute_program(options->vm, options->program, options->scope);
    char * tmp = handlebars_talloc_asprintf(
            options->vm,
            "<a href=\"%s\">%s</a>",
            handlebars_value_get_strval(name),
            res
    );
    handlebars_talloc_free(res);
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, tmp);
    handlebars_talloc_free(tmp);
    return result;
}

FIXTURE_FN(788468697)
{
    assert(options->scope != NULL);
    assert(options->scope->type == HANDLEBARS_VALUE_TYPE_STRING);
    FIXTURE_INTEGER(strlen(options->scope->v.strval));
}

FIXTURE_FN(902433745)
{
    // "function () {\n          return 'foo';\n        }"
    FIXTURE_STRING("foo");
}

FIXTURE_FN(922226146)
{
    // "function (block) { return block.fn(''); }"
    struct handlebars_value * context = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(context, "");
    char * tmp = handlebars_vm_execute_program(options->vm, options->program, context);
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, tmp);
    handlebars_talloc_free(tmp);
    return result;
}

FIXTURE_FN(929767352)
{
    // "function (options) {\n        return options.data.adjective + ' world' + (this.exclaim ? '!' : '');\n      }"
    struct handlebars_value * adjective = handlebars_value_map_find(options->data, "adjective");
    struct handlebars_value * exclaim = handlebars_value_map_find(options->scope, "exclaim");
    char * ret = handlebars_talloc_asprintf(
            options->vm,
            "%s world%s",
            handlebars_value_get_strval(adjective),
            handlebars_value_is_empty(exclaim) ? "" : "!"
    );
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, ret);
    handlebars_talloc_free(ret);
    return result;
}

FIXTURE_FN(931412676)
{
    // "function (options) {\n            var frame = Handlebars.createFrame(options.data);\n            frame.depth = options.data.depth + 1;\n            return options.fn(this, {data: frame});\n          }"
    struct handlebars_value * frame = handlebars_value_ctor(CONTEXT);
    handlebars_value_map_init(frame);
    struct handlebars_value_iterator * it = handlebars_value_iterator_ctor(options->data);
    for( ; it->current; handlebars_value_iterator_next(it) ) {
        if( 0 == strcmp(it->key, "depth") ) {
            struct handlebars_value * tmp = handlebars_value_ctor(CONTEXT);
            handlebars_value_integer(tmp, handlebars_value_get_intval(it->current) + 1);
            handlebars_map_add(frame->v.map, it->key, tmp);
            handlebars_value_delref(tmp);
        } else {
            handlebars_map_add(frame->v.map, it->key, it->current);
        }
    }
    handlebars_map_update(frame->v.map, "_parent", options->data);
    char * res = handlebars_vm_execute_program_ex(options->vm, options->program, options->scope, frame, NULL);
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, res);
    handlebars_talloc_free(res);
    return result;
}

FIXTURE_FN(958795451)
{
    struct handlebars_value * truthiness = handlebars_value_map_find(options->scope, "truthiness");
    if( truthiness->type == HANDLEBARS_VALUE_TYPE_HELPER ) {
        return truthiness->v.helper(options);
    }
    return truthiness;
}

FIXTURE_FN(1211570580)
{
    // "function () {\n        return 'ran: ' + arguments[arguments.length - 1].name;\n      }"
    char * tmp = handlebars_talloc_asprintf(
            options->vm,
            "ran: %s",
            options->name
    );
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, tmp);
    handlebars_talloc_free(tmp);
    return result;
}

FIXTURE_FN(1091971719)
{
    // "function (options) {\n          if (options.name === 'link_to') {\n            return new Handlebars.SafeString('<a>winning<\/a>');\n          }\n        }"
    if( 0 == strcmp(options->name, "link_to") ) {
        char * tmp = handlebars_talloc_asprintf(
                options->vm,
                "<a>%s</a>",
                "winning"
        );
        struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
        handlebars_value_string(result, tmp);
        handlebars_talloc_free(tmp);
        result->flags |= HANDLEBARS_VALUE_FLAG_SAFE_STRING;
        return result;
    } else {
        return NULL;
    }
}

FIXTURE_FN(1041501180)
{
    // "function (a, b) {\n        return a + b;\n      }"
    struct handlebars_value * a = handlebars_stack_get(options->params, 0);
    struct handlebars_value * b = handlebars_stack_get(options->params, 1);
    char * tmp = handlebars_talloc_asprintf(
            options->vm,
            "%s%s",
            handlebars_value_get_strval(a),
            handlebars_value_get_strval(b)
    );
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, tmp);
    handlebars_talloc_free(tmp);
    return result;
}

FIXTURE_FN(1102272015)
{
    struct handlebars_value * print = handlebars_value_map_find(options->hash, "print");
    if( print->type != HANDLEBARS_VALUE_TYPE_BOOLEAN ) {
        FIXTURE_STRING("THIS SHOULD NOT HAPPEND");
    } else if( handlebars_value_get_boolval(print) ) {
        struct handlebars_value * cruel = handlebars_value_map_find(options->hash, "cruel");
        struct handlebars_value * world = handlebars_value_map_find(options->hash, "world");
        char * tmp = handlebars_talloc_asprintf(
                options->vm,
                "GOODBYE %s %s",
                handlebars_value_get_strval(cruel),
                handlebars_value_get_strval(world)
        );
        struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
        handlebars_value_string(result, tmp);
        handlebars_talloc_free(tmp);
        return result;
    } else {
        FIXTURE_STRING("NOT PRINTING");
    }
}

FIXTURE_FN(1198465479)
{
    // "function (noun, options) {\n        return options.data.adjective + ' ' + noun + (this.exclaim ? '!' : '');\n      }"
    struct handlebars_value * adjective = handlebars_value_map_find(options->data, "adjective");
    struct handlebars_value * noun = handlebars_stack_get(options->params, 0);
    struct handlebars_value * exclaim = handlebars_value_map_find(options->scope, "exclaim");
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    char * tmp = handlebars_talloc_asprintf(
            result,
            "%s %s%s",
            handlebars_value_get_strval(adjective),
            handlebars_value_get_strval(noun),
            (handlebars_value_get_boolval(exclaim) ? "!" : "")
    );
    handlebars_value_string(result, tmp);
    handlebars_talloc_free(tmp);
    return result;
}

FIXTURE_FN(1252527367)
{
    // "function () {\n        return 'winning';\n      }"
    FIXTURE_STRING("winning");
}

FIXTURE_FN(1283397100)
{
    // "function (options) {\n        return options.fn({exclaim: '?'});\n      }"
    struct handlebars_value * context = handlebars_value_from_json_string(CONTEXT, "{\"exclaim\": \"?\"}");
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    char * tmp = handlebars_vm_execute_program(options->vm, options->program, context);
    handlebars_value_string(result, tmp);
    handlebars_talloc_free(tmp);
    return result;
}

FIXTURE_FN(1341397520)
{
    // "function (options) {\n        return options.data && options.data.exclaim;\n      }"
    if( options->data ) {
        return handlebars_value_map_find(options->data, "exclaim");
    } else {
        return handlebars_value_ctor(CONTEXT);
    }
}

FIXTURE_FN(1582700088)
{
    struct handlebars_value * fun = handlebars_value_map_find(options->hash, "fun");
    char * tmp = handlebars_value_get_strval(fun);
    char * res = handlebars_talloc_asprintf(
            options->vm,
            "val is %s",
            tmp
    );
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, res);
    handlebars_talloc_free(res);
    return result;
}

FIXTURE_FN(1623791204)
{
    struct handlebars_value * noun = handlebars_value_map_find(options->hash, "noun");
    char * tmp = handlebars_value_get_strval(noun);
    char * res = handlebars_talloc_asprintf(
            options->vm,
            "Hello %s",
            !*tmp ? "undefined" : tmp
    );
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, res);
    handlebars_talloc_free(res);
    return result;
}

FIXTURE_FN(1644694756)
{
    // "function (x, y) {\n        return x === y;\n      }"
    struct handlebars_value * x = handlebars_stack_get(options->params, 0);
    struct handlebars_value * y = handlebars_stack_get(options->params, 1);
    bool ret = false;
    if( x->type != y->type ) {
        // nothing
    } else if( memcmp(&x->v, &y->v, sizeof(x->v)) ) {
        ret = true;
    } else if( x->type == HANDLEBARS_VALUE_TYPE_MAP ||
            x->type == HANDLEBARS_VALUE_TYPE_ARRAY ||
            y->type == HANDLEBARS_VALUE_TYPE_MAP ||
            y->type == HANDLEBARS_VALUE_TYPE_MAP ) {
        // nothing
    } else if( 0 == strcmp(handlebars_value_get_strval(x), handlebars_value_get_strval(y)) ) {
        ret = true;
    }
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_boolean(result, ret);
    return result;
}

FIXTURE_FN(1774917451)
{
    // "function (options) { return '<form>' + options.fn(this) + '<\/form>'; }"
    char * res = handlebars_vm_execute_program(options->vm, options->program, options->scope);
    char * tmp = handlebars_talloc_asprintf(
            options->vm,
            "<form>%s</form>",
            res
    );
    handlebars_talloc_free(res);
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, tmp);
    handlebars_talloc_free(tmp);
    return result;
}

FIXTURE_FN(1818365722)
{
    // "function (param) { return 'Hello ' + param; }"
    struct handlebars_value * param = handlebars_stack_get(options->params, 0);
    char * tmp = handlebars_talloc_asprintf(
            options->vm,
            "Hello %s",
            handlebars_value_get_strval(param)
    );
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, tmp);
    handlebars_talloc_free(tmp);
    return result;
}

FIXTURE_FN(1872958178)
{
    // "function (options) {\n        return options.fn(this);\n      }"
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    char * tmp = handlebars_vm_execute_program(options->vm, options->program, options->scope);
    handlebars_value_string(result, tmp);
    handlebars_talloc_free(tmp);
    return result;
}

FIXTURE_FN(1983911259)
{
    char * ret = handlebars_vm_execute_program(options->vm, options->program, options->scope);
    char * tmp = handlebars_talloc_asprintf(
            options->vm,
            "%s%s%s%s",
            ret,
            handlebars_value_get_strval(handlebars_stack_get(options->params, 0)),
            handlebars_value_get_strval(handlebars_stack_get(options->params, 1)),
            handlebars_value_get_strval(handlebars_stack_get(options->params, 2))
    );
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, tmp);
    handlebars_talloc_free(tmp);
    return result;
}

FIXTURE_FN(2084318034)
{
    // This is a dumb test
    // "function (_undefined, _null, options) {\n            return (_undefined === undefined) + ' ' + (_null === null) + ' ' + (typeof options);\n          }"
    struct handlebars_value * arg1 = handlebars_stack_get(options->params, 0);
    struct handlebars_value * arg2 = handlebars_stack_get(options->params, 1);
    char * res = handlebars_talloc_asprintf(options->vm, "%s %s %s",
                                            (arg1->type == HANDLEBARS_VALUE_TYPE_NULL ? "true" : "false"),
                                            (arg1->type == HANDLEBARS_VALUE_TYPE_NULL ? "true" : "false"),
                                            "object");
    struct handlebars_value * value = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(value, res);
    handlebars_talloc_free(res);
    return value;
}

FIXTURE_FN(2089689191)
{
    // "function link(options) {\n      return '<a href=\"\/people\/' + this.id + '\">' + options.fn(this) + '<\/a>';\n    }"
    struct handlebars_value * id = handlebars_value_map_find(options->scope, "id");
    char * res = handlebars_vm_execute_program(options->vm, options->program, options->scope);
    char * tmp = handlebars_talloc_asprintf(
            options->vm,
            "<a href=\"/people/%s\">%s</a>",
            handlebars_value_get_strval(id),
            res
    );
    handlebars_talloc_free(res);
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, tmp);
    handlebars_talloc_free(tmp);
    return result;
}

FIXTURE_FN(2096893161)
{
    // "function () {\n            return 'null!';\n          }"
    FIXTURE_STRING("null!");
}

FIXTURE_FN(2107645267)
{
    // "function (prefix) {\n      return '<a href=\"' + prefix + '\/' + this.url + '\">' + this.text + '<\/a>';\n    }"
    struct handlebars_value * prefix = handlebars_stack_get(options->params, 0);
    struct handlebars_value * url = handlebars_value_map_find(options->scope, "url");
    struct handlebars_value * text = handlebars_value_map_find(options->scope, "text");
    char * tmp = handlebars_talloc_asprintf(
            options->vm,
            "<a href=\"%s/%s\">%s</a>",
            handlebars_value_get_strval(prefix),
            handlebars_value_get_strval(url),
            handlebars_value_get_strval(text)
    );
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, tmp);
    handlebars_talloc_free(tmp);
    return result;
}

FIXTURE_FN(2182811123)
{
    // "function (val) {\n        return val + val;\n      }"
    struct handlebars_value * value = handlebars_stack_get(options->params, 0);
    char * tmp = handlebars_talloc_asprintf(
            options->vm,
            "%s%s",
            handlebars_value_get_strval(value),
            handlebars_value_get_strval(value)
    );
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, tmp);
    handlebars_talloc_free(tmp);
    return result;

}

FIXTURE_FN(2259424295)
{
    struct handlebars_value * value = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(value, "&'\\<>");
    value->flags |= HANDLEBARS_VALUE_FLAG_SAFE_STRING;
    return value;
}

FIXTURE_FN(2262633698)
{
    // "function (a, b) {\n        return a + '-' + b;\n      }"
    struct handlebars_value * a = handlebars_stack_get(options->params, 0);
    struct handlebars_value * b = handlebars_stack_get(options->params, 1);
    char * tmp = handlebars_talloc_asprintf(
            options->vm,
            "%s-%s",
            handlebars_value_get_strval(a),
            handlebars_value_get_strval(b)
    );
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, tmp);
    handlebars_talloc_free(tmp);
    return result;
}

FIXTURE_FN(2305563493)
{
    // "function () { return [{text: 'goodbye'}, {text: 'Goodbye'}, {text: 'GOODBYE'}]; }"
    struct handlebars_value * value = handlebars_value_from_json_string(CONTEXT, "[{\"text\": \"goodbye\"}, {\"text\": \"Goodbye\"}, {\"text\": \"GOODBYE\"}]");
    handlebars_value_convert(value);
    return value;
}

FIXTURE_FN(2327777290)
{
    // "function (block) { return block.inverse(''); }"
    struct handlebars_value * context = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(context, "");
    char * tmp = handlebars_vm_execute_program(options->vm, options->inverse, context);
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, tmp);
    handlebars_talloc_free(tmp);
    return result;
}

FIXTURE_FN(2439252451)
{
    struct handlebars_value * value = options->scope;
    handlebars_value_addref(value);
    return value;
}

FIXTURE_FN(2499873302)
{
    struct handlebars_value * value = handlebars_value_ctor(CONTEXT);
    handlebars_value_boolean(value, 0);
    return value;
}

FIXTURE_FN(2515293198)
{
    // "function (param, times, bool1, bool2) {\n        if (typeof times !== 'number') { times = 'NaN'; }\n        if (typeof bool1 !== 'boolean') { bool1 = 'NaB'; }\n        if (typeof bool2 !== 'boolean') { bool2 = 'NaB'; }\n        return 'Hello ' + param + ' ' + times + ' times: ' + bool1 + ' ' + bool2;\n      }"
    struct handlebars_value * param = handlebars_stack_get(options->params, 0);
    struct handlebars_value * times = handlebars_stack_get(options->params, 1);
    struct handlebars_value * bool1 = handlebars_stack_get(options->params, 2);
    struct handlebars_value * bool2 = handlebars_stack_get(options->params, 3);
    // @todo check types
    char * tmp = handlebars_talloc_asprintf(
            options->vm,
            "Hello %s %s times: %s %s",
            handlebars_value_get_strval(param),
            handlebars_value_get_strval(times),
            handlebars_value_get_strval(bool1),
            handlebars_value_get_strval(bool2)
    );
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, tmp);
    handlebars_talloc_free(tmp);
    return result;
}

FIXTURE_FN(2554595758)
{
    // "function () { return 'bar'; }"
    FIXTURE_STRING("bar");
}

FIXTURE_FN(2560952765)
{
    // "function () { return 'foo'; }"
    FIXTURE_STRING("foo");
}

FIXTURE_FN(2573932141)
{
    // "function (world) {\n          return 'cruel ' + world.toUpperCase();\n        }"
    struct handlebars_value * value = handlebars_stack_get(options->params, 0);
    char * tmp = handlebars_talloc_strdup(options->vm, handlebars_value_get_strval(value));
    size_t i  = 0;
    while( tmp[i] ) {
        tmp[i] = toupper(tmp[i]);
        i++;
    }
    char * tmp2 = handlebars_talloc_asprintf(
            options->vm,
            "cruel %s",
            tmp
    );
    handlebars_talloc_free(tmp);
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, tmp2);
    handlebars_talloc_free(tmp2);
    return result;
}

FIXTURE_FN(2596410860)
{
    // "function (context, options) { return options.fn(context); }"
    struct handlebars_value * context = handlebars_stack_get(options->params, 0);
    char * res = handlebars_vm_execute_program(options->vm, options->program, context);
    struct handlebars_value * value = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(value, res);
    handlebars_talloc_free(res);
    return value;
}

FIXTURE_FN(2600345162)
{
    // "function (defaultString) {\n        return new Handlebars.SafeString(defaultString);\n      }"
    struct handlebars_value * context = handlebars_stack_get(options->params, 0);
    struct handlebars_value * value = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(value, handlebars_value_get_strval(context));
    value->flags |= HANDLEBARS_VALUE_FLAG_SAFE_STRING;
    return value;
}

FIXTURE_FN(2608073270)
{
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_boolean(result, false);
    return result;
}

FIXTURE_FN(2632597106)
{
    // "function (options) {\n      var out = '';\n      var byes = ['Goodbye', 'goodbye', 'GOODBYE'];\n      for (var i = 0, j = byes.length; i < j; i++) {\n        out += byes[i] + ' ' + options.fn(this) + '! ';\n      }\n      return out;\n    }",
    char * tmp = handlebars_talloc_asprintf(
            options->vm,
            "%s %s! %s %s! %s %s! ",
            "Goodbye",
            handlebars_vm_execute_program(options->vm, options->program, options->scope),
            "goodbye",
            handlebars_vm_execute_program(options->vm, options->program, options->scope),
            "GOODBYE",
            handlebars_vm_execute_program(options->vm, options->program, options->scope)
    );
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, tmp);
    handlebars_talloc_free(tmp);
    return result;
}

FIXTURE_FN(2659134105)
{
    // "function (options) {\n          return 'GOODBYE ' + options.hash.cruel + ' ' + options.hash.world + ' ' + options.hash.times + ' TIMES';\n        }"
    struct handlebars_value * cruel = handlebars_value_map_find(options->hash, "cruel");
    struct handlebars_value * world = handlebars_value_map_find(options->hash, "world");
    struct handlebars_value * times = handlebars_value_map_find(options->hash, "times");
    char * tmp = handlebars_talloc_asprintf(
            options->vm,
            "GOODBYE %s %s %s TIMES",
            handlebars_value_get_strval(cruel),
            handlebars_value_get_strval(world),
            handlebars_value_get_strval(times)
    );
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, tmp);
    handlebars_talloc_free(tmp);
    return result;
}

FIXTURE_FN(2736662431)
{
    // "function (options) {\n          equals(options.fn.blockParams, 1);\n          return options.fn({}, {blockParams: [1, 2]});\n        }"
    // @todo equals
    struct handlebars_value * block_params = handlebars_value_from_json_string(CONTEXT, "[1, 2]");
    handlebars_value_convert(block_params);
    struct handlebars_value * context = handlebars_value_ctor(CONTEXT);
    handlebars_value_map_init(context);
    char * tmp = handlebars_vm_execute_program_ex(options->vm, options->program, context, NULL, block_params);
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, tmp);
    handlebars_talloc_free(tmp);
    return result;
}

FIXTURE_FN(2795443460)
{
    // "function (options) { return options.fn({text: 'GOODBYE'}); }"
    struct handlebars_value * context = handlebars_value_from_json_string(CONTEXT, "{\"text\": \"GOODBYE\"}");
    handlebars_value_convert(context);
    char * tmp = handlebars_vm_execute_program(options->vm, options->program, context);
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, tmp);
    handlebars_talloc_free(tmp);
    return result;
}

FIXTURE_FN(2818908139)
{
    // "function (options) {\n        return options.fn({exclaim: '?'}, { data: {adjective: 'sad'} });\n      }"
    struct handlebars_value * context = handlebars_value_from_json_string(CONTEXT, "{\"exclaim\": \"?\"}");
    struct handlebars_value * data = handlebars_value_from_json_string(CONTEXT, "{\"adjective\": \"sad\"}");
    struct handlebars_value * exclaim = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(exclaim, "!");
    char * res = handlebars_vm_execute_program_ex(options->vm, options->program, context, data, NULL);
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, res);
    handlebars_talloc_free(res);
    return result;
}

FIXTURE_FN(2842041837)
{
    // "function () {\n        return 'helper missing: ' + arguments[arguments.length - 1].name;\n      }"
    char * tmp = handlebars_talloc_asprintf(
            options->vm,
            "helper missing: %s",
            options->name
    );
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, tmp);
    handlebars_talloc_free(tmp);
    return result;
}

FIXTURE_FN(2857704189)
{
    // "function (options) {\n        return new Handlebars.SafeString(options.fn());\n      }"
    char * tmp = handlebars_vm_execute_program(options->vm, options->program, options->scope);
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, tmp);
    handlebars_talloc_free(tmp);
    result->flags |= HANDLEBARS_VALUE_FLAG_SAFE_STRING;
    return result;
}

FIXTURE_FN(2919388099)
{
    // "function (options) {\n        var frame = Handlebars.createFrame(options.data);\n        for (var prop in options.hash) {\n          if (prop in options.hash) {\n            frame[prop] = options.hash[prop];\n          }\n        }\n        return options.fn(this, {data: frame});\n      }"
    struct handlebars_value * frame = handlebars_value_ctor(CONTEXT);
    handlebars_value_map_init(frame);
    struct handlebars_value_iterator *it = handlebars_value_iterator_ctor(options->data);
    for (; it->current; handlebars_value_iterator_next(it)) {
        handlebars_map_add(frame->v.map, it->key, it->current);
    }
    struct handlebars_value_iterator *it2 = handlebars_value_iterator_ctor(options->hash);
    for (; it2->current; handlebars_value_iterator_next(it2)) {
        handlebars_map_update(frame->v.map, it2->key, it2->current);
    }
    handlebars_map_update(frame->v.map, "_parent", options->data);
    char * res = handlebars_vm_execute_program_ex(options->vm, options->program, options->scope, frame, NULL);
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, res);
    handlebars_talloc_free(res);
    return result;
}

FIXTURE_FN(2927692429)
{
    // "function () { return 'hello'; }"
    FIXTURE_STRING("hello");
}

FIXTURE_FN(2940930721)
{
    // "function () { return 'world'; }"
    FIXTURE_STRING("world");
}

FIXTURE_FN(2961119846)
{
    // "function (options) {\n        return options.data.adjective + ' ' + this.noun;\n      }"
    struct handlebars_value * adjective = handlebars_value_map_find(options->data, "adjective");
    struct handlebars_value * noun = handlebars_value_map_find(options->scope, "noun");
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    char * tmp = handlebars_talloc_asprintf(
            result,
            "%s %s",
            handlebars_value_get_strval(adjective),
            handlebars_value_get_strval(noun)
    );
    handlebars_value_string(result, tmp);
    handlebars_talloc_free(tmp);
    return result;
}

FIXTURE_FN(3011980185)
{
    // "function (options) {\n          equals(options.fn.blockParams, 1);\n          return options.fn({value: 'bar'}, {blockParams: [1, 2]});\n        }"
    // @todo equals
    struct handlebars_value * block_params = handlebars_value_from_json_string(CONTEXT, "[1, 2]");
    handlebars_value_convert(block_params);
    struct handlebars_value * context = handlebars_value_from_json_string(CONTEXT, "{\"value\": \"bar\"}");
    handlebars_value_convert(context);
    char * tmp = handlebars_vm_execute_program_ex(options->vm, options->program, context, NULL, block_params);
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, tmp);
    handlebars_talloc_free(tmp);
    return result;
}

FIXTURE_FN(3058305845)
{
    // "function () {return this.foo; }"
    struct handlebars_value * value = handlebars_value_map_find(options->scope, "foo");
    if( !value ) {
        value = handlebars_value_ctor(CONTEXT);
    }
    return value;
}

FIXTURE_FN(3065257350)
{
    // "function (options) {\n          return this.goodbye.toUpperCase() + options.fn(this);\n        }"
    struct handlebars_value * goodbye = handlebars_value_map_find(options->scope, "goodbye");
    char * tmp = handlebars_talloc_strdup(options->vm, handlebars_value_get_strval(goodbye));
    size_t i  = 0;
    while( tmp[i] ) {
        tmp[i] = toupper(tmp[i]);
        i++;
    }
    char * tmp2 = handlebars_vm_execute_program(options->vm, options->program, options->scope);
    handlebars_talloc_strdup_append(tmp, tmp2);
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, tmp);
    handlebars_talloc_free(tmp);
    handlebars_talloc_free(tmp2);
    return result;
}

FIXTURE_FN(3113355970)
{
    FIXTURE_STRING("world!");
}

FIXTURE_FN(3123251961)
{
    // "function () { return 'helper'; }"
    FIXTURE_STRING("helper");
}

FIXTURE_FN(3167423302)
{
    // "function () { return this.bar; }"
    return handlebars_value_map_find(options->scope, "bar");
}

FIXTURE_FN(3168412868)
{
    // "function (options) {\n        return options.fn({exclaim: '?', zomg: 'world'}, { data: {adjective: 'sad'} });\n      }"
    struct handlebars_value * context = handlebars_value_from_json_string(CONTEXT, "{\"exclaim\":\"?\", \"zomg\":\"world\"}");
    struct handlebars_value * data = handlebars_value_from_json_string(CONTEXT, "{\"adjective\": \"sad\"}");
    handlebars_value_convert(context);
    handlebars_value_convert(data);
    char * res = handlebars_vm_execute_program_ex(options->vm, options->program, context, data, NULL);
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, res);
    handlebars_talloc_free(res);
    return result;
}

FIXTURE_FN(3206093801)
{
    // "function (context, options) { return '<form>' + options.fn(context) + '<\/form>'; }"
    struct handlebars_value * context = handlebars_stack_get(options->params, 0);
    char * res = handlebars_vm_execute_program(options->vm, options->program, context);
    char * tmp = handlebars_talloc_asprintf(
            options->vm,
            "<form>%s</form>",
            res
    );
    handlebars_talloc_free(res);
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, tmp);
    handlebars_talloc_free(tmp);
    return result;
}

FIXTURE_FN(325991858)
{
    // "function (options) {\n      var out = '';\n      var byes = ['Goodbye', 'goodbye', 'GOODBYE'];\n      for (var i = 0, j = byes.length; i < j; i++) {\n        out += byes[i] + ' ' + options.fn({}) + '! ';\n      }\n      return out;\n    }"
    struct handlebars_value * context = handlebars_value_ctor(CONTEXT);
    handlebars_value_map_init(context);
    char * tmp = handlebars_talloc_asprintf(
            options->vm,
            "%s %s! %s %s! %s %s! ",
            "Goodbye",
            handlebars_vm_execute_program(options->vm, options->program, context),
            "goodbye",
            handlebars_vm_execute_program(options->vm, options->program, context),
            "GOODBYE",
            handlebars_vm_execute_program(options->vm, options->program, context)
    );
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, tmp);
    handlebars_talloc_free(tmp);
    return result;
}

FIXTURE_FN(3307473738)
{
    FIXTURE_STRING("Awesome");
}

FIXTURE_FN(3287026061)
{
    // "function () {\n      return '';\n    }"
    FIXTURE_STRING("");
}

FIXTURE_FN(3308130198)
{
    // "function (value) {\n      return 'foo ' + value;\n    }"
    struct handlebars_value * value = handlebars_stack_get(options->params, 0);
    char * tmp = handlebars_talloc_asprintf(
            options->vm,
            "foo %s",
            handlebars_value_get_strval(value)
    );
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, tmp);
    handlebars_talloc_free(tmp);
    return result;
}

FIXTURE_FN(3325763044)
{
    // "function (val, that, theOther) {\n        return 'val is ' + val + ', ' + that + ' and ' + theOther;\n      }"
    struct handlebars_value * val = handlebars_stack_get(options->params, 0);
    struct handlebars_value * that = handlebars_stack_get(options->params, 1);
    struct handlebars_value * theOther = handlebars_stack_get(options->params, 2);
    char * tmp = handlebars_talloc_asprintf(
            options->vm,
            "val is %s, %s and %s",
            handlebars_value_get_strval(val),
            handlebars_value_get_strval(that),
            handlebars_value_get_strval(theOther)
    );
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, tmp);
    handlebars_talloc_free(tmp);
    return result;
}

FIXTURE_FN(3327136760)
{
    // "function () {\n          return this.goodbye.toUpperCase();\n        }"
    struct handlebars_value * goodbye = handlebars_value_map_find(options->scope, "goodbye");
    char * tmp = handlebars_talloc_strdup(options->vm, handlebars_value_get_strval(goodbye));
    size_t i  = 0;
    while( tmp[i] ) {
        tmp[i] = toupper(tmp[i]);
        i++;
    }
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, tmp);
    handlebars_talloc_free(tmp);
    return result;
}

FIXTURE_FN(3328314220)
{
    // "function () { return 'helpers'; }"
    FIXTURE_STRING("helpers");
}

FIXTURE_FN(3379432388)
{
    // "function () { return this.more; }"
    struct handlebars_value * value = handlebars_value_map_find(options->scope, "more");
    if( !value ) {
        value = handlebars_value_ctor(CONTEXT);
    }
    return value;
}

FIXTURE_FN(3407223629)
{
    // "function () {\n        return 'missing: ' + arguments[arguments.length - 1].name;\n      }",
    char * tmp = handlebars_talloc_asprintf(
            options->vm,
            "missing: %s",
            options->name
    );
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, tmp);
    handlebars_talloc_free(tmp);
    return result;
}

FIXTURE_FN(3578728160)
{
    // "function () {\n            return 'undefined!';\n          }"
    struct handlebars_value * value = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(value, "undefined!");
    return value;
}

FIXTURE_FN(3659403207)
{
    // "function (value) {\n        return 'bar ' + value;\n    }"
    struct handlebars_value * arg = handlebars_stack_get(options->params, 0);
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    char * r1 = handlebars_value_get_strval(arg);
    char * r2 = handlebars_talloc_strdup(result, "bar ");
    handlebars_talloc_strdup_append(r2, r1);
    handlebars_value_string(result, r2);
    return result;
}

FIXTURE_FN(3691188061)
{
    // "function (val) {\n        return 'val is ' + val;\n      }"
    struct handlbars_value * value = handlebars_stack_get(options->params, 0);
    char * ret = handlebars_talloc_asprintf(
            options->vm,
            "val is %s",
            handlebars_value_get_strval(value)
    );
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, ret);
    handlebars_talloc_free(ret);
    return result;
}

FIXTURE_FN(3697740723)
{
    FIXTURE_STRING("found it!");
}

FIXTURE_FN(3707047013)
{
    // "function (value) { return value; }"
    struct handlbars_value * value = handlebars_stack_get(options->params, 0);
    handlebars_value_addref(value);
    return value;
}

FIXTURE_FN(3728875550)
{
    // "function (options) {\n        return options.data.accessData + ' ' + options.fn({exclaim: '?'});\n      }"
    struct handlebars_value * access_data = handlebars_value_map_find(options->data, "accessData");
    struct handlebars_value * context = handlebars_value_from_json_string(CONTEXT, "{\"exclaim\": \"?\"}");
    char * ret = handlebars_vm_execute_program(options->vm, options->program, context);
    ret = handlebars_talloc_asprintf(
            options->vm,
            "%s %s",
            handlebars_value_get_strval(access_data),
            ret
    );
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, ret);
    handlebars_talloc_free(ret);
    return result;
}

FIXTURE_FN(3781305181)
{
    // "function (times) {\n      if (typeof times !== 'number') { times = 'NaN'; }\n      return 'Hello ' + times + ' times';\n    }"
    struct handlebars_value * times = handlebars_stack_get(options->params, 0);
    // @todo this should be a float perhaps?
    /* if( times->type != HANDLEBARS_VALUE_TYPE_FLOAT || times->type != HANDLEBARS_VALUE_TYPE_INTEGER ) {
        handlebars_value_string(times, "NaN");
    }*/
    char * tmp = handlebars_talloc_asprintf(
            options->vm,
            "Hello %s times",
            handlebars_value_get_strval(times)
    );
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, tmp);
    handlebars_talloc_free(tmp);
    return result;
}

FIXTURE_FN(3878511480)
{
    // "function list(context, options) {\n      if (context.length > 0) {\n        var out = '<ul>';\n        for (var i = 0, j = context.length; i < j; i++) {\n          out += '<li>';\n          out += options.fn(context[i]);\n          out += '<\/li>';\n        }\n        out += '<\/ul>';\n        return out;\n      } else {\n        return '<p>' + options.inverse(this) + '<\/p>';\n      }\n    }"
    struct handlebars_value * context = handlebars_stack_get(options->params, 0);
    char *tmp;
    if( !handlebars_value_is_empty(context) ) {
        struct handlebars_value_iterator *it = handlebars_value_iterator_ctor(context);
        tmp = handlebars_talloc_strdup(options->vm, "<ul>");
        for (; it->current != NULL; handlebars_value_iterator_next(it)) {
            char *tmp2 = handlebars_vm_execute_program(options->vm, options->program, it->current);
            tmp = handlebars_talloc_asprintf_append(
                    tmp,
                    "<li>%s</li>",
                    tmp2
            );
            handlebars_talloc_free(tmp2);
        }
        tmp = handlebars_talloc_strdup_append(tmp, "</ul>");
    } else {
        char * tmp2 = handlebars_vm_execute_program(options->vm, options->inverse, options->scope);
        tmp = handlebars_talloc_asprintf(
                options->vm,
                "<p>%s</p>",
                tmp2
        );
        handlebars_talloc_free(tmp2);
    }
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, tmp);
    handlebars_talloc_free(tmp);
    return result;
}

FIXTURE_FN(4005129518)
{
    // "function (options) {\n        var hash = options.hash;\n        var ariaLabel = Handlebars.Utils.escapeExpression(hash['aria-label']);\n        var placeholder = Handlebars.Utils.escapeExpression(hash.placeholder);\n        return new Handlebars.SafeString('<input aria-label=\"' + ariaLabel + '\" placeholder=\"' + placeholder + '\" \/>');\n      }"
    struct handlebars_value * label = handlebars_value_map_find(options->hash, "aria-label");
    struct handlebars_value * placeholder = handlebars_value_map_find(options->hash, "placeholder");
    char * tmp = handlebars_talloc_asprintf(
            options->vm,
            "<input aria-label=\"%s\" placeholder=\"%s\" />",
            handlebars_value_expression(label, 1),
            handlebars_value_expression(placeholder, 1)
    );
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, tmp);
    handlebars_talloc_free(tmp);
    result->flags |= HANDLEBARS_VALUE_FLAG_SAFE_STRING;
    return result;
}

FIXTURE_FN(4112130635)
{
    // "function (thing, options) {\n        return options.data.adjective + ' ' + thing + (this.exclaim || '');\n      }"
    struct handlebars_value * adjective = handlebars_value_map_find(options->data, "adjective");
    struct handlebars_value * thing = handlebars_stack_get(options->params, 0);
    struct handlebars_value * exclaim = handlebars_value_map_find(options->scope, "exclaim");
    char * res = handlebars_talloc_asprintf(
            options->vm,
            "%s %s%s",
            handlebars_value_get_strval(adjective),
            handlebars_value_get_strval(thing),
            handlebars_value_get_strval(exclaim)
    );
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, res);
    handlebars_talloc_free(res);
    return result;
}

FIXTURE_FN(4158918668)
{
    struct handlebars_value * noun = handlebars_stack_get(options->params, 0);
    char * tmp = handlebars_value_get_strval(noun);
    char * res = handlebars_talloc_asprintf(
            options->vm,
            "Hello %s",
            !*tmp ? "undefined" : tmp
    );
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, res);
    handlebars_talloc_free(res);
    return result;
}

FIXTURE_FN(4204859626)
{
    char * res = handlebars_vm_execute_program_ex(options->vm, options->program, options->scope, NULL, NULL);
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, res);
    handlebars_talloc_free(res);
    return result;
}

FIXTURE_FN(4207421535)
{
    // "function (options) {\n          equals(options.fn.blockParams, 1);\n          return options.fn(this, {blockParams: [1, 2]});\n        }"
    // @todo equals
    struct handlebars_value * block_params = handlebars_value_from_json_string(CONTEXT, "[1, 2]");
    handlebars_value_convert(block_params);
    char * tmp = handlebars_vm_execute_program_ex(options->vm, options->program, options->scope, NULL, block_params);
    struct handlebars_value * result = handlebars_value_ctor(CONTEXT);
    handlebars_value_string(result, tmp);
    handlebars_talloc_free(tmp);
    return result;
}

static void convert_value_to_fixture(struct handlebars_value * value)
{
#define FIXTURE_CASE(hash) \
    case hash: \
        SET_FUNCTION(fixture_ ## hash); \
        break
#define FIXTURE_CASE_ALIAS(hash1, hash2) \
    case hash1: \
        SET_FUNCTION(fixture_ ## hash2); \
        break;

#define SET_FUNCTION(func) \
    handlebars_value_null(value); \
    value->type = HANDLEBARS_VALUE_TYPE_HELPER; \
    value->v.helper = &func;

    assert(value->type == HANDLEBARS_VALUE_TYPE_MAP);

    struct handlebars_value * jsvalue = handlebars_value_map_find(value, "javascript");
    if( !jsvalue ) {
        jsvalue = handlebars_value_map_find(value, "php");
    }
    assert(jsvalue != NULL);
    assert(jsvalue->type == HANDLEBARS_VALUE_TYPE_STRING);
    uint32_t hash = adler32(jsvalue->v.strval, strlen(jsvalue->v.strval));

    switch( hash ) {
        FIXTURE_CASE(20974934);
        FIXTURE_CASE(49286285);
        FIXTURE_CASE(126946175);
        FIXTURE_CASE(169151220);
        FIXTURE_CASE(276040703);
        FIXTURE_CASE(454102302);
        FIXTURE_CASE(459219799);
        FIXTURE_CASE(461441956);
        FIXTURE_CASE(464915369);
        FIXTURE_CASE(471141295);
        FIXTURE_CASE(510017722);
        FIXTURE_CASE(585442881);
        FIXTURE_CASE(620640779);
        FIXTURE_CASE(620828131);
        FIXTURE_CASE(665715952);
        FIXTURE_CASE(666457330);
        FIXTURE_CASE(662835958);
        FIXTURE_CASE(690821881);
        FIXTURE_CASE(730081660);
        FIXTURE_CASE(730672213);
        FIXTURE_CASE(739773491);
        FIXTURE_CASE(748362646);
        FIXTURE_CASE(788468697);
        FIXTURE_CASE(902433745);
        FIXTURE_CASE(922226146);
        FIXTURE_CASE(929767352);
        FIXTURE_CASE(931412676);
        FIXTURE_CASE(958795451);
        FIXTURE_CASE(1041501180);
        FIXTURE_CASE(1091971719);
        FIXTURE_CASE(1102272015);
        FIXTURE_CASE(1198465479);
        FIXTURE_CASE(1211570580);
        FIXTURE_CASE(1252527367);
        FIXTURE_CASE(1283397100);
        FIXTURE_CASE(1341397520);
        FIXTURE_CASE(1582700088);
        FIXTURE_CASE(1623791204);
        FIXTURE_CASE(1644694756);
        FIXTURE_CASE(1774917451);
        FIXTURE_CASE(1818365722);
        FIXTURE_CASE(1872958178);
        FIXTURE_CASE(1983911259);
        FIXTURE_CASE(2084318034);
        FIXTURE_CASE(2089689191);
        FIXTURE_CASE(2096893161);
        FIXTURE_CASE(2107645267);
        FIXTURE_CASE(2182811123);
        FIXTURE_CASE(2259424295);
        FIXTURE_CASE(2262633698);
        FIXTURE_CASE(2305563493);
        FIXTURE_CASE(2327777290);
        FIXTURE_CASE(2439252451);
        FIXTURE_CASE(2499873302);
        FIXTURE_CASE(2515293198);
        FIXTURE_CASE(2554595758);
        FIXTURE_CASE(2560952765);
        FIXTURE_CASE(2573932141);
        FIXTURE_CASE(2596410860);
        FIXTURE_CASE(2600345162);
        FIXTURE_CASE(2608073270);
        FIXTURE_CASE(2632597106);
        FIXTURE_CASE(2659134105);
        FIXTURE_CASE(2736662431);
        FIXTURE_CASE(2795443460);
        FIXTURE_CASE(2818908139);
        FIXTURE_CASE(2842041837);
        FIXTURE_CASE(2857704189);
        FIXTURE_CASE(2919388099);
        FIXTURE_CASE(2927692429);
        FIXTURE_CASE(2940930721);
        FIXTURE_CASE(2961119846);
        FIXTURE_CASE(3011980185);
        FIXTURE_CASE(3058305845);
        FIXTURE_CASE(3065257350);
        FIXTURE_CASE(3113355970);
        FIXTURE_CASE(3123251961);
        FIXTURE_CASE(3167423302);
        FIXTURE_CASE(3168412868);
        FIXTURE_CASE(3206093801);
        FIXTURE_CASE(325991858);
        FIXTURE_CASE(3287026061);
        FIXTURE_CASE(3307473738);
        FIXTURE_CASE(3308130198);
        FIXTURE_CASE(3325763044);
        FIXTURE_CASE(3327136760);
        FIXTURE_CASE(3328314220);
        FIXTURE_CASE(3379432388);
        FIXTURE_CASE(3407223629);
        FIXTURE_CASE(3578728160);
        FIXTURE_CASE(3659403207);
        FIXTURE_CASE(3691188061);
        FIXTURE_CASE(3697740723);
        FIXTURE_CASE(3707047013);
        FIXTURE_CASE(3728875550);
        FIXTURE_CASE(3781305181);
        FIXTURE_CASE(3878511480);
        FIXTURE_CASE(4005129518);
        FIXTURE_CASE(4112130635);
        FIXTURE_CASE(4158918668);
        FIXTURE_CASE(4204859626);
        FIXTURE_CASE(4207421535);

        FIXTURE_CASE_ALIAS(304353340, 1644694756);
        FIXTURE_CASE_ALIAS(401083957, 3707047013);
        FIXTURE_CASE_ALIAS(882643306, 4204859626);
        FIXTURE_CASE_ALIAS(1111103580, 1341397520);
        FIXTURE_CASE_ALIAS(2836204191, 739773491);
        FIXTURE_CASE_ALIAS(3153085867, 2919388099);
        FIXTURE_CASE_ALIAS(3584035731, 3697740723);

        default:
            fprintf(stderr, "Unimplemented test fixture [%u]:\n%s\n", hash, jsvalue->v.strval);
            return;
    }

#ifndef NDEBUG
    fprintf(stderr, "Got fixture [%u]\n", hash);
#endif

#undef SET_FUNCTION
}

void load_fixtures(struct handlebars_value * value)
{
    struct handlebars_value_iterator * it;
    struct handlebars_value * child;

    // This shouldn't happen ...
    assert(value != NULL);

    handlebars_value_convert(value);

    switch( value->type ) {
        case HANDLEBARS_VALUE_TYPE_MAP:
            // Check if it contains a "!code" key
            child = handlebars_value_map_find(value, "!code");
            if( child ) {
                // Convert to helper
                convert_value_to_fixture(value);
                handlebars_value_delref(child);
            } else {
                // Recurse
                it = handlebars_value_iterator_ctor(value);
                for( ; it && it->current != NULL; handlebars_value_iterator_next(it) ) {
                    load_fixtures(it->current);
                }
                handlebars_talloc_free(it);
            }
            break;
        case HANDLEBARS_VALUE_TYPE_ARRAY:
            it = handlebars_value_iterator_ctor(value);
            for( ; it && it->current != NULL; handlebars_value_iterator_next(it) ) {
                load_fixtures(it->current);
            }
            handlebars_talloc_free(it);
            break;
    }
}
