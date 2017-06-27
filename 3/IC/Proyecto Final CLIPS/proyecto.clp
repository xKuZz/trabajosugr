;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;; MENU ;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(deffacts lanzador
	(mostrarMenu)
	(opcion 3 " Proteccion de datos.")
	(opcion 2 " Compatibilidad de software.")
	(opcion 1 " Seleccionar licencia de software.")
)


(defrule IniciarMostrarMenu
	?aBorrar <- (mostrarMenu)
	=>
	(retract ?aBorrar)
	(printout t "Modulos disponibles:" crlf)
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
	(printout t "Seleccione una opcion: ")
	(bind ?seleccion (read))
	(assert (Elegir ?seleccion))
	(retract ?m)
)

(defrule TratarEleccionCorrecta
	?s <- (Elegir ?seleccion)
	(not (Elegido ?seleccion))
	(opcion ?seleccion $?)
	=>
	(assert (Elegido ?seleccion))
	(retract ?s)
)


(defrule TratarEleccionIncorrecta2
	?s <- (Elegir ?seleccion)
	(not (opcion ?seleccion $?))
	=>
	(printout t "La opcion seleccionada no existe." crlf)
	(retract ?s)
	(assert (mostrarMenu))
)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;; CONOCIMIENTO ;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(deftemplate Licencia
	(field Nombre)
	(field Libreria)
	(field Distribucion)
	(field Modificacion)
	(field Patente)
	(field UsoPrivado)
	(field SubLicencia)
	(field ID)
)

(deffacts Licencias_t
	(Licencia
		(Nombre Apache)
		(Libreria 2)
		(Distribucion 1)
		(Modificacion 2)
		(Patente 3)
		(UsoPrivado 1)
		(SubLicencia 2)
		(ID 1)
	)

	(Licencia
		(Nombre Boost)
		(Libreria 2)
		(Distribucion 2)
		(Modificacion 2)
		(Patente 1)
		(UsoPrivado 1)
		(SubLicencia 3)
		(ID 2)
	)

	(Licencia
		(Nombre BSD)
		(Libreria 2)
		(Distribucion 1)
		(Modificacion 2)
		(Patente 2)
		(UsoPrivado 1)
		(SubLicencia 2)
		(ID 3)
	)

	(Licencia
		(Nombre CC-BY-SA)
		(Libreria 3)
		(Distribucion 2)
		(Modificacion 3)
		(Patente 1)
		(UsoPrivado 1)
		(SubLicencia 4)
		(ID 4)
	)

	(Licencia
		(Nombre "Creative Commons Zero")
		(Libreria 1)
		(Distribucion 0)
		(Modificacion 1)
		(Patente 1)
		(UsoPrivado 1.5)
		(SubLicencia 1)
		(ID 5)
	)

	(Licencia
		(Nombre Eclipse)
		(Libreria 1.5)
		(Distribucion 0.5)
		(Modificacion 1.5)
		(Patente 3)
		(UsoPrivado 1)
		(SubLicencia 1.5)
		(ID 6)
	)

	(Licencia
		(Nombre GPL)
		(Libreria 4)
		(Distribucion 2)
		(Modificacion 3)
		(Patente 3)
		(UsoPrivado 1)
		(SubLicencia 3)
		(ID 0)
	)


	(Licencia
		(Nombre IBM)
		(Libreria 3)
		(Distribucion 2)
		(Modificacion 3)
		(Patente 2)
		(UsoPrivado 2)
		(SubLicencia 2)
		(ID 7)
	)

	(Licencia
		(Nombre "Intel Open Software")
		(Libreria 2)
		(Distribucion 1)
		(Modificacion 2)
		(Patente 2)
		(UsoPrivado 1)
		(SubLicencia 2)
		(ID 8)
	)


	(Licencia
		(Nombre LaTeX)
		(Libreria 2)
		(Distribucion 2)
		(Modificacion 2)
		(Patente 1)
		(UsoPrivado 1)
		(SubLicencia 1)
		(ID 9)
	)


	(Licencia
		(Nombre LGPL)
		(Libreria 1)
		(Distribucion 2)
		(Modificacion 3)
		(Patente 3)
		(UsoPrivado 1)
		(SubLicencia 3)
		(ID 10)
	)


	(Licencia
		(Nombre "Microsoft Public License")
		(Libreria 1)
		(Distribucion 1)
		(Modificacion 1)
		(Patente 1)
		(UsoPrivado 1)
		(SubLicencia 3.5)
		(ID 11)
	)

	(Licencia
		(Nombre "Microsoft Reciprocal License")
		(Libreria 1)
		(Distribucion 1)
		(Modificacion 1)
		(Patente 1)
		(UsoPrivado 1)
		(SubLicencia 3.5)
		(ID 12)
	)


	(Licencia
		(Nombre MIT)
		(Libreria 2)
		(Distribucion 1)
		(Modificacion 2)
		(Patente 2)
		(UsoPrivado 1)
		(SubLicencia 2)
		(ID 13)
	)

	
	(Licencia
		(Nombre Mozilla)
		(Libreria 2)
		(Distribucion 2)
		(Modificacion 3)
		(Patente 3)
		(UsoPrivado 1)
		(SubLicencia 3)
		(ID 14)
	)

	(Licencia
		(Nombre Netscape)
		(Libreria 1.5)
		(Distribucion 2)
		(Modificacion 1.5)
		(Patente 3)
		(UsoPrivado 1)
		(SubLicencia 3)
		(ID 15)
	)

	(Licencia
		(Nombre OpenSSL)
		(Libreria 2)
		(Distribucion 1)
		(Modificacion 2)
		(Patente 2)
		(UsoPrivado 1)
		(SubLicencia 2)
		(ID 16)
	)

	(Licencia
		(Nombre Privativa)
		(Libreria 5)
		(Distribucion 3)
		(Modificacion 4)
		(Patente 3)
		(UsoPrivado 2)
		(SubLicencia 4)
		(ID 17)
	)

	(Licencia
		(Nombre Unlincense)
		(Libreria 1)
		(Distribucion 0)
		(Modificacion 1)
		(Patente 1)
		(UsoPrivado 1)
		(SubLicencia 1)
		(ID 18)
	)

	(Licencia
		(Nombre WTFPL)
		(Libreria 1)
		(Distribucion 1)
		(Modificacion 1)
		(Patente 1)
		(UsoPrivado 1)
		(SubLicencia 1)
		(ID 19)
	)

)

(deftemplate Dato
    (field nombre)
    (field tipo)
    (field ID)
)

(deffacts TiposDatos
(Dato
    (nombre "Lengua materna")
    (tipo "caracteristicasPersonales")
    (ID 29)
  )

  (Dato
    (nombre "Nacionalidad")
    (tipo "caracteristicasPersonales")
    (ID 28)
  )

  (Dato
    (nombre "Sexo")
    (tipo "caracteristicasPersonales")
    (ID 27)
  )

  (Dato
    (nombre "Edad")
    (tipo "caracteristicasPersonales")
    (ID 26)
  )

  (Dato
    (nombre "Lugar de nacimiento")
    (tipo "caracteristicasPersonales")
    (ID 25)
  )

  (Dato
    (nombre "Fecha de nacimiento")
    (tipo "caracteristicasPersonales")
    (ID 24)
  )

  (Dato
    (nombre "Datos de familia")
    (tipo "caracteristicasPersonales")
    (ID 23)
  )

  (Dato
    (nombre "Datos de estado civil")
    (tipo "caracteristicasPersonales")
    (ID 22)
  )

  (Dato
    (nombre "Tarjeta Sanitaria")
    (tipo "datosIdentificativos")
    (ID 21)
  )

  (Dato
    (nombre "Firma electronica")
    (tipo "datosIdentificativos")
    (ID 20)
  )

  (Dato
    (nombre "Firma/huella")
    (tipo "datosIdentificativos")
    (ID 19)
  )

  (Dato
    (nombre "Apellidos")
    (tipo "datosIdentificativos")
    (ID 18)
  )

  (Dato
    (nombre "Nombre")
    (tipo "datosIdentificativos")
    (ID 17)
  )

  (Dato
    (nombre "Marcas fisicas")
    (tipo "datosIdentificativos")
    (ID 16)
  )

  (Dato
    (nombre "Telefono")
    (tipo "datosIdentificativos")
    (ID 15)
  )

  (Dato
    (nombre "Numero de Seguridad Social")
    (tipo "datosIdentificativos")
    (ID 14)
  )

  (Dato
    (nombre "voz")
    (tipo "datosIdentificativos")
    (ID 13)
  )

  (Dato
    (nombre "Imagen")
    (tipo "datosIdentificativos")
    (ID 12)
  )

  (Dato
    (nombre "Direccion")
    (tipo "datosIdentificativos")
    (ID 11)
  )

  (Dato
    (nombre "DNI")
    (tipo "datosIdentificativos")
    (ID 10)
  )

  (Dato
    (nombre "Vida Sexual")
    (tipo "especialmenteProtegidos")
    (ID 9)
  )

  (Dato
    (nombre "Salud")
    (tipo "especialmenteProtegidos")
    (ID 8)
  )

  (Dato
    (nombre "Origen etnico")
    (tipo "especialmenteProtegidos")
    (ID 7)
  )

  (Dato
    (nombre "Origen Racial")
    (tipo "especialmenteProtegidos")
    (ID 6)
  )

  (Dato
    (nombre "Creencias")
    (tipo "especialmenteProtegidos")
    (ID 5)
  )

  (Dato
    (nombre "Religion")
    (tipo "especialmenteProtegidos")
    (ID 4)
  )

  (Dato
    (nombre "Sindical")
    (tipo "especialmenteProtegidos")
    (ID 3)
  )

  (Dato
    (nombre "Afiliacion")
    (tipo "especialmenteProtegidos")
    (ID 2)
  )

  (Dato
    (nombre "Ideologia")
    (tipo "especialmenteProtegidos")
    (ID 1)
  )

  (MostrarDatos)
)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;; MODULO 1 ;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; Regla que inicializa todas las posibilidades al entrar al módulo 1
(defrule ActivarModulo1
	(declare (salience 10))
	(Elegido 1)
	=>
	;; Activamos sólo las que hemos puesto en la rejilla de repertorio
	(assert (PosibleLicencia Apache))
	(assert (PosibleLicencia BSD))
	(assert (PosibleLicencia GPL))
	(assert (PosibleLicencia Eclipse))
	(assert (PosibleLicencia MIT))
	(assert (PosibleLicencia Privativa))
	(assert (PosibleLicencia Mozilla))
	(assert (Pregunta 1))
	(assert (StopControlFact))
)

;; Preguntas

(defrule PrimeraPregunta
	(Elegido 1)
	?erase <- (Pregunta 1)
	=>
	(printout t "Sobre la distribucion y modificacion  de su software:" crlf)
	(printout t "1-No desea que se haga uso libre de ello (Privativa)." crlf)
	(printout t "2-Desea que se haga uso libre de ello." crlf)
	(printout t "Opcion seleccionada: ")
	(assert (Respuesta 1 (read)))
	(retract ?erase)
)

(defrule SegundaPregunta
	(Elegido 1)
	?erase <- (Pregunta 2)
	(not (ComprobarPosibilidades))
	=>
	(printout t "Desea que la modificacion del codigo original este sujeta a CopyLeft (toda modificacion esta sujeta a la restriccion de distribuirla con esta licencia, por lo que debe de seguir siendo libre?" crlf)
	(printout t "1-No se desea uso de CopyLeft." crlf)
	(printout t "2-Se desea el uso de CopyLeft." crlf)
	(printout t "Opcion seleccionada: ")
	(assert (Respuesta 2 (read)))
	(retract ?erase)
)

(defrule TerceraPregunta
	(Elegido 1)
	?erase <- (Pregunta 3)
	(not (ComprobarPosibilidades))
	=>
	(printout t "Desea que se pueda enlazar el software con otro software mas libre (Ej: Uso como libreria)?" crlf)
	(printout t "1-No se desea que se pueda enlazar con software mas libre." crlf)
	(printout t "2-Se desea que solo se pueda enlazar con compatibles con la misma licencia" crlf)
	(printout t "Opcion seleccionada: ")
	(assert (Respuesta 3 (read)))
	(retract ?erase)
)

(defrule CuartaPregunta
	(Elegido 1)
	?erase <- (Pregunta 4)
	(not (ComprobarPosibilidades))
	=>
	(printout t "Si no se realiza una extension o modulo separado, quiere exigir que este se publique libremente?" crlf)
	(printout t "1-No deseo que se tenga que distribuir libremente." crlf)
	(printout t "2-Deseo que sea obligatorio distribuirlo." crlf)
	(printout t "Opcion seleccionada: ")
	(assert (Respuesta 4 (read)))
	(retract ?erase)
)

(defrule QuintaPregunta
	(Elegido 1)
	?erase <- (Pregunta 5)
	(not (ComprobarPosibilidades))
	=>
	(printout t "Con respecto a la proteccion de patentes?" crlf)
	(printout t "1-Me basta con que pueda introducirla yo de manera manual." crlf)
	(printout t "2-Prefiero que la licencia que use me garantice directamente la proteccion." crlf)
	(printout t "Opcion seleccionada: ")
	(assert (Respuesta 5 (read)))
	(retract ?erase)
)

(defrule SextaPregunta
	(Elegido 1)
	?erase <- (Pregunta 6)
	(not (ComprobarPosibilidades))
	=>
	(printout t "Aparte de en el codigo, desea que la licencia diga explicitamente que debe constar usted en los derechos de autor de cualquier binario creado con su trabajo?" crlf)
	(printout t "1-Me basta con aparecer en el codigo." crlf)
	(printout t "2-Debo aparecer en el software tambien." crlf)
	(printout t "Opcion seleccionada: ")
	(assert (Respuesta 6 (read)))
	(retract ?erase)
)



;; Tratamiento de respuestas


(defrule Pregunta1Op1
	(Respuesta 1 1)
	(Elegido 1)
	(Licencia (Nombre ?nombre)
			  (Distribucion ?d)
			  (Modificacion ?m)
			  
	)
	(or
		(test (< ?d 3))
		(test (< ?m 4))
	)
	?erase<- (PosibleLicencia ?nombre)
	=>
	(retract ?erase)
	(assert (ComprobarPosibilidades))
	(printout t "Descartamos " ?nombre " por no ser privativa" crlf)
)

(defrule Pregunta1Op2
	(Elegido 1)
	(Licencia (Nombre ?nombre)
			  (Distribucion ?d)
			  (Modificacion ?m)
	)
	(or
		(test (>= ?d 3))
		(test (>= ?m 4))
	)
	(Respuesta 1 2)
	?erase<- (PosibleLicencia ?nombre)
	=>
	(retract ?erase)
	(assert (ComprobarPosibilidades))
	(printout t "Descartamos " ?nombre " por ser privativa" crlf)
	(assert (Pregunta 2))
)

(defrule Pregunta2Op1
	(Elegido 1)
	(Licencia (Nombre ?nombre)
			  (Modificacion ?m)
	)
	(test (= ?m 3))
	(Respuesta 2 1)
	?erase<- (PosibleLicencia ?nombre)
	=>
	(retract ?erase)
	(assert (ComprobarPosibilidades))
	(printout t "Descartamos " ?nombre " por usar CopyLeft para la modificacion" crlf)
	(assert (Pregunta 4))
)

(defrule Pregunta2Op2
	(Elegido 1)
	(Licencia (Nombre ?nombre)
			  (Modificacion ?m)
	)
	(test (<> ?m 3))
	(Respuesta 2 2)
	?erase<- (PosibleLicencia ?nombre)
	=>
	(retract ?erase)
	(assert (ComprobarPosibilidades))
	(printout t "Descartamos " ?nombre " por no usar CopyLeft para la modificacion." crlf)
	(assert (Pregunta 3))
)

(defrule Pregunta3Op1
	(Elegido 1)
	(Licencia (Nombre ?nombre)
			  (Libreria ?l)
	)
	(test (< ?l 4))
	(Respuesta 3 1)
	?erase<- (PosibleLicencia ?nombre)
	=>
	(retract ?erase)
	(assert (ComprobarPosibilidades))
	(printout t "Descartamos " ?nombre " por permitir enlaces con otros modulos de mas libres." crlf)
	1
)

(defrule Pregunta3Op2
	(Elegido 1)
	(Licencia (Nombre ?nombre)
			  (Libreria ?l)
	)
	(test (>= ?l 4))
	(Respuesta 3 2)
	?erase<- (PosibleLicencia ?nombre)
	=>
	(retract ?erase)
	(assert (ComprobarPosibilidades))
	(printout t "Descartamos " ?nombre " por solo permitir enlaces con su misma tipo." crlf)
)

(defrule Pregunta4Op1
	(Elegido 1)
	(Licencia (Nombre ?nombre)
			  (Distribucion ?d)
	)
	(test (= ?d 0.5))
	(Respuesta 4 1)
	?erase<- (PosibleLicencia ?nombre)
	=>
	(retract ?erase)
	(assert (ComprobarPosibilidades))
	(printout t "Descartamos " ?nombre " por exigir que se publique" crlf)
	(assert (Pregunta 5))
)

(defrule Pregunta4Op2
	(Elegido 1)
	(Licencia (Nombre ?nombre)
		(Distribucion ?d)
	)
	(test (<> ?d 0.5))
	(Respuesta 4 2)
	?erase<- (PosibleLicencia ?nombre)
	=>
	(retract ?erase)
	(assert (ComprobarPosibilidades))
	(printout t "Descartamos " ?nombre " por no exigir que se publique" crlf)
)

(defrule Pregunta5Op1
	(Elegido 1)
	(Licencia (Nombre ?nombre)
		  (Patente ?p)
	)
	(test (= ?p 3))
	(Respuesta 5 1)
	?erase<- (PosibleLicencia ?nombre)
	=>
	(retract ?erase)
	(assert (ComprobarPosibilidades))
	(printout t "Descartamos " ?nombre " por tener un sistema de proteccion de patente automatico" crlf)
	(assert (Pregunta 6))
)

(defrule Pregunta5Op2
	(Elegido 1)
	(Licencia (Nombre ?nombre)
		  (Patente ?p)
	)
	(test (<> ?p 3))
	(Respuesta 5 2)
	?erase<- (PosibleLicencia ?nombre)
	=>
	(retract ?erase)
	(assert (ComprobarPosibilidades))
	(printout t "Descartamos " ?nombre " por no tener un sistema de proteccion de patente automatico" crlf)
	
)

(defrule Pregunta6Op1
	(Elegido 1)
	(Respuesta 6 1)
	?erase<- (PosibleLicencia BSD)
	=>
	(retract ?erase)
	(assert (ComprobarPosibilidades))
	(printout t "Descartamos BSD por indicar explicitamente que se reconozcan los derechos de autor en los binarios" crlf)
)

(defrule Pregunta6Op2
	(Elegido 1)
	(Respuesta 6 2)
	?erase<- (PosibleLicencia MIT)
	=>
	(retract ?erase)
	(assert (ComprobarPosibilidades))
	(printout t "Descartamos MIT por no indicar explicitamente que se reconozcan los derechos de autor en los binarios" crlf)
)


(defrule OpcionInvalidaMod1
	(declare (salience -20))
	(Elegido 1)
	?erase <- (Respuesta ?pregunta ?opcion)
	=>
	(retract ?erase)
	(printout t "La opcion " ?opcion " no es valida. Revise su respuesta." crlf crlf)
	(assert (Pregunta ?pregunta))
)

(defrule MostrarDisponiblesLabel
	(declare (salience -1))
	?erase <- (Respuesta ?pregunta ?opcion)
	(ComprobarPosibilidades)
	?erase2 <- (StopControlFact)
	(Elegido 1)
	=>
	(retract ?erase)
	(retract ?erase2)
	(printout t "Quedan las siguientes licencias disponibles:" crlf)
)

(defrule MostrarDisponibles
	(declare (salience -2))
	(ComprobarPosibilidades)
	(Elegido 1)
	(PosibleLicencia ?nombre)
	=>
	(printout t ?nombre crlf)
)

(defrule StopComprobar
	(declare (salience -3))
	?erase <- (ComprobarPosibilidades)
	=>
	(retract ?erase)
	(assert (StopControlFact))
)

;; Para el módulo 1 cuando sólo queda 1 posible licencia de las conocidas
(defrule StopMod1
	(declare (salience -30))
	(StopControlFact)
	(not (ComprobarPosibilidades))
	(test (= (length (find-all-facts ((?f PosibleLicencia)) TRUE)) 1))
	?erase <- (Elegido 1)
	=>
	(printout t "Puesto que solo disponemos de una posibilidad la ejecucion del modulo 1 ha finalizado" crlf)
	(retract ?erase)
	(assert (mostrarMenu))
	
)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;; MODULO 2 ;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defrule Modulo2MiSoft
	(Elegido 2)
	=>
	(printout t "Elija la licencia usar para su software:" crlf)
	(printout t "0-GPL" crlf)
	(printout t "1-Apache" crlf)
	(printout t "2-Boost License" crlf)
	(printout t "3-BSD 2 clausulas" crlf)
	(printout t "4-CC-BY-SA" crlf)
	(printout t "5-Creative Commons Zero" crlf)
	(printout t "6-Eclipse" crlf)
	(printout t "7-IBM" crlf)
	(printout t "8-Intel Open Source License" crlf)
	(printout t "9-LaTeX License" crlf)
	(printout t "10-LGPL" crlf)
	(printout t "11-Microsoft Public License" crlf)
	(printout t "12-Microsoft Reciprocal License" crlf)
	(printout t "13-MIT License" crlf)
	(printout t "14-Mozilla Public License" crlf)
	(printout t "15-Netscape License" crlf)
	(printout t "16-OpenSSL License" crlf)
	(printout t "17-Licencias Privativas" crlf)
	(printout t "18-Unlicense" crlf)
	(printout t "19-WTFPL" crlf)
	(printout t "Selecciona una opcion: ")
	(assert (Seleccionada (read)))
)

(defrule Modulo2Comp
	(Elegido 2)
	(Seleccionada ?s)
	=>
	(printout t "Elija la licencia del software de terceros que desea usar:" crlf)
	(printout t "0-GPL" crlf)
	(printout t "1-Apache" crlf)
	(printout t "2-Boost License" crlf)
	(printout t "3-BSD 2 clausulas" crlf)
	(printout t "4-CC-BY-SA" crlf)
	(printout t "5-Creative Commons Zero" crlf)
	(printout t "6-Eclipse" crlf)
	(printout t "7-IBM" crlf)
	(printout t "8-Intel Open Source License" crlf)
	(printout t "9-LaTeX License" crlf)
	(printout t "10-LGPL" crlf)
	(printout t "11-Microsoft Public License" crlf)
	(printout t "12-Microsoft Reciprocal License" crlf)
	(printout t "13-MIT License" crlf)
	(printout t "14-Mozilla Public License" crlf)
	(printout t "15-Netscape License" crlf)
	(printout t "16-OpenSSL License" crlf)
	(printout t "17-Licencias Privativas" crlf)
	(printout t "18-Unlicense" crlf)
	(printout t "19-WTFPL" crlf)
	(printout t "Selecciona una opcion: ")
	(assert (Compatible (read)))
)

(defrule Compatibilidad1
	?erase <-(Elegido 2)
	?erase2 <- (Seleccionada ?l)
	?erase3 <- (Compatible ?c)

	(Licencia (Nombre ?misoftware)
		  (ID ?l)
		  (Distribucion ?d2)
	)

	(Licencia (Nombre ?compatible)
		  (ID ?c)
	)

	(test (< ?d2 0.25))
	=>
	(printout t "La licencia " ?misoftware " es compatible con " ?compatible " ya que la distribucion de " ?misoftware " es dominio publico" crlf)
	(retract ?erase)
	(retract ?erase2)
	(retract ?erase3)
	(assert (mostrarMenu))
)



(defrule Compatibilidad2
	?erase <-(Elegido 2)
	?erase2 <- (Seleccionada ?l)
	?erase3 <- (Compatible ?c)

	(Licencia (Nombre ?misoftware)
		  (ID ?l)
		  (Distribucion ?d2)
		  (Modificacion ?m2)
		  (UsoPrivado ?p2)
		  (SubLicencia ?s2)
	)

	(Licencia (Nombre ?compatible)
		  (ID ?c)
		  (Libreria ?lib)
	)

	(test (>= ?lib 1.5))
	(test (< ?lib 4.5))
	(test (>= ?d2 0.25))
	(test (>= ?m2 1.75))
	(test (< ?p2 1.5))
	(test (>= ?s2 2.5))
	=>
	(printout t "La licencia " ?misoftware " es compatible con " ?compatible " ya que el uso enlazado de " ?compatible " es de estilo CopyLeft o alternativas parecidas a este," crlf)
	(printout t "la modificacion de la licencia " ?misoftware " no es de dominio publico y permite el uso para proyectos privados del software." crlf)
	(retract ?erase)
	(retract ?erase2)
	(retract ?erase3)
	(assert (mostrarMenu))
)

; Rule number: 189 [.outcome=1 cover=1 (3%) prob=1.00]
;    Distribución2>=0.25
;    Modificación2>=1.75
;    Libreria1>=1.5
;    Libreria1< 4.5
;    Privado2< 1.5
;    SubLicencia2< 2.5
;    Patentes1< 1.5

(defrule Compatibilidad3
	?erase <-(Elegido 2)
	?erase2 <- (Seleccionada ?l)
	?erase3 <- (Compatible ?c)

	(Licencia (Nombre ?misoftware)
		  (ID ?l)
		  (Distribucion ?d2)
		  (Modificacion ?m2)
		  (UsoPrivado ?p2)
		  (SubLicencia ?s2)
	)

	(Licencia (Nombre ?compatible)
		  (ID ?c)
		  (Libreria ?lib)
		  (Patente ?pat1)
	)

	(test (>= ?lib 1.5))
	(test (< ?lib 4.5))
	(test (>= ?d2 0.25))
	(test (>= ?m2 1.75))
	(test (< ?p2 1.5))
	(test (< ?s2 2.5))
	(test (< ?pat1 1.5))
	=>
	(printout t "La licencia " ?misoftware " es compatible con " ?compatible " ya que el uso enlazado de " ?compatible " es de estilo CopyLeft o alternativas parecidas a este," crlf)
	(printout t "la modificacion de la licencia " ?misoftware " no es de dominio publico, permite el uso para proyectos privados del software y" crlf)
	(printout t "Permite solo sublicencias permisivas y de dominio publico y la licencia del sotware a usar no tiene proteccion de patentes." crlf)
	(retract ?erase)
	(retract ?erase2)
	(retract ?erase3)
	(assert (mostrarMenu))
)


(defrule Compatibilidad4
	?erase <-(Elegido 2)
	?erase2 <- (Seleccionada ?l)
	?erase3 <- (Compatible ?c)

	(Licencia (Nombre ?misoftware)
		  (ID ?l)
		  (Distribucion ?d2)
		  (Modificacion ?m2)
		  (UsoPrivado ?p2)
		  (SubLicencia ?s2)
	)

	(Licencia (Nombre ?compatible)
		  (ID ?c)
		  (Libreria ?lib)
		  (Patente ?pat1)
	)

	(test (>= ?lib 1.5))
	(test (< ?lib 3))
	(test (>= ?d2 1.5))
	(test (>= ?m2 1.75))
	(test (< ?p2 1.5))
	(test (< ?s2 2.5))
	(test (>= ?pat1 1.5))
	=>
	(printout t "La licencia " ?misoftware " es compatible con " ?compatible " ya que el uso enlazado de " ?compatible " es de estilo CopyLeft o ligeramente menos restrictivo," crlf)
	(printout t "la modificacion y la distribucion de la licencia " ?misoftware " es CopyLeft o no se puede, permite el uso para proyectos privados del software y" crlf)
	(printout t "Permite solo sublicencias permisivas y de dominio publico y la licencia del sotware a usar  tiene proteccion automatica de patentes." crlf)
	(retract ?erase)
	(retract ?erase2)
	(retract ?erase3)
	(assert (mostrarMenu))
)

(defrule CompatibilidadParcial5
	?erase <-(Elegido 2)
	?erase2 <- (Seleccionada ?l)
	?erase3 <- (Compatible ?c)

	(Licencia (Nombre ?misoftware)
		  (ID ?l)
		  (Distribucion ?d2)
		  (Modificacion ?m2)
		  (UsoPrivado ?p2)
		  (SubLicencia ?s2)
	)

	(Licencia (Nombre ?compatible)
		  (ID ?c)
		  (Libreria ?lib)
		  (Patente ?pat1)
	)

	(test (>= ?lib 1.5))
	(test (< ?lib 4.5))
	(test (> ?d2 0.25))
	(test (< ?d2 1.5))
	(test (>= ?m2 1.75))
	(test (< ?p2 1.5))
	(test (< ?s2 2.5))
	(test (>= ?pat1 2.5))
	=>
	(printout t "La licencia " ?misoftware " es compatible con " ?compatible " ya que el uso enlazado de " ?compatible " es de estilo permisivo o mas restrictivo," crlf)
	(printout t "la modificacion y la distribucion de la licencia " ?misoftware " es CopyLeft o no se puede, permite el uso para proyectos privados del software y" crlf)
	(printout t "Permite solo sublicencias permisivas y de dominio publico  y la licencia del sotware a usar tiene proteccion automatica de patentes." crlf)
	(printout t "Existen excepciones para este caso pero un 83 % de las veces son compatibles." crlf)
	(retract ?erase)
	(retract ?erase2)
	(retract ?erase3)
	(assert (mostrarMenu))
)

(defrule Incompatibilidad6
	?erase <-(Elegido 2)
	?erase2 <- (Seleccionada ?l)
	?erase3 <- (Compatible ?c)

	(Licencia (Nombre ?misoftware)
		  (ID ?l)
		  (Distribucion ?d2)
		  (Modificacion ?m2)
		  (UsoPrivado ?p2)
		  (SubLicencia ?s2)
	)

	(Licencia (Nombre ?compatible)
		  (ID ?c)
		  (Libreria ?lib)
		  (Patente ?pat1)
	)

	(test (>= ?lib 1.5))
	(test (< ?lib 4.5))
	(test (> ?d2 0.25))
	(test (< ?d2 1.5))
	(test (>= ?m2 1.75))
	(test (< ?p2 1.5))
	(test (< ?s2 2.5))
	(test (< ?pat1 2.5))
	=>
	(printout t "La licencia " ?misoftware " no es compatible con " ?compatible " ya que el uso enlazado de " ?compatible " es de estilo permisivo o mas restrictivo," crlf)
	(printout t "la modificacion y la distribucion de la licencia " ?misoftware " es CopyLeft o no se puede, permite el uso para proyectos privados del software y" crlf)
	(printout t "Permite solo sublicencias permisivas y de dominio publico y la licencia del sotware a usar no tiene proteccion automatica de patentes." crlf)
	(retract ?erase)
	(retract ?erase2)
	(retract ?erase3)
	(assert (mostrarMenu))
)

 ; Rule number: 752 [.outcome=0 cover=1 (3%) prob=0.00]
 ;   Distribución2>=0.25
 ;   Modificación2>=1.75
 ;   Libreria1>=1.5
 ;   Libreria1< 4.5
 ;   Privado2< 1.5
 ;   SubLicencia2< 2.5
 ;   Patentes1>=1.5
 ;   Distribución2>=1.5
 ;   Libreria1>=3


(defrule Incompatibilidad7
	?erase <-(Elegido 2)
	?erase2 <- (Seleccionada ?l)
	?erase3 <- (Compatible ?c)

	(Licencia (Nombre ?misoftware)
		  (ID ?l)
		  (Distribucion ?d2)
		  (Modificacion ?m2)
		  (UsoPrivado ?p2)
		  (SubLicencia ?s2)
	)

	(Licencia (Nombre ?compatible)
		  (ID ?c)
		  (Libreria ?lib)
		  (Patente ?pat1)
	)

	(test (>= ?lib 3))
	(test (< ?lib 4.5))
	(test (>= ?d2 1.5))
	(test (>= ?m2 1.75))
	(test (< ?p2 1.5))
	(test (< ?s2 2.5))
	(test (>= ?pat1 1.5))
	=>
	(printout t "La licencia " ?misoftware " no es compatible con " ?compatible " ya que el uso enlazado de " ?compatible " es de estilo CopyLeft o mas restrictivo," crlf)
	(printout t "la modificacion y la distribucion de la licencia " ?misoftware " permisiva o mas restrictiva, permite el uso para proyectos privados del software y" crlf)
	(printout t "permite solo sublicencias que no sea de dominio publico y la licencia del sotware a usar no tiene proteccion automatica de patentes." crlf)
	(retract ?erase)
	(retract ?erase2)
	(retract ?erase3)
	(assert (mostrarMenu))
)

(defrule Incompatibilidad8
	?erase <-(Elegido 2)
	?erase2 <- (Seleccionada ?l)
	?erase3 <- (Compatible ?c)

	(Licencia (Nombre ?misoftware)
		  (ID ?l)
		  (Distribucion ?d2)
		  (Modificacion ?m2)
		  (UsoPrivado ?p2)
		  (SubLicencia ?s2)
	)

	(Licencia (Nombre ?compatible)
		  (ID ?c)
		  (Libreria ?lib)
		  (Patente ?pat1)
	)

	(test (>= ?lib 1.5))
	(test (< ?lib 4.5))
	(test (>= ?d2 0.25))
	(test (>= ?m2 1.75))
	(test (>= ?p2 1.5))

	=>
	(printout t "La licencia " ?misoftware " no es compatible con " ?compatible " ya que el uso enlazado de " ?compatible " es de estilo limitado o mas restrictivo pero no esta prohibido," crlf)
	(printout t "la modificacion de la licencia " ?misoftware " permisiva o mas restrictiva, no permite el uso para proyectos privados del software y" crlf)
	(printout t "la distribucion no es de dominio publico." crlf)
	(retract ?erase)
	(retract ?erase2)
	(retract ?erase3)
	(assert (mostrarMenu))
)

;  Rule number: 22 [.outcome=0 cover=3 (9%) prob=0.00]
;    Distribución2>=0.25
;    Modificación2>=1.75
;    Libreria1>=1.5
;    Libreria1>=4.5

(defrule Incompatibilidad9
	?erase <-(Elegido 2)
	?erase2 <- (Seleccionada ?l)
	?erase3 <- (Compatible ?c)

	(Licencia (Nombre ?misoftware)
		  (ID ?l)
		  (Distribucion ?d2)
		  (Modificacion ?m2)
		  (UsoPrivado ?p2)
		  (SubLicencia ?s2)
	)

	(Licencia (Nombre ?compatible)
		  (ID ?c)
		  (Libreria ?lib)
		  (Patente ?pat1)
	)

	(test (>= ?lib 4.5))
	(test (>= ?d2 0.25))
	(test (>= ?m2 1.75))

	=>
	(printout t "La licencia " ?misoftware " no es compatible con " ?compatible " ya que el uso enlazado de " ?compatible " esta prohibido" crlf)
	(retract ?erase)
	(retract ?erase2)
	(retract ?erase3)
	(assert (mostrarMenu))
)

;  Rule number: 10 [.outcome=0 cover=3 (9%) prob=0.00]
;    Distribución2>=0.25
;    Modificación2>=1.75
;    Libreria1< 1.5

(defrule Incompatibilidad10
	?erase <-(Elegido 2)
	?erase2 <- (Seleccionada ?l)
	?erase3 <- (Compatible ?c)

	(Licencia (Nombre ?misoftware)
		  (ID ?l)
		  (Distribucion ?d2)
		  (Modificacion ?m2)
		  (UsoPrivado ?p2)
		  (SubLicencia ?s2)
	)

	(Licencia (Nombre ?compatible)
		  (ID ?c)
		  (Libreria ?lib)
		  (Patente ?pat1)
	)

	(test (< ?lib 1.5))
	(test (>= ?d2 0.25))
	(test (>= ?m2 1.75))

	=>
	(printout t "La licencia " ?misoftware " no es compatible con " ?compatible " ya que el uso enlazado de " ?compatible " es de dominio publico" crlf)
	(printout t "pero la modificacion de " ?misoftware " es permisiva o mas restrictiva y la distribucion no es de dominio publico" crlf)
	(retract ?erase)
	(retract ?erase2)
	(retract ?erase3)
	(assert (mostrarMenu))
)

;  Rule number: 4 [.outcome=0 cover=5 (16%) prob=0.00]
;    Distribución2>=0.25
;    Modificación2< 1.75

(defrule Incompatibilidad11
	?erase <-(Elegido 2)
	?erase2 <- (Seleccionada ?l)
	?erase3 <- (Compatible ?c)

	(Licencia (Nombre ?misoftware)
		  (ID ?l)
		  (Distribucion ?d2)
		  (Modificacion ?m2)
		  (UsoPrivado ?p2)
		  (SubLicencia ?s2)
	)

	(Licencia (Nombre ?compatible)
		  (ID ?c)
		  (Libreria ?lib)
		  (Patente ?pat1)
	)

	(test (>= ?d2 0.25))
	(test (< ?m2 1.75))

	=>
	(printout t "La licencia " ?misoftware " no es compatible con " ?compatible " ya que la distribucion de" crlf)
	(printout t ?misoftware " no es de dominio publico y la modificacion es de dominio publico" crlf)
	(retract ?erase)
	(retract ?erase2)
	(retract ?erase3)
	(assert (mostrarMenu))
)

(defrule ErrorModulo2
	(declare (salience -30))
	?erase <-(Elegido 2)
	?erase2 <- (Seleccionada ?l)
	?erase3 <- (Compatible ?c)
	=>
	(printout t "Se desconocen las licencias seleccionadas o hay un error en la base de conocimiento." crlf)
	(printout t "Por favor vuelva a introducir las licencias y revise que su seleccion es correcta." crlf)
	(retract ?erase)
	(retract ?erase2)
	(retract ?erase3)
	(assert (mostrarMenu))
)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;; MODULO 3 ;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defrule IniciarModulo3
	(Elegido 3)
	=>
	  (assert (OpcionDisponible 29))
	  (assert (OpcionDisponible 28))
	  (assert (OpcionDisponible 27))
	  (assert (OpcionDisponible 26))
	  (assert (OpcionDisponible 25))
	  (assert (OpcionDisponible 24))
	  (assert (OpcionDisponible 23))
	  (assert (OpcionDisponible 22))
	  (assert (OpcionDisponible 21))
	  (assert (OpcionDisponible 20))
	  (assert (OpcionDisponible 19))
	  (assert (OpcionDisponible 18))
	  (assert (OpcionDisponible 17))
	  (assert (OpcionDisponible 16))
	  (assert (OpcionDisponible 15))
	  (assert (OpcionDisponible 14))
	  (assert (OpcionDisponible 13))
	  (assert (OpcionDisponible 12))
	  (assert (OpcionDisponible 11))
	  (assert (OpcionDisponible 10))
	  (assert (OpcionDisponible 9))
	  (assert (OpcionDisponible 8))
	  (assert (OpcionDisponible 7))
	  (assert (OpcionDisponible 6))
	  (assert (OpcionDisponible 5))
	  (assert (OpcionDisponible 4))
	  (assert (OpcionDisponible 3))
	  (assert (OpcionDisponible 2))
	  (assert (OpcionDisponible 1))

)

(defrule datosLabel
    (declare (salience 5))
    (Elegido 3)
    (MostrarDatos)
    =>
    (printout t "Seleccione los datos manejados por el sistema:" crlf)
)

(defrule MostrarDatosPosibles
    (Elegido 3)
    (MostrarDatos)
    (Dato (nombre ?d)
        (tipo ?t)
        (ID ?id)
    )
    (OpcionDisponible ?id)
    =>
    (printout t ?id "- " ?d " (" ?t ")" crlf )
)


(defrule SeleccionarDato
    (declare (salience -1))
    (Elegido 3)
    ?erase <- (MostrarDatos)
    =>
    (printout t "0-No tengo ninguno mas de estos datos" crlf)
    (printout t "Seleccione opcion: ")
    (assert (tipoDato (read)))
    (retract ?erase)
)

(defrule SeleccionCorrecta
    (Elegido 3)
    ?erase <- (tipoDato ?id)
    ?erase2 <- (OpcionDisponible ?id)
    =>
    (retract ?erase)
    (retract ?erase2)
    (assert (MostrarDatos))
)

(defrule SeleccionSeguir
    (Elegido 3)
    ?erase <- (tipoDato 0)
    =>
    (retract ?erase)
    (assert (ElegirOrganizacion))
)

(defrule SeleccionIncorrecta
    (declare (salience -3))
    (Elegido 3)
    ?erase <- (tipoDato ?id)
    (not (OpcionDisponible ?id))
    =>
    (retract ?erase)
    (printout t "La opcion seleccionada no existe." crlf)
    (assert (MostrarDatos))
)


(defrule TiposOrganizaciones
    (ElegirOrganizacion)
    =>
        (printout t "Seleccione el tipo de organizacion:" crlf)
        (printout t "1- Usuario domestico." crlf)
        (printout t "2- Empresa privada." crlf)
        (printout t "3- Administracion publica." crlf) 
        (printout t "4- Cuerpos y fuerzas de seguridad del estado." crlf)
        (printout t "Seleccione opcion: ")
        (assert (organizacion (read)))
)

(defrule SeleccionarOrganizacion
    (declare (salience -1))
    ?erase <- (ElegirOrganizacion)
    (organizacion ?org)
    (test (> ?org 0))
    (test (< ?org 5))
    =>
    (assert (ElegirSituacion))
    (retract ?erase)        
)

(defrule SeleccionarOrganizacionIncorrecta
    (declare (salience -1))
    ?erase <- (ElegirOrganizacion)
    ?erase2 <- (organizacion ?org)
    (or
        (test (<= ?org 0))
        (test (>= ?org 5))
    )
    =>
    (printout t "El tipo de organizacion elegido no existe." crlf)
    (retract ?erase)     
    (retract ?erase2)  
    (assert (ElegirOrganizacion))
)

(defrule TiposZonas
    (ElegirSituacion)
    =>
    (printout t "Seleccione el area geografica:" crlf)
    (printout t "1- Espana." crlf)
    (printout t "2- Union Europea." crlf)
    (printout t "3- Paises considerados con un nivel de proteccion adecuados: Islandia, Liechtenstein, Noruega, Suiza, Argentina." crlf)
    (printout t "4- Resto de paises." crlf)
    (printout t "Seleccione opcion: ")
    (assert (zona (read)))
)

(defrule TratarZona
    (declare (salience -1))
    ?erase <- (ElegirSituacion)
    (zona ?zona)
    (test (> ?zona 0))
    (test (< ?zona 5)) 
    =>
    (assert (ElegirUso))
    (retract ?erase)        
)

(defrule TratarZonaIncorrecta
    (declare (salience -1))
    ?erase <- (ElegirSituacion)
    ?erase2 <- (zona ?zona)
    (or
        (test (<= ?zona 0))
        (test (>= ?zona 5))
    )
    =>
    (printout t "La zona elegida no existe." crlf)
    (retract ?erase)
    (retract ?erase2)       
    (assert (ElegirSituacion))
)


(defrule TiposUso
    (ElegirUso)
    =>
    (printout t "Seleccione el uso que se le dara a los datos:" crlf)
    (printout t "1- Utilizacion general de datos (Empresa publica)." crlf)
    (printout t "2- Utilizacion general de datos (Empresa privada)." crlf)
    (printout t "3- Uso policial y juridico." crlf) 
    (printout t "Seleccione opcion: ")
    (assert (uso (read)))
)

(defrule TratarUso
    (declare (salience -1))
    ?erase <- (ElegirUso)
    (uso ?uso)
    (test (> ?uso 0))
    (test (< ?uso 4)) 
    =>
    (assert (ComprobarID))
    (retract ?erase)        
)

(defrule TratarUsoIncorrecto
    (declare (salience -1))
    ?erase <- (ElegirUso)
    ?erase2 <- (uso ?uso)
    (or
        (test (<= ?uso 0))
        (test (>= ?uso 4)) 
    )
    =>
    (printout t "El uso escogido no es valido." crlf)
    (retract ?erase)
    (retract ?erase2)       
    (assert (ElegirUso))
)

(defrule ComprobarIdentificacion
    ?erase <- (ComprobarID)
    (Dato (nombre ?nombre)
          (tipo "datosIdentificativos")
          (ID ?id)
    )
    (not (OpcionDisponible ?id))
    =>
    (printout t "Podemos identificar a una persona ya que al menos su " ?nombre " se guarda" crlf)
    (printout t "y este es un dato de caracter identificativo." crlf)
    (retract ?erase)
    (assert (MedidasLOPD))
    (assert (EsPersonal))
)

(defrule NoIdentificacion
    (declare (salience -1))
    ?erase <- (ComprobarID)
    =>
    (printout t "No existe ningun dato identificativo de la persona." crlf)
    (retract ?erase)
    (assert (MedidasLOPD))
)


(defrule MedidasSi
	(declare (salience 5))
	(MedidasLOPD)
	(EsPersonal)
	=>
	(printout t "Debe implementar todas las medidas de la pagina web http://www.cuidatusdatos.com/infocomocumplirlopd.html" crlf)
)

(defrule MedidasNoEspecialmenteProtegido
	(MedidasLOPD)
	(not (exists (Dato (tipo "especialmenteProtegidos")
	      	           (ID ?id)
		     )
		     (not (OpcionDisponible ?id))
	     )	
	)
	
	=>
	(printout t "excepto la seccion Datos Especialmente Protegidos ya que no dispone de ninguno" crlf)
)

(defrule MedidasNoConsentimiento
	(or
		(organizacion 3)
		(organizacion 4)
	)
	(MedidasLOPD)
	=>
	(printout t "excepto la seccion de consentimiento mientras el uso de los datos sea en los fines de la administracion publica, " crlf)
	(printout t "judicial o cuerpo del estado para el que trabaje" crlf)
)

(defrule MedidasNoInternacional
	(zona ?z)
	(test (<> ?z 4))
	(MedidasLOPD)
	=>
	(printout t "excepto la seccion de trasferencia internacional de datos ya que trata con paises con un nivel de proteccion adecuado" crlf)
)
(defrule MedidasNoPersonal
	?erase <- (MedidasLOPD)
	(not (EsPersonal))
	=>
	(printout t "No dispone de datos personales que requieran medidas para la ley de proteccion de datos" crlf)
	(assert (ARCO))
	(retract ?erase)
)

(defrule SeguridadAlta
	(declare (salience -5))
	?erase <- (MedidasLOPD)
	(Dato (tipo "especialmenteProtegidos")
	              (ID ?id)
        )
	(not (OpcionDisponible ?id))
	=>
	(printout t "Nivel de seguridad alto ya que tiene datos especialmente protegidos" crlf)
	(retract ?erase)
	(assert (ARCO))
)

(defrule SeguridadOtra
	(declare (salience -6))
	?erase <- (MedidasLOPD)
	=>
	(printout t "Nivel de seguridad al menos medio si tiene datos de alguno de los siguientes:" crlf)
	(printout t "-Informacion juridica o infracciones adminsitrativas." crlf)
	(printout t "-Servicios de solvencia patrimonial o credito y servicios financieros." crlf)
	(printout t "-Organizaciones con potestades de Administraciones tributarias y Seguridad Social." crlf)
	(printout t "-Datos que permitan averiguar las caracteristicas o personalidad de una persona." crlf)
	(printout t "En otro caso nivel de seguridad al menos bajo." crlf)
	(retract ?erase)
	(assert (ARCO))
)


(defrule ARCOSolicitarDatosComunes
	?erase <- (ARCO)
	?erase2 <- (zona ?z)
	?erase3 <- (uso ?u)
	?erase4 <- (organizacion ?o)
	=>
	(printout t "Datos generales necesarios para todos los modelos ARCO:" crlf)
	(printout t "Introduzca los siguientes datos sobre el RESPONSABLE DEL FICHERO:" crlf)
	(printout t "Nombre/Razon social: ")
	(assert (nombreResponsable (readline)))
	(printout t "Direccion de la Oficina / Servicio ante el que se ejercita el derecho" crlf "de oposicion (solo el nomre):")
	(assert (direccionResponsable (readline)))
	(printout t "numero (direccion): ")
	(assert (dirNumeroResponsable (readline)))
	(printout t "Codigo Postal: ")
	(assert (cpResponsable (readline)))
	(printout t "Localidad: ")
	(assert (localidadResponsable (readline)))
	(printout t "Provincia: ")
	(assert (provinciaResponsable (readline)))
	(printout t "Comunidad Autonoma:")
	(assert (comunidadResponsable (readline)))
	(printout t "C.I.F-/D.N.I.:")
	(assert (cifResponsable (readline)))

	(printout t "Introduzca los siguientes datos sobre el INTERSADO O SU REPRESENTANTE LEGAL:" crlf)
	(printout t "Nombre: ")
	(assert (nombreInteresado (readline)))
	(printout t "Direccion del Interesado (solo nombre):")
	(assert (direccionInteresado (readline)))
	(printout t "numero (direccion): ")
	(assert (dirNumeroInteresado (readline)))
	(printout t "Codigo Postal: ")
	(assert (cpInteresado (readline)))
	(printout t "Localidad: ")
	(assert (localidadInteresado (readline)))
	(printout t "Provincia: ")
	(assert (provinciaInteresado (readline)))
	(printout t "Comunidad Autonoma:")
	(assert (comunidadInteresado (readline)))
	(printout t "D.N.I.:")
	(assert (dniInteresado (readline)))
	(assert (MenuLOPD))

	(retract ?erase)
	(retract ?erase2)
	(retract ?erase3)
	(retract ?erase4)
)

(defrule LOPDMenu
	(MenuLOPD)
	=>
	(printout t "1-Deseo generar el derecho de Acceso" crlf)
	(printout t "2-Deseo generar el derecho de Rectificacion" crlf)
	(printout t "3-Deseo generar el derecho de Cancelacion" crlf)
	(printout t "4-Deseo generar el derecho de Oposicion" crlf)
	(printout t "Opcion seleccionada:")
	(assert (LOPDSeleccion (read)))
)

(defrule CrearAcceso
	?erase <-(MenuLOPD)
	(LOPDSeleccion 1)
	=>
	(printout t "El formulario se guardara en el archivo del espacio de trabajo llamado Acceso.txt" crlf)
	(open "Acceso.txt" archivo "w")
	(printout archivo "A. DERECHO DE ACCESO." crlf)
	(printout archivo "A.1 EJERCICIO DEL DERECHO DE ACCESO (1)." crlf)
	(assert (ParteComunInicial))
	(retract ?erase)
)

(defrule CrearRectificacion
	?erase <-(MenuLOPD)
	(LOPDSeleccion 2)
	=>
	(printout t "El formulario se guardara en el archivo del espacio de trabajo llamado Rectificacion.txt" crlf)
	(open "Rectificacion.txt" archivo "w")
	(printout archivo "B. DERECHO DE RECTIFICACION." crlf)
	(printout archivo "B.1 EJERCICIO DEL DERECHO DE RECTIFICACION (1)." crlf)
	(assert (ParteComunInicial))
	(retract ?erase)
)

(defrule CrearCancelacion
	?erase <-(MenuLOPD)
	(LOPDSeleccion 3)
	=>
	(printout t "El formulario se guardara en el archivo del espacio de trabajo llamado Cancelacion.txt" crlf)
	(open "Cancelacion.txt" archivo "w")
	(printout archivo "C. DERECHO DE CANCELACIÓN." crlf)
	(printout archivo "C.1 EJERCICIO DEL DERECHO DE CANCELACIÓN (1)." crlf)
	(assert (ParteComunInicial))
	(retract ?erase)
)

(defrule CrearOposicion
	?erase <-(MenuLOPD)
	(LOPDSeleccion 4)
	=>
	(printout t "El formulario se guardara en el archivo del espacio de trabajo llamado Oposicion.txt" crlf)
	(open "Oposicion.txt" archivo "w")
	(printout archivo "DERECHO DE OPOSICIÓN." crlf)
	(printout archivo "E.1 EJERCICIO DEL DERECHO DE OPOSICIÓN (1)." crlf)
	(assert (ParteComunInicial))
	(retract ?erase)
)

(defrule ErrorMenuLOPD
	(declare (salience -1))
	?erase <- (MenuLOPD)
	?erase2 <- (LOPDSeleccion ?aux)
	=>
	(printout t "No ha escogido una opcion valida. Revise su seleccion." crlf)
	(retract ?erase2)
	(retract ?erase)
	(assert (MenuLOPD))
)

(defrule EscribirParteComunInicial
	?e <-(ParteComunInicial)
	?e1 <-(nombreResponsable ?nr)
	?e2 <-(direccionResponsable ?dr)
	?e3 <-(dirNumeroResponsable ?dnr)
	?e4 <-(cpResponsable ?cpr)
	?e5 <-(localidadResponsable ?lr)
	?e6 <-(provinciaResponsable ?pr)
	?e7 <-(comunidadResponsable ?cr)
	?e8 <-(cifResponsable ?cifr)
	?e9 <-(nombreInteresado ?ni)
	?e10 <-(direccionInteresado ?di)
	?e11 <-(dirNumeroInteresado ?dni)
	?e12 <-(cpInteresado ?cpi)
	?e13 <-(localidadInteresado ?li)
	?e14 <-(provinciaInteresado ?pi)
	?e15 <-(comunidadInteresado ?ci)
	?e16 <-(dniInteresado ?dnii)
	=>
	(printout archivo crlf "DATOS DEL RESPONSABLE DEL FICHERO (2)" crlf crlf)
	(printout archivo "Nombre/Razon social: " ?nr)
	(printout archivo " Dirección de la Oficina / Servicio ante el que se ejercita el derecho de acceso C/Plaza: " ?dr)
	(printout archivo " nº: " ?dnr)
	(printout archivo ", C. ostal: " ?cpr)
	(printout archivo ", Localidad: " ?lr)
	(printout archivo ", Provincia: " ?pr)
	(printout archivo ", Comunidad Autónoma: " ?cr)
	(printout archivo " y C.I.F./D.N.I.: " ?cifr)

	(printout archivo crlf crlf "DATOS DEL INTERESADO O REPRESENTANTE LEGAL(3)." crlf crlf)
	(printout archivo "Don/Dona: " ?ni ", mayor de edad con")
	(printout archivo " Domicilio en la C/Plaza: " ?di)
	(printout archivo " nº: " ?dni)
	(printout archivo ", Localidad: " ?li)
	(printout archivo " Provincia: " ?pi)
	(printout archivo " C.P.: " ?cpi)
	(printout archivo " Comunidad Autónoma: " ?ci)
	(printout archivo " con D.N.I.: " ?dnii)
	(printout archivo ", del que acompaña copia, por medio del presente escrito ejerce el derecho de ")


	(retract ?e)
	(retract ?e1)
	(retract ?e2)
	(retract ?e3)
	(retract ?e4)
	(retract ?e5)
	(retract ?e6)
	(retract ?e7)
	(retract ?e8)
	(retract ?e9)
	(retract ?e10)
	(retract ?e11)
	(retract ?e12)
	(retract ?e13)
	(retract ?e14)
	(retract ?e15)
	(retract ?e16)
	(assert (ParteEspecifica))

)

(defrule EscribirParteEspecificaAcceso
	?erase <- (LOPDSeleccion 1)
	?erase2 <- (ParteEspecifica)
	=>
	(printout archivo "acceso, de conformidad con lo previsto en el")
	(printout archivo " articulo 15 de la Ley Organica 15/1999, de 13 de diciembre, de Protección de Datos de Carácter")
	(printout archivo "  Personal y en los artículos 27 y 28 del Real Decreto 1720/2007, de 21 de diciembre, por el que se")
	(printout archivo " desarrolla la misma, y en consecuencia," crlf crlf "SOLICITA" crlf crlf)
	
	(printout archivo "Que se le facilite gratuitamente el derecho de acceso a sus ficheros en el plazo máximo de un ")
	(printout archivo " mes a contar desde la recepción de esta solicitud, y que se remita por correo la información a la")
	(printout archivo " dirección arriba indicada en el plazo de diez días a contar desde la resolución estimatoria de la")
	(printout archivo " solicitud de acceso." crlf crlf)

	(printout archivo "Asimismo, se solicita que dicha información comprenda, de modo legible e inteligible, los datos de")
	(printout archivo " base que sobre mi persona están incluidos en sus ficheros, los resultantes de cualquier")
	(printout archivo " elaboración, proceso o tratamiento, así como el origen de los mismos, los cesionarios y la")
	(printout archivo " especificación de los concretos usos y finalidades para los que se almacenaron.")

	(assert (explicacion "Se trata de la petición de información sobre los datos personales incluidos en un fichero. Este derecho se ejerce ante el responsable del fichero (Organismo Público o entidad privada) que es quien dispone de los datos. La Agencia Española de Proteccion de Datos no dispone de sus datos personales sino solamente de la ubicacion del citado responsable si el fichero esta inscrito en el Registro General de Protección de Datos."))
	(assert (ParteComunFinal))
	(retract ?erase)
	(retract ?erase2)
)

(defrule EscribirParteEspecificaRectificacion
	?erase <- (LOPDSeleccion 2)
	?erase2 <- (ParteEspecifica)
	=>
	(printout archivo "rectificación sobre los datos anexos, aportando los correspondientes justificantes, de conformidad con lo")
	(printout archivo " previsto en el artículo 16 de la Ley Orgánica 15/1999, de 13 de diciembre, de Protección de Datos de Carácter")
	(printout archivo " Personal y en los artículos 31 y 32 del Real Decreto 1720/2007, de 21 de diciembre, por el que se desarrolla")
	(printout archivo " la misma y en consecuencia, " crlf crlf "SOLICITA" crlf crlf)
	
	(printout archivo "Que se proceda a acordar la rectificación de los datos personales sobre los cuales se ejercita el derecho, que")
	(printout archivo " se realice en el plazo de diez dias a contar desde la recogida de esta solicitud, y que se me notifique de forma")
	(printout archivo " escrita el resultado de la rectificación practicada." crlf crlf)

	(printout archivo "Que en caso de que se acuerde, dentro del plazo de diez días hábiles, que no procede acceder a practicar")
	(printout archivo " total o parcialmente las rectificaciones propuestas, se me comunique motivadamente a fin de, en su caso,")
	(printout archivo " solicitar la tutela de la Agencia Espanola de Proteccion de Datos, al amparo del articulo 18 de la citada Ley")
	(printout archivo " Orgánica 15/1999." crlf crlf)


	(printout archivo "Que si los datos rectificados hubieran sido comunicados previamente se notifique al responsable del fichero la")
	(printout archivo " rectificación practicada, con el fin de que también este proceda a hacer las correcciones oportunas para que")
	(printout archivo " se respete el deber de calidad de los datos a que se refiere el artículo 4 de la mencionada Ley Orgánica")
	(printout archivo " 15/1999." crlf crlf)

	(assert (explicacion "Consiste en la petición dirigida al responsable del fichero con el fin de que los datos personales respondan con veracidad a la situacion actual del afectado."))
	(assert (ParteComunFinal))
	(retract ?erase)
	(retract ?erase2)
)

(defrule EscribirParteEspecificaCancelacion
	?erase <- (LOPDSeleccion 3)
	?erase2 <- (ParteEspecifica)
	=>
	(printout archivo "cancelación, de conformidad con lo previsto en el")
	(printout archivo " articulo 16 de la Ley Organica 15/1999, de 13 de diciembre, de Protección de Datos de Carácter")
	(printout archivo " Personal y en los articulos 31 y 32 del Real Decreto 1720/2007, de 21 de diciembre, por el que se")
	(printout archivo " desarrolla la misma y en consecuencia," crlf crlf "SOLICITA" crlf crlf)
	

	(printout archivo "Que se proceda a acordar la cancelación de los datos personales sobre los cuales se ejercita el")
	(printout archivo " derecho, que se realice en el plazo de diez días a contar desde la recogida de esta solicitud, y que")
	(printout archivo " se me notifique de forma escrita el resultado de la cancelación practicada." crlf crlf)

	(printout archivo "Que en caso de que se acuerde dentro del plazo de diez días hábiles que no procede acceder a")
	(printout archivo " practicar total o parcialmente las cancelaciones propuestas, se me comunique motivadamente a fin")
	(printout archivo " de, en su caso, solicitar la tutela de la Agencia Española de Protección de Datos, al amparo del")
	(printout archivo " artículo 18 de la citada Ley Orgánica 15/1999." crlf crlf)

	(printout archivo "Que si los datos cancelados hubieran sido comunicados previamente se notifique al responsable")
	(printout archivo " del fichero la cancelación practicada con el fin de que también éste proceda a hacer las")
	(printout archivo " correcciones oportunas para que se respete el deber de calidad de los datos a que se refiere el")
	(printout archivo " artículo 4 de la mencionada Ley Orgánica 15/1999." crlf crlf)

	(assert (explicacion "Consiste en la petición de cancelación de un dato que resulte innecesario o no pertinente para la finalidad con la que fue recabado. El dato será bloqueado, es decir, será identificado y reservado con el fin de impedir su tratamiento."))
	(assert (ParteComunFinal))
	(retract ?erase)
	(retract ?erase2)
)

(defrule EscribirParteEspecificaOposicion
	?erase <- (LOPDSeleccion 4)
	?erase2 <- (ParteEspecifica)
	=>

	(printout archivo "oposición, de conformidad con lo previsto en los")
	(printout archivo " artículos 6.4, 17 y 30.4 de la Ley Orgánica 15/1999, de 13 de diciembre, de Protección de Datos de")
	(printout archivo " carácter personal y en los artículos 34 y 35 del Real Decreto 1720/2007, de 21 de diciembre , que")
	(printout archivo " la desarrolla y en consecuencia," crlf crlf "SOLICITA" crlf crlf "EXPONGO, ")
	
	(printout t " Exponga en un unico parrafo la situacion en la que se produce el tratamiento" crlf)
	(printout t " de sus datos personales y enumerar los motivos porlos que se opone al mismo:" crlf)

	(printout archivo (readline) crlf crlf)

	(printout archivo "SOLICITO," crlf)
	(printout archivo "Para acreditar la situación descrita, acompaño una copia de los siguientes documentos:")

	(printout archivo "Para acreditar la situación descrita, acompaño una copia de los siguientes documentos:" crlf)
	(printout t " Enumere en unico parrafo todos los archivos que adjunta para acreditar la situacion descrita: " crlf)
	(printout archivo (readline) crlf crlf)


	(assert (explicacion "Se trata de la solicitud de oposición al tratamiento de los datos personales incluidos en un fichero. Este derecho se ejerce ante el responsable del fichero (Organismo Público o entidad privada) que es quien dispone de los datos. La Agencia Espñola de Protección de Datos no dispone de sus datos personales sino solamente de la ubicación del citado responsable si el fichero está inscrito en el Registro General de Protección de Datos."))
	(assert (ParteComunFinal))
	(retract ?erase)
	(retract ?erase2)
)



(defrule EscribirParteComunFinal
	?erase <- (ParteComunFinal)
	?erase2 <- (explicacion ?exp)
	?erase3 <- (Elegido 3)
	=>
	(printout t "Lugar donde se va a firmar el archivo: ")
	(bind ?lugar (read))
	(printout t "Dia en el que se va a firmar el archivo: ")
	(bind ?dia (read))
	(printout t "Nombre del mes en el que se va a firmar el archivo: ")
	(bind ?mes (read))
	(printout t "Anio en el que se va a firmar el archivo: ")
	(bind ?ano (read))


	(printout archivo crlf crlf "En " ?lugar ", a " ?dia " de " ?mes " de " ?ano crlf)
	(printout archivo crlf "     Firmado" crlf crlf)
	(printout archivo "(1) " ?exp crlf crlf)
	(printout archivo "(2) Si Vd. desconoce la dirección del responsable del fichero puede dirigirse a la Agencia Espanola" crlf)
	(printout archivo " de Protección de Datos para solicitar esta información en el teléfono 901 100 099. " crlf crlf)
        (printout archivo "(3) También podrá ejercitarse a través de representación legal,")
        (printout archivo " en cuyo caso, además del DNI del interesado, habrá de aportarse DNI y documento acreditativo autentico de la representación del tercero.")
	(retract ?erase)
	(retract ?erase2)
	(retract ?erase3)
	(close archivo)
	(printout t "Archivo generado en el directorio de trabajo" crlf)
	(assert (mostrarMenu))
	(assert (MostrarDatos))
)