# Derleyici ve bayraklar
CC      = gcc
CFLAGS  = -g -O0 -I Inc -Wall -Wextra -std=c99

# Klasör ve dosya tanımlamaları
SRCDIR  = Src
OBJDIR  = Obj
SOURCES = $(SRCDIR)/command_handler.c $(SRCDIR)/hash_table.c $(SRCDIR)/main.c
OBJECTS = $(OBJDIR)/command_handler.o $(OBJDIR)/hash_table.o $(OBJDIR)/main.o

# Nihai hedef: main.exe
main.exe: $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

# Obj klasörünü (dizinini) oluştur (yoksa)
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Genel derleme kuralı: %.c -> Obj/%.o
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Temizlik komutu: Obj klasörünü (içeriğiyle birlikte) siler
clean:
	@if exist $(OBJDIR) rmdir /S /Q $(OBJDIR)