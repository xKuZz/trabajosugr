package cliente;

import java.awt.Color;
import java.awt.event.KeyEvent;
import java.awt.event.WindowEvent;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import javax.swing.text.*;
import javax.swing.JFrame;
import javax.swing.KeyStroke;

/**
 *
 * @author Alejandro Campoy Nieves.
 * @author David Criado Ramón
 * 
 * La clase GUI se encarga de manejar la interacción del usuario mientras se
 * encuentre conectado en el chat.
 */
public class GUI extends JFrame {
    private final ClienteTCP cliente; // Se encarga de la emisiones de datos del cliente.
    private final HashMap<String, Color> myColor = new HashMap(); // Para poner cada user de un color
    private final ArrayList<Color> possibleColors = new ArrayList();
    private  Iterator<Color> currentColor;
    /**
     * Inicializamos todo en el contructor
     * @param c Única instancia creada de la clase ClienteTCP (no es un singleton)
     */
    public GUI(ClienteTCP c) {
        cliente = c;
        setTitle(c.getUserName()+"@"+c.getHost());
        initComponents();
        // Desactivamos la función estándar del enter para sólo permitir usar Enter para enviar.
        texto.getInputMap().put(KeyStroke.getKeyStroke("ENTER"), "none");
        myColor.put(c.getUserName(), Color.green);
        updateList(c.getUsuarios());
        
        
        // Añadimos colores que sean visibles sobre un fondo oscuro
        possibleColors.add(Color.cyan);
        possibleColors.add(Color.orange);
        possibleColors.add(Color.yellow);
        possibleColors.add(Color.pink);
        possibleColors.add(Color.blue);
        possibleColors.add(Color.magenta);
        possibleColors.add(Color.red);
        currentColor = possibleColors.iterator();
    }
    /**
     * Actualiza la lista de usuarios con el conjunto de usuarios dado.
     * 
     * @param users Conjunto de usuarios a mostrar.
     */
    
    public final void updateList(HashSet<String> users) {
        // Obtenemos el documento estilizado
        list.setText("");
        Document doc = list.getStyledDocument();
        for (String user : users) {
            // Sacamos el color que corresponde al usuario
            Color color = myColor.get(user);
            
            if (color == null) { // Si no tiene le asignamos el siguiente.
                if (!currentColor.hasNext()) // Si no hay más colores empezamos a repetir
                    currentColor = possibleColors.iterator();
                 color = currentColor.next();
            }
                
           
            myColor.put(user, color);
            
            // Escribimos
            SimpleAttributeSet set = new SimpleAttributeSet();
            StyleConstants.setForeground(set, color);
           // StyleConstants.setBold(set, true);
            
            try {
                doc.insertString(doc.getLength(), user + "\n", set);
            } catch (BadLocationException ex) {
                System.err.println("Error al insertar texto en lista de usuarios");
            }
        }
    }
    
    /**
     * Este método es utilizado por la hebra lectora para añadir el mensaje
     * recibido a la interfaz
     * @param message Mensaje a añadir en el área de chat.
     */
    public void addMessage(String message) {
        try {
            int pos = message.indexOf(":");
            String user = message.substring(0, pos);
            Date date = new Date();
            Calendar calendar = GregorianCalendar.getInstance();
            calendar.setTime(date);
            int hour = calendar.get(Calendar.HOUR_OF_DAY);
            int minute = calendar.get(Calendar.MINUTE);
            String time = " [%02d:%02d] ";
            time = String.format(time, hour, minute);
            String data = message.substring(pos + 1);
            
            /** Ponemos de un color el usuario y de otro el texto. **/
            // 1- Obtenemos el documento (Styled para poder poner colores y tal) del TextPane
            Document doc = chat.getStyledDocument();
            
            // 2 - Configuramos un color
            SimpleAttributeSet set = new SimpleAttributeSet();
            // Ponemos verde en verde y negrita
            StyleConstants.setForeground(set, myColor.get(user));
            StyleConstants.setBold(set, true);
            
            // 3 - Insertamos el nombre de usuario y la hora de recepción
            doc.insertString(doc.getLength(), user, set);
            
            set = new SimpleAttributeSet();
            // Ponemos el color asignado al usuario
            StyleConstants.setForeground(set, myColor.get(user));
            
            doc.insertString(doc.getLength(), time, set);
            // 4 - Para el texto lo dejamos en blanco
            set = new SimpleAttributeSet();
            StyleConstants.setForeground(set, Color.white);
            
            doc.insertString(doc.getLength(), data, set);
        } catch (BadLocationException ex) {
            System.err.println(ex);
            System.err.println("Error al colocar texto en la posición indicada.");
        }
    }

    @Override
    protected void processWindowEvent(WindowEvent e) {
        if (e.getID() == WindowEvent.WINDOW_CLOSING) {
            if (!cliente.close()) 
                System.err.println("Mensaje de despedida incorrecto");
            
        }
        super.processWindowEvent(e); 
    }
    
    

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {
        java.awt.GridBagConstraints gridBagConstraints;

        jScrollPane1 = new javax.swing.JScrollPane();
        chat = new javax.swing.JTextPane();
        jScrollPane2 = new javax.swing.JScrollPane();
        texto = new javax.swing.JTextArea();
        enviar = new javax.swing.JButton();
        jLabel1 = new javax.swing.JLabel();
        jScrollPane4 = new javax.swing.JScrollPane();
        list = new javax.swing.JTextPane();

        getContentPane().setLayout(new java.awt.GridBagLayout());

        jScrollPane1.setHorizontalScrollBarPolicy(javax.swing.ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);

        chat.setEditable(false);
        chat.setBackground(new java.awt.Color(70, 70, 70));
        jScrollPane1.setViewportView(chat);

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.gridheight = 2;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        gridBagConstraints.ipadx = 582;
        gridBagConstraints.ipady = 274;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTHWEST;
        gridBagConstraints.weightx = 1.0;
        gridBagConstraints.weighty = 1.0;
        getContentPane().add(jScrollPane1, gridBagConstraints);

        jScrollPane2.setHorizontalScrollBarPolicy(javax.swing.ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);

        texto.setBackground(new java.awt.Color(156, 156, 156));
        texto.setColumns(20);
        texto.setForeground(new java.awt.Color(254, 254, 254));
        texto.setRows(5);
        texto.addKeyListener(new java.awt.event.KeyAdapter() {
            public void keyPressed(java.awt.event.KeyEvent evt) {
                textoKeyPressed(evt);
            }
        });
        jScrollPane2.setViewportView(texto);

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 2;
        gridBagConstraints.gridheight = 2;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        gridBagConstraints.ipadx = 582;
        gridBagConstraints.ipady = 86;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTHWEST;
        gridBagConstraints.weightx = 1.0;
        gridBagConstraints.weighty = 1.0;
        gridBagConstraints.insets = new java.awt.Insets(10, 0, 0, 0);
        getContentPane().add(jScrollPane2, gridBagConstraints);

        enviar.setText("Enviar");
        enviar.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                enviarActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 1;
        gridBagConstraints.gridy = 3;
        gridBagConstraints.ipadx = 62;
        gridBagConstraints.ipady = 17;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTHWEST;
        gridBagConstraints.insets = new java.awt.Insets(59, 31, 0, 0);
        getContentPane().add(enviar, gridBagConstraints);

        jLabel1.setText("LISTA DE USUARIOS");
        getContentPane().add(jLabel1, new java.awt.GridBagConstraints());

        list.setBackground(new java.awt.Color(156, 156, 156));
        jScrollPane4.setViewportView(list);

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 1;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.fill = java.awt.GridBagConstraints.VERTICAL;
        gridBagConstraints.ipadx = 163;
        gridBagConstraints.ipady = 256;
        getContentPane().add(jScrollPane4, gridBagConstraints);
    }// </editor-fold>//GEN-END:initComponents
    // Al pulsar enviar vaciamos el área de escritura y envimos el texto.
    private void enviarActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_enviarActionPerformed
        String toSend = texto.getText();
        if (!toSend.isEmpty()) {
            cliente.sendMessage(toSend);
            addMessage(cliente.getUserName() + ": " + toSend + "\n");
            texto.setText("");
        }
    }//GEN-LAST:event_enviarActionPerformed
    // Pulsar Enter equivale a enviar.
    private void textoKeyPressed(java.awt.event.KeyEvent evt) {//GEN-FIRST:event_textoKeyPressed
        if (evt.getKeyCode() == KeyEvent.VK_ENTER)
            enviarActionPerformed(null);
      
    }//GEN-LAST:event_textoKeyPressed


    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JTextPane chat;
    private javax.swing.JButton enviar;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JScrollPane jScrollPane2;
    private javax.swing.JScrollPane jScrollPane4;
    private javax.swing.JTextPane list;
    private javax.swing.JTextArea texto;
    // End of variables declaration//GEN-END:variables
}
