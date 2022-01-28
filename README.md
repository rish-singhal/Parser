# Tree-walk Interpreter

This repository contains my implementation of the [task](https://gist.github.com/chriseth/be1f936b6a86d4202b3556ed6f73f94c).

---

## Instructions
To start the parser,
```bash
$ cd cmake-build-debug
```

```bash
$ make
```

```bash
$ ./parser
> 1 + 1
2
> 1 - 1
0
> 1 + (1 + 1)
3
> test
All test passed!
> exit
```



## Grammar

The parser supports single digits `'0-9', +, -, *, /` 

```
expression -> term ((+|-) term)*
term -> factor ((*|/) factor)*
factor -> '0-9'
       -> LPAREN expression RPAREN
```

## Directory Structure

```
├── src
│   ├── AST
│   │   ├── evaluateAST.h
│   │   └── node.h
│   ├── Parser
│   │   ├── parser.cpp
│   │   └── parser.h
│   ├── main.cpp
│   └── solver.h
└── tests
    └── test.h
```

## Author

[Rishabh Singhal](https://github.com/rish-singhal)
