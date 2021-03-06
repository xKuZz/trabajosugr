(define (problem TerrenosMochilaBelkan)
  
  (:domain DOMINIO_BELKAN_3)
  
  (:objects
    jugador1 - jugador
    ZONE_00_00 - arenoso ZONE_00_01 - pedregoso ZONE_00_02 - pedregoso ZONE_00_03 - arenoso ZONE_00_04 - arenoso
    ZONE_01_00 - pedregoso ZONE_01_01 - arenoso ZONE_01_02 - pedregoso ZONE_01_03 - pedregoso ZONE_01_04 - agua
    ZONE_02_00 - pedregoso ZONE_02_01 - precipicio ZONE_02_02 - agua ZONE_02_03 - agua ZONE_02_04 - agua
    ZONE_03_00 - bosque ZONE_03_01 - bosque ZONE_03_02 - pedregoso ZONE_03_03 - bosque ZONE_03_04 - agua
    ZONE_04_00 - pedregoso ZONE_04_01 - arenoso ZONE_04_02 - bosque ZONE_04_03 - precipicio ZONE_04_04 - bosque
    norte - orientacion
    sur - orientacion
    este - orientacion
    oeste - orientacion
    oscar - objeto
    algoritmo - objeto
    manzana - objeto
    oro - objeto
    rosa - objeto
    bruja - personaje
    princesa - personaje
    principe - personaje
    profesor - personaje
    leonardo - personaje
    bikini - objeto
    zapatillas - objeto
  )

  (:init
    (esta_en jugador1 zone_00_00)
    (mira_hacia jugador1 norte)
    (camino ZONE_00_00 ZONE_01_00 SUR)
    (camino ZONE_00_00 ZONE_00_01 ESTE)
    (camino ZONE_00_01 ZONE_01_01 SUR)
    (camino ZONE_00_01 ZONE_00_00 OESTE)
    (camino ZONE_00_01 ZONE_00_02 ESTE)
    (camino ZONE_00_02 ZONE_01_02 SUR)
    (camino ZONE_00_02 ZONE_00_01 OESTE)
    (camino ZONE_00_02 ZONE_00_03 ESTE)
    (camino ZONE_00_03 ZONE_01_03 SUR)
    (camino ZONE_00_03 ZONE_00_02 OESTE)
    (camino ZONE_00_03 ZONE_00_04 ESTE)
    (camino ZONE_00_04 ZONE_01_04 SUR)
    (camino ZONE_00_04 ZONE_00_03 OESTE)
    (camino ZONE_01_00 ZONE_00_00 NORTE)
    (camino ZONE_01_00 ZONE_02_00 SUR)
    (camino ZONE_01_00 ZONE_01_01 ESTE)
    (camino ZONE_01_01 ZONE_00_01 NORTE)
    (camino ZONE_01_01 ZONE_02_01 SUR)
    (camino ZONE_01_01 ZONE_01_00 OESTE)
    (camino ZONE_01_01 ZONE_01_02 ESTE)
    (camino ZONE_01_02 ZONE_00_02 NORTE)
    (camino ZONE_01_02 ZONE_02_02 SUR)
    (camino ZONE_01_02 ZONE_01_01 OESTE)
    (camino ZONE_01_02 ZONE_01_03 ESTE)
    (camino ZONE_01_03 ZONE_00_03 NORTE)
    (camino ZONE_01_03 ZONE_02_03 SUR)
    (camino ZONE_01_03 ZONE_01_02 OESTE)
    (camino ZONE_01_03 ZONE_01_04 ESTE)
    (camino ZONE_01_04 ZONE_00_04 NORTE)
    (camino ZONE_01_04 ZONE_02_04 SUR)
    (camino ZONE_01_04 ZONE_01_03 OESTE)
    (camino ZONE_02_00 ZONE_01_00 NORTE)
    (camino ZONE_02_00 ZONE_03_00 SUR)
    (camino ZONE_02_00 ZONE_02_01 ESTE)
    (camino ZONE_02_01 ZONE_01_01 NORTE)
    (camino ZONE_02_01 ZONE_03_01 SUR)
    (camino ZONE_02_01 ZONE_02_00 OESTE)
    (camino ZONE_02_01 ZONE_02_02 ESTE)
    (camino ZONE_02_02 ZONE_01_02 NORTE)
    (camino ZONE_02_02 ZONE_03_02 SUR)
    (camino ZONE_02_02 ZONE_02_01 OESTE)
    (camino ZONE_02_02 ZONE_02_03 ESTE)
    (camino ZONE_02_03 ZONE_01_03 NORTE)
    (camino ZONE_02_03 ZONE_03_03 SUR)
    (camino ZONE_02_03 ZONE_02_02 OESTE)
    (camino ZONE_02_03 ZONE_02_04 ESTE)
    (camino ZONE_02_04 ZONE_01_04 NORTE)
    (camino ZONE_02_04 ZONE_03_04 SUR)
    (camino ZONE_02_04 ZONE_02_03 OESTE)
    (camino ZONE_03_00 ZONE_02_00 NORTE)
    (camino ZONE_03_00 ZONE_04_00 SUR)
    (camino ZONE_03_00 ZONE_03_01 ESTE)
    (camino ZONE_03_01 ZONE_02_01 NORTE)
    (camino ZONE_03_01 ZONE_04_01 SUR)
    (camino ZONE_03_01 ZONE_03_00 OESTE)
    (camino ZONE_03_01 ZONE_03_02 ESTE)
    (camino ZONE_03_02 ZONE_02_02 NORTE)
    (camino ZONE_03_02 ZONE_04_02 SUR)
    (camino ZONE_03_02 ZONE_03_01 OESTE)
    (camino ZONE_03_02 ZONE_03_03 ESTE)
    (camino ZONE_03_03 ZONE_02_03 NORTE)
    (camino ZONE_03_03 ZONE_04_03 SUR)
    (camino ZONE_03_03 ZONE_03_02 OESTE)
    (camino ZONE_03_03 ZONE_03_04 ESTE)
    (camino ZONE_03_04 ZONE_02_04 NORTE)
    (camino ZONE_03_04 ZONE_04_04 SUR)
    (camino ZONE_03_04 ZONE_03_03 OESTE)
    (camino ZONE_04_00 ZONE_03_00 NORTE)
    (camino ZONE_04_00 ZONE_04_01 ESTE)
    (camino ZONE_04_01 ZONE_03_01 NORTE)
    (camino ZONE_04_01 ZONE_04_00 OESTE)
    (camino ZONE_04_01 ZONE_04_02 ESTE)
    (camino ZONE_04_02 ZONE_03_02 NORTE)
    (camino ZONE_04_02 ZONE_04_01 OESTE)
    (camino ZONE_04_02 ZONE_04_03 ESTE)
    (camino ZONE_04_03 ZONE_03_03 NORTE)
    (camino ZONE_04_03 ZONE_04_02 OESTE)
    (camino ZONE_04_03 ZONE_04_04 ESTE)
    (camino ZONE_04_04 ZONE_03_04 NORTE)
    (camino ZONE_04_04 ZONE_04_03 OESTE)
    (= (costemovimiento) 10)
    (= (distanciatotal) 0)

    (esta_en algoritmo ZONE_02_02)
    (esta_en manzana zone_01_04)
    (esta_en oscar zone_03_00)
    (esta_en oro zone_01_03)
    (esta_en rosa zone_03_03)

    (esta_en bruja zone_04_04)
    (esta_en princesa zone_00_01) 
    (esta_en leonardo zone_00_04)
    (esta_en principe zone_04_00)
    (esta_en profesor zone_01_02)
    (esta_en bikini zone_00_02)
    (esta_en zapatillas zone_01_04)
  ) 
  

  (:goal
    (exists (?o1 ?o2 ?o3 ?o4 ?o5 - objeto) 
        (and
            (posee bruja ?o1)
            (posee princesa ?o2)
            (posee principe ?o3)
            (posee leonardo ?o4)
            (posee profesor ?o5)
        )
    )
  )

  (:metric 
    minimize (distanciatotal)
  )
)