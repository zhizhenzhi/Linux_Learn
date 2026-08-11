CC:=gcc
virtual:virtual.c
	-$(CC) -o $@ $^
	-./$@ "test"
	-rm ./$@