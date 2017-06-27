(define (problem GiroDerechaBelkan)
	
  (:domain DOMINIO_BELKAN_1)

  (:objects
    jugador1 - jugador
    zona1 - zona
    norte - orientacion
    sur - orientacion
    este - orientacion
    oeste - orientacion
    oscar - objeto
    bruja - personaje
  )

  (:init
    (esta_en jugador1 zona1)
    (mira_hacia jugador1 norte)
  ) 

  (:goal
    (mira_hacia jugador1 este)
  )

)