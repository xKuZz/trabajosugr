## Autor: David Criado Ramón
## DNI: 26254133-R
## email: davidcr96@correo.ugr.es
## Grupo AA2 (Jueves 17:30-19:30)
## PRÁCTICA 1

## ----setup, include=FALSE------------------------------------------------
knitr::opts_chunk$set(echo = TRUE)
set.seed(45)
setwd("./datos")


## ------------------------------------------------------------------------
# Función proporcionada en paraTrabajo1.R
simula_unif = function (N = 2,
                        dims = 2,
                        rango = c(0, 1)) {
  m = matrix(
    runif(N * dims, min = rango[1], max = rango[2]),
    nrow = N,
    ncol = dims,
    byrow = T
  )
  m
}

# SECCIÓN 1 - Ejercicio 1a
## 1) Dibujar una gráfica con la nube de puntos de la salida correspondiente
### a) Considere N = 50, dim = 2, rango = [-50,+50] con simula_unif(N, dims, rango)
ejercicio1_1a = function(N = 50,
                         dims = 2,
                         rango = c(-50, 50)) {
  # Cogemos los puntos de una distribución uniforme.
  puntos = simula_unif(N, dims, rango)
  # Creamos una gráfica vacía con el título del ejercicio.
  plot(
    rango,
    rango,
    xlab = "x",
    ylab = "y",
    type = "n",
    main = "Ejercicio 1-1a"
  )
  # Ponemos los puntos con colores aleatorios.
  points(
    x = puntos,
    col = colors(),
    lwd = 2,
    pch = 19
  )
}
ejercicio1_1a()
invisible(readline(prompt = "Pulsar [enter] para continuar"))

## ------------------------------------------------------------------------
simula_gaus = function(N = 2, dim = 2, sigma) {
  if (missing(sigma))
    stop("Debe dar un vector de varianzas")
  sigma = sqrt(sigma)  # para la generación se usa sd, y no la varianza
  if (dim != length(sigma))
    stop ("El numero de varianzas es distinto de la dimensiÃ³n")
  # genera 1 muestra, con las desviaciones especificadas
  simula_gauss1 = function()
    rnorm(dim, sd = sigma)
  # repite N veces, simula_gauss1 y se hace la traspuesta
  m = t(replicate(N, simula_gauss1()))
  m
}
# SECCIÓN 1 - Ejercicio 1b
### b) Considere N = 50, dim = 2 y sigma = [5,7] con simula_gauss(N, dim, sigma)
ejercicio1_1b = function(N = 50,
                         dims = 2,
                         sigma = c(5, 7)) {
  # Cogemos los puntos aleatorios de la distribución gaussiana.
  puntos = simula_gaus(N, dims, sigma)
  # Creamos el gráfico vacío teniendo en cuenta el rango de los puntos.
  plot(
    range(puntos[, 1]),
    range(puntos[, 2]),
    xlab = "x",
    ylab = "y",
    type = "n",
    main = "Ejercicio 1-1b"
  )
  # Pintamos los puntos con colores aleatorios.
  points(
    x = puntos,
    col = colors(),
    lwd = 2,
    pch = 19
  )
}
ejercicio1_1b()
invisible(readline(prompt = "Pulsar [enter] para continuar"))

## ------------------------------------------------------------------------
# Proporcionada en paraTrabajo1.R
simula_recta = function (intervalo = c(-1, 1),
                         visible = F) {
  ptos = simula_unif(2, 2, intervalo) # se generan 2 puntos
  a = (ptos[1, 2] - ptos[2, 2]) / (ptos[1, 1] - ptos[2, 1]) # calculo de la pendiente
  b = ptos[1, 2] - a * ptos[1, 1]  # calculo del punto de corte
  
  if (visible) {
    # pinta la recta y los 2 puntos
    if (dev.cur() == 1)
      # no esta abierto el dispositivo lo abre con plot
      plot(1,
           type = "n",
           xlim = intervalo,
           ylim = intervalo)
    points(ptos, col = 3)  #pinta en verde los puntos
    abline(b, a, col = 3)   # y la recta
  }
  c(a, b) # devuelve el par pendiente y punto de corte
}

# Sección 1 - Apartado 2a
# ---------------------------------------------------
# Función de clasificación: Signo de y - ax * b
etiquetar = function(punto, recta) {
  sign(punto[2] - recta[1] * punto[1] - recta[2])
}

## 2) Con ayuda de la función simula_unif() generar una muestra de puntos 2D a los que vamos añadir una etiqueta usando el signo de la función f(x,y) = y - ax - b, es decir el signo de la distancia de cada punto a la recta simulada con simula_recta().

###  a) Dibujar una gráfica donde los puntos muestren el resultado de su etiqueta junto con la recta usada para ello. (Observar que todos los puntos están bien clasificados respecto de la recta)
ejercicio1_2a = function(N = 50,
                         dims = 2,
                         rango = c(-50, 50)) {
  # Generamos los puntos aleatorios siguiendo una distribución uniforme
  puntos = simula_unif(N, dims, rango)
  # Generamos una gráfica vacía
  plot(
    range(puntos[, 1]),
    range(puntos[, 2]),
    type = "n",
    xlab = "",
    ylab = "",
    main = "Ejercicio 1-2a"
  )
  # Generamos una recta aleatoria
  recta = simula_recta(intervalo = c(0, 1))
  
  # Pintamos la recta en la gráfica
  abline(recta[2], recta[1])
  
  # Clasificamos los puntos basándonos en si se encuentran a un lado u otro de la recta
  etiquetas = apply(
    X = puntos,
    MARGIN = 1,
    FUN = etiquetar,
    recta = recta
  )
  # Pintamos los puntos en la gráfica
  points(
    x = puntos,
    col = 32 + 19 * etiquetas,
    lwd = 2,
    pch = 19
  )
  # Devolvemos los puntos, la recta y el etiquetado para otros ejercicios
  list(puntos = puntos,
       recta = recta,
       etiquetas = etiquetas)
}
ejer1_2a = ejercicio1_2a()
invisible(readline(prompt = "Pulsar [enter] para continuar"))

## ------------------------------------------------------------------------
mete_ruido = function(etiquetas, porcentaje) {
  # Apuntamos los índice cuales son positivos y cuales son negativos
  positivos = which(etiquetas == 1)
  negativos = which(etiquetas == -1)
  # Cogemos una muestra del porcentaje de cada uno
  muestra_positivos = sample(positivos, length(positivos) * porcentaje)
  muestra_negativos = sample(negativos, length(negativos) * porcentaje)
  # Alteramos la etiqueta
  etiquetas[muestra_positivos] = -1
  etiquetas[muestra_negativos] =  1
  etiquetas
}
# SECCIÓN 1 - Ejercicio 2b
### b) Modifique de forma aleatoria un 10 % etiquetas positivas y otra 10 % de negativas. Dibuje de nuevo la gráfica anterior. (Ahora hay puntos mal clasificados respecto de la recta)
ejercicio1_2b = function(puntos = ejer1_2a[[1]],
                         recta = ejer1_2a[[2]],
                         etiquetas = ejer1_2a[[3]]) {
  # Metemos el ruido del 10 % en cada clase
  etiquetas = mete_ruido(etiquetas, 0.1)
  # Dibujamos la nueva gráfica
  plot(
    range(puntos[, 1]),
    range(puntos[, 2]),
    type = "n",
    xlab = "",
    ylab = "",
    main = "Ejercicio 1-2b"
  )
  abline(recta[2], recta[1])
  points(
    x = puntos,
    col = 32 + 19 * etiquetas,
    lwd = 2,
    pch = 19
  )
  # Devolvemos el nuevo etiquetado
  etiquetas
}
ejer1_2b = ejercicio1_2b()
invisible(readline(prompt = "Pulsar [enter] para continuar"))

## ------------------------------------------------------------------------
# Proporcionada en paraTrabajo1.R
pintar_frontera = function(f, rango = c(-50, 50)) {
  x = y = seq(rango[1], rango[2], length.out = 100)
  z = outer(x, y, FUN = f)
  if (dev.cur() == 1)
    # no esta abierto el dispositivo lo abre con plot
    plot(1,
         type = "n",
         xlim = rango,
         ylim = rango)
  contour(
    x,
    y,
    z,
    levels = 0,
    drawlabels = FALSE,
    xlim = rango,
    ylim = rango,
    xlab = "x",
    ylab = "y"
  )
}
# FUNCIONES PARA PINTAR EN EJERCICIO 1-3
f3a = function(x, y) {
  (x - 10) * (x - 10) + (y - 20) * (y - 20) - 400
}

f3b = function(x, y) {
  0.5 * (x + 10) * (x + 10) + (y - 20) * (y - 20) - 400
}

f3c = function(x, y) {
  0.5 * (x - 10) * (x - 10) - (y - 20) * (y - 20) - 400
}

f3d = function(x, y) {
  y - 20 * x * x - 5 * x + 3
}

# Ejercicio 1-3 Visualizar el etiquetado generado en 2b junto con cada una de las gráficas de cada una de las funciones. Comparar las formas de las regiones positivas y negativas de estas nuevas funciones con las obtenidas en el caso de la recta ¿Hemos ganado algo en mejora de clasificación al utilizar una funciones más complejas que la dada por una función lineal? Explicar el razonamiento.
ejercicio1_3 = function(puntos = ejer1_2a[[1]]) {
  pintar_frontera(f3a)
  etiquetas = sign(mapply(f3a, puntos[, 1], puntos[, 2]))
  points(
    x = puntos,
    col = 32 + 19 * etiquetas,
    lwd = 2,
    pch = 19
  )
  invisible(readline(prompt = "Pulsar [enter] para continuar"))
  pintar_frontera(f3b)
  etiquetas = sign(mapply(f3b, puntos[, 1], puntos[, 2]))
  points(
    x = puntos,
    col = 32 + 19 * etiquetas,
    lwd = 2,
    pch = 19
  )
  invisible(readline(prompt = "Pulsar [enter] para continuar"))
  pintar_frontera(f3c)
  etiquetas = sign(mapply(f3c, puntos[, 1], puntos[, 2]))
  points(
    x = puntos,
    col = 32 + 19 * etiquetas,
    lwd = 2,
    pch = 19
  )
  invisible(readline(prompt = "Pulsar [enter] para continuar"))
  pintar_frontera(f3d)
  etiquetas = sign(mapply(f3d, puntos[, 1], puntos[, 2]))
  points(
    x = puntos,
    col = 32 + 19 * etiquetas,
    lwd = 2,
    pch = 19
  )
  invisible(readline(prompt = "Pulsar [enter] para continuar"))
}

ejercicio1_3()
## EJERCICIO 2-1: ## 1) Implementar la función ajusta_PLA(datos, label, max_iter, vini) que calcula el hiperplano solución a un algoritmo de clasificación binaria usando el algoritmo PLA. La entrada datos es una matriz donde cada item con su etiqueta está representado por una fila de la matriz, *label* el vector de etiquetas (cada etiqueta es valor +1 o -1), max_iter es el número máximo de iteraciones permitidas y vini el valor inicial del vector. La función devuelve los coeficientes del hiperplano
## ------------------------------------------------------------------------
ajusta_PLA = function(datos, label, max_iter, vini) {
  datos = cbind(1, datos) # Añadimos la columna de 1
  i = 0 # contador para el número de iteraciones
  cambio = T # indica si se ha producido algún cambio o se debe parar
  w = vini # vector de pesos
  while (i < max_iter & cambio) {
    cambio = F # puesto que hemos empezado la iteración no se ha podido producir
    # ningún cambio
    # recorremos todos los datos
    for (x in sample(1:nrow(datos))) {
      # Aplicamos signo
      signo = sign(sum(datos[x, ] * w))
      if (label[x] != signo) {
        # Si no coinciden el signo y la etiqueta cambiamos el valor del vector de pesos
        # wnew = wold + yi * xi
        w = w + datos[x, ] * label[x]
        # indicamos que se ha producido un cambio
        cambio = T
      }
    }
    i = i + 1 # aumentamos el contador de iteraciones
  }
  # parámetros del hiperplano (recta en este caso) y número de iteraciones usadas
  list(w = w,
       iteraciones = i,
       vini = vini)
}

# Calcula una recta basada en el vector de pesos w y pondemos pintarla en un plot
# previamente creado
calcula_recta = function(w, pintar = F) {
  a = -w[2] / w[3]
  b = -w[1] / w[3]
  abline(b, a, col = "red")
  list(a = a, b = b)
}
## Ejercicio 2-2: Ejecutar el algoritmo PLA con los datos simulados en el apartado 2a de la sección 1. Inicializar el algoritmo con: a) el vector 0, y b) con vectores de números aleatorios en [0,1] (10 veces). Anotar el número medio de iteraciones en ambos para converger. Valorar el resultado relacionando el punto de inicio con el número de iteraciones
## ------------------------------------------------------------------------
ejercicio2_2 = function(puntos = ejer1_2a$puntos,
                        etiquetas = ejer1_2a$etiquetas) {
  # Caso A: Inicializando el vector de pesos a 0
  ajuste = t(replicate(10, as.numeric(unlist(
    ajusta_PLA(
      datos = puntos,
      label = etiquetas,
      vini = c(0, 0, 0),
      max_iter = 1000
    )
  ))))
  
  # # Caso B: Inicio de vectores de pesos aleatorios
  ajusteAleatorio = t(replicate(10, as.numeric(unlist(
    ajusta_PLA(
      datos = puntos,
      label = etiquetas,
      vini = runif(3),
      max_iter = 1000
    )
  ))))
  
  # Asignamos nombres a las columnas para que quede claro al hacer print
  # wf hace referencia a vector de pesos final
  # wi hacer referencia a vector de pesos inicial
  colnames(ajuste) = c("wf1", "wf2", "wf3", "iters", "wi1", "wi2", "wi3")
  colnames(ajusteAleatorio) = c("wf1", "wf2", "wf3", "iters", "wi1", "wi2", "wi3")
  
  # Pintamos una gráfica y mostramos la tabla para caso [0,0,0]
  plot(
    x = puntos,
    col = 32 + 19 * etiquetas,
    lwd = 2,
    pch = 19,
    type = "p",
    xlab = "",
    ylab = "",
    main = "PLA inicializado a 0."
  )
  apply(
    X = ajuste,
    MARGIN = 1,
    FUN = calcula_recta,
    pintar = T
  )
  print(ajuste)
  cat("De media en el caso inicializado a 0 hemos usado ",
      mean(ajuste[, 4]),
      " iteraciones.\n")
  invisible(readline(prompt = "Pulsar [enter] para continuar"))
  # Pintamos una gráfica y mostramos la tabla para caso aleatorio
  plot(
    x = puntos,
    col = 32 + 19 * etiquetas,
    lwd = 2,
    pch = 19,
    type = "p",
    xlab = "",
    ylab = "",
    main = "PLA inicializado aleatoriamente."
  )
  apply(
    X = ajuste,
    MARGIN = 1,
    FUN = calcula_recta,
    pintar = T
  )
  print(ajusteAleatorio)
  cat(
    "De media en el caso aleatorio se han utilizado",
    mean(ajusteAleatorio[, 4]),
    "iteraciones.\n"
  )
  invisible(readline(prompt = "Pulsar [enter] para continuar"))
}
ejercicio2_2()

## EJERCICIO 2-3: Hacer los mismo que antes usando ahora los datos del apartado 2b de la sección 1. ¿Observa algún comportamiento diferente? En caso afirmativo diga cual y las razones para que ello ocurra.
## ------------------------------------------------------------------------
ejercicio2_2(puntos = ejer1_2a$puntos, etiquetas = ejer1_2b)

## EJERCICIO 3-1: Lectura de datos
## ------------------------------------------------------------------------
# Función que lee el archivo, seleccionando instancias de 1 y 5
lectura = function(file) {
  # Leemos el archivo
  digit <-
    read.table(
      file,
      quote = "\"",
      comment.char = "",
      stringsAsFactors = FALSE
    )
  # Seleccionamos instancias de 1 y 5
  digit15 = digit[digit$V1 == 1 | digit$V1 == 5, ]
  # Cogemos sus etiquetas
  etiquetas = digit15[, 1]
  # Pasamos las etiquetas 5 a -1
  etiquetas[etiquetas == 5] = -1
  # Sacamos el tamaño del conjunto seleccionado
  n = nrow(digit15)
  # Sacamos la matriz de grises
  grises = array(unlist(subset(digit15, select = -V1)), c(n, 16, 16))
  
  # Devolvemos grises y el etiquetado original
  list (grises = grises, etiquetas = etiquetas)
}
zip_training = lectura("zip.train")
zip_test = lectura("zip.test")

par(mfrow = c(2, 2))
for (i in 1:4) {
  imagen = zip_training$grises[i, , 16:1] # se rota para verlo bien
  image(z = imagen)
}
par(mfrow = c(1, 1))
invisible(readline(prompt = "Pulsar [enter] para continuar"))

## Ejercicio 3-2: Cálculo características media, simetría en training
## ------------------------------------------------------------------------
fsimetria <- function(A) {
  A = abs(A - A[, ncol(A):1])
  mean(A)
}

calcula_media_simetria = function(zip = zip_training, pintar = T) {
  # Calculamos la media
  media = apply(X = zip$grises,
                MARGIN = 1,
                FUN = mean)
  # Calculamos la simetría
  simetria = apply(X = zip$grises,
                   MARGIN = 1,
                   FUN = fsimetria)
  # Pintamos la gráfica con los puntos
  if (pintar) {
    plot(
      x = media,
      y = simetria,
      type = "p",
      xlab = "Media",
      ylab = "Simetría",
      main = "Instancias Training",
      lwd = 2,
      pch = 19,
      col = 32 + 19 * zip$etiquetas
    )
  }
  
  # Devolvemos la media y la simetría para el siguiente apartado
  list(media = media, simetria = simetria)
}
caracteristicas_training = calcula_media_simetria()
invisible(readline(prompt = "Pulsar [enter] para continuar"))

## ------------------------------------------------------------------------
#### Ejercicio 3-3 Regresión lineal y ein
Regress_Lin = function(datos, label) {
  # Añadimos la columna 1
  x = cbind(1, datos)
  # Aplicamos svd
  svd = svd(x)
  # Sacamos la matriz ortogonal V
  V = svd$v
  # Sacamos la matriz diagonal d
  d = svd$d
  # Calculamos la pseudoinversa como la matriz diagonal de d que
  # si un dato es mayor que el epsilon de la máquina (escogido por mí como 0.0001)
  # invierte el valor
  D = diag(ifelse(d > 0.0001, 1 / d, d))
  
  # Calculamos el vector de pesos (Importante D²)
  w = V %*% D ^ 2 %*% t(V) %*% t(x) %*% label
}

etiquetar_regresion = function(x, w) {
  x = c(1, x) # Añadimos 1 al principio del vector de características
  # La etiqueta viene dada por el signo de la sumatoria de xi * wi
  sign(sum(x * w))
}
apartado3 = function(training = caracteristicas_training) {
  # Preparamos el vector de características de training
  datos_training = cbind(training$media, training$simetria)
  # Aplicamos regresión
  w_training = Regress_Lin(datos_training, zip_training$etiquetas)
  # Usamos la regresión para etiquetar
  etiq_regr_training = apply(datos_training, 1, etiquetar_regresion, w_training)
  
  # Pintamos etiquetado original a izquierda y regresión a derecha (TRAINING)
  par(mfrow = c(1, 2))
  plot(
    datos_training,
    xlab = "Media",
    ylab = "Simetría",
    lwd = 2,
    pch = 19,
    main = "Etiquetas reales training",
    col = 32 + 19 * zip_training$etiquetas
  )
  cat("\n")
  plot(
    datos_training,
    xlab = "Media",
    ylab = "Simetría",
    lwd = 2,
    pch = 19,
    main = "Etiquetas regresión training",
    col = 32 + 19 * etiq_regr_training
  )
  calcula_recta(w_training, pintar = T)
  
  # Calculamos y mostramos ein
  ein = sum(etiq_regr_training != zip_training$etiquetas)
  cat(
    "El error dentro de la muestra de entrenamiento (Ein) es del ",
    ein / nrow(datos_training) * 100,
    "%\n"
  )
  
  # Calculamos las características de TEST
  caracteristicas_test = calcula_media_simetria(zip = zip_test, pintar = F)
  # Las juntamos en una matriz
  datos_test = cbind(caracteristicas_test$media, caracteristicas_test$simetria)
  # Calculamos el etiquetado con respecto al ajuste de training
  etiq_regr_test = apply(datos_test, 1, etiquetar_regresion, w_training)
  
  # Pintamos etiquetado original a izquierda y regresión a derecha (TEST)
  plot(
    datos_test ,
    xlab = "Media",
    ylab = "Simetría",
    lwd = 2,
    pch = 19,
    col = 32 + 19 * zip_test$etiquetas,
    main = "Etiquetas reales test"
  )
  cat("\n")
  plot(
    datos_test ,
    xlab = "Media",
    ylab = "Simetría",
    lwd = 2,
    pch = 19,
    col = 32 + 19 * etiq_regr_test,
    main = "Etiquetas regresión test"
  )
  calcula_recta(w_training, pintar = T)
  eout = sum(etiq_regr_test != zip_test$etiquetas)
  
  cat(
    "El error dentro de la muestra de entranmiento (en test) (Eout) es del ",
    eout / nrow(datos_test) * 100,
    "%\n"
  )
  par(mfrow = c(1, 1))
}

apartado3()
invisible(readline(prompt = "Pulsar [enter] para continuar"))

## ------------------------------------------------------------------------
## EXPERIMENTO 1
etiquetado_exp1 = function (x1, x2) {
  sign((x1 + 0.2) ^ 2 + x2 ^ 2 - 0.6)
}

## EXPERIMENTO 1-A: Punotos aleatorios en el cuadrado
exp1a = function (size, plot = T) {
  puntos = simula_unif(N = 1000, dims = 2, c(-size, size))
  if (plot) {
    # Ponemos los puntos con colores aleatorios.
    plot(
      puntos,
      xlab = "x",
      ylab = "y",
      lwd = 2,
      pch = 19,
      main = "Experimento 1",
      col = colors()
    )
  }
  puntos
}

puntos_exp1a = exp1a(1)
invisible(readline(prompt = "Pulsar [enter] para continuar"))

## ------------------------------------------------------------------------
## EXPERIMENTO 1-B: Añadir ruido al etiquetado
exp1b = function(puntos = puntos_exp1a, plot = T) {
  etiquetas = mapply(etiquetado_exp1, puntos[, 1], puntos[, 2])
  # Metemos ruido del 10 %
  etiquetas = mete_ruido(etiquetas, 0.1)
  if (plot) {
    plot(
      puntos,
      xlab = "x",
      ylab = "y",
      lwd = 2,
      pch = 19,
      main = "Experimento 1-b (RUIDO)",
      col = 32 + 19 * etiquetas
    )
  }
  # Devolvemos las nuevas etiquetas
  etiquetas
}

etiquetas_exp1b = exp1b()
invisible(readline(prompt = "Pulsar [enter] para continuar"))

## ------------------------------------------------------------------------
## EXPERIMENTO 1-C: Ajuste por regresión y Ein
exp1c = function(puntos = puntos_exp1a,
                 etiquetas_orig = etiquetas_exp1b,
                 plot = T) {
  entradaAjuste = puntos
  ajuste = Regress_Lin(entradaAjuste, etiquetas_orig)
  par(mfrow = c(1, 2))
  etiquetas_regr = apply(puntos, 1, etiquetar_regresion, w = ajuste)
  ein = sum(etiquetas_regr != etiquetas_orig)
  if (plot) {
    plot(
      puntos,
      xlab = "",
      ylab = "",
      lwd = 2,
      pch = 19,
      main = "Etiquetado original",
      col = 32 + 19 * etiquetas_orig
    )
    calcula_recta(ajuste, pintar = T)
    plot(
      puntos,
      xlab = "",
      ylab = "",
      lwd = 2,
      pch = 19,
      main = "Regresión EXP 1-C",
      col = 32 + 19 * etiquetas_regr
    )
    calcula_recta(ajuste, pintar = T)
    cat("El error Ein es del ", ein / nrow(puntos) * 100, "%\n")
  }
  par(mfrow = c(1, 1))
  
  list(Ein = ein, w = ajuste)
}
exp1cdata = exp1c()
invisible(readline(prompt = "Pulsar [enter] para continuar"))

## ------------------------------------------------------------------------
## FUNCIÓN PARA REPETIR LOS PASOS DEL EXPERIMENTO 1
experimento1 = function(X = 1) {
  # X es el valor del cuadrado donde obtener puntos
  # Training (Uso los apartados anteriores)
  # a) Genero muestra
  puntos = exp1a(1, plot = F)
  # b) Calculo etiquetas CON RUIDO
  etiquetado_original = exp1b(puntos, plot = F)
  # c) Ajusto y calculo Ein
  ein_ajuste = exp1c(puntos, etiquetado_original, plot = F)
  # Test
  # a) Genero muestras de test
  puntos_test = simula_unif(N = 1000, dims = 2, c(-X, X))
  # b) Genero etiquetas de f SIN RUIDO
  etiquetas_test_orig = mapply(etiquetado_exp1, puntos_test[, 1], puntos_test[, 2])
  # c) Calculo las etiquetas con la g obtenida en TRAINING
  etiquetas_test_regr = apply(puntos_test, 1, etiquetar_regresion, ein_ajuste$w)
  # d) Calculo Eout
  Eout = sum(etiquetas_test_orig != etiquetas_test_regr)
  
  # Devuelvo Ein y Eout
  c(ein_ajuste$Ein, Eout)
}

## EXPERIMENTO 1-D REPETIMOS 1000 VECES EL EXPERIMENTO
exp1d = function(iters = 1000) {
  # Repetimos el experimento 1000 veces
  resultados = replicate(n = iters, experimento1())
  # Mostramos las medias por pantalla
  cat("Media de Ein:  ",
      mean(resultados[1, ]) / ncol(resultados) * 100,
      " %.\n")
  cat("Media de Eout: ",
      mean(resultados[2, ]) / ncol(resultados) * 100,
      " %.\n")
}

exp1ddata = exp1d()
invisible(readline(prompt = "Pulsar [enter] para continuar"))

## EXPERIMENTO 2-A: VECTOR CARACTERÍSTICAS AMPLIADO, AJUSTE Y EIN
## ------------------------------------------------------------------------
exp2a = function(puntos = puntos_exp1a,
                 etiquetas_orig = etiquetas_exp1b,
                 plot = T) {
  entradaAjuste = cbind(puntos[, 1], puntos[, 2], puntos[, 1] * puntos[, 2],
                        puntos[, 1] ^ 2, puntos[, 2] ^ 2)
  ajuste = Regress_Lin(entradaAjuste, etiquetas_orig)
  etiquetas_regr = apply(entradaAjuste, 1, etiquetar_regresion, ajuste)
  ein = sum(etiquetas_regr != etiquetas_orig)
  if (plot) {
    par(mfrow = c(1, 2))
    plot(
      puntos,
      xlab = "",
      ylab = "",
      pch = 19,
      lwd = 2,
      main = "Original con ruido",
      col = 32 + 19 * etiquetas_orig
    )
    cat("\n")
    plot(
      puntos,
      xlab = "",
      ylab = "",
      pch = 19,
      lwd = 2,
      main = "Experimento 2-a (Regresión)",
      col = 32 + 19 * etiquetas_regr
    )
    cat("\n")
    par(mfrow = c(1, 1))
    cat("El error Ein es del ", ein / nrow(puntos) * 100, "%\n")
  }
  list(Ein = ein, ajuste = ajuste)
}
ein_ajuste2 = exp2a()
invisible(readline(prompt = "Pulsar [enter] para continuar"))

## ------------------------------------------------------------------------
# FUNCIÓN PARA REPETIR EL EXPERIMENTO
experimento2 = function(X = 1) { 
  # Cogemos los puntos
  puntos = exp1a(X, F)
  # Adaptamos los puntos al vector de características
  caracteristicas = cbind(puntos[, 1], puntos[, 2], puntos[, 1] * puntos[, 2],
                          puntos[, 1] ^ 2, puntos[, 2] ^ 2)
  # Calculo el etiquetado original
  etiquetado_orig = exp1b(puntos, F)
  # Ajustamos con el vector de características
  ein_ajuste = exp2a(caracteristicas, etiquetado_orig, F)
  w = ein_ajuste$ajuste
  # Saco una muestra de test
  puntos_test = simula_unif(N = 1000, dims = 2, c(-1, 1))
  # Obtengo las etiquetas originales de test
  etiquetas_orig = mapply(etiquetado_exp1, puntos_test[, 1], puntos_test[, 2])
  # Obtengo las etiquetas de regresión de test
  caracteristicas_test = cbind(
    puntos_test[, 1],
    puntos_test[, 2],
    puntos_test[, 1] * puntos_test[, 2],
    puntos_test[, 1] ^ 2,
    puntos_test[, 2] ^ 2
  )
  etiquetas_regr = apply(caracteristicas_test, 1, etiquetar_regresion, w)
  Eout = sum(etiquetas_orig != etiquetas_regr)
  c(ein_ajuste$Ein, Eout)
}
# REPETIMOS EL EXPERIMENTO 1000 VECES
exp2b = function(iters = 1000) {
  resultados = replicate(iters, experimento2())
  cat("La media de Ein es de ", mean(resultados[1, ]) / iters * 100, "%\n")
  cat("La media de Eout es de ", mean(resultados[2, ]) / iters * 100, "%\n")
}

exp2b()
invisible(readline(prompt = "Pulsar [enter] para continuar"))

## ------------------------------------------------------------------------
# BONUS 1a
regresion_recta_ein = function(X = 10, N = 100) {
  # Calculamos una muestra aleatoria de tamaño N
  muestras = simula_unif(N = N,
                         dims = 2,
                         rango = c(-X, X))
  # Calculamos una recta f aleatoria que corta el cuadrado
  f = simula_recta(intervalo = c(-X, X))
  # Calculamos las etiquetas con respecto a la recta
  etiquetas = apply(
    X = muestras,
    MARGIN = 1,
    FUN = etiquetar,
    recta = f
  )
  # Calculamos la función de regresión g (pesos)
  g = Regress_Lin(datos = muestras, label = etiquetas)
  # Calculamos las etiquetas con respecto a la regresión
  etiquetasRegresion = apply(muestras, 1, etiquetar_regresion, g)
  
  # Devolvemos ein
  sum(etiquetas != etiquetasRegresion)
}
bonus1a = function(iters = 1000) {
  Ein = replicate(iters, regresion_recta_ein())
  cat("La media de Ein es ", mean(Ein), "\n")
}
bonus1a()
invisible(readline(prompt = "Pulsar [enter] para continuar"))

## ------------------------------------------------------------------------
# BONUS 1b
regresion_recta_eout = function(X = 10, N = 100) {
  # TRAINING
  # Calculamos una muestra aleatoria de tamaño N
  muestras = simula_unif(N = N,
                         dims = 2,
                         rango = c(-X, X))
  # Calculamos una recta f aleatoria que corta el cuadrado
  f = simula_recta(intervalo = c(-X, X))
  # Calculamos las etiquetas con respecto a la recta
  etiquetas = apply(
    X = muestras,
    MARGIN = 1,
    FUN = etiquetar,
    recta = f
  )
  # Calculamos la función de regresión g (pesos)
  g = Regress_Lin(datos = muestras, label = etiquetas)
  
  # TEST
  # Cogemos una nueva muestra aleatoria uniforme de tamaño N
  muestras = simula_unif(N = N,
                         dims = 2,
                         rango = c(-X, X))
  # Miramos las etiquetas de test con respecto de la recta
  etiquetas = apply(
    X = muestras,
    MARGIN = 1,
    FUN = etiquetar,
    recta = f
  )
  # Calculamos las etiquetas de test con respecto a la regresión
  etiquetasRegresion = apply(muestras, 1, etiquetar_regresion, g)
  
  # Devolvemos eout
  sum(etiquetas != etiquetasRegresion)
}
bonus1b = function(iters = 1000) {
  Eout = replicate(iters, regresion_recta_eout())
  
  cat("La media de Eout es ", mean(Eout), "\n")
}
bonus1b()
invisible(readline(prompt = "Pulsar [enter] para continuar"))

## ------------------------------------------------------------------------
# BONUS 1c
regresion_pla = function(N = 10, X = 10) {
  muestras = simula_unif(N = N,
                         dims = 2,
                         rango = c(-X, X))
  # Calculamos una muestra aleatoria de tamaño N
  muestras = simula_unif(N = N,
                         dims = 2,
                         rango = c(-X, X))
  # Calculamos una recta f aleatoria que corta el cuadrado
  f = simula_recta(intervalo = c(-X, X))
  # Calculamos las etiquetas con respecto a la recta
  etiquetas = apply(
    X = muestras,
    MARGIN = 1,
    FUN = etiquetar,
    recta = f
  )
  # Calculamos la función de regresión g (pesos)
  g = Regress_Lin(datos = muestras, label = etiquetas)
  # Aplicamos PLA
  pla = ajusta_PLA(muestras, etiquetas, 1000, g)
  pla$iteraciones
}


bonus1c = function(iters = 1000) {
  resultados = replicate(1000, regresion_pla())
  print(resultados)
  cat(
    "La media de iteraciones utilizadas por el PLA inicializado ",
    "con regresión es ",
    mean(resultados),
    "\n"
  )
}

bonus1c()

