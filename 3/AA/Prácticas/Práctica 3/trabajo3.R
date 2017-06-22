## ----puntoParada, include=FALSE, echo = FALSE, eval=FALSE----------------
## invisible(readline(prompt = "Pulse Enter para continuar\n"))

## ----setup, include=FALSE------------------------------------------------
#Autores:
# - Carlos Morales Aguilera
# - David Criado Ramón
knitr::opts_chunk$set(echo = TRUE)

# Librerías a incluir
library(caret)
library(leaps)
library(glmnet)
library(knitr)

## ------------------------------------------------------------------------
# Establecemos la semilla aleatoria
set.seed(11)

# Cambiamos de directorio
setwd("./datos")

# Lectura del fichero
spam = read.table("spam.data",
                  quote="\"", comment.char="", stringsAsFactors=FALSE)

# Salimos del directorio de los datos
setwd("..")

# Eliminación de valores perdidos
spam = na.omit(spam)

## ------------------------------------------------------------------------
# Función que particiona los datos dados unos porcentajes
# y devuelve subconjuntos de índices
particionar = function(porcentajeTraining=2/3, porcentajeValidacion=0, data) {
    # Obtenemos un subconjunto de índices aleatorios que correspondera al training
    training = sample(1:nrow(data), porcentajeTraining*nrow(data))
    
    # Cogemos aquellos índices que no hayan sido utilizados para el subconjunto
    # de test
    test = (1:nrow(data))[-training]
    
    # Cogemos de training un porcentaje para el conjunto de validación
    validacion = sample(training,porcentajeValidacion*length(training))
    if (length(validacion) != 0) training = training[-validacion] 
    
    # Devolvemos una lista con los tres subconjuntos
    list(training = training, test = test, validacion = validacion)
}

# Realizamos la partición de datos
i = particionar(data = spam)

## ------------------------------------------------------------------------
# 1. ELIMINAMOS LAS VARIABLES CON UN ALTO GRADO DE CORRELACIÓN.
# Obtenemos la matriz de correlaciones de los datos de training
descrCor = cor(spam[i$training,])
# Cogemos aquellos atributos cuyo grado de correlación es mayor al 75%
highCor = findCorrelation(descrCor, cutoff = .75)
# Quitamos dichos atributos
if (length(highCor) != 0) spam = spam[,-highCor]

# 2. UTILIZAMOS EL FILTRO PCA PARA REDUCIR LA DIMENSIONALIDAD
# Con los datos escalados y centrados, aplicamos el algoritmo PCA
pcaObject = prcomp(spam,center = TRUE, scale. = TRUE)
# Calculamos el porcentaje de la varianza y lo mostramos en una gráfica
porcentVariance = pcaObject$sd^2/sum(pcaObject$sd^2)*100
plot(porcentVariance, type="p", pch = 19, col = 19)

# 3. REALIZAMOS EL PREPROCESAMIENTO CON LAS TRANSFORMACIONES
# PREVIAMENTE MENCIONADAS Y EL BOXCOX
# Calculamos la transformación del preprocesamiento basándonos en training
preProc = preProcess(x = spam[i$training,1:(ncol(spam)-1)],
                     method = c("BoxCox", "center", "scale", "pca"),
                     outcome = spam[i$training, ncol(spam)],
                     thresh = 0.8
                     )

# Aplicamos la transformación a los subconjuntos.
training = predict(preProc, spam[i$training,1:(ncol(spam)-1)])
test = predict(preProc, spam[i$test,1:(ncol(spam)-1)])

## ----puntoParada, include=FALSE------------------------------------------
invisible(readline(prompt = "Pulse Enter para continuar\n"))

## ----warning = FALSE-----------------------------------------------------
# Realizamos la selección de modelos
formulas = regsubsets(x=training, y = spam[i$training, ncol(spam)])
# Mostramos la tabla de modelos a probar
summary(formulas)$outmat

# Pasamos la matriz preprocesada a un dataframe
training_df = data.frame(training)
training_df["y"] = as.factor(spam[i$training, ncol(spam)])

# Creamos la matriz de precisiones de modelos
modelos = matrix(nrow = 5, ncol = 2)

# Función que da la precisión de un modelo regularizado para su mejor lambda y alpha
obtenerAccuracy = function(modelo) {
  modelo$results$Accuracy[modelo$results$lambda == modelo$bestTune$lambda &
                          modelo$results$alpha  == modelo$bestTune$alpha]
}

# Ajustamos los modelos
modelo1 = train(y ~ PC1 + PC2 + PC3 + PC11, data = training_df,
                     method ="glm", family ="binomial")
modelo1reg = train(y ~ PC1 + PC2 + PC3 + PC11,
                   data = training_df, method ="glmnet", family ="binomial")
modelo2 = train(y ~ PC1 + PC2 + PC3 + PC4 + PC11, data = training_df,
                     method ="glm", family ="binomial")
modelo2reg = train(y ~ PC1 + PC2 + PC3 + PC4 + PC11,
                     data = training_df, method ="glmnet", family ="binomial")
modelo3 = train(y ~ PC1 + PC2 + PC3 + PC4 + PC8 + PC11, data = training_df,
                     method ="glm", family ="binomial")
modelo3reg = train(y ~ PC1 + PC2 + PC3 + PC4 + PC8 + PC11,
                   data = training_df, method ="glmnet", family ="binomial")
modelo4 = train(y ~ PC1 + PC2 + PC3 + PC4 + PC6 + PC8 + PC11,
    data = training_df, method ="glm", family ="binomial")

modelo4reg = train(y ~ PC1 + PC2 + PC3 + PC4 + PC6 + PC8 +
          PC11, data = training_df, method ="glmnet", family ="binomial")

modelo5 = train(y ~ PC1 + PC2 + PC3 + PC4 + PC6 + PC8 + PC11 + PC19,
    data = training_df, method ="glm", family ="binomial")

modelo5reg = train(y ~ PC1 + PC2 + PC3 + PC4 + PC6 + PC8 + PC11
      + PC19, data = training_df, method ="glmnet", family ="binomial")


# Rellenamos la matriz con las precisiones de los modelos
modelos[1,1] = modelo1$results$Accuracy
modelos[1,2] = obtenerAccuracy(modelo1reg)
modelos[2,1] = modelo2$results$Accuracy
modelos[2,2] = obtenerAccuracy(modelo2reg)
modelos[3,1] = modelo3$results$Accuracy
modelos[3,2] = obtenerAccuracy(modelo3reg)
modelos[4,1] = modelo4$results$Accuracy
modelos[4,2] = obtenerAccuracy(modelo4reg)
modelos[5,1] = modelo5$results$Accuracy
modelos[5,2] = obtenerAccuracy(modelo5reg)

rownames(modelos) = c("(1) PC1 + PC2 + PC3 + PC11", 
                      "(2) PC1 + PC2 + PC3 + PC4 + PC11",
                      "(3) PC1 + PC2 + PC3 + PC4 + PC8 + PC11",
                      "(4) PC1 + PC2 + PC3 + PC4 + PC6 + PC8 + PC11",
                      "(5) PC1 + PC2 + PC3 + PC4 + PC6 + PC8 + PC11 + PC19")

# Visualizamos la tabla de resultados
kable(x = modelos, caption = "Comparativa de la precisión de los distintos modelos",
      col.names = c("Sin regularización", "Con regularización"))

## ------------------------------------------------------------------------
# Nos quedamos con el modelo 4
 etiquetas = predict(modelo4, newdata = training)
 ein = sum(etiquetas != spam[i$training, ncol(spam)])*100/length(i$training)
 etiquetas = predict(modelo4, newdata = test)
 eout = sum(etiquetas != spam[i$test, ncol(spam)])*100/length(i$test)
 
 cat("El error dentro de la muestra de entrenamiento (Ein) es de", ein, "%\n")
 cat("La estimación del error fuera de la muestra (Eout) es de", eout, "%\n")

## ----puntoParada, include=FALSE------------------------------------------
invisible(readline(prompt = "Pulse Enter para continuar\n"))

## ------------------------------------------------------------------------
# Establecemos la semilla aleatoria
set.seed(11)

# Cambiamos de directorio
setwd("./datos")

# Lectura del fichero
LAozone = read.table("LAozone.data", sep=",",head=T)

# Salimos del directorio de los datos
setwd("..")

# Eliminación de valores perdidos
LAozone = na.omit(LAozone)

# Eliminamos el atributo día del año al no ser representativo
LAozone = LAozone[,-10]

# Realizamos la partición de los subconjuntos
i = particionar(data = LAozone)

## ------------------------------------------------------------------------
# 1. ELIMINAMOS LAS VARIABLES CON UN ALTO GRADO DE CORRELACIÓN.
# Obtenemos la matriz de correlaciones de los datos de training
descrCor = cor(LAozone[i$training,])

# Cogemos aquellos atributos cuyo grado de correlación es mayor al 90%
highCor = findCorrelation(descrCor, cutoff = .90)
# Quitamos dichos atributos
if (length(highCor) != 0) spam = spam[,-highCor]

# 2. REALIZAMOS EL PREPROCESAMIENTO CON LAS TRANSFORMACIONES
# PREVIAMENTE MENCIONADAS Y EL BOXCOX
# Calculamos la transformación del preprocesamiento basándonos en training
preProc = preProcess(x = LAozone[i$training,2:ncol(LAozone)],
                     method = c("BoxCox", "center", "scale"),
                     outcome = LAozone[i$training, 1],
                     )

# Aplicamos la transformación a los subconjuntos.
training = predict(preProc, LAozone[i$training,2:ncol(LAozone)])
test = predict(preProc, LAozone[i$test,2:ncol(LAozone)])

# Transformamos los subconjuntos en dataframes
training = data.frame(training)
test = data.frame(test)
test["y"] = LAozone[i$test,1]

## ----warning = FALSE-----------------------------------------------------
# Realizamos la selección de modelos
formulas = regsubsets(x= training, y = LAozone[i$training, 1])
# Mostramos la tabla de modelos a probar
summary(formulas)$outmat

# Pasamos la matriz preprocesada a un dataframe
training_df = data.frame(training)
training_df["y"] = LAozone[i$training,1]

# Creamos la matriz de rsquared
modelos = matrix(nrow = 6, ncol = 2)

# Función que dado un modelo ajustado devuelve el Rsquared para la mejor
# combinación de alfa y lambda
obtenerRSquared = function(modelo) {
  modelo$results$Rsquared[modelo$results$lambda == modelo$bestTune$lambda &
                          modelo$results$alpha  == modelo$bestTune$alpha]
}

# Ajustamos todos los modelos

modelo1 = train(y ~ humidity + temp + ibh, data = training_df, method="glm",
                family="gaussian")
modelo1reg = train(y ~ humidity + temp + ibh, data = training_df,
                   method="glmnet", family="gaussian")

modelo2 = train(y ~ humidity + temp + ibh + vis, data = training_df, method="glm",
                family="gaussian")
modelo2reg = train(y ~ humidity + temp + ibh + vis, data = training_df,
                   method="glmnet", family="gaussian")

modelo3 = train(y ~ wind + humidity + temp + ibh + vis, data = training_df, method="glm",
                family="gaussian")
modelo3reg = train(y ~ wind + humidity + temp + ibh + vis,
                   data = training_df, method="glmnet", family="gaussian")

modelo4 = train(y ~ humidity + temp + ibh + dpg + ibt + vis,
                data = training_df, method="glm", family="gaussian")
modelo4reg = train(y ~ humidity + temp + ibh + dpg + ibt + vis,
                   data = training_df, method="glmnet", family="gaussian")

modelo5 = train(y ~ vh + humidity + temp + ibh + dpg + ibt + vis, 
                data = training_df, method="glm", family="gaussian")
modelo5reg = train(y ~ vh + humidity + temp + ibh + dpg + ibt + vis,
                   data = training_df, method="glmnet", family="gaussian")

modelo6 = train(y ~ vh + wind + humidity + temp + ibh + dpg + ibt + vis, 
                data = training_df, method="glm", family="gaussian")
modelo6reg = train(y ~ vh + wind + humidity + temp + ibh + dpg + ibt + vis,
                   data = training_df, method="glmnet", family="gaussian")

# Creamos la matriz de medidas Rsquared

modelos[1,1] = modelo1$results$Rsquared
modelos[1,2] = obtenerRSquared(modelo1reg)
modelos[2,1] = modelo2$results$Rsquared
modelos[2,2] = obtenerRSquared(modelo2reg)
modelos[3,1] = modelo3$results$Rsquared
modelos[3,2] = obtenerRSquared(modelo3reg)
modelos[4,1] = modelo4$results$Rsquared
modelos[4,2] = obtenerRSquared(modelo4reg)
modelos[5,1] = modelo5$results$Rsquared
modelos[5,2] = obtenerRSquared(modelo5reg)
modelos[6,1] = modelo6$results$Rsquared
modelos[6,2] = obtenerRSquared(modelo6reg)

rownames(modelos) = c("(1) humidity + temp + ibh", 
                      "(2) humidity + temp + ibh + vis",
                      "(3) wind + humidity + temp + ibh + vis",
                      "(4) humidity + temp + ibh + dpg + ibt + vis",
                      "(5) vh + humidity + temp + ibh + dpg + ibt + vis",
                      "(6) vh + wind + humidity + temp + ibh + dpg + ibt + vis")

kable(x = modelos, caption = "Comparativa del RSquared de los distintos modelos",
      col.names = c("Sin regularización", "Con regularización"))

## ----puntoParada, include=FALSE------------------------------------------
invisible(readline(prompt = "Pulse Enter para continuar\n"))

## ------------------------------------------------------------------------
# Función que calcula el error porcentual en regresión, dados dos conjuntos
# de etiquetas
error_porcentual = function(etiquetas_test, etiquetas_pesos){
  diferencia = max(c(etiquetas_pesos, etiquetas_test))
              -min(c(etiquetas_pesos, etiquetas_test))
  error = mean(abs(etiquetas_test - etiquetas_pesos)/diferencia)
  error
}
# Nos quedamos con el modelo 4
 etiquetas = predict(modelo1, newdata = training)
 ein = error_porcentual(LAozone[i$training,1], etiquetas)
 etiquetas = predict(modelo1, newdata = test)
 eout = error_porcentual(LAozone[i$test,1], etiquetas)
 
 cat("El error dentro de la muestra de entrenamiento (Ein) es de", ein*100, "%\n")
 cat("La estimación del error fuera de la muestra (Eout) es de", eout*100, "%\n")

