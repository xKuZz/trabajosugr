# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

require_relative 'player'
require_relative 'cultist'
module NapakalakiGame
  class CultistPlayer < Player
    @@totalCultistPlayers = 0
    def initialize(p,c)
      @myCultistCard=c
      @@totalCultistPlayers += 1
      self.copy(p)
    end
    
    def self.totalCultistPlayers
      @@totalCultistPLayers
    end
    
    protected
    def getCombatLevel
      (Player.instance_method(:getCombatLevel).bind(self).call*1.2+@myCultistCard.gainedLevels*@@totalCultistPlayers).to_i
    end
    
    def getOponentLevel(m)
      m.levelChangeAgainstCultistPlayer
    end
    
    def shouldConvert
      false
    end
    
    protected
    def giveMeATreasure
      @visibleTreasures.delete_at(rand(@visibleTreasures.size))
    end
    
    def canYouGiveMeATreasure
      !@visibleTreasures.empty?
    end
    
  end
end
