.PHONY: clean doc rapport lib obj bin demo-1 demo-2 demo-3 demo-4 demo-5 demo-6 test

CC=gcc
CFLAGS= -Wall -Werror
TGZ= Skoda_Jerome_TP2.tgz

# Repertoire global
SRCDIR     := src
OBJDIR     := obj
BINDIR     := bin
LIBDIR     := lib

#Lib
COLIMACON_STATIC   := $(LIBDIR)/colimacon.a
COLIMACON_DYNMIC   := $(LIBDIR)/colimacon.so

# Zone source de COLIMACON
COLIMACON_DIR      := colimacon
SRCDIR_COLIMACON   := $(SRCDIR)/$(COLIMACON_DIR)
OBJDIR_COLIMACON   := $(OBJDIR)/$(COLIMACON_DIR)
SOURCES_COLIMACON  := $(wildcard $(SRCDIR_COLIMACON)/*.c)
HEADERS_COLIMACON  := $(wildcard $(SRCDIR_COLIMACON)/*.h)
OBJECTS_COLIMACON  := $(SOURCES_COLIMACON:$(SRCDIR_COLIMACON)/%.c=$(OBJDIR_COLIMACON)/%.o)

# Zone source de démo
DEMO_DIR      := demo
SRCDIR_DEMO   := $(SRCDIR)/$(DEMO_DIR)
OBJDIR_DEMO   := $(OBJDIR)/$(DEMO_DIR)
SOURCES_DEMO  := $(wildcard $(SRCDIR_DEMO)/*.c)
HEADERS_DEMO  := $(wildcard $(SRCDIR_DEMO)/*.h)
OBJECTS_DEMO  := $(SOURCES_DEMO:$(SRCDIR_DEMO)/%.c=$(OBJDIR_DEMO)/%.o)

# Zone source de test
TEST_DIR      := test
SRCDIR_TEST   := $(SRCDIR)/$(TEST_DIR)
OBJDIR_TEST   := $(OBJDIR)/$(TEST_DIR)
SOURCES_TEST  := $(wildcard $(SRCDIR_TEST)/*.c)
HEADERS_TEST  := $(wildcard $(SRCDIR_TEST)/*.h)
OBJECTS_TEST  := $(SOURCES_TEST:$(SRCDIR_TEST)/%.c=$(OBJDIR_TEST)/%.o)

# Zone binaire de démo
BINDIR_DEMO   := $(BINDIR)/$(DEMO_DIR)
BIN_DEMO      := $(patsubst $(SRCDIR_DEMO)/%.c,$(BINDIR_DEMO)/%,$(SOURCES_DEMO))

# Zone binaire de test
BINDIR_TEST   := $(BINDIR)/$(TEST_DIR)
BIN_TEST      := $(patsubst $(SRCDIR_TEST)/%.c,$(BINDIR_TEST)/%,$(SOURCES_TEST))

# Recette pour une compilation complete
all: lib obj bin

lib: $(COLIMACON_STATIC) $(COLIMACON_DYNMIC)

obj: $(OBJECTS_COLIMACON) $(OBJECTS_DEMO) $(OBJECTS_TEST)

bin: $(BIN_TEST) $(BIN_DEMO)

# Recette de compilatation de objets de démo
$(OBJDIR_DEMO)/%.o : $(SRCDIR_DEMO)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "Compilation "$@" reussite!"

# Recette de compilatation de objets de test
$(OBJDIR_TEST)/%.o : $(SRCDIR_TEST)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "Compilation "$@" reussite!"

# Recette de compilatation de objets de la bibliotheque COLIMACON
$(OBJDIR_COLIMACON)/%.o : $(SRCDIR_COLIMACON)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "Compilation "$@" reussite!"

# Recette de compilatation des exécutable de test
$(BINDIR_TEST)/%: $(OBJDIR_TEST)/%.o $(OBJECTS_COLIMACON)
	@mkdir -p $(dir $@)
	@$(CC) $(OBJECTS_COLIMACON) $(subst $(BINDIR_TEST)/,$(OBJDIR_TEST)/,$@).o -o $@
	@echo "Compilation "$@" reussite!"

# Recette de compilatation des exécutable de demo
$(BINDIR_DEMO)/%: $(OBJDIR_DEMO)/%.o $(OBJECTS_COLIMACON)
	@mkdir -p $(dir $@)
	@$(CC) $(OBJECTS_COLIMACON) $(subst $(BINDIR_DEMO)/,$(OBJDIR_DEMO)/,$@).o -o $@
	@echo "Compilation "$@" reussite!"

# Netoyage du projet
clean:
	@rm -rf $(OBJDIR)
	@echo "Répertoire "$(OBJDIR)" supprimé"
	@rm -rf $(BINDIR)
	@echo "Répertoire "$(BINDIR)" supprimé"
	@rm -rf $(LIBDIR)
	@echo "Répertoire "$(LIBDIR)" supprimé"

# Lancement de script de test
test: $(BIN_TEST)
	@chmod +x script/test.sh
	@./script/test.sh
	@echo "Script de test terminé"

# Lancement du générateur de document
doc:
	@doxygen doc/doxyfile
	@echo "Génération de la doc terminé"

# Lancement du générateur de rapport
rapport:
	@cd rapport && $(MAKE)
	@cp rapport/rapport.pdf rapport.pdf
	@echo "Génération du rapport terminé"

# Lancement des démos
demo-1: $(BIN_DEMO)
ifndef ligne
	@echo "Utilisation: make demo-1 ligne=X col=X"
else
ifndef col
	@echo "Utilisation: make demo-1 ligne=X col=X"
else
		@./bin/demo/1-colimacon $(ligne) $(col)
		@echo "Démo terminé"
endif
endif

demo-2: $(BIN_DEMO)
	@./bin/demo/2-horizontal
	@echo "Démo terminé"

demo-3: $(BIN_DEMO)
	@./bin/demo/3-vertical
	@echo "Démo terminé"

demo-4: $(BIN_DEMO)
	@./bin/demo/4-carre
	@echo "Démo terminé"

demo-5: $(BIN_DEMO)
ifndef ligne
	@echo "Utilisation: make demo-5 ligne=X col=X"
else
ifndef col
	@echo "Utilisation: make demo-5 ligne=X col=X"
else
		@./bin/demo/5-colimacon-no-print $(ligne) $(col)
		@echo "Démo terminé"
endif
endif

demo-6: $(BIN_DEMO)
ifndef ligne
	@echo "Utilisation: make demo-6 ligne=X col=X"
else
ifndef col
	@echo "Utilisation: make demo-6 ligne=X col=X"
else
		@./bin/demo/6-colimacon-time $(ligne) $(col)
		@echo "Démo terminé"
endif
endif

bench: $(BIN_DEMO)
ifndef echantillon
	@echo "Utilisation: make bench echantillon=X fichier=X"
else
ifndef fichier
	@echo "Utilisation: make bench echantillon=X fichier=X"
else
		@./script/bench.sh $(echantillon) >> $(fichier)
		@echo "Bench terminé"
endif
endif

tgz:
	@$(MAKE) clean
	@rm -rf $(TGZ)
	@tar -zcvf $(TGZ) *
	@echo "Archive "$(TGZ)" créé!"


#lib
$(COLIMACON_STATIC): $(OBJECTS_COLIMACON)
	@mkdir -p $(dir $@)
	@ar -q $@ $(OBJECTS_COLIMACON)
	@echo "Compilation "$@" reussite!"


$(COLIMACON_DYNMIC): $(SOURCES_COLIMACON)
	@mkdir -p $(dir $@)
	@$(CC) -c -fpic -o $@ $(SOURCES_COLIMACON)
	@echo "Compilation "$@" reussite!"
