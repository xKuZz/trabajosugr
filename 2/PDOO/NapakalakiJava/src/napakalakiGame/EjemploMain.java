
package napakalakiGame;

import GUI.Dice;
import Test.GameTester;
import GUI.NapakalakiView;
import GUI.PlayersNameCapture;
import java.util.ArrayList;

public class EjemploMain {

    public static void main(String[] args) {
      ArrayList<String> names;
      
      Napakalaki game = Napakalaki.getInstance();
      NapakalakiView napakalakiView = new NapakalakiView();
      Dice.createInstance(napakalakiView);
      PlayersNameCapture namesCapture = new PlayersNameCapture(napakalakiView, true);
      names = namesCapture.getNames();
      game.initGame(names);
      napakalakiView.setNapakalaki(game);
      napakalakiView.setVisible(true);
    }
}
