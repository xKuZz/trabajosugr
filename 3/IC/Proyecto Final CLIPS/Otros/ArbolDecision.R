# Cargamos librerías
library(caret)
library(rpart)
library(party)
library(rattle)

# Inicio semilla pseudoaleatorios
set.seed(16)
# Leemos tabla comparativa
df = read.csv2("Compatibilidad.csv",header = T)
# Entrenamos el modelo
modelo = train(as.factor(Compatibilidad) ~ ., data = df[-1], method ="rpart",
                     control=rpart.control(minsplit=2, minbucket=1, cp=0.001))

# Sacamos el árbol de decisión como imagen
fancyRpartPlot(modelo$finalModel, sub="")

# Sacamos las reglas a implementar en texto
asRules(modelo$finalModel)