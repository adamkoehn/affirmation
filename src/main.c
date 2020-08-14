#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <libnotify/notify.h>

#ifndef optarg
extern char *optarg;
#endif

#ifdef HAVE_CONFIG_H
#include "config.h"
#else
#define PACKAGE_STRING "miscompiled constant-affirmation wihtout a version (you did it wrong)"
#endif

int run;

static void main_send_notification()
{
    GError *error = NULL;
    NotifyNotification *notification = notify_notification_new("You're doing a great job!", "Keep up the good work! What you're doing is fantastic! Good job!", 0);
    notify_notification_show(notification, &error);
}

static void main_sig_shutdown(int signo)
{
    run = 0;
}

static void main_loop(int seconds)
{
    struct sigaction new_sig, old_sig;
    new_sig.sa_handler = main_sig_shutdown;
    sigemptyset(&new_sig.sa_mask);
    new_sig.sa_flags = 0;

    sigaction(SIGINT, NULL, &old_sig);
    if (old_sig.sa_handler != SIG_IGN)
        sigaction(SIGINT, &new_sig, NULL);
    sigaction(SIGTERM, NULL, &old_sig);
    if (old_sig.sa_handler != SIG_IGN)
        sigaction(SIGTERM, &new_sig, NULL);

    run = 1;
    notify_init("Constant Affirmation");
    while (run)
    {
        main_send_notification();
        sleep(seconds);
    }
    notify_uninit();
}

static void main_run_as_daemon(int seconds)
{
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork");
        exit(1);
    }

    if (pid > 0)
        return;

    umask(0);
    if (setsid() < 0)
    {
        perror("setsid");
        exit(1);
    }

    if (chdir("/") < 0)
    {
        perror("chdir");
        exit(2);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    main_loop(seconds);
    exit(0);
}

static void main_show_version()
{
    printf("%s\n", PACKAGE_STRING);
    exit(0);
}

static void main_show_usage()
{
    printf("Usage: affirmation [options]\n");
    printf("options\n");
    printf("-f            Run in foreground instead of as a daemon\n");
    printf("-h            Display this help and exit\n");
    printf("-s SECONDS    Seconds between each affirmation [default: 30]\n");
    printf("-v            Display version info and exit\n");
    exit(0);
}

int main(int argc, char **argv)
{
    int opt;
    int daemon = 1;
    int seconds = 30;
    while ((opt = getopt(argc, argv, "fhvs:")) != -1)
    {
        switch (opt)
        {
        case 'h':
            main_show_usage();
            break;
        case 'v':
            main_show_version();
            break;
        case 'f':
            daemon = 0;
            break;
        case 's':
            seconds = atoi(optarg);
            if (seconds < 1)
                seconds = 1;
            break;
        }
    }

    printf("You shall receive new affirmations every %d seconds!\n", seconds);
    printf("I hope you enjoy your constant affirmation! Have a great day!\n");

    if (daemon)
        main_run_as_daemon(seconds);
    else
        main_loop(seconds);

    return 0;
}
