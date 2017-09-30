# Flare32 Assembler
My first real attempt at writing an assembler, for my custom architecture
called Flare32.


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


Define a symbol (can't have same name as label):
```
.define nice 5
.define nice nice + 1 ; redefines nice as 6 because defines are evaluated
                      ; immediately
```
Defined symbols can be assigned the value of an expression, which does mean
you can use a label in a define.

As mentioned before, defines are evaluated immediately.

It is also possible to use ```.defn``` instead of ```.define``` for
shorthand purposes.



# Other features
Labels can have the same name as instructions or registers.

Label addresses can be used in immedate values, as part of expressions.

Example:
```
.org 9001
some_lab:
    addi r5, r9, some_lab + some_lab
```

This will store r9 + (9001 + 9001) to r5 if actually executed by a Flare32
CPU.





Not quite accurate C-style operator precedence, but some C-style operators
exist for use in expressions, primarily arithmetic and bitwise operators.

In particular, every operator that exists besides + and - has the same
precedence as * and /, so it's a good idea to use parentheses when
necessary.

C-style comparison operators (==, !=) do not exist.




All arithmetic expressions use an int64\_t underneath.
