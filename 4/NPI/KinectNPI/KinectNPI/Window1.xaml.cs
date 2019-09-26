using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace NPIGrupo7Kinect
{
    /// <summary>
    /// Lógica de interacción para la ventana de Información de un evento
    /// </summary>
    public partial class Window1 : Window
    {
        /**
         * Constructor de la ventana
         * @param titulo Titulo de la ventana.
         * @param informacion Información a mostrar en la ventana.
         */
        public Window1(String titulo, String informacion)
        {
            InitializeComponent();
            this.Title = titulo;
            textoPopUp.Text = informacion;
        }

        /**
         * Método para ampliar el tamaño de fuente del texto (lo duplica).
         */
        public void Ampliar() {
            textoPopUp.FontSize *= 2;
        }

        /** 
         * Método para reducir el tamaño de fuente del texto (lo reduce a la mitad)
         */
        public void Reducir()
        {
            textoPopUp.FontSize /= 2;
        }

      
    }
}
