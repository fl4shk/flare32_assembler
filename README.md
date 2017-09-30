# Flare32 Assembler
My first real attempt at writing an assembler


# Assembler directives

Change the current assembling address (really dumb, may overwrite existing
code)
```
.org address
```



Insert a series of expressions, encoded as bytes:
```
.db stuff1
.db stuff1, stuff2
.db stuff1, stuff2, stuff3, ...
```


Insert a series of expressions, encoded as 32-bit values:
```
.dw stuff1
.dw stuff1, stuff2
.dw stuff1, stuff2, stuff3, ...
```
