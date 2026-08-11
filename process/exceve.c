#include <stdio.h>
#include <unistd.h>
int main(int argc, char const *argv[])
{
    char *name="banzhang";
    printf("%s\t%d\n",name,getpid());

    //执行跳转
    /*
    const char *__path:执行程序的路径
    char *const __argv[]:传入的参数 -》对应执行程序main方法的第二个参数
                    1.第一个参数固定是程序的名称--执行程序的路径
                    2.执行程序需要传入的参数
                    3.最后一个参数一定是NULL
    char *const __envp[]：传递的环境变量
                    1.环境变量参数：key=value
                    2.最后一个参数一定是NULL
    return: 成功根本没办法返回 下面的代码也没有意义 失败返回-1
    跳转前后只有进程号保留下来  别的变量都删除了
    int execve (const char *__path, char *const __argv[],
		   char *const __envp[])
    */
   char *args[]={"/home/yang/LINUX开发/process/erlou",name,NULL};
   char *envs[]={NULL};
    int re=execve(args[0],args,envs);
    if (re==-1)
    {
        printf("no\n");
        return 1;
    }
    //此处代码没有意义，因为程序跳转，不再往下执行
    return 0;
}
