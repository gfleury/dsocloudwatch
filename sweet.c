
#include <stdio.h>
#include <dlfcn.h>

#include <pthread.h>
#include <stdint.h>
#include <unistd.h>

typedef int32_t                     ngx_atomic_int_t;
typedef uint32_t                    ngx_atomic_uint_t;
typedef volatile ngx_atomic_uint_t ngx_atomic_t;
extern ngx_atomic_t *ngx_stat_accepted;
//  *ngx_stat_handled;
//  *ngx_stat_active;
//  *ngx_stat_requests;
//  *ngx_stat_reading;
//  *ngx_stat_writing;
//  *ngx_stat_waiting;
//
void *__XX_collect_metrics_thread(void *x) {
		
	while (1) {
		if(ngx_stat_accepted) {
			printf("this -> %lu \n",*ngx_stat_accepted) ;
		}	
		sleep(10);
	}
}

static void* (*__XX_real_malloc)(size_t) = NULL;
static void __XX_wrapper(void);

void *malloc(size_t size) {
    if(__XX_real_malloc == NULL) {
        __XX_wrapper();
    }
	printf("salve");
    return __XX_real_malloc(size);
}

//static void* (*malloc)(size_t) = __XX_fake_malloc;

static void __XX_wrapper(void) {
	__XX_real_malloc = (void* (*)(size_t)) dlsym(RTLD_NEXT, "malloc");
	if (NULL == __XX_real_malloc) {
		fprintf(stderr, "Error in `dlsym`: %s\n", dlerror());
	}
	pthread_t _thread;
	if(pthread_create(&_thread, NULL, __XX_collect_metrics_thread, NULL)) {
		fprintf(stderr, "Error creating thread\n");
	}
// 	malloc = __XX_real_malloc; 
}

