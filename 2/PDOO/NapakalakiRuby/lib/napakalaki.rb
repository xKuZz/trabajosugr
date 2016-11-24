# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
require 'singleton'
require_relative 'card_dealer'
require_relative 'player'
require_relative 'cultist_player'
module NapakalakiGame
class Napakalaki
  include Singleton
  attr_reader :currentPlayer, :currentMonster
  
  def initialize
    @currentPlayer
    @players=Array.new
    @currentMonster
    @dealer=CardDealer.instance
  end
  
  def initPlayers(names)
    names.each { |name| @players << Player.new(name)}
  end
  
  def nextPlayer 
    if (@currentPlayer.nil?)
      @currentPlayer=@players.sample
    else
      a=@players.index(@currentPlayer)
      if (a+1==@players.size)
        a=0
      else
        a=a+1
      end
      @currentPlayer=@players[a]
    end
  end
  
  def nextTurnAllowed
    return true if @currentPlayer.nil?
    @currentPlayer.validState
  end
  
  def setEnemies
    a=0
    @players.each do |p|
      loop do
        a=rand(0...@players.size)
        break if @players[a]!=p
      end
      p.enemy=@players[a]
    end
  end
  
  def developCombat
    m=@currentMonster;
    cr= @currentPlayer.combat(m);
    if (cr==CombatResult::LOSEANDCONVERT)
      carta=@dealer.nextCultist
      cult=CultistPlayer.new(@currentPlayer,carta)
      index=@players.index(@currentPlayer)
      @players[index]=cult
      @currentPlayer=cult
    end
    @dealer.giveMonsterBack(m);
    cr;
  end
  
  def discardVisibleTreasures(treasures)
    treasures.each do |t|
      @currentPlayer.discardVisibleTreasure(t)
      @dealer.giveTreasureBack(t)
    end
  end
  
  def discardHiddenTreasures(treasures)
    treasures.each do |t|
      @currentPlayer.discardHiddenTreasure(t)
      @dealer.giveTreasureBack(t)
    end
  end
  
  def makeTreasuresVisible(treasures)
    treasures.each{|t| @currentPlayer.makeTreasureVisible(t)}
  end
  
  def initGame(players)
    initPlayers(players)
    setEnemies
    @dealer.initCards
    nextTurn
  end
 
  def nextTurn
    stateOK=nextTurnAllowed
    if (stateOK)
      @currentMonster=@dealer.nextMonster
      @currentPlayer=nextPlayer
      dead=@currentPlayer.dead
      if (dead)
        @currentPlayer.initTreasures
      end  
    end
    stateOK
  end
  
  def getCurrentPlayer
    @currentPlayer
  end
  
  def getCurrentMonster
    @currentMonster
  end
  
  def endOfGame(result)
    result==CombatResult::WINGAME
  end
  private :initPlayers, :nextPlayer, :nextTurnAllowed, :setEnemies
end
end
