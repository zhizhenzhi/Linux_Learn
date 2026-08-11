CC:=gcc

system_test:system_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

fork:fork.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

fork_fd:fork_fd.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

erlou:erlou.c
	-$(CC) -o $@ $^

exceve:exceve.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@


fork_execve:fork_execve.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

waitpid:waitpid.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@


pstree:pstree.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

perror:perror.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

unnamed_pipe:unnamed_pipe.c
	-$(CC) -o $@ $^
	-./$@ "test"
	-rm ./$@


fifo_write:fifo_write.c
	-$(CC) -o $@ $^

fifo_read:fifo_read.c
	-$(CC) -o $@ $^

shared_memory:shared_memory.c
	-$(CC) -o $@ $^
	-./$@ "test"
	-rm ./$@

mq_test:mq_test.c
	-$(CC) -o $@ $^
	-./$@ "test"
	-rm ./$@

producer:producer.c
	-$(CC) -o $@ $^

consumer:consumer.c
	-$(CC) -o $@ $^

signal:signal.c
	-$(CC) -o $@ $^
	-./$@ "test"
	-rm ./$@
