CC:=gcc
create_thread:create_thread.c
	-$(CC) -o $@ $^
	-./$@ "test"
	-rm ./$@

terminate:terminate.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

detach:detach.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

cancel:cancel.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

mute:mute.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

read_write_lock:read_write_lock.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

rwlock:rwlock.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

rwlock_hungry:rwlock_hungry.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

cond:cond.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

sem_bin:sem_bin.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

unnamed_sem_count:unnamed_sem_count.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

unnamed_sem_count_process:unnamed_sem_count_process.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

named_sem_bin:named_sem_bin.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

thread_pool:thread_pool.c
	-$(CC) -o $@ $^ `pkg-config --cflags --libs glib-2.0`
	-./$@
	-rm ./$@