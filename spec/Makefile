spec.pdf: spec.tex style.sty coding-style.tex hypersetup.tex submission.tex title.tex
	xelatex $< && xelatex $< && xelatex $<

.PHONY: clean
clean:
	rm -f *.aux *.log *.out *.toc *.pdf *.bak
