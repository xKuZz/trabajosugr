;;; Con templates

(deftemplate Persona 
  (field nombre)
  (field sexo)
  (field padre)
  (field madre)
)

(deffacts personas_t 
	(Persona
		(nombre David)
		(sexo   Hombre)
		(padre  Andres)
		(madre  Paqui)
	)
    (Persona
    	(nombre AnaMaria)
    	(sexo   Mujer)
    	(padre  Andres)
    	(madre  Paqui)
    )
    (Persona
    	(nombre Veronica)
    	(sexo   Mujer)
    	(padre  Andres)
    	(madre  Paqui)
    )
    (Persona 
   		(nombre Andres)
   		(sexo	Hombre)
   		(padre  Paco)
   		(madre  Mari)
   	)
   	(Persona
   		(nombre Paqui)
   		(sexo   Mujer)
   		(padre  Crisanto)
   		(madre  MariaTeresa)
   	)
   	(estarCasado Andres Paqui)
   	(estarCasado Paco Mari)
   	(estarCasado Cristanto MariaTeresa)

    ; Ti@s maternales
   	(Persona
   		(nombre AnaR)
   		(sexo   Mujer)
   		(padre  Crisanto)
   		(madre  MariaTeresa)
   	)
   	(Persona
   		(nombre Ramon)
   		(sexo   Hombre)
   		(padre  Crisanto)
   		(madre  MariaTeresa)
   	)
   	(estarCasado Ramon Susana)
   	(Persona
   		(nombre Jesualdo)
   		(sexo   Hombre)
   		(padre  Crisanto)
   		(madre  MariaTeresa)
   	)
   	(estarCasado Jesualdo Diana)

    ; Prim@s maternales
    (Persona
    	(nombre JesualdoJr)
    	(sexo   Hombre)
    	(padre  Jesualdo)
    	(madre  Diana)
    )
    (Persona
    	(nombre Natalia)
    	(sexo   Mujer)
    	(padre  Alberto)
    	(madre  AnaR)
    )
    (Persona
    	(nombre Ana)
    	(sexo   Mujer)
    	(padre  Alberto)
    	(madre  AnaR)
    )
    (Persona
    	(nombre Joaquin)
    	(sexo   Hombre)
    	(padre  Antonio)
    	(madre  AnaR)
    )
    (Persona
    	(nombre Hector)
    	(sexo   Hombre)
    	(padre  Ramon)
    	(madre  Susana)
    )
    (Persona
    	(nombre Jorge)
    	(sexo   Hombre)
    	(padre  Ramon)
    	(madre  Susana)
    )
    ; Ti@s paternales
    (Persona 
   		(nombre PacoElTio)
   		(sexo	Hombre)
   		(padre  Paco)
   		(madre  Mari)
   	)
   	(estarCasado PacoElTio Antonia)
   	(Persona 
   		(nombre JoseLuis)
   		(sexo	Hombre)
   		(padre  Paco)
   		(madre  Mari)
   	)
   	(Persona 
   		(nombre JuanCarlos)
   		(sexo	Hombre)
   		(padre  Paco)
   		(madre  Mari)
   	)
   	(estarCasado JuanCarlos MariAngeles)
   	(Persona 
   		(nombre Jesus)
   		(sexo	Hombre)
   		(padre  Paco)
   		(madre  Mari)
   	)

   	; Prim@s paternales
   	(Persona
   		(nombre Javi)
   		(sexo   Hombre)
   		(padre  PacoElTio)
   		(madre  Antonia)
   	)
   	(Persona
   		(nombre MariCarmen)
   		(sexo   Mujer)
   		(padre  PacoElTio)
   		(madre  Antonia)
   	)

   	(Persona
   		(nombre Raquel)
   		(sexo   Mujer)
   		(padre  Jesus)
   		(madre  AnaG)
   	)
   	(Persona
   		(nombre Daniel)
   		(sexo   Hombre)
   		(padre  Jesus)
   		(madre  AnaG)
   	)
   	(Persona
   		(nombre Cristina)
   		(sexo   Mujer)
   		(padre  JuanCarlos)
   		(madre  MariAngeles)
   	)
   	(iniciar)

)

;;;; -------------------------

;; Reglas con templates

(defrule SerHermano
	(Persona
		(nombre ?nombre1)
		(sexo Hombre)
		(padre ?padre)
		(madre ?madre)
	)
	(Persona
		(nombre ?nombre2 & ~?nombre1)
		(padre 	?padre)
		(madre 	?madre)
	)
	=>
	(assert (EsHermano ?nombre1 ?nombre2))
)

(defrule SerHermana
	(Persona
		(nombre ?nombre1)
		(sexo Mujer)
		(padre ?padre)
		(madre ?madre)
	)
	(Persona
		(nombre ?nombre2 & ~?nombre1)
		(padre 	?padre)
		(madre 	?madre)
	)
	=>
	(assert (EsHermana ?nombre1 ?nombre2))
)

(defrule SerPadre
	(Persona
		(nombre ?nombre2)
		(padre  ?nombre1)
	)
	=>
	(assert (EsPadre ?nombre1 ?nombre2))
	(assert (EsProgenitor ?nombre1 ?nombre2))
)

(defrule SerMadre
	(Persona
		(nombre ?nombre2)
		(madre  ?nombre1)
	)
	=>
	(assert (EsMadre ?nombre1 ?nombre2))
	(assert (EsProgenitor ?nombre1 ?nombre2))
)

(defrule SerHijo
	(EsProgenitor ?nombre1 ?nombre2)
	(Persona
		(nombre ?nombre2)
		(sexo  Hombre)
	)
	=>
	(assert (EsHijo ?nombre2 ?nombre1))
)

(defrule SerHija
	(EsProgenitor ?nombre1 ?nombre2)
	(Persona
		(nombre ?nombre2)
		(sexo  Mujer)
	)
	=>
	(assert (EsHija ?nombre2 ?nombre1))
)

(defrule SerAbuelo
	(or
		(EsHijo ?nombre1 ?progenitor)
		(EsHija ?nombre1 ?progenitor)
	)
	(EsPadre ?nombre2 ?progenitor)
	=>
	(assert (EsAbuelo ?nombre2 ?nombre1))
)

(defrule SerAbuela
	(or
		(EsHijo ?nombre1 ?progenitor)
		(EsHija ?nombre1 ?progenitor)
	)
	(EsMadre ?nombre2 ?progenitor)
	=>
	(assert (EsAbuela ?nombre2 ?nombre1))
)

(defrule SerNieto
	(Persona
		(nombre ?nombre1)
		(sexo   Hombre)
	)
	(or
		(EsAbuelo ?nombre2 ?nombre1)
		(EsAbuela ?nombre2 ?nombre1)
	)
	=>
	(assert (EsNieto ?nombre1 ?nombre2))
)

(defrule SerNieta
	(Persona
		(nombre ?nombre1)
		(sexo   Mujer)
	)
	(or
		(EsAbuelo ?nombre2 ?nombre1)
		(EsAbuela ?nombre2 ?nombre1)
	)
	=>
	(assert (EsNieta ?nombre1 ?nombre2))
)

(defrule SerTio
	(EsProgenitor ?progenitor ?sobri)
	(EsHermano ?tio ?progenitor)
	=>
	(assert (EsTio ?tio ?sobri))
)

(defrule SerTia
	(EsProgenitor ?progenitor ?sobri)
	(EsHermana ?tia ?progenitor)
	=>
	(assert (EsTia ?tia ?sobri))
)

(defrule SerSobrino
	(or
		(EsTio ?tio ?sobrino)
		(EsTia ?tio ?sobrino)
	)
	(Persona
		(nombre ?sobrino)
		(sexo   Hombre)
	)
	=>
	(assert (EsSobrino ?sobrino ?tio))
)

(defrule SerSobrina
	(or
		(EsTio ?tio ?sobrina)
		(EsTia ?tio ?sobrina)
	)
	(Persona
		(nombre ?sobrina)
		(sexo   Mujer)
	)
	=>
	(assert (EsSobrina ?sobrina ?tio))
)

(defrule SerPrimo
	(Persona 
		(nombre ?primo1)
		(sexo   Hombre)
	)
	(EsProgenitor ?progenitor1 ?primo1)
	(or
		(EsHermano ?progenitor1 ?progenitor2)
		(EsHermana ?progenitor1 ?progenitor2)
		(EsHermanastro ?progenitor1 ?progenitor2)
		(EsHermanastra ?progenitor1 ?progenitor2)
	)
	(EsProgenitor ?progenitor2 ?primo2)
	=>
	(assert (EsPrimo ?primo1 ?primo2))
)

(defrule SerPrima
	(Persona 
		(nombre ?primo1)
		(sexo   Mujer)
	)
	(EsProgenitor ?progenitor1 ?primo1)
	(or
		(EsHermano ?progenitor1 ?progenitor2)
		(EsHermana ?progenitor1 ?progenitor2)
		(EsHermanastro ?progenitor1 ?progenitor2)
		(EsHermanastra ?progenitor1 ?progenitor2)
	)
	(EsProgenitor ?progenitor2 ?primo2)
	=>
	(assert (EsPrima ?primo1 ?primo2))
)

(defrule SerHermanastro
	(Persona
		(nombre ?nombre1)
		(sexo   Hombre)
		(padre  ?padre)
		(madre  ?madre)
	)
	(or
		(Persona
			(nombre ?nombre2 & ~?nombre1)
			(padre  ?padre)
			(madre  ?madre2 & ~?madre)
		)
		(Persona
			(nombre ?nombre2 & ~?nombre1)
			(padre  ?padre2 & ~?padre)
			(madre  ?madre)
		)
	)
	=>
	(assert (EsHermanastro ?nombre1 ?nombre2))
)

(defrule SerHermanastra
	(Persona
		(nombre ?nombre1)
		(sexo   Mujer)
		(padre  ?padre)
		(madre  ?madre)
	)
	(or
		(Persona
			(nombre ?nombre2 & ~?nombre1)
			(padre  ?padre)
			(madre  ?madre2 & ~?madre)
		)
		(Persona
			(nombre ?nombre2 & ~?nombre1)
			(padre  ?padre2 & ~?padre)
			(madre  ?madre)
		)
	)
	=>
	(assert (EsHermanastra ?nombre1 ?nombre2))
)

(defrule Casados
	(estarCasado ?marido ?esposa)
	=>
	(assert (EsMarido ?marido ?esposa))
	(assert (EsEsposa ?esposa ?marido))
)

(defrule SerSuegros1
	(estarCasado ?conyuge1 ?conyuge2)
	(Persona
		(nombre ?conyuge1)
		(padre  ?padre1)
		(madre  ?madre1)
	)
	=>
	(assert (EsSuegro ?padre1 ?conyuge2))
	(assert (EsSuegra ?madre1 ?conyuge2))
)

(defrule SerSuegros2
	(estarCasado ?conyuge1 ?conyuge2)
	(Persona
		(nombre ?conyuge2)
		(padre  ?padre2)
		(madre  ?madre2)
	)
	=>
	(assert (EsSuegro ?padre2 ?conyuge1))
	(assert (EsSuegra ?madre2 ?conyuge1))
)

;;; Reglas para las explicaciones
(defrule ExplicarHermano
	?r <-(buscar_relaciones ?a ?b)
	(EsHermano ?a ?b)
	(EsPadre ?padre ?a)
	(EsMadre ?madre ?a)
	=>
	(printout t ?a " es hermano de " ?b)
	(printout t " porque " ?padre " es padre de amb@s y ")
	(printout t ?madre " es madre de amb@s." crlf)
	(retract ?r)
	(assert (iniciar))
)

(defrule ExplicarHermana
	?r <-(buscar_relaciones ?a ?b)
	(EsHermana ?a ?b)
	(EsPadre ?padre ?a)
	(EsMadre ?madre ?a)
	=>
	(printout t ?a " es hermana de " ?b)
	(printout t " porque " ?padre " es padre de amb@s y ")
	(printout t ?madre " es madre de amb@s." crlf)
	(retract ?r)
	(assert (iniciar))
)

(defrule ExplicarPadre
	?r <-(buscar_relaciones ?a ?b)
	(EsPadre ?a ?b)
	=>
	(printout t ?a " es el padre de " ?b "." crlf)
	(retract ?r)
	(assert (iniciar))
)

(defrule ExplicarMadre
	?r <- (buscar_relaciones ?a ?b)
	(EsMadre ?a ?b)
	=>
	(printout t ?a " es la madre de " ?b "." crlf)
	(retract ?r)
	(assert (iniciar))
)

(defrule ExplicarHijo
	?r <- (buscar_relaciones ?a ?b)
	(EsHijo ?a ?b)
	=>
	(printout t ?a " es hijo de " ?b "." crlf)
	(retract ?r)
	(assert (iniciar))
)

(defrule ExplicarHija
	?r <-(buscar_relaciones ?a ?b)
	(EsHija ?a ?b)
	=>
	(printout t ?a " es hija de " ?b "." crlf)
	(retract ?r)
	(assert (iniciar))
)

(defrule ExplicarAbuelo
	?r <-(buscar_relaciones ?a ?b)
	(EsAbuelo ?a ?b)
	(EsProgenitor ?a ?c)
	(EsProgenitor ?c ?b)
	=>
	(printout t ?a " es abuelo de " ?b)
	(printout t " porque " ?a " es el padre de " ?c" y ") 
	(printout t ?c " es progenitor de " ?b "." crlf)
	(retract ?r)
	(assert (iniciar))
)

(defrule ExplicarAbuela
	?r <-(buscar_relaciones ?a ?b)
	(EsAbuela ?a ?b)
	(EsProgenitor ?a ?c)
	(EsProgenitor ?c ?b)
	=>
	(printout t ?a " es abuela de " ?b)
	(printout t " porque " ?a " es la madre de " ?c" y ") 
	(printout t ?c " es progenitor de " ?b "." crlf)
	(retract ?r)
	(assert (iniciar))
)

(defrule ExplicarNieto
	?r <-(buscar_relaciones ?b ?a)
	(EsNieto ?b ?a)
	(EsProgenitor ?a ?c)
	(EsProgenitor ?c ?b)
	=>
	(printout t ?b " es nieto de " ?a)
	(printout t " porque " ?a " es progenitor de " ?c" y ") 
	(printout t ?c " es progenitor de " ?b "." crlf)
	(retract ?r)
	(assert (iniciar))
)

(defrule ExplicarNieta
	?r <-(buscar_relaciones ?b ?a)
	(EsNieta ?b ?a)
	(EsProgenitor ?a ?c)
	(EsProgenitor ?c ?b)
	=>
	(printout t ?b " es nieta de " ?a)
	(printout t " porque " ?a " es progenitor de " ?c" y ") 
	(printout t ?c " es progenitor de " ?b "." crlf)
	(retract ?r)
	(assert (iniciar))
)

(defrule ExplicarTio
	?r <-(buscar_relaciones ?a ?b)
	(EsTio ?a ?b)
	(EsProgenitor ?c ?b)
	=>
	(printout t ?a " es el tio de " ?b)
	(printout t " porque " ?a " es hermano de " ?c " y ")
	(printout t ?c " es progenitor de " ?b "." crlf)
	(retract ?r)
	(assert (iniciar))
)

(defrule ExplicarTia
	?r <- (buscar_relaciones ?a ?b)
	(EsTia ?a ?b)
	(EsProgenitor ?c ?b)
	=>
	(printout t ?a " es la tia de " ?b)
	(printout t " porque " ?a " es hermana de " ?c " y ")
	(printout t ?c " es progenitor de " ?b "." crlf)
	(retract ?r)
	(assert (iniciar))
)

(defrule ExplicarSobrino
	?r <- (buscar_relaciones ?b ?a)
	(EsSobrino ?b ?a)
	(EsProgenitor ?c ?b)
	=>
	(printout t ?b " es el sobrino de " ?a)
	(printout t " porque " ?a " y " ?c " son herman@s y ")
	(printout t ?c " es progenitor de " ?b "." crlf)
	(retract ?r)
	(assert (iniciar))
)

(defrule ExplicarSobrina
	?r <- (buscar_relaciones ?b ?a)
	(EsSobrino ?b ?a)
	(EsProgenitor ?c ?b)
	=>
	(printout t ?b " es la sobrina de " ?a)
	(printout t " porque " ?a " y " ?c " son herman@s y ")
	(printout t ?c " es progenitor de " ?b "." crlf)
	(retract ?r)
	(assert (iniciar))
)

(defrule ExplicarPrimo
	?r <- (buscar_relaciones ?a ?b)
	(EsPrimo ?a ?b)
	(EsProgenitor ?c ?a)
	(EsProgenitor ?d ?b)
	(or
		(EsHermano ?c ?d)
		(EsHermana ?c ?d)
	)
	=>
	(printout t ?a " es primo de " ?b)
	(printout t " porque " ?c " es progenitor de " ?a ", ")
	(printout t ?d " es progenitor de " ?b " y ")
	(printout t ?c " y " ?d " son herman@s." crlf)
	(retract ?r)
	(assert (iniciar))
)

(defrule ExplicarPrima
	?r <- (buscar_relaciones ?a ?b)
	(EsPrima ?a ?b)
	(EsProgenitor ?c ?a)
	(EsProgenitor ?d ?b)
	(or
		(EsHermano ?c ?d)
		(EsHermana ?c ?d)
	)
	=>
	(printout t ?a " es prima de " ?b)
	(printout t " porque " ?c " es progenitor de " ?a ", ")
	(printout t ?d " es progenitor de " ?b " y ")
	(printout t ?c " y " ?d " son herman@s." crlf)
	(retract ?r)
	(assert (iniciar))
)

(defrule ExplicarHermanastro
	?r <- (buscar_relaciones ?a ?b)
	(EsHermanastro ?a ?b)
	(or
		(and
			(EsPadre ?c ?a)
			(EsPadre ?c ?b)
		)
		(and
			(EsMadre ?c ?a)
			(EsMadre ?c ?b)
		)
	)
	=>
	(printout t ?a " es hermanastro de " ?b " poque ")
	(printout t ?a " comparten a " ?c " como progenitor pero")
	(printout t " no comparten al otro progenitor")
	(retract ?r)
	(assert (iniciar))
)

(defrule ExplicarHermanastra
	?r <- (buscar_relaciones ?a ?b)
	(EsHermanastra ?a ?b)
	(or
		(and
			(EsPadre ?c ?a)
			(EsPadre ?c ?b)
		)
		(and
			(EsMadre ?c ?a)
			(EsMadre ?c ?b)
		)
	)
	=>
	(printout t ?a " es hermanastra de " ?b " poque ")
	(printout t ?a " comparten a " ?c " como progenitor pero")
	(printout t " no comparten al otro progenitor")
	(retract ?r)
	(assert (iniciar))
)

(defrule ExplicarMarido
	?r <- (buscar_relaciones ?a ?b)
	(esMarido ?a ?b)
	=>
	(printout t ?a " es el marido de " ?b " porque estan casados uno con otro." crlf)
	(retract ?r)
	(assert (iniciar))
)

(defrule ExplicarEsposa
	?r <- (buscar_relaciones ?a ?b)
	(EsEsposa ?a ?b)
	=>
	(printout t ?a " es la esposa de " ?b " porque estan casados uno con otro." crlf)
	(retract ?r)
	(assert (iniciar))
)

(defrule ExplicarSuegro
	?r <- (buscar_relaciones ?a ?b)
	(EsSuegro ?a ?b)
	(or
		(estarCasado ?b ?c)
		(estarCasado ?c ?b)
	)
	=>
	(printout t ?a " es el suegro de " ?b " porque ")
	(printout t ?b " y " ?c " estan casados y ")
	(printout t ?a " es el padre de " ?c crlf)
	(retract ?r)
	(assert (iniciar))
)

(defrule ExplicarSuegra
	?r <- (buscar_relaciones ?a ?b)
	(EsSuegra ?a ?b)
	(or
		(estarCasado ?b ?c)
		(estarCasado ?c ?b)
	)
	=>
	(printout t ?a " es la suegra de " ?b " porque ")
	(printout t ?b " y " ?c " estan casados y ")
	(printout t ?a " es la madre de " ?c crlf)
	(retract ?r)
	(assert (iniciar))
)

;;; Regla para lectura
(defrule ObtenerNombrePersonas
	?i <- (iniciar)
	=>
    (printout t "Introduzca el nombre de la primera persona" crlf)
    (bind ?persona1 (read))
	(printout t "Introduzca el nombre de la segunda persona" crlf)
	(bind ?persona2 (read))
	(assert (buscar_relaciones ?persona1 ?persona2))
	(retract ?i)
) 
