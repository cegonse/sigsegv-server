all: server

server:
	@mkdir -p build
	@cd build && cmake .. && make && cd ..

test: server
	@find build -name "test_*" -type f -perm +111 -print0 | xargs -0 -I % sh -c %

clean:
	@rm -rf build
	@rm -rf *.dSYM

.PHONY: clean server
