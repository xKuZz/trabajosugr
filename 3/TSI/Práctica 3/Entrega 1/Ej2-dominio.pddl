;;;;;;;;;;;;;;
;; Ejercicio 2 - Definición de dominio
;;;;;;;;;;;;;;
(define (domain DOMINIO_BELKAN_2)
  (:requirements :adl :typing :fluents)
  (:types localizable
  	      jugador - localizable
  	      personaje - localizable 

  	      objeto - localizable

  	      orientacion

  	      princesa - personaje
  	      principe - personaje
  	      leonardo - personaje
  	      profesor - personaje
  	      bruja - personaje

  	      oscar - objeto
  	      manzana - objeto
  	      rosa - objeto
  	      algoritmo - objeto
          oro - objeto
          
  	      zona

  )
  (:predicates
  	(esta_en ?l - localizable ?z - zona) ;; Posición de un objeto localizable
  	(mira_hacia ?j - jugador ?o - orientacion) ;; Orientación del personaje
    (camino ?origen - zona ?destino - zona ?o - orientacion) ;; Representación del grafo
  	(en_mano ?j - jugador ?o - objeto) ;; Objeto en mano
    (posee ?p - personaje ?o - objeto) ;; Indica qué objeto hemos entregado a qué personaje
  )

  (:functions
    (distanciatotal)
    (distancia ?origen - zona ?destino - zona)
  )

  (:action GIRAR-IZQUIERDA
  	 :parameters (?j - jugador ?o - orientacion)
  	 :precondition (mira_hacia ?j ?o)
  	 :effect (and
                (when (mira_hacia ?j norte) (mira_hacia ?j oeste) )
                (when (mira_hacia ?j oeste) (mira_hacia ?j sur) )
                (when (mira_hacia ?j sur)   (mira_hacia ?j este) )
                (when (mira_hacia ?j este)  (mira_hacia ?j norte) )
                (not (mira_hacia ?j ?o) )
  	 		     )
  )
  (:action GIRAR-DERECHA
     :parameters (?j - jugador ?o - orientacion)
     :precondition (mira_hacia ?j ?o)
     :effect (and
                (when (mira_hacia ?j norte) (mira_hacia ?j este) )
                (when (mira_hacia ?j oeste) (mira_hacia ?j norte) )
                (when (mira_hacia ?j sur)   (mira_hacia ?j oeste) )
                (when (mira_hacia ?j este)  (mira_hacia ?j sur) )
                (not (mira_hacia ?j ?o) )
             )
  )
  (:action AVANZAR
    :parameters (?j - jugador ?o - orientacion ?origen - zona ?destino - zona)
    :precondition (and 
                    (mira_hacia ?j ?o)
                    (esta_en ?j ?origen)
                    (camino ?origen ?destino ?o)
                  )
    :effect (and 
              (not (esta_en ?j ?origen))
              (esta_en ?j ?destino)
              (increase (distanciatotal) (distancia ?origen ?destino))
            )
  )
  (:action COGER-OBJETO
    :parameters (?j - jugador ?z - zona ?o - objeto)
    :precondition (and 
                    (not (exists (?i - objeto) (en_mano ?j ?i)))
                    (esta_en ?j ?z)
                    (esta_en ?o ?z)
                  )
    :effect (and
              (en_mano ?j ?o)
              (not (esta_en ?o ?z))
            )
  )
  (:action DEJAR-OBJETO
    :parameters (?j - jugador ?z - zona ?o - objeto)
    :precondition (and 
                    (en_mano ?j ?o)
                    (esta_en ?j ?z)
                    (not (esta_en ?o ?z))
                  )
    :effect (and 
              (not (en_mano ?j ?o))
              (esta_en ?o ?z)
            )
  )
  (:action DAR-OBJETO
    :parameters (?j - jugador ?z - zona ?o - objeto ?p - personaje)
    :precondition (and 
                    (en_mano ?j ?o)
                    (esta_en ?j ?z)
                    (esta_en ?p ?z)
                  )
    :effect (and 
              (not (en_mano ?j ?o))
              (posee ?p ?o)
            )
  )
)