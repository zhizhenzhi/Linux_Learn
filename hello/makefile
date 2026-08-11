# Makefile内容通常由三部分组成
#<目标名称>:<前置依赖>
#	\t<需要执行的命令>

#定义变量 objects
objects := hello.o \
main.o

#放在第一个的是默认目标
#目标是编译出main文件 依赖hello.o和main.o
#编译命令
main: $(objects)
	gcc $(objects) -o main 

# main.o:main.c hello.h
# 	gcc -c main.c -o main.o
main.o:hello.h

hello.o:hello.h
# hello.o:hello.c hello.h
# 	gcc -c hello.c

#声明伪目标
# .PHONY:clean

clean:
	-rm $(objects) main