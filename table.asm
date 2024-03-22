
source | IR     | sp | x64 assembly                    |
-------+--------|----|---------------------------------+
< A    | PUSH 0 |  0 | vmovaps zmm0       , zword[rdi] |
< B    | PUSH 1 |  1 | vmovaps zmm1       , zword[rsi] |
+      | ADD    |  0 | vaddps  zmm0       , zmm0, zmm1 |
< C    | PUSH 2 |  1 | vmovaps zmm1       , zword[rdx] |
< D    | PUSH 3 |  2 | vmovaps zmm2       , zword[rcx] |
+      | ADD    |  1 | vaddps  zmm1       , zmm1, zmm2 |
*      | MUL    |  0 | vmulps  zmm0       , zmm0, zmm1 |
< C    | PUSH 2 |  1 | vmovaps zmm2       , zword[rdx] |
< D    | PUSH 3 |  2 | vmovaps zmm3       , zword[rcx] |
+      | ADD    |  1 | vaddps  zmm1       , zmm1, zmm2 |
< C    | PUSH 2 |  2 | vmovaps zmm2       , zword[rdx] |
< D    | PUSH 3 |  3 | vmovaps zmm3       , zword[rcx] |
+      | ADD    |  2 | vaddps  zmm2       , zmm2, zmm3 |
*      | MUL    |  1 | vmulps  zmm1       , zmm1, zmm2 |
/      | DIV    |  0 | vdivps  zmm0       , zmm0, zmm1 |
> O    | POP 0  | -1 | vmovaps zword [rsi], zmm0       |

