#include "notification.h"

int notification_path(char *path)
{
#ifdef SYSCONFDIR
    return sprintf(path, "%s/affirmation", SYSCONFDIR);
#else
    return sprintf(path, "/etc/affirmation");
#endif
}

int notification_total()
{
    FILE *notification;
    int count = 0;
    char line[4096];
    char path[4096];

    notification_path(path);
    notification = fopen(path, "r");
    if (notification == NULL)
        return 0;

    while (fgets(line, 4096, notification))
        count++;

    fclose(notification);

    return count;
}

int notification_random(int lines, char *summary, char *body)
{
    int ret = 0;
    int count = 0;
    char line[4096];
    char path[4096];
    char *summary_temp;
    char *body_temp;
    char *tok = NULL;
    FILE *notification;
    time_t seed = time(NULL);
    int chosen = rand_r((unsigned int *)&seed) % lines;

    if (lines == 0)
        return 0;

    notification_path(path);
    notification = fopen(path, "r");
    if (notification == NULL)
        return 0;

    while (fgets(line, 4096, notification))
    {
        if (count == chosen)
        {
            summary_temp = strtok_r(line, "\t", &tok);
            body_temp = strtok_r(NULL, "\n", &tok);
            strncpy(summary, summary_temp, 4096);
            strncpy(body, body_temp, 4096);
            ret = 1;
        }
        count++;
    }

    fclose(notification);

    return ret;
}
