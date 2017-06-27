;;;;;;;;;;;;;;
;; Ejercicio 4 - Definición de dominio
;;;;;;;;;;;;;;
(define (domain DOMINIO_BELKAN_5)
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
          bikini - objeto
          zapatillas - objeto
          ARENOSO PEDREGOSO - puedemoverse
          puedemoverse AGUA BOSQUE PRECIPICIO - zona
          zona

  )
  (:predicates
    (esta_en ?l - localizable ?z - zona) ;; Posición de un objeto localizable
    (mira_hacia ?j - jugador ?o - orientacion) ;; Orientación del personaje
    (camino ?origen - zona ?destino - zona ?o - orientacion) ;; Representación del grafo
    (en_mano ?j - jugador ?o - objeto) ;; Objeto en mano
    (en_mochila ?j - jugador ?o - objeto) ;; Objeto en mochila
    (posee ?p - personaje ?o - objeto) ;; Indica qué objeto hemos entregado a qué personaje
  )

  (:functions
    (distanciatotal)
    (costemovimiento)
    (puntua ?p - personaje ?o - objeto)
    (puntuacion)
    (capacidad_mochila)
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
  (:action AVANZAR-ARENOSOPEDREGOSO
    :parameters (?j - jugador ?o - orientacion ?origen - zona ?destino - puedemoverse)
    :precondition (and 
                    (mira_hacia ?j ?o)
                    (esta_en ?j ?origen)
                    (camino ?origen ?destino ?o)
                  )
    :effect (and 
              (not (esta_en ?j ?origen))
              (esta_en ?j ?destino)
              (increase (distanciatotal) (costemovimiento))
            )
  )

  (:action AVANZAR-AGUA
    :parameters (?j - jugador ?o - orientacion ?origen - zona ?destino - AGUA)
    :precondition (and 
                    (mira_hacia ?j ?o)
                    (esta_en ?j ?origen)
                    (camino ?origen ?destino ?o)
                    (or
                      (en_mano ?j bikini)
                      (en_mochila ?j bikini)
                    )
                  )
    :effect (and 
              (not (esta_en ?j ?origen))
              (esta_en ?j ?destino)
              (increase (distanciatotal) (costemovimiento))
            )
  )

   (:action AVANZAR-BOSQUE
    :parameters (?j - jugador ?o - orientacion ?origen - zona ?destino - BOSQUE)
    :precondition (and 
                    (mira_hacia ?j ?o)
                    (esta_en ?j ?origen)
                    (camino ?origen ?destino ?o)
                    (or
                      (en_mano ?j zapatillas)
                      (en_mochila ?j zapatillas)
                    )
                  )
    :effect (and 
              (not (esta_en ?j ?origen))
              (esta_en ?j ?destino)
              (increase (distanciatotal) (costemovimiento))
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
                  )
    :effect (and 
              (not (en_mano ?j ?o))
              (esta_en ?o ?z)
            )
  )

  (:action GUARDAR-MOCHILA
    :parameters (?j - jugador ? ?o - objeto)
    :precondition (and 
                    ;; Como está hecho sólo podemos tener un objeto del mismo tipo
                    (not (en_mochila ?j ?o))
                    ;; Si queda capacidad en la mochila
                    (> (capacidad_mochila) 0)
                    (en_mano ?j ?o)
                  )
    :effect (and
              (not (en_mano ?j ?o))
              (en_mochila ?j ?o)
              (decrease (capacidad_mochila) 1)
            )
  )

  (:action SACAR-MOCHILA
    :parameters (?j - jugador ?o - objeto)
    :precondition (and 
                    (not (exists (?i - objeto) (en_mano ?j ?i)))
                    (en_mochila ?j ?o)
                  )
    :effect (and
              (not (en_mochila ?j ?o))
              (en_mano ?j ?o)
              (increase (capacidad_mochila) 1)
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
              (increase (puntuacion) (puntua ?p ?o))
            )
  )
)