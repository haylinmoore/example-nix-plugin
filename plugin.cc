#include "eval.hh"
#include "eval-inline.hh"
#include "eval-settings.hh"
#include "primops.hh"
#include "store-api.hh"
#include "util.hh"

using namespace nix;

static void example_op(EvalState & state, const PosIdx pos, Value ** args, Value & v)
{
    // Force evaluation of both arguments
    state.forceValue(*args[0], pos);
    state.forceValue(*args[1], pos);

    // Convert arguments to strings
    NixStringContext context;
    auto key = state.coerceToString(pos, *args[0], context, 
        "while evaluating the first argument", false, false);
    auto value = state.coerceToString(pos, *args[1], context,
        "while evaluating the second argument", false, false);

    // Create an attribute set with 3 entries
    auto attrs = state.buildBindings(3);

    // Create values and add them to the attribute set
    attrs.alloc("hello").mkString("world");
    attrs.alloc("hola").mkString("mundo");
    attrs.alloc(*key).mkString(*value);

    // Set the result value as the attribute set
    v.mkAttrs(attrs);
}

static RegisterPrimOp rp1({
    .name = "__example_op",
     // Our op accepts two arguments
    .arity = 2,
    .fun = example_op,
});

static struct PrimOpDebug {
    PrimOpDebug() {
        fprintf(stderr, "Plugin Registered\n");
    }
} primOpDebugInstance;
