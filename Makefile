# Makefile - Exportado do CMakeLists.txt com apoio de IA

CC ?= cc
AR ?= ar
CFLAGS ?= -std=c11 -Wall -Wextra -g -I./src
LDFLAGS ?=
RANLIB ?= ranlib

OBJDIR := obj
BINDIR := bin
LIBDIR := lib

LIB1_SRCS := src/lib/cliente.c src/lib/decisao.c src/lib/avl.c
LIB2_SRCS := src/classificacao.c src/armazenamento.c src/validacao.c
MAIN_SRC  := src/main.c

TEST_SRCS := test/cliente_test.c test/avl_test.c test/decisao_test.c

LIB1_OBJS := $(patsubst src/%.c,$(OBJDIR)/%.o,$(LIB1_SRCS))
LIB2_OBJS := $(patsubst src/%.c,$(OBJDIR)/%.o,$(LIB2_SRCS))
MAIN_OBJ  := $(patsubst src/%.c,$(OBJDIR)/%.o,$(MAIN_SRC))
TEST_OBJS := $(patsubst test/%.c,$(OBJDIR)/test/%.o,$(TEST_SRCS))

LIB1 := $(LIBDIR)/libufabc_aedi_proj_lib.a
LIB2 := $(LIBDIR)/libufabc_aedi_proj_helpers.a

MAIN_BIN := $(BINDIR)/ufabc_aedi_proj
TEST_BINS := $(BINDIR)/run_cliente_tests $(BINDIR)/run_avl_tests $(BINDIR)/run_decisao_tests

$(BINDIR)/run_cliente_tests: $(OBJDIR)/test/cliente_test.o $(LIB1) $(LIB2)
	@mkdir -p $(BINDIR)
	$(CC) $(LDFLAGS) -o $@ $< -L$(LIBDIR) -lufabc_aedi_proj_helpers -lufabc_aedi_proj_lib

$(BINDIR)/run_avl_tests: $(OBJDIR)/test/avl_test.o $(LIB1) $(LIB2)
	@mkdir -p $(BINDIR)
	$(CC) $(LDFLAGS) -o $@ $< -L$(LIBDIR) -lufabc_aedi_proj_lib

$(BINDIR)/run_decisao_tests: $(OBJDIR)/test/decisao_test.o $(LIB1) $(LIB2)
	@mkdir -p $(BINDIR)
	$(CC) $(LDFLAGS) -o $@ $< -L$(LIBDIR) -lufabc_aedi_proj_lib

$(MAIN_BIN): $(MAIN_OBJ) $(LIB1) $(LIB2)
	@mkdir -p $(BINDIR)
	$(CC) $(LDFLAGS) -o $@ $(MAIN_OBJ) -L$(LIBDIR) -lufabc_aedi_proj_helpers -lufabc_aedi_proj_lib

$(LIB1): $(LIB1_OBJS)
	@mkdir -p $(LIBDIR)
	$(AR) rcs $@ $^
	-$(RANLIB) $@ 2>/dev/null || true

$(LIB2): $(LIB2_OBJS)
	@mkdir -p $(LIBDIR)
	$(AR) rcs $@ $^
	-$(RANLIB) $@ 2>/dev/null || true

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/test/%.o: test/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I./src -c -o $@ $<

.PHONY: all clean test help

all: $(MAIN_BIN) $(TEST_BINS)

test: all
	@echo "Running cliente tests..."
	@$(BINDIR)/run_cliente_tests criacao || { echo "cliente criacao: FAIL"; exit 1; }
	@$(BINDIR)/run_cliente_tests idade || { echo "cliente idade: FAIL"; exit 1; }
	@$(BINDIR)/run_cliente_tests cnh || { echo "cliente cnh: FAIL"; exit 1; }
	@$(BINDIR)/run_cliente_tests inadimplencia || { echo "cliente inadimplencia: FAIL"; exit 1; }
	@$(BINDIR)/run_cliente_tests acidentes || { echo "cliente acidentes: FAIL"; exit 1; }
	@$(BINDIR)/run_cliente_tests gastos || { echo "cliente gastos: FAIL"; exit 1; }
	@$(BINDIR)/run_cliente_tests dias || { echo "cliente dias: FAIL"; exit 1; }
	@echo "Running avl tests..."
	@$(BINDIR)/run_avl_tests criacao || { echo "avl criacao: FAIL"; exit 1; }
	@$(BINDIR)/run_avl_tests simples || { echo "avl simples: FAIL"; exit 1; }
	@$(BINDIR)/run_avl_tests multipla || { echo "avl multipla: FAIL"; exit 1; }
	@$(BINDIR)/run_avl_tests rot_dir || { echo "avl rot_dir: FAIL"; exit 1; }
	@$(BINDIR)/run_avl_tests rot_esq || { echo "avl rot_esq: FAIL"; exit 1; }
	@$(BINDIR)/run_avl_tests rot_lr || { echo "avl rot_lr: FAIL"; exit 1; }
	@$(BINDIR)/run_avl_tests rot_rl || { echo "avl rot_rl: FAIL"; exit 1; }
	@$(BINDIR)/run_avl_tests busca || { echo "avl busca: FAIL"; exit 1; }
	@echo "Running decisao tests..."
	@$(BINDIR)/run_decisao_tests folha || { echo "decisao folha: FAIL"; exit 1; }
	@$(BINDIR)/run_decisao_tests simples || { echo "decisao simples: FAIL"; exit 1; }
	@$(BINDIR)/run_decisao_tests complexa || { echo "decisao complexa: FAIL"; exit 1; }
	@echo "ALL TESTS PASSED"

clean:
	@echo "Cleaning build artifacts..."
	@rm -rf $(OBJDIR) $(LIBDIR) $(BINDIR)

help:
	@echo "Makefile targets:"
	@echo "  make        -> build main binary and tests"
	@echo "  make test   -> build & run tests (runs each test executable with args)"
	@echo "  make clean  -> remove obj/, lib/, bin/"
