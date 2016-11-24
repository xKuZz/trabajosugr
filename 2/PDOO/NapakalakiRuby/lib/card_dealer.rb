#encoding: utf-8
require 'singleton'
require_relative 'monster'
require_relative 'prize'
require_relative 'bad_consequence'
require_relative 'cultist'
require_relative 'specific_bad_consequence'
require_relative 'numeric_bad_consequence'
require_relative 'death_bad_consequence'

module NapakalakiGame
class CardDealer
  include Singleton
   
  def initialize
    @unusedMonsters=Array.new
    @usedMonsters=Array.new
    @unusedTreasures=Array.new
    @usedTreasures=Array.new
    @unusedCultist=Array.new
  end
  
  
  def initTreasureCardDeck
    @unusedTreasures << Treasure.new("Sí mi amo", 4, TreasureKind::HELMET)
    @unusedTreasures << Treasure.new("Botas de investigación", 3, TreasureKind::SHOES)
    @unusedTreasures << Treasure.new("Capucha de Cthulu", 3, TreasureKind::HELMET)
    @unusedTreasures << Treasure.new("A prueba de babas", 2, TreasureKind::ARMOR)
    @unusedTreasures << Treasure.new("Botas de lluvia ácida", 1, TreasureKind::BOTHHANDS)
    @unusedTreasures << Treasure.new("Casco minero", 2, TreasureKind::HELMET)
    @unusedTreasures << Treasure.new("Ametralladora Thompson", 4, TreasureKind::BOTHHANDS)
    @unusedTreasures << Treasure.new("Camiseta de la UGR", 1, TreasureKind::ARMOR)
    @unusedTreasures << Treasure.new("Clavo de rail ferroviario", 3, TreasureKind::ONEHAND)
    @unusedTreasures << Treasure.new("Cuchillo de shushi arcano", 2, TreasureKind::ONEHAND)
    @unusedTreasures << Treasure.new("Fez alópodo", 3, TreasureKind::HELMET)
    @unusedTreasures << Treasure.new("Hacha prehistórica", 2, TreasureKind::ONEHAND)
    @unusedTreasures << Treasure.new("El aparato del Pr. Tesla", 4, TreasureKind::ARMOR)
    @unusedTreasures << Treasure.new("Gaita", 4, TreasureKind::BOTHHANDS)
    @unusedTreasures << Treasure.new("Insecticida", 2, TreasureKind::ONEHAND)
    @unusedTreasures << Treasure.new("Escopeta de 3 cañones", 4, TreasureKind::BOTHHANDS)
    @unusedTreasures << Treasure.new("Garabato místico", 2, TreasureKind::ONEHAND)
    @unusedTreasures << Treasure.new("La rebeca metálica", 2, TreasureKind::ARMOR)
    @unusedTreasures << Treasure.new("Lanzallamas", 4,TreasureKind::BOTHHANDS)
    @unusedTreasures << Treasure.new("Necro-comicón", 1, TreasureKind::ONEHAND)
    @unusedTreasures << Treasure.new("Necronomicón", 5, TreasureKind::BOTHHANDS)
    @unusedTreasures << Treasure.new("Linterna a 2 manos", 3, TreasureKind::BOTHHANDS)
    @unusedTreasures << Treasure.new("Necro-gnomicón", 2, TreasureKind::ONEHAND)
    @unusedTreasures << Treasure.new("Necrotelecom", 2, TreasureKind::HELMET)
    @unusedTreasures << Treasure.new("Mazo de los antiguos", 3, TreasureKind::ONEHAND)
    @unusedTreasures << Treasure.new("Necro-playboycón", 3, TreasureKind::ONEHAND)
    @unusedTreasures << Treasure.new("Porra preternatural", 2, TreasureKind::ONEHAND)
    @unusedTreasures << Treasure.new("Shogulador", 1, TreasureKind::BOTHHANDS)
    @unusedTreasures << Treasure.new("Varita de atizamiento", 3, TreasureKind::ONEHAND)
    @unusedTreasures << Treasure.new("Tentáculo de pega", 2, TreasureKind::HELMET)
    @unusedTreasures << Treasure.new("Zapato deja-amigos", 1, TreasureKind::SHOES)
  end
  
  def initMonsterCardDeck
    price = Prize.new(4,2) 
    badconsequence = NumericBadConsequence.new("Pierdes 5 niveles y 3 tesoros visibles",5 , 3, 0) 
    @unusedMonsters << Monster.newMonster("El rey de rosa",13,badconsequence,price)
    price = Prize.new(4,1) 
    badconsequence = SpecificBadConsequence.new("Te atrapan para llevarte de fiesta y te dejan caer en mitad del vuelo. Descarta 1 mano visible y 1 mano oculta", 0,[TreasureKind::ONEHAND],
    [TreasureKind::ONEHAND])  
    @unusedMonsters << Monster.newMonster("Ángeles de la noche ibicenca", 14, badconsequence, price)
    price = Prize.new(2,1)
    badconsequence= SpecificBadConsequence.new("Pierdes una armadura visible y otra oculta",0,[TreasureKind::ARMOR],[TreasureKind::ARMOR])
    @unusedMonsters << Monster.newMonster("3 Byakhees de bonanza", 8, badconsequence, price)
    price= Prize.new(1,1);
    badconsequence= SpecificBadConsequence.new("Embobados con el lindo primigenio te descartas de tu casco visible", 0,[TreasureKind::HELMET],Array.new)
    @unusedMonsters << Monster.newMonster("Chibithulhu", 2, badconsequence, price)
    badconsequence = SpecificBadConsequence.new("El primordial bostezo contagioso. Pierdes el calzado visible",0,[TreasureKind::SHOES],Array.new)
    @unusedMonsters << Monster.newMonster("El sopor de Dunwich", 2, badconsequence, price)
    price=Prize.new(3,1)
    badconsequence= SpecificBadConsequence.new("Pierdes todos tus tesoros visibles", 0, [TreasureKind::ARMOR,TreasureKind::HELMET,TreasureKind::SHOES,TreasureKind::ONEHAND,TreasureKind::BOTHHANDS],Array.new)
    @unusedMonsters << Monster.newMonster("El gorrón en el umbral", 10, badconsequence, price)  
    price=Prize.new(2,1)
    badconsequence= SpecificBadConsequence.new("Pierdes la armadura visible",0,[TreasureKind::ARMOR],Array.new)
    @unusedMonsters << Monster.newMonster("H.P. Munchcraft", 6, badconsequence, price)
    price=Prize.new(1,1)
    badconsequence= SpecificBadConsequence.new("Sientes bichos bajo la ropa. Descarta la armadura visible",0,[TreasureKind::ARMOR],Array.new)
    @unusedMonsters << Monster.newMonster("Bichgoth", 2, badconsequence, price)
    badconsequence= NumericBadConsequence.new("Toses los pulmones y pierdes 2 niveles", 2, 0, 0)
    @unusedMonsters << Monster.newMonster("Lo que redacta en las tinieblas", 2, badconsequence, price)
    price=Prize.new(2,1)
    badconsequence= DeathBadConsequence.new("Estos monstruos resultan bastante superficiales y te aburren mortalmente. Estás muerto")
    @unusedMonsters << Monster.newMonster("Los hondos", 8, badconsequence, price)
    badconsequence= NumericBadConsequence.new("Pierdes 2 niveles y 2 tesoros ocultos", 2, 0, 2)
    @unusedMonsters << Monster.newMonster("Semillas Cthulhu", 4, badconsequence, price)
    badconsequence= SpecificBadConsequence.new("Te intentas escaquear. Pierdes una mano visible",0,[TreasureKind::ONEHAND],Array.new)
    @unusedMonsters << Monster.newMonster("Dameargo", 1, badconsequence, price)
    price=Prize.new(1,1)
    badconsequence= NumericBadConsequence.new("Da muchos asquito. Pierdes 3 niveles", 3, 0, 0)
    @unusedMonsters << Monster.newMonster("Pollipólipo volante", 3, badconsequence, price)
    price=Prize.new(3,1)
    badconsequence= DeathBadConsequence.new("No le hace gracia que pronuncien mal su nombre. Estás muerto")
    @unusedMonsters << Monster.newMonster("Yshktihyssg-Goth", 12, badconsequence, price)
    price=Prize.new(4,1)
    badconsequence= DeathBadConsequence.new("La familia te atrapa. Estás muerto.")
    @unusedMonsters << Monster.newMonster("Familia feliz", 1, badconsequence, price)
    price=Prize.new(2,1)
    badconsequence= SpecificBadConsequence.new("La quinta directiva primaria te obliga a perder 2 niveles y un tesoro 2 manos visible", 2, [TreasureKind::BOTHHANDS], Array.new)
    @unusedMonsters << Monster.newMonster("Roboggoth", 8, badconsequence, price)
    price=Prize.new(1,1)
    badconsequence= SpecificBadConsequence.new("Te asusta en la noche. Pierdes un casco visible.", 0, [TreasureKind::HELMET], Array.new)
    @unusedMonsters << Monster.newMonster("El espia", 5, badconsequence, price)
    badconsequence= NumericBadConsequence.new("Menudo susto te llevas. Pierdes 2 niveles y 5 tesoros visible", 2, 5, 0)
    @unusedMonsters << Monster.newMonster("El lenguas", 20, badconsequence, price)
    badconsequence= SpecificBadConsequence.new("Te faltan manos para tanta cabeza. Pierdes 3 niveles y tus tesoros visibles de las manos", 3, [TreasureKind::BOTHHANDS], Array.new)
    @unusedMonsters << Monster.newMonster("Bicéfalo", 20, badconsequence,price)
    price = Prize.new(3,1) 
    badconsequence = SpecificBadConsequence.new("Pierdes 1 mano visible",0 , [TreasureKind::ONEHAND], Array.new) 
    @unusedMonsters << Monster.newCultist("El mal indecible impronunciable",10,badconsequence,price,-2)
    price = Prize.new(2,1) 
    badconsequence= SpecificBadConsequence.new("Pierdes todos tus tesoros visibles. Jajaja", 0, [TreasureKind::ARMOR,TreasureKind::HELMET,TreasureKind::SHOES,TreasureKind::ONEHAND,TreasureKind::BOTHHANDS],Array.new)
    @unusedMonsters << Monster.newCultist("Testigos oculares",6,badconsequence,price,2)
    price = Prize.new(5,2) 
    badconsequence= DeathBadConsequence.new("Hoy no es tu dia de suerte. Mueres")
    @unusedMonsters << Monster.newCultist("El gran cthulhu",20,badconsequence,price,4)
    price = Prize.new(2,1)
    badconsequence= NumericBadConsequence.new("Tu gobierno te recorta 2 niveles",2,0,0)
    @unusedMonsters << Monster.newCultist("Serpiente Politico",8,badconsequence,price,-2)
    price = Prize.new(1,1)
    badconsequence= SpecificBadConsequence.new("Pierdes tu casco y tu armadura visible", 0, [TreasureKind::HELMET,TreasureKind::ARMOR],[TreasureKind::BOTHHANDS])
    @unusedMonsters << Monster.newCultist("Felpugoth",2,badconsequence,price,5)
    price = Prize.new(4,2)
    badconsequence= NumericBadConsequence.new("Pierdes 2 niveles.", 2, 0, 0)
    @unusedMonsters << Monster.newCultist("Shogoth",16,badconsequence,price,-4)
    price = Prize.new(1,1)
    badconsequence= NumericBadConsequence.new("Pintalabios negro. Pierdes 2 niveles.", 2, 0, 0)
    @unusedMonsters << Monster.newCultist("Lolitagoth",2,badconsequence,price,3)
    


  end
  
  def shuffleTreasures
    @unusedTreasures.shuffle!
  end
  
  def shuffleMonsters
    @unusedMonsters.shuffle!
  end
  
  def nextTreasure
    if @unusedTreasures.empty?
      @unusedTreasures=Array.new(@usedTreasures)
      shuffleTreasures
      @usedTreasures=Array.new
    end
      t=@unusedTreasures[0]
      @unusedTreasures.delete(t)
      t
  end
  
  def nextMonster
     if @unusedMonsters.empty?
      @unusedMonsters=Array.new(@usedMonsters)
      shuffleMonsters
      @usedMonsters.clear
    end
      m=@unusedMonsters[0]
      @unusedMonsters.delete(m)
      m
  end
  
  def giveTreasureBack(t)
    @usedTreasures << t
  end
  
  def giveMonsterBack(m)
    @usedMonsters << m
  end
  
  def initCards
    initMonsterCardDeck
    initTreasureCardDeck
    initCultistCardDeck
    shuffleMonsters
    shuffleTreasures
    shuffleCultist
  end
  def nextCultist
    @unusedCultist.delete_at(0)
  end
  private
  def initCultistCardDeck
    @unusedCultist << Cultist.new("Sectario",1)
    @unusedCultist << Cultist.new("Sectario",2)
    @unusedCultist << Cultist.new("Sectario",1)
    @unusedCultist << Cultist.new("Sectario",2)
    @unusedCultist << Cultist.new("Sectario",1)
    @unusedCultist << Cultist.new("Sectario",1)
  end
  
 
 
 
  def shuffleCultist
    @unusedCultist.shuffle!
  end
  
private :initTreasureCardDeck, :initMonsterCardDeck, :shuffleTreasures, :shuffleMonsters  
end
end