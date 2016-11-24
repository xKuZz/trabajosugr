.SUFFIXES:
.PHONY: c

srcs:=$(wildcard *.java)
classf:=$(addsuffix .class, $(basename $(srcs)))

c: $(classf)

$(classf): $(srcs)
	javac $(srcs)
	
clean:
	rm -rf *.class
