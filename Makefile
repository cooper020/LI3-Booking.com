CC=gcc

CFLAGS=-Wall -Iinclude `pkg-config --cflags glib-2.0` -o3 -g

LDFLAGS=`pkg-config --libs glib-2.0` -lm -lncurses

ODIR = objects

all: programa-principal programa-testes

programa-principal: $(ODIR)/main.o $(ODIR)/executor.o $(ODIR)/tests_funcs.o $(ODIR)/catalog_u.o $(ODIR)/validacao.o $(ODIR)/users.o $(ODIR)/flights.o $(ODIR)/passengers.o $(ODIR)/reservations.o $(ODIR)/catalog_f.o $(ODIR)/catalog_p.o $(ODIR)/catalog_r.o $(ODIR)/date.o $(ODIR)/queries.o $(ODIR)/parser.o $(ODIR)/view.o $(ODIR)/menus.o $(ODIR)/page.o $(ODIR)/output.o
	@mkdir -p Resultados
	@mkdir -p $(ODIR)
	$(CC) $^ $(LDFLAGS) $(CFLAGS) -o $@

programa-testes: $(ODIR)/main_tests.o $(ODIR)/tests_funcs.o $(ODIR)/executor.o $(ODIR)/catalog_u.o $(ODIR)/validacao.o $(ODIR)/users.o $(ODIR)/flights.o $(ODIR)/passengers.o $(ODIR)/reservations.o $(ODIR)/catalog_f.o $(ODIR)/catalog_p.o $(ODIR)/catalog_r.o $(ODIR)/date.o $(ODIR)/queries.o $(ODIR)/parser.o $(ODIR)/view.o $(ODIR)/menus.o $(ODIR)/page.o $(ODIR)/output.o
	@mkdir -p Resultados
	@mkdir -p $(ODIR)
	$(CC) $^ $(LDFLAGS) $(CFLAGS) -o $@

$(ODIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -f programa-principal programa-testes $(ODIR)/*.o Resultados/*.csv Resultados/*.txt

