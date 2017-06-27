(defrule Abrir
	(declare (salience 10))
	=>
	(open "Mensajes.txt" mensajes)
	(assert (SeguirLeyendo))
)

(defrule Leer
	?f <- (SeguirLeyendo)
	=>
	(bind ?etiqueta (read mensajes))

	(retract ?f)
	(if (neq ?etiqueta EOF) then
		(assert (Mensaje ?etiqueta (read mensajes)))
		(assert (SeguirLeyendo))
	)
)

(defrule Cerrar
	(declare (salience -10))
	=>
	(close mensajes)
	(open "Mensaje_L.txt" escritura "w")
)

(defrule Escribir
	(declare (salience -30))
	(Mensaje L ?mensaje)
	=>
	(printout escritura ?mensaje crlf)
)
