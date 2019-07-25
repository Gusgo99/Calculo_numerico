# Compilador e padrao da linguagem
CC			:=	c++
STD			:=	c++17

# Diretorios
INCDIR		:=	./include
SRCDIR		:=	./src
BINDIR		:=	./bin
OBJDIR		:=	./objects

# Flags
CFLAGS		:=	-Wall -Wextra -Wshadow -Wcast-align -Wunused -pedantic -O0 -DDEBUG
CPPFLAGS	:=	-Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual
INCHEADERS	:= -iquote$(INCDIR)

##################################################################################################################################################
# Debug

# Atualiza executavel de debug a partir dos object files
$(BINDIR)/debug/calculo_numerico.exe: $(OBJDIR)/debug/main.o $(OBJDIR)/debug/zeros.o $(OBJDIR)/debug/interpolacao.o $(OBJDIR)/debug/SEL.o
	$(CC) $(OBJDIR)/debug/*.o -o $(BINDIR)/debug/calculo_numerico.exe -O0

# Atualiza object files de debug
$(OBJDIR)/debug/main.o: $(SRCDIR)/main.cpp $(INCDIR)/zeros.hpp $(INCDIR)/interpolacao.hpp $(INCDIR)/SEL.hpp
	$(CC) -std=$(STD) $(SRCDIR)/main.cpp -c -o $(OBJDIR)/debug/main.o $(INCHEADERS) $(CFLAGS) $(CPPFLAGS)

$(OBJDIR)/debug/zeros.o: $(INCDIR)/zeros.hpp $(SRCDIR)/zeros.cpp
	$(CC) -std=$(STD) $(SRCDIR)/zeros.cpp -c -o $(OBJDIR)/debug/zeros.o $(INCHEADERS) $(CFLAGS) $(CPPFLAGS)
	
$(OBJDIR)/debug/interpolacao.o: $(INCDIR)/interpolacao.hpp $(SRCDIR)/interpolacao.cpp
	$(CC) -std=$(STD) $(SRCDIR)/interpolacao.cpp -c -o $(OBJDIR)/debug/interpolacao.o $(INCHEADERS) $(CFLAGS) $(CPPFLAGS)
	
$(OBJDIR)/debug/SEL.o: $(INCDIR)/SEL.hpp $(SRCDIR)/SEL.cpp
	$(CC) -std=$(STD) $(SRCDIR)/SEL.cpp -c -o $(OBJDIR)/debug/SEL.o $(INCHEADERS) $(CFLAGS) $(CPPFLAGS)

##################################################################################################################################################
# Prod

# Atualiza executavel de prod a partir dos object files
$(BINDIR)/prod/calculo_numerico.exe: $(OBJDIR)/prod/main.o $(OBJDIR)/prod/zeros.o $(OBJDIR)/prod/interpolacao.o $(OBJDIR)/prod/SEL.o
	$(CC) $(OBJDIR)/prod/*.o -o $(BINDIR)/prod/calculo_numerico.exe -O3

# Atualiza object files de prod
$(OBJDIR)/prod/main.o: $(SRCDIR)/main.cpp $(INCDIR)/zeros.hpp $(INCDIR)/interpolacao.hpp $(INCDIR)/SEL.hpp
	$(CC) -std=$(STD) $(SRCDIR)/main.cpp -c -o $(OBJDIR)/prod/main.o $(INCHEADERS) -O3

$(OBJDIR)/prod/zeros.o: $(INCDIR)/zeros.hpp $(SRCDIR)/zeros.cpp
	$(CC) -std=$(STD) $(SRCDIR)/zeros.cpp -c -o $(OBJDIR)/prod/zeros.o $(INCHEADERS) -O3
	
$(OBJDIR)/prod/interpolacao.o: $(INCDIR)/interpolacao.hpp $(SRCDIR)/interpolacao.cpp
	$(CC) -std=$(STD) $(SRCDIR)/interpolacao.cpp -c -o $(OBJDIR)/prod/interpolacao.o $(INCHEADERS) -O3
	
$(OBJDIR)/prod/SEL.o: $(INCDIR)/SEL.hpp $(SRCDIR)/SEL.cpp
	$(CC) -std=$(STD) $(SRCDIR)/SEL.cpp -c -o $(OBJDIR)/prod/SEL.o $(INCHEADERS) -O3

.PHONY: clean cleaner prod disassemble prodDisassemble

# Limpa objetos criados (somente windows)
clean:
	del .\objects\debug\*.o
	del .\objects\prod\*.o

# Limpa tudo (objetos, binarios) (somente windows)
cleaner: clean
	del .\bin\debug\*.exe
	del .\bin\prod\*.exe
	del .\*.log

# Compila arquivos com otimizacao para runtime.
prod: $(BINDIR)/prod/calculo_numerico.exe