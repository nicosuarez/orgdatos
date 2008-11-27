#
# Reglas genéricas para compilar los documentos. Se supone que las variables
# TARGET_FILES y TMP_FILES están definidas.
#

# Comandos de compilación ###############################################

# Script para compilar Latex, que compila tantas veces como sea necesario
# hasta que las referencias cruzadas queden correctas:
LATEX = latex
LATEX_OPTS = --interaction nonstopmode
LATEX2DVI = { \
	$(LATEX) $(LATEX_OPTS) $< && \
	while grep -q \
	'No file .*\.\(aux\|toc\).\|Rerun to get cross-references right.' \
	       $(basename $<).log ; \
	do \
		$(LATEX) $(LATEX_OPTS) $<; \
	done; }

LATEX2HTML = latex2html
LATEX2HTML_OPTS = -split 0 -ascii_mode -no_navigation -no_auto_link -show_section_numbers -toc_depth 5 -no_subdir -info 0

# Para pasar de HTML a PHP hay que reemplazar los links internos (referncias
# cruzadas):
# HTML2PHP = sed -e 's/$(basename $<)\.html/$(basename $<)\.php/g' $< >$@
HTML2PHP = awk 'BEGIN {body = 0} /<[ \t]*\/BODY[ \t]*>/ { body = 0 } { if (body) { gsub(/$(basename $<)\.html/, "$(basename $@).php"); print } } /<[ \t]*BODY[ \t]*>/ {body = 1}' $< >$@

DVI2PDF = dvipdf
DVI2PDF_OPTS =

LYX2LATEX = lyx
LYX2LATEX_OPTS = -e latex


# Reglas principales #####################################################

.PHONY: clean clean-tmp all

all: $(TARGET_FILES) clean-tmp

clean: clean-tmp
	@echo "Borrando objetivos de $(TARGET)..."
	@rm -fv $(TARGET_FILES)

clean-tmp:
	@echo "Borrando archivos temporales de $(TARGET)..."
	@rm -fv $(TMP_FILES)


# Reglas genéricas #######################################################

%.dvi : %.tex
	@echo "Generando $@..."
	@$(LATEX2DVI)

%.html : %.tex
	@echo "Generando $@..."
	@if [ $< -nt $*.aux ]; then $(LATEX2DVI) fi
	@$(LATEX2HTML) $(LATEX2HTML_OPTS) $<

index.php : $(TARGET).html
	@echo "Generando $@..."
	@$(HTML2PHP)

%.pdf: %.tex
	@echo "Generando $@..."
	@if [ $< -nt $*.dvi ]; then $(LATEX2DVI) fi
	@$(DVI2PDF) $(DVI2PDF_OPTS) $*.dvi

ifdef LYX_SOURCE
%.tex: %.lyx
	@echo "Generando $@..."
	@$(LYX2LATEX) $(LYX2LATEX_OPTS) $<
endif

