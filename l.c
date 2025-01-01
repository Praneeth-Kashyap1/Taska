#include<stdio.h>
#include<math.h>
int main(){
    int b,n,m;
    printf("Enter the value for Base\n");
    scanf("%d",&b);
    printf("Enter the value of exponent\n");
    scanf("%d",&n);
    printf("Enter the value for modulus\n");
    scanf("%d",&m);
    int k=pow(b,n);
    k=k%m;
    printf("The result of the expression is:%d\n", k); 
    return 0;
}