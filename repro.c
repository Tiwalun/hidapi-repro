#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <hidapi.h>

void* thread_fun(void* data);

int main() {
    
    const uint32_t num_tries = 100;

    for (uint32_t i = 0; i < num_tries; i++) {
        printf("Try %u\n", i);

        pthread_t thread;
        int res = pthread_create(&thread, NULL, &thread_fun, &i);

        if (res != 0) {
            printf("Failed to create thread\n");
            return -1;
        }

        res = pthread_join(thread, NULL);
        if (res != 0) {
            printf("Failed to join thread\n");
            return -1;
        }
    }

    return 0;
}

void* thread_fun(void* data) {
    uint32_t iteration = *((uint32_t*)data);
    char thread_name[100];
    sprintf(thread_name, "try %u", iteration);
    pthread_setname_np(thread_name);

    if (iteration == 0)
    {
        int res = hid_init();

        if (res != 0) {
            printf("Failed to initialize hidapi!");
        }
    }

    struct hid_device_info* enumeration = hid_enumerate(0, 0);

    if (enumeration != NULL)
    {
        hid_free_enumeration(enumeration);
    } 
    else 
    {
        printf("Failed to enumerate HID devices!");
    }


    return NULL;
}