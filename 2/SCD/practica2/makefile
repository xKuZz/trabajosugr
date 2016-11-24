
.SUFFIXES:
.PHONY: msg_uso, msg_clases, comp, recomp, clean, pc, le, cd

JAVASRCS:=$(wildcard *.java)
CLASSES_BASE:=$(shell grep class *.java | cut -d' ' -f2)
CLASSES:=$(addsuffix .class,$(CLASSES_BASE))

msg_uso:
	@echo "SCD: Ejemplos de monitores en Java."
	@echo "usar con:"
	@echo "   make comp  : compilar todos los archivos java si es necesario"
	@echo "   make recomp: compilar todo incondicionalmente"
	@echo "   make pc    : compilar todo y ejecutar ejemplo del productor-consumidor (20 10 5 2 4)"
	@echo "   make le    : idem para el ejemplo de lectores-escritores (5 20 15 25)"
	@echo "   make cd    : idem para el ejemplo del contador de días"
	@echo "   make clean : elimina todos los archivos .class"
	
comp: msg_clases monitor_classes $(CLASSES)

recomp:
	make clean	
	make comp

$(CLASSES): $(JAVASRCS)
	javac -g $(JAVASRCS)

monitor_classes: $(wildcard monitor/*.class)
	javac -g monitor/*.java -d .

clean:
	rm -rf *.class monitor/*.class scd-p02-ejemplos.zip
	
pc: MainProductorConsumidor.class
	java MainProductorConsumidor 20 10 5 2 4
	
le: MainLectorEscritor.class
	java MainLectorEscritor 5 20 15 25

cd: MainContadorDias.class
	java MainContadorDias
	
msg_clases:
	@echo "fuentes java = " $(JAVASRCS)
	@echo "clases = " $(CLASSES_BASE)
	
zip:	scd-p02-ejemplos.zip



