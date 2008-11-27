TARGET=user_manual

TARGET_FILES := $(patsubst %, $(TARGET).%, dvi pdf)
TMP_FILES := $(patsubst %, $(TARGET).%, aux css log out toc)

# Directorio donde están las imágenes incluidas:
TP_IMG = tp-img

GRAFICOS =

include Rules.mk

# Dependencias adicionales para el .dvi:
$(TARGET).dvi : $(GRAFICOS:%=$(TP_IMG)/%.tex)

$(GRAFICOS:%=$(TP_IMG)/%.tex): %.tex: %.plot
	cd $(TP_IMG); gnuplot $(notdir $<); cd ..
