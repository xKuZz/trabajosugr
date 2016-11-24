# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

require_relative 'bad_consequence'
module NapakalakiGame
  class NumericBadConsequence < BadConsequence
    attr_reader :nVisibleTreasures, :nHiddenTreasures
    public_class_method :new
    def initialize(t,l,v,h)
      super(t,l)
      @nVisibleTreasures = v
      @nHiddenTreasures  = h
    end
    
    def isEmpty
    @levels==0 && @nVisibleTreasures==0 && @nHiddenTreasures==0 
    end
  
  def substractVisibleTreasure(t)
    if @nVisibleTreasures!=0
      @nVisibleTreasures -=1
    end
  end
  def substractHiddenTreasure(t)
    if @nHiddenTreasures!=0
      @nHiddenTreasures -=1
    end
  end
  
  def adjustToFitTreasureList(v,h)
    NumericBadConsequence.new("",0,[v.size,@nVisibleTreasures].min, \
    [h.size,@nHiddenTreasures].min)
  end
  end
end
