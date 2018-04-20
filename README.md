### Techniki kompilacji - LTurtle
Interpreter języka pozwalającego definiować L-system i opisywać elementarne operacje w tym systemie w języku “grafiki żółwia”.  

Przykładowy kod tworzący drzewo binarne ([przykład L-systemu z Wikipedii](https://en.wikipedia.org/wiki/L-system))  
(zamienione nazwy symboli: s0 zamiast 0, s1 zamiast 1, left zamiat [, right zamiast ]): 
```
s0 = { forward(1.0); };
s1 = { forward(2.0); };
left = { pushstate(); rotate(-45.0); };
right = { popstate(); rotate(45.0); };
s1 -> s1 + s1;
s0 -> s1 + left + s0 + right + s0;
tree3 = evaluate(3, s0);
execute(tree3);
```
