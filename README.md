# rev-hooks

<!--
#field
CTF

#groups
Tool

#languages
C

#frames and libs

-->

Compile the hook program to a shared library, then patch the original binary to hook the functions

```bash
gcc -o hook.so hook.c -shared -fPIC -ggdb && patchelf --add-needed ./hook.so my_program
```

