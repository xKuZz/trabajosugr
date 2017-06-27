(define (problem AvanzarBelkan)
	
  (:domain DOMINIO_BELKAN_1)

  (:objects
    jugador1 - jugador
    zona1 - zona
    zona2 - zona
    zona3 - zona
    zona4 - zona
    zona5 - zona
    zona6 - zona
    zona7 - zona
    norte - orientacion
    sur - orientacion
    este - orientacion
    oeste - orientacion
    oscar1 - oscar
  )

  (:init
    (esta_en jugador1 zona2)
    (mira_hacia jugador1 norte)

    ;; Grafo de caminos (Grafo propuesto en pdf)
    (camino zona1 zona3 sur)
    (camino zona2 zona3 este)
    (camino zona3 zona1 norte)
    (camino zona3 zona2 oeste)
    (camino zona3 zona4 este)
    (camino zona3 zona6 sur)
    (camino zona4 zona3 oeste)
    (camino zona5 zona6 este)
    (camino zona6 zona3 norte)
    (camino zona6 zona5 oeste)
    (camino zona6 zona7 este)
    (camino zona7 zona6 oeste)
  ) 

  (:goal
    (esta_en jugador1 zona7)
  )

)