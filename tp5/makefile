#  Jérôme Skoda <contact@jeromeskoda.fr>

.PHONY: clean tar run-inherit run-explicit mrproper

CC = gcc
CFLAGS = -pthread -g -Wall --std=gnu99 -Werror

BIN_DIR = bin
SRC_DIR = src

TGZ= Skoda_Jerome_TP5.tgz
EXEC_FILE = bin/thread_priority_invert

all: $(EXEC_FILE)

$(EXEC_FILE): src/thread_priority_invert.c
	@mkdir -p $(dir $@)
	$(CC) -o $@ $^ $(CFLAGS)

run-inherit: $(EXEC_FILE)
	sudo taskset -c 0 $^

run-explicit: $(EXEC_FILE)
	taskset -c 0 $^ 0

clean:
	rm -rf */*.o */*.a */*.so

mrproper: clean
	rm -rf $(EXEC_FILE)
	rm -rf $(TGZ)

tar: clean
	@rm -rf $(TGZ)
	@tar -zcvf $(TGZ) *
	@echo "Archive "$(TGZ)" créé!"
