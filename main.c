#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

FILE *sfp;

static size_t header_callback(char *buffer, size_t size, size_t nitems, void *userdata)
{
    if (strstr(buffer, "onion-location:"))
    {
        printf("Found onion-location: %s\n", buffer);
        fprintf(sfp, "%s", buffer);
    }

    return nitems * size;
}

int main(int argc, char *argv[])
{

    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("top.csv", "r");
    if (fp == NULL)
    {
        exit(EXIT_FAILURE);
    }

    sfp = fopen("success.txt", "a");
    if (sfp == NULL)
    {
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, fp)) != -1)
    {
        CURL *curl;
        CURLcode res;

        char *token = strtok(line, ",");
        char *record[2];
        int i = 0;
        while (token != NULL)
        {
            record[i] = token;
            token = strtok(NULL, ",");
            i++;

            if (i == 2)
            {
                break;
            }
        }

        char *url = strtok(record[1], "\r\n");
        if (url)
        {
            curl = curl_easy_init();
            if (curl)
            {
                printf("Checking: %s\n", url);

                curl_easy_setopt(curl, CURLOPT_URL, url);
                curl_easy_setopt(curl, CURLOPT_HEADER, 0L);
                curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
                curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
                curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
                curl_easy_setopt(curl, CURLOPT_TIMEOUT, 1L);
                curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);

                res = curl_easy_perform(curl);
                if (res != CURLE_OK)
                {
                    continue;
                }
            }
        }
        curl_easy_cleanup(curl);
    }

    fclose(fp);
    fclose(sfp);

    if (line)
    {
        free(line);
    }

    exit(EXIT_SUCCESS);
}
