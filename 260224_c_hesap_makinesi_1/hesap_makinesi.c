#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAX_EXPR 1024
#define MAX_STACK 256

// Sabitler
#define PI 3.14159265358979323846
#define E  2.71828182845904523536
#define PHI 1.61803398874989484820

// Stack yapıları
double numStack[MAX_STACK];
int numTop = -1;

char opStack[MAX_STACK];
int opTop = -1;

// Stack işlemleri - sayılar
void pushNum(double val) {
    numStack[++numTop] = val;
}

double popNum() {
    if (numTop < 0) return 0;
    return numStack[numTop--];
}

// Stack işlemleri - operatörler
void pushOp(char op) {
    opStack[++opTop] = op;
}

char popOp() {
    if (opTop < 0) return '\0';
    return opStack[opTop--];
}

char peekOp() {
    if (opTop < 0) return '\0';
    return opStack[opTop];
}

// Faktöriyel
double factorial(int n) {
    if (n < 0) return NAN;
    if (n == 0 || n == 1) return 1;
    double result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Operatör önceliği
int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
        case '%':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

// İşlem yap
void applyOp() {
    char op = popOp();
    double b = popNum();
    double a = popNum();

    switch (op) {
        case '+': pushNum(a + b); break;
        case '-': pushNum(a - b); break;
        case '*': pushNum(a * b); break;
        case '/':
            if (b == 0) {
                printf("Hata: Sıfıra bölme!\n");
                pushNum(NAN);
            } else {
                pushNum(a / b);
            }
            break;
        case '%': pushNum(fmod(a, b)); break;
        case '^': pushNum(pow(a, b)); break;
    }
}

// Fonksiyon uygula
double applyFunction(const char *func, double val) {
    if (strcmp(func, "sin") == 0) return sin(val * PI / 180);
    if (strcmp(func, "cos") == 0) return cos(val * PI / 180);
    if (strcmp(func, "tan") == 0) return tan(val * PI / 180);
    if (strcmp(func, "asin") == 0) return asin(val) * 180 / PI;
    if (strcmp(func, "acos") == 0) return acos(val) * 180 / PI;
    if (strcmp(func, "atan") == 0) return atan(val) * 180 / PI;
    if (strcmp(func, "log") == 0) return log10(val);
    if (strcmp(func, "ln") == 0) return log(val);
    if (strcmp(func, "sqrt") == 0) return sqrt(val);
    if (strcmp(func, "cbrt") == 0) return cbrt(val);
    if (strcmp(func, "abs") == 0) return fabs(val);
    if (strcmp(func, "fact") == 0) return factorial((int)val);
    return val;
}

// İfadeyi değerlendir
double evaluate(char *expr) {
    numTop = -1;
    opTop = -1;

    int i = 0;
    int len = strlen(expr);

    while (i < len) {
        // Boşlukları atla
        if (isspace(expr[i])) {
            i++;
            continue;
        }

        // Sayı
        if (isdigit(expr[i]) || (expr[i] == '.' && isdigit(expr[i+1]))) {
            double num = 0;
            int decimal = 0;
            double divisor = 1;

            while (i < len && (isdigit(expr[i]) || expr[i] == '.')) {
                if (expr[i] == '.') {
                    decimal = 1;
                } else {
                    if (decimal) {
                        divisor *= 10;
                        num = num + (expr[i] - '0') / divisor;
                    } else {
                        num = num * 10 + (expr[i] - '0');
                    }
                }
                i++;
            }
            pushNum(num);
            continue;
        }

        // Sabitler ve fonksiyonlar
        if (isalpha(expr[i])) {
            char token[32];
            int j = 0;
            while (i < len && (isalpha(expr[i]) || isdigit(expr[i]))) {
                token[j++] = tolower(expr[i++]);
            }
            token[j] = '\0';

            // Sabitler
            if (strcmp(token, "pi") == 0) {
                pushNum(PI);
                continue;
            }
            if (strcmp(token, "e") == 0) {
                pushNum(E);
                continue;
            }
            if (strcmp(token, "phi") == 0) {
                pushNum(PHI);
                continue;
            }

            // Fonksiyonlar - parantez içini hesapla
            if (expr[i] == '(') {
                i++; // '(' atla
                int paren = 1;
                int start = i;
                while (i < len && paren > 0) {
                    if (expr[i] == '(') paren++;
                    if (expr[i] == ')') paren--;
                    i++;
                }
                char subexpr[MAX_EXPR];
                strncpy(subexpr, expr + start, i - start - 1);
                subexpr[i - start - 1] = '\0';
                double val = evaluate(subexpr);
                pushNum(applyFunction(token, val));
            }
            continue;
        }

        // Parantez aç
        if (expr[i] == '(') {
            pushOp('(');
            i++;
            continue;
        }

        // Parantez kapat
        if (expr[i] == ')') {
            while (opTop >= 0 && peekOp() != '(') {
                applyOp();
            }
            if (opTop >= 0) popOp(); // '(' kaldır
            i++;
            continue;
        }

        // Operatörler
        if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' ||
            expr[i] == '/' || expr[i] == '%' || expr[i] == '^') {

            // Negatif sayı kontrolü
            if (expr[i] == '-' && (i == 0 || expr[i-1] == '(' ||
                expr[i-1] == '+' || expr[i-1] == '-' ||
                expr[i-1] == '*' || expr[i-1] == '/' || expr[i-1] == '^')) {
                i++;
                double num = 0;
                int decimal = 0;
                double divisor = 1;

                while (i < len && (isdigit(expr[i]) || expr[i] == '.')) {
                    if (expr[i] == '.') {
                        decimal = 1;
                    } else {
                        if (decimal) {
                            divisor *= 10;
                            num = num + (expr[i] - '0') / divisor;
                        } else {
                            num = num * 10 + (expr[i] - '0');
                        }
                    }
                    i++;
                }
                pushNum(-num);
                continue;
            }

            while (opTop >= 0 && peekOp() != '(' &&
                   precedence(peekOp()) >= precedence(expr[i])) {
                applyOp();
            }
            pushOp(expr[i]);
            i++;
            continue;
        }

        // Faktöriyel
        if (expr[i] == '!') {
            double val = popNum();
            pushNum(factorial((int)val));
            i++;
            continue;
        }

        i++;
    }

    // Kalan operatörleri uygula
    while (opTop >= 0) {
        applyOp();
    }

    return numTop >= 0 ? numStack[numTop] : 0;
}

void printMenu() {
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║            ★ BİLİMSEL HESAP MAKİNESİ ★                       ║\n");
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    printf("║  Temel: + - * / %% ^                                         ║\n");
    printf("║  Fonksiyonlar: sin, cos, tan, asin, acos, atan              ║\n");
    printf("║                log, ln, sqrt, cbrt, abs, fact               ║\n");
    printf("║  Sabitler: pi, e, phi                                       ║\n");
    printf("║  Parantez: ( )    Faktöriyel: !                             ║\n");
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    printf("║  Örnek: 9/(768+987)*123  veya  sin(30)+cos(60)              ║\n");
    printf("║  Çıkış için: q veya exit                                    ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n");
}

int main() {
    char input[MAX_EXPR];

    printMenu();

    while (1) {
        printf("\n► ");

        if (fgets(input, MAX_EXPR, stdin) == NULL) break;

        // Yeni satır karakterini kaldır
        input[strcspn(input, "\n")] = 0;

        // Boş giriş
        if (strlen(input) == 0) continue;

        // Çıkış
        if (strcmp(input, "q") == 0 || strcmp(input, "exit") == 0 ||
            strcmp(input, "quit") == 0 || strcmp(input, "cikis") == 0) {
            printf("\nGüle güle!\n");
            break;
        }

        // Menü
        if (strcmp(input, "menu") == 0 || strcmp(input, "help") == 0 ||
            strcmp(input, "yardim") == 0) {
            printMenu();
            continue;
        }

        // Hesapla
        double result = evaluate(input);

        if (isnan(result)) {
            printf("= Hata\n");
        } else if (isinf(result)) {
            printf("= %s∞\n", result > 0 ? "" : "-");
        } else if (result == (long long)result) {
            printf("= %.0f\n", result);
        } else {
            printf("= %.10g\n", result);
        }
    }

    return 0;
}
