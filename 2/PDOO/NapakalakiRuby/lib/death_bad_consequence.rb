# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

require_relative 'player'
require_relative 'bad_consequence'
require_relative 'numeric_bad_consequence'
module NapakalakiGame
  class DeathBadConsequence < NumericBadConsequence
    def initialize (text)
      super(text,Player.MAXLEVEL,BadConsequence.MAXTREASURES,BadConsequence.MAXTREASURES)
    end
  end
end
