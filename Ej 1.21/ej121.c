#include <signal.h>
#include <stdio.h>
#include <unistd.h>

static int contador;

void handler(int);
int main(){

    struct sigaction sa = { .sa_flags = 0, .sa_handler = handler };
    sigaction(SIGALRM, &sa, NULL);
    while(1){
        alarm(1);
        pause();
    }

}

void handler(int sig){
    contador++;
    printf("Señal recibida. El valor del contador es: %d\n", contador);
}