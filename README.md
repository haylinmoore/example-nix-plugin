# Example Nix Plugin

This repo contains an example Nix plugin that adds a new builtin called `example_op`.
This op currently contains a print on load for debugging, but that should probably be removed in proper use.

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
