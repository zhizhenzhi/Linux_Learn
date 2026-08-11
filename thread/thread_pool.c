#include <glib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
void task_func(gpointer data,gpointer user_data){
    int task_num=*(int*)data;
    free(data);
    printf("start %d\n",task_num);
    sleep(task_num);
}
int main(int argc, char const *argv[])
{
    GThreadPool *pool=g_thread_pool_new(task_func,NULL,5,TRUE,NULL);
    for (size_t i = 0; i < 10; i++)
    {
        int *tmp=malloc(sizeof(int));
        *tmp=i+1;
        g_thread_pool_push(pool,tmp,NULL);
    }

    g_thread_pool_free(pool,false,true);
    printf("end\n");
    return 0;
}
