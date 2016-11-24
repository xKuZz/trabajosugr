#encoding: utf-8
module NapakalakiGame
class Prize
  attr_reader :treasures, :level
  def initialize (t,l)
    @treasures=t
    @level=l
  end
  
  def to_s
    "\nTesoros ganados: #{@treasures}\n" +
    "Niveles ganados: #{@level}"
  end
end
end
