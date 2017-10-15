.PHONY: clean doc rapport

CC=gcc
CFLAGS= -Wall

# Repertoire global
SRCDIR     := src
OBJDIR     := obj
BINDIR     := bin

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
all:  $(OBJECTS_COLIMACON) $(OBJECTS_DEMO) $(OBJECTS_TEST) $(BIN_DEMO) $(BIN_TEST)

# Recette de compilatation de objets de démo
$(OBJDIR_DEMO)/%.o : $(SRCDIR_DEMO)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "Compilation "$<" reussite!"

# Recette de compilatation de objets de test
$(OBJDIR_TEST)/%.o : $(SRCDIR_TEST)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "Compilation "$<" reussite!"

# Recette de compilatation de objets de la bibliotheque COLIMACON
$(OBJDIR_COLIMACON)/%.o : $(SRCDIR_COLIMACON)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "Compilation "$<" reussite!"

# Recette de compilatation des exécutable de test
$(BINDIR_TEST)/%: $(OBJDIR_TEST)/%.o $(OBJECTS_COLIMACON)
	@mkdir -p $(dir $@)
	@$(CC) $(OBJECTS_COLIMACON) $(subst $(BINDIR_TEST)/,$(OBJDIR_TEST)/,$@).o -o $@
	@echo "Compilation "$<" reussite!"

# Recette de compilatation des exécutable de demo
$(BINDIR_DEMO)/%: $(OBJDIR_DEMO)/%.o $(OBJECTS_COLIMACON)
	@mkdir -p $(dir $@)
	@$(CC) $(OBJECTS_COLIMACON) $(subst $(BINDIR_DEMO)/,$(OBJDIR_DEMO)/,$@).o -o $@
	@echo "Compilation "$<" reussite!"

# Netoyage du projet
clean:
	@rm -rf $(OBJDIR)
	@echo "Répertoire "$(OBJDIR)" supprimé"
	@rm -rf $(BINDIR)
	@echo "Répertoire "$(BINDIR)" supprimé"

# Lancement de script de test
test: all
	@chmod +x script/test.sh
	@./script/test.sh
	@echo "\n\nScript de test terminé"

# Lancement du générateur de document
doc:
	@doxygen doc/doxyfile
	@echo "\n\nGénération de la doc terminé"

# Lancement du générateur de rapport
rapport:
	@cd rapport && $(MAKE) 
	@cp rapport/rapport.pdf rapport.pdf 
	@echo "\n\nGénération du rapport terminé"
