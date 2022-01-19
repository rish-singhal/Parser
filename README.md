# Parser Task

This repository contains my implementation of the [task](https://gist.github.com/chriseth/be1f936b6a86d4202b3556ed6f73f94c).

---

## Grammar

The parser supports single digits `'0-9', +, -, *, /` 

```
expr -> term ((+|-) term)*
term -> factor ((*|/) factor)*
factor -> '0-9'
       -> LPAREN expr RPAREN
```
