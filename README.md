# Example Nix Plugin
This repo is based on [nix-plugins](https://github.com/shlevy/nix-plugins) by Shea Levy

This repo contains an example Nix plugin that adds a new builtin called `example_op`.
This op currently contains a print on load for debugging, but that should probably be removed in proper use.

## How?
There is not much published on how to properly write nix plugins, what functions are available to a developer, etc. 
When writing this basic example plugin I used shlevy's [nix-plugins](https://github.com/shlevy/nix-plugins) repo for the CMake build and the official
[primops source code](https://github.com/NixOS/nix/blob/2.26-maintenance/src/libexpr/primops.cc) for primop implementation examples.  
This repo currently only has a plugin compiling for Nix 2.26 (updated from [nix-plugins](https://github.com/shlevy/nix-plugins) which supports 2.24).
This version can be changed in the default.nix, though imports and types will likely need to be updated.

### Testing with eval
```
$ nix eval --expr 'builtins.example_op "saluton" "mondo"' --extra-plugin-files "$(nix-build --no-out-link)/lib/nix/plugins/"
Plugin Registered
{ hello = "world"; hola = "mundo"; saluton = "mondo"; }
````

### Access repl
```
nix repl --extra-plugin-files "$(nix-build --no-out-link)/lib/nix/plugins/"
```
