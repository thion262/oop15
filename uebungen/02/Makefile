Figures :=	$(wildcard *.mp)
PDFs :=		$(patsubst %.mp,%.pdf,$(Figures))
PDF1s :=	$(patsubst %.mp,%-1.pdf,$(Figures))
EPSFigures :=	$(patsubst %.mp,%.1,$(Figures))

.PHONY:		all
all:		$(PDFs)

$(PDFs):	%.pdf: %-1.pdf
		ln -s $< $@

$(PDF1s):	%-1.pdf: %.1
		rm -f $*.pdf
		mptopdf $*

$(EPSFigures):	%.1: %.mp
		rm -f $*.pdf
		mpost $*

.PHONY:		clean
clean:
		rm -f mptextmp.*
		rm -f mpx*
