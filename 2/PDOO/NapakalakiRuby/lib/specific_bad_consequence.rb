# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

require_relative 'bad_consequence'
module NapakalakiGame
  class SpecificBadConsequence < BadConsequence
    attr_reader :specificHiddenTreasures, :specificVisibleTreasures
    public_class_method :new
    def initialize(t,l,v,h)
      super(t,l)
      @specificVisibleTreasures = v
      @specificHiddenTreasures  = h
    end
  
  def isEmpty
    @levels==0 && @specificVisibleTreasures.empty? && @specificHiddenTreasures.empty? 
  end
  
  def substractVisibleTreasure(t)
    if(!((i=@specificVisibleTreasures.index(t.type)).nil?))
      @specificVisibleTreasures.delete_at(i)
    end
  end
  def substractHiddenTreasure(t)
    if(!((i=@specificHiddenTreasures.index(t.type)).nil?))
      @specificHiddenTreasures.delete_at(i)
    end
  end
  
  private
  def sameSpecific (t,s)
    salida=Array.new
    aux=Array.new(t)
    s.each do |a|
      t.each do |b|
        if (a==b.type)
          salida << b.type
          aux.delete(b)
          break
        end
      end
    end 
    salida
  end
  
  public
  def adjustToFitTreasureList(v,h)
   SpecificBadConsequence.new("",0, \
    sameSpecific(v,@specificVisibleTreasures), sameSpecific(h,@specificHiddenTreasures))
  end
end
end
