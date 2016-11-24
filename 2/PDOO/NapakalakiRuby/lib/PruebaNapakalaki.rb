#encoding: utf-8

require_relative 'monster'
require_relative 'card_dealer'
require_relative 'dice'



begin
  elcartas=CardDealer.instance
  elcartas.initCards
  
  puts elcartas.inspect
end

