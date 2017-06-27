(define (domain zeno-travel)


(:requirements
  :typing
  :fluents
  :derived-predicates
  :negative-preconditions
  :universal-preconditions
  :disjuntive-preconditions
  :conditional-effects
  :htn-expansion

  ; Requisitos adicionales para el manejo del tiempo
  :durative-actions
  :metatags
 )

(:types aircraft person city - object)
(:constants slow fast - object)
(:predicates (at ?x - (either person aircraft) ?c - city)
             (in ?p - person ?a - aircraft)
             (different ?x ?y) (igual ?x ?y)
             (hay-fuel ?a ?c1 ?c2)
             (puedo_rapido ?a - aircraft ?c1 - city ?c2 - city)
             (puedo_lento ?a - aircraft ?c1 - city ?c2 - city)
             )
(:functions (fuel ?a - aircraft)
            (distance ?c1 - city ?c2 - city)
            (slow-speed ?a - aircraft)
            (fast-speed ?a - aircraft)
            (slow-burn ?a - aircraft)
            (fast-burn ?a - aircraft)
            (capacity ?a - aircraft)
            (refuel-rate ?a - aircraft)
            (total-fuel-used)
            (fuel-limit)
            (boarding-time)
            (debarking-time)
            )

;; el consecuente "vac�o" se representa como "()" y significa "siempre verdad"
(:derived
  (igual ?x ?x) ())

(:derived 
  (different ?x ?y) (not (igual ?x ?y)))




;; este literal derivado se utiliza para deducir, a partir de la información en el estado actual, 
;; si hay fuel suficiente para que el avión ?a vuele de la ciudad ?c1 a la ?c2
;; el antecedente de este literal derivado comprueba si el fuel actual de ?a es mayor que 1. 
;; En este caso es una forma de describir que no hay restricciones de fuel. Pueden introducirse una
;; restricción más copleja  si en lugar de 1 se representa una expresión más elaborada (esto es objeto de
;; los siguientes ejercicios).
(:derived 
  
  (hay-fuel ?a - aircraft ?c1 - city ?c2 - city)
  (> (fuel ?a) 1))

(:task transport-person
	:parameters (?p - person ?c - city)
	
  (:method Case1 ; si la persona est� en la ciudad no se hace nada
	 :precondition (at ?p ?c)
	 :tasks ()
   )
	 
   
   (:method Case2 ;si no est� en la ciudad destino, pero avion y persona est�n en la misma ciudad
	  :precondition (and (at ?p - person ?c1 - city)
			                 (at ?a - aircraft ?c1 - city))
				     
	  :tasks ( 
	  	      (board ?p ?a ?c1)
		        (mover-avion ?a ?c1 ?c)
		        (debark ?p ?a ?c )
    )
  )
   ;; EJERCICIO 1
   (:method Case3 ; si el avion y la persona están en ciudades disntintas
    :precondition (and (at ?a - aircraft ?ca - city)
                       (at ?p - person ?cp - city)
                  )
    :tasks (
            (mover-avion ?a ?ca ?cp)
            (board ?p ?a ?cp)
            (mover-avion ?a ?cp ?c)
            (debark ?p ?a ?c)
    )
   )

)

;; Ejercicio 3
(:derived 
  (puedo_rapido ?a ?c1 ?c2)
  (<= (+ (total-fuel-used) (* (distance ?c1 ?c2) (fast-burn ?a)) )
      (fuel-limit))
)

(:derived 
  (puedo_lento ?a ?c1 ?c2)
  (<= (+ (total-fuel-used) (* (distance ?c1 ?c2) (slow-burn ?a)) )
      (fuel-limit))
)


(:task mover-avion
 :parameters (?a - aircraft ?c1 - city ?c2 - city)
 ;; Ejercicio 3
 (:method fuel-suficiente-fast
  :precondition (and (hay-fuel ?a ?c1 ?c2)
                     (puedo_rapido ?a ?c1 ?c2)
                )
  :tasks (
          (zoom ?a ?c1 ?c2)
         )
 )
 (:method sin-fuel-fast
      :precondition (puedo_rapido ?a ?c1 ?c2)
      :tasks(
          (refuel ?a ?c1)
          (zoom ?a ?c1 ?c2)
      )
  )

  (:method fuel-suficiente-slow
  :precondition (and (hay-fuel ?a ?c1 ?c2)
                     (puedo_lento ?a ?c1 ?c2)
                )
  :tasks (
          (fly ?a ?c1 ?c2)
         )
   )
  ;; EJERCICIO 2
  (:method sin-fuel-slow
      :precondition (puedo_lento ?a ?c1 ?c2)
      :tasks(
          (refuel ?a ?c1)
          (fly ?a ?c1 ?c2)
      )
  )
 )
 
(:import "Primitivas-Zenotravel.pddl") 


)
