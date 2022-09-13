// suspend-shim
// 9-13-2022 - impost0r/secret.club
// provide application to be spawned w/o ASLR as argv[1]
// License - GPL-3

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <spawn.h>
#include <stdbool.h>

#define POSIX_SPAWN_DISABLE_ASLR 0x0100
#define POSIX_SPAWN_ALLOW_DATA_EXEC 0x2000 //unused?
#define PLATFORM_IOS 2

extern char **environ;
extern int posix_spawnattr_set_platform_np; //for use at your discretion

bool assert_perror(int val, char* fn) {
    if (val != 0) {
        perror(fn);
        return false;
    }
    return true;
}

int main(int argc, char* argv[]) {

    pid_t pid;
    int rv;
    posix_spawnattr_t attrp;
    rv = posix_spawnattr_init(&attrp);

    if ( assert_perror(rv, "posix_spawnattr_init") != true ) {
        exit(EXIT_FAILURE);
    }

    rv = posix_spawnattr_setflags(&attrp, POSIX_SPAWN_START_SUSPENDED | POSIX_SPAWN_DISABLE_ASLR); //lol

    if ( assert_perror(rv, "posix_spawnattr_setflags") != true ) {
        exit(EXIT_FAILURE);
    }

    rv = posix_spawn(&pid, argv[1], NULL, &attrp, NULL, environ);
    if ( assert_perror(rv, "posix_spawn") != true) {
        exit(EXIT_FAILURE);
    }
    printf("Spawned %s (PID: %d)", argv[1], pid);


}
