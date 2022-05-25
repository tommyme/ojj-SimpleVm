mac: vm.o

test: mac
	./mac

.PHONY: clean
clean:
	rm -rf mac *.o