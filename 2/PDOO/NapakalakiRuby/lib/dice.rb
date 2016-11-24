# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
module NapakalakiGame
require 'singleton'
class Dice
  include Singleton
  def initialize
    
  end
  def nextNumber()
    rand(1...7)
  end
end
end
