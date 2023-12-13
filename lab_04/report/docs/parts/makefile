PDF = RPZ_RAZIN_IU7_44B
MAIN = main
FLAGS = --shell-escape -interaction=nonstopmode
$(PDF) : $(MAIN).tex *.tex
	pdflatex $(FLAGS) $< 
	pdflatex  $(FLAGS) $<
	biber $(MAIN).bcf
	pdflatex  $(FLAGS) $<
	
	make clean



clean:
	rm  *.aux *.log *.out *.toc *.bbl  *.gz *.aux *.fls

.PHONY: clean, bib