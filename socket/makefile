CC:=gcc
num_endianess:num_endianess.c
	-$(CC) -o $@ $^
	-./$@ "test"
	-rm ./$@

inet_endian:inet_endian.c
	-$(CC) -o $@ $^
	-./$@ "test"
	-rm ./$@

server:server.c
	-$(CC) -o $@ $^

client:client.c
	-$(CC) -o $@ $^

multi_thread_server:multi_thread_server.c
	-$(CC) -o $@ $^

multi_thread_client:multi_thread_client.c
	-$(CC) -o $@ $^

udp_server:udp_server.c
	-$(CC) -o $@ $^

udp_client:udp_client.c
	-$(CC) -o $@ $^