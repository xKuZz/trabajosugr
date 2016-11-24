
#encoding: utf-8
 require_relative 'bad_consequence'
 require_relative 'combat_result'
 require_relative 'dice'
 require_relative 'treasure'
 require_relative 'treasure_kind'
 module NapakalakiGame
class Player
  attr_reader :name, :dead, :level, :canISteal, :hiddenTreasures, :visibleTreasures, :enemy
  attr_reader :pendingBadConsequence
  attr_writer :pendingBadConsequence, :enemy
  
  @@MAXLEVEL=10
  def initialize(name)
    @enemy
    @name=name
    @level=1
    @dead=true
    @canISteal=true
    @hiddenTreasures=Array.new
    @visibleTreasures=Array.new
    @pendingBadConsequence
    
  end
  
  def bringToLife
    @dead=false;
  end
  
  def copy(p)
    @enemy=p.enemy
    @name=p.name
    @level=p.level
    @dead=p.dead
    @canISteal=p.canISteal
    @hiddenTreasures=Array.new(p.hiddenTreasures)
    @visibleTreasures=Array.new(p.visibleTreasures)
    @pendingBadConsequence=p.pendingBadConsequence
    puts "ERES CULTIST!!!!!!!!!!!!!!"
  end
  def self.MAXLEVEL
    @@MAXLEVEL
  end
  
  def incrementLevels(l)
    if ((@level+l)<@@MAXLEVEL)
      @level=@level+l
    else
      @level=@@MAXLEVEL
    end
  end
  
  def decrementLevels(l)
    if ((@level-l)>0)
      @level=@level-l
    else
      @level=1
    end
  end
  
  def applyPrize(m)
    nLevels=m.price.level
    incrementLevels(nLevels)
    nTreasures=m.price.treasures
    if (nTreasures>0)
      dealer=CardDealer.instance
      for i in 0..nTreasures-1 do
        t=dealer.nextTreasure
        @hiddenTreasures << t
      end
    end
  end
  
  def applyBadConsequence(m)
    badConsequence=m.bc
    nLevels=badConsequence.levels
    decrementLevels(nLevels);
    @pendingBadConsequence=badConsequence.adjustToFitTreasureList(@visibleTreasures, @hiddenTreasures);        
    
  end
  
  def canMakeTreasureVisible(t)
    return false if (!@pendingBadConsequence.nil? && !@pendingBadConsequence.isEmpty)
    if (t.type==TreasureKind::BOTHHANDS)
      @visibleTreasures.each {|t1| return false if (t1.type==TreasureKind::BOTHHANDS || t1.type==TreasureKind::ONEHAND)}
    elsif (t.type==TreasureKind::ONEHAND)
      contador=0;
      @visibleTreasures.each do |t1|
          contador += 2 if t1.type==TreasureKind::BOTHHANDS
          contador += 1 if t1.type==TreasureKind::ONEHAND
      end
      return contador<2
    else
      @visibleTreasures.each{|t1| return false if t.type==t1.type}
    end
    true
      
  end
    
 
  
  def howManyVisibleTreasures(tKind)
    contador=0
    @visibleTreasures.each do |t|
      if (t.type==tKind)
          if (tKind==TreasureKind::BOTHHANDS)
            contador=contador+2
          else
            contador=contador+1
          end
      end
    end
    contador
  end
  
  def dieIfNoTreasures
    if (@hiddenTreasures.empty? && @visibleTreasures.empty?)
      @dead=true
    end
  end
  
  def combat(m)
    myLevel=getCombatLevel
    monsterLevel=getOponentLevel(m)
        if (myLevel>monsterLevel)
            applyPrize(m)
            if (level>=@@MAXLEVEL)
                CombatResult::WINGAME
            else
                CombatResult::WIN
            end
        
        else
            applyBadConsequence(m)
            if(shouldConvert)
              CombatResult::LOSEANDCONVERT
            else
              CombatResult::LOSE
            end
        end
  end
  
  def makeTreasureVisible(t)
    canI=canMakeTreasureVisible(t);
        if (canI)
            @visibleTreasures << (t);
            @hiddenTreasures.delete(t);
        end
  end
  
  def discardVisibleTreasure(t)
    @visibleTreasures.delete(t)
        if (!@pendingBadConsequence.nil? && !@pendingBadConsequence.isEmpty)
            @pendingBadConsequence.substractVisibleTreasure(t);
        end
        dieIfNoTreasures 
  end
  
  def discardHiddenTreasure(t)
    @hiddenTreasures.delete(t)
        if (!@pendingBadConsequence.nil? && !@pendingBadConsequence.isEmpty)
            @pendingBadConsequence.substractHiddenTreasure(t);
        end
        dieIfNoTreasures
  end
  
  def validState
    (@pendingBadConsequence.nil? || @pendingBadConsequence.isEmpty) && 
    @hiddenTreasures.length<=4
  end
  
  def initTreasures
    dealer=CardDealer.instance
    dice=Dice.instance
    bringToLife
    @hiddenTreasures << dealer.nextTreasure
    number=dice.nextNumber
    @hiddenTreasures << dealer.nextTreasure if number>1
    @hiddenTreasures << dealer.nextTreasure if number==6
  end
  
  def stealTreasure
        canI=canISteal();
        if (canI)
            canYou = @enemy.canYouGiveMeATreasure
            if (canYou)
                treasure=@enemy.giveMeATreasure
                @hiddenTreasures << treasure
                haveStolen
            end
        end
        treasure;
  end
  
  def giveMeATreasure
    @hiddenTreasures.delete_at(rand(@hiddenTreasures.size))
  end
  
  def canYouGiveMeATreasure
    !@hiddenTreasures.empty?
  end
  def getCombatLevel
    l=@level;
    @visibleTreasures.each{|t| l=l+t.bonus}
    l
  end
  def haveStolen
    @canISteal=false
  end
  
  def discardAllTreasures
     for i in 0..@visibleTreasures.size-1 do
       discardVisibleTreasure(@visibleTreasures[0])
     end
     for i in 0..@hiddenTreasures.size-1 do
       discardHiddenTreasure(@hiddenTreasures[0])
     end
  end
  
  def getVisibleTreasures
    @visibleTreasures
  end
  
  def getHiddenTreasures
    @hiddenTreasures
  end
  
  def getName
    @name
  end
  
  def to_s
    "#{@name}\n" +
    "Nivel: #{@level}\n" +
    "Enemigo:#{@enemy.name}\n" +
    "Mala cons:\n#{@pendingBadConsequence}\n"
  end
  
  def getOponentLevel(m)
    m.combatLevel
  end
  
  def shouldConvert
    dice=Dice.instance
    number=dice.nextNumber
    number==1
  end
  private :bringToLife, :incrementLevels, :decrementLevels, :applyPrize, :applyBadConsequence
  private :canMakeTreasureVisible, :howManyVisibleTreasures, :dieIfNoTreasures, :haveStolen
  private :getCombatLevel
  protected :canYouGiveMeATreasure, :giveMeATreasure, :getCombatLevel, :getOponentLevel
  protected :shouldConvert
end
 end
