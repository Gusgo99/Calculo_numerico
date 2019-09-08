# Flags do make
MAKEFLAGS	:= -j18

NOMEPROJ	:= calculo_numerico

# Compilador e padrao da linguagem
CC			:=	c++
STD			:=	c++17

# Diretorios
INCDIR		:=	include
SRCDIR		:=	src
BINDIR		:=	bin
OBJDIR		:=	objects

# Flags
CFLAGS		:= -Wall -Wextra -Wshadow -Wcast-align -Wunused -pedantic -O0 -DDEBUG -g
CPPFLAGS	:= -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual
LINKFLAGS	:= -LC:/libraries/lib -g
INCHEADERS	:= -iquote$(INCDIR)
LIBRARIES	:= -IC:/libraries/include

##################################################################################################################################################
# Debug

# Atualiza executavel de debug a partir dos object files
$(BINDIR)/debug/$(NOMEPROJ)_debug.exe: 	$(OBJDIR)/debug/main.o				\
										$(OBJDIR)/debug/zeros.o				\
										$(OBJDIR)/debug/interpolacao.o		\
										$(OBJDIR)/debug/SEL.o				\
										$(OBJDIR)/debug/EDO.o				\
										$(OBJDIR)/debug/mathio.o			\
										$(OBJDIR)/debug/integracao.o
	$(CC) $(OBJDIR)/debug/*.o -o $(BINDIR)/debug/$(NOMEPROJ)_debug.exe $(LINKFLAGS)

# Atualiza object files de debug
$(OBJDIR)/debug/main.o:	$(SRCDIR)/main.cpp							\
						$(INCDIR)/EDO.hpp							\
						$(INCDIR)/integracao.hpp					\
						$(INCDIR)/interpolacao.hpp					\
						$(INCDIR)/mathio.hpp						\
						$(INCDIR)/SEL.hpp							\
						$(INCDIR)/zeros.hpp
	$(CC) -std=$(STD) $(SRCDIR)/main.cpp -c -o $(OBJDIR)/debug/main.o $(INCHEADERS) $(CFLAGS) $(CPPFLAGS) $(LIBRARIES)
	
$(OBJDIR)/debug/%.o: $(SRCDIR)/%.cpp $(INCDIR)/%.hpp
	$(CC) -std=$(STD) $< -c -o $@ $(INCHEADERS) $(CFLAGS) $(CPPFLAGS) $(LIBRARIES)

##################################################################################################################################################
# Release

# Atualiza executavel de release a partir dos object files
$(BINDIR)/release/$(NOMEPROJ).exe: 	$(OBJDIR)/release/main.o				\
									$(OBJDIR)/release/zeros.o				\
									$(OBJDIR)/release/interpolacao.o		\
									$(OBJDIR)/release/SEL.o					\
									$(OBJDIR)/release/EDO.o					\
									$(OBJDIR)/release/mathio.o				\
									$(OBJDIR)/release/integracao.o
	$(CC) $(OBJDIR)/release/*.o -o $(BINDIR)/release/$(NOMEPROJ).exe -LC:/libraries/lib

# Atualiza object files de release
$(OBJDIR)/release/main.o:	$(SRCDIR)/main.cpp							\
							$(INCDIR)/EDO.hpp							\
							$(INCDIR)/integracao.hpp					\
							$(INCDIR)/interpolacao.hpp					\
							$(INCDIR)/mathio.hpp						\
							$(INCDIR)/SEL.hpp							\
							$(INCDIR)/zeros.hpp
	$(CC) -std=$(STD) $(SRCDIR)/main.cpp -c -o $(OBJDIR)/release/main.o $(INCHEADERS) -O3 $(LIBRARIES)
	
$(OBJDIR)/release/%.o: $(SRCDIR)/%.cpp $(INCDIR)/%.hpp
	$(CC) -std=$(STD) $< -c -o $@ $(INCHEADERS) $(LIBRARIES) -O3
	
$(OBJDIR)/release:
	@ mkdir $(OBJDIR)\release

.PHONY: clean cleaner release setup exec exec_release

# Limpa objetc files (somente windows)
clean:
	@ del .\objects\debug\*.o
	@ del .\objects\release\*.o

# Limpa tudo (objetos, binarios) (somente windows)
cleaner: clean
	@ del .\bin\debug\*.exe
	@ del .\bin\release\*.exe
	@ del .\*.log

# Compila arquivos sem otimizacao.
debug: $(BINDIR)/debug/$(NOMEPROJ)_debug.exe

# Compila arquivos com otimizacao para runtime.
release: $(BINDIR)/release/$(NOMEPROJ).exe

# Executa arquivos gerados para debug e gera log
exec:
	@ cls
	@ $(BINDIR)/debug/$(NOMEPROJ)_debug.exe

exec_release:
	@ cls
	@ $(BINDIR)/release/$(NOMEPROJ).exe

setup:
	@ mkdir $(OBJDIR)\debug
	@ mkdir $(OBJDIR)\release
	@ mkdir $(BINDIR)\debug
	@ mkdir $(BINDIR)\release
