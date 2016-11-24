#encoding: utf-8
require_relative 'treasure_kind'
require_relative 'player'


module NapakalakiGame
class BadConsequence
  attr_reader :text, :levels
  private_class_method :new
  @@MAXTREASURES=10
  def initialize(t,l)
    @text   = t
    @levels = l
  end
 
  def to_s
    "Texto: #{@text}\n" +
    "Niveles: #{@levels}\n" +
    "Tesoros visibles: #{@nVisibleTreasures}\n" +
    "-----especificos:#{@specificVisibleTreasures}\n" +
    "Tesoros ocultos: #{@nHiddenTreasures}\n" +
    "----especificos: #{@specificHiddenTreasures}\n" 
  end
  def self.MAXTREASURES
    @@MAXTREASURES
  end
  
  def isEmpty
    
  end
  
  def substractVisibleTreasure(t)
    
  end
  
  def substractHiddenTreasure(t)
    
  end
  
  def adjustToFitTreasureList(v,h)
    
  end
end
end
