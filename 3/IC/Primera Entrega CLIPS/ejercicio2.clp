(deffacts lanzador
	(mostrarMenu)
	(opcion 4 " Elegir cuarta opcion.")
	(opcion 3 " Elegir tercera opcion.")
	(opcion 2 " Elegir segunda opcion.")
	(opcion 1 " Elegir primera opcion.")
)


(defrule IniciarMostrarMenu
	?aBorrar <- (mostrarMenu)
	=>
	(retract ?aBorrar)
	(printout t "Opciones disponibles:" crlf)
	(assert (mostrarOpciones))
)

(defrule MostrarOpciones
	(declare (salience 10))
	(mostrarOpciones)
	(opcion ?numero ?texto)
	=>
	(printout t ?numero " - " ?texto crlf)
)

(defrule PedirDatos
	?m <- (mostrarOpciones)
	(opcion $? $?)
	=>
	(printout t "Seleccione una opcion: " crlf)
	(bind ?seleccion (read))
	(assert (Elegir ?seleccion))
	(retract ?m)
)

(defrule TratarEleccionCorrecta
	?s <- (Elegir ?seleccion)
	?o <- (opcion ?seleccion $?)
	(not (Elegido ?seleccion))
	=>
	(printout t "Has seleccionado la opcion " ?seleccion "." crlf)
	(assert (Elegido ?seleccion))
	(retract ?s)
	(retract ?o)
	(assert (mostrarMenu))
)

(defrule TratarEleccionIncorrecta1
	?s <- (Elegir ?seleccion)
	(Elegido ?seleccion)	
	=>
	(printout t "La opcion ha sido escogida previamente." crlf)
	(retract ?s)
	(assert (mostrarMenu))
)

(defrule TratarEleccionIncorrecta2
	?s <- (Elegir ?seleccion)
	(not (opcion ?seleccion $?))
	=>
	(printout t "La opcion seleccionada no existe." crlf)
	(retract ?s)
	(assert (mostrarMenu))
)