#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


int precedence(char op) {
    if ( op == '-') return 1;
    if (op == '+' ) return 2;
    if (op == '*' ) return 3;
    if ( op == '/') return 4;
    return 0;
}


int apply_operation(int a, int b, char op) {
    if (op == '+') return a + b;
    if (op == '-') return a - b;
    if (op == '*') return a * b;
    if (op == '/') {
        if (b == 0) {
            printf("Error: Division by zero.\n");
            exit(0);
        }
        return a / b;
    }
    return 0;
}


void push_number(int *numbers,int *number_top,int number){
    numbers[++(*number_top)]=number;
}

void push_operator(char *operators,int *operator_top,char operator){
    operators[++(*operator_top)]=operator;

}
int pop_number(int *numbers,int *number_top){
    return numbers[(*number_top)--];
}
int pop_operator(char *opertaors,int *operator_top){
    return opertaors[(*operator_top)--];
}


int evaluate_expression(char* expression) {
    int numbers[100]; 
    int number_top = -1;
    char operators[100];   
    int operator_top = -1;

    for (int i = 0; expression[i]; i++) {
        if (isspace(expression[i])) continue;

       
        if (isdigit(expression[i])) {
            int digit = 0;
            while (i < strlen(expression) && isdigit(expression[i])) {
                digit = digit * 10 + (expression[i] - '0');
                i++;
            }
            push_number(numbers,&number_top,digit);
            i--; 
        }
       
        else if (expression[i] == '(') {
           push_operator(operators,&operator_top,expression[i]);
        }
       
        else if (expression[i] == ')') {
            while (operator_top >= 0 && operators[operator_top] != '(') {
                int b = numbers[number_top--];
                int a = numbers[number_top--];
                char op = operators[operator_top--];
                push_number(numbers,&number_top, apply_operation(a, b, op));
            }
            pop_operator(operators,&operator_top);
        }
       
        else {
            while (operator_top >= 0 && precedence(operators[operator_top]) >= precedence(expression[i])) {
                int b = pop_number(numbers,&number_top);
                int a = pop_number(numbers,&number_top);
                char op = pop_operator(operators,&operator_top);
                push_number(numbers,&number_top, apply_operation(a, b, op));
            }
            push_operator(operators,&operator_top,expression[i]);
        }
    }

   
    while (operator_top >= 0) {
        int b = pop_number(numbers,&number_top);
        int a = pop_number(numbers,&number_top);
        char op = pop_operator(operators,&operator_top);
        push_number(numbers,&number_top, apply_operation(a, b, op));
    }

    return numbers[0]; 
}

int main() {
    char expression[100];
    printf("Enter the expression: ");
    fgets(expression, 100, stdin);

    expression[strcspn(expression,"\n")]=0;
    //!isspace(expression[i])

    for (int i = 0; expression[i]; i++) {
        if (!(expression[i]>='0' && expression[i]<='9') && expression[i]!=' ' && expression[i] != '+' &&
            expression[i] != '-' && expression[i] != '*' && expression[i] != '/' &&
            expression[i] != '(' && expression[i] != ')') {
            printf("Error: Invalid expression.\n");
            return 0;
        }
    }

    
    int result = evaluate_expression(expression);
    printf("Result: %d\n", result);

    return 0;
}
//Updated