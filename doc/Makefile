DOCUMENT=thesis
#MODE=-interaction=batchmode

ifeq ($(OS),Windows_NT)
SHELL := pwsh.exe
.SHELLFLAGS := -NoProfile -Command
endif

.PHONY: all clean

all:
	@latexmk -pdf thesis.tex -latexoption=-file-line-error -latexoption=-interaction=batchmode -quiet -shell-escape -bibtex -f
	@make clean

clean:
	@echo Cleaning temporary files...
	@rm **/*.aux, *.aux, *.fdb_latexmk, *.dvi, *.thm, *.lof, *.log, *.lot, *.fls, *.out, *.toc, *.bbl, *.blg