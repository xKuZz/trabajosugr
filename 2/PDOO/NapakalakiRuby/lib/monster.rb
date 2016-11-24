#encoding: utf-8

module NapakalakiGame

class Monster
  attr_reader :name, :combatLevel, :bc, :price, :levelChangeAgainstCultistPlayer
  private_class_method :new
  def initialize(n,cl,bc,p,lc)
    @name=n
    @combatLevel=cl
    @bc=bc
    @price=p
    @levelChangeAgainstCultistPlayer=lc
  end
  
  def self.newMonster(n,cl,bc,p)
    new(n,cl,bc,p,0)
  end
  
  def self.newCultist(n,cl,bc,p,lc)
    new(n,cl,bc,p,lc)
  end
  
  def getCombatLevelAgainstCultistPlayer
    @levelChangeAgainstCultistPlayer+@combatLevel
  end
  def to_s
    "Nombre: #{@name} \nNivel: #{@combatLevel}\n" +
    "Mal rollo:\n #{@bc.to_s}\n" +
    "Premio: #{@price.to_s}\n"
  end
end
end
