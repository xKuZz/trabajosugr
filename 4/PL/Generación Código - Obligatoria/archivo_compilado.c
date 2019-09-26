#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
int n, curr;
int main() {
printf("%s", "Introduce número: ");
scanf("%d", &n);
printf("%s", " ");
printf("%d", n);
printf("%s", " == ");
curr = 2;
etiqueta0:
;
 {
int temp0;
temp0 = curr <= n;
if (!temp0) goto etiqueta1;
 {
int d;
int temp1;
temp1 = n / curr;
d = temp1;
int temp2;
temp2 = d * curr;
int temp3;
temp3 = temp2 == n;
if (!temp3) goto etiqueta2;
 {
 {
printf("%s", "* ");
printf("%d", curr);
printf("%s", " ");
int temp4;
temp4 = n / curr;
n = temp4;
}
}
goto etiqueta3;
etiqueta2:
;
 {
int temp5;
temp5 = curr + 1;
curr = temp5;
}
etiqueta3:
;
}
goto etiqueta0;
}
etiqueta1:
;
printf("%s", "\n");
}
